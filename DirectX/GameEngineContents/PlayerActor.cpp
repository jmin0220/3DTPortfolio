#include "PreCompile.h"
#include "PlayerActor.h"
#include <GameEngineBase/GameEngineRandom.h>
#include "StageParentLevel.h"
#include "VirtualPhysXLevel.h"

#include "CameraArm.h"
#include "ServerPacket.h"

float SPEED_PLAYER = 2500.0f;
float AngularSpeed = 520.0f;

PlayerActor* PlayerActor::MainPlayer = nullptr;
bool PlayerActor::IsMainPlayerSpawned_ = false;

PlayerActor::PlayerActor() :
	CheckPointFlag_(false),
	CheckPointPos_(float4::ZERO),
	IsGoal_(false),
	IsStanding_(false),
	IsPlayerble_(false)
{
}

PlayerActor::~PlayerActor() 
{
}


physx::PxRigidDynamic* PlayerActor::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics)
{

	return DynamicActorComponent_->CreatePhysXActors(_Scene, _physics, 
		physx::PxVec3(MeshBoundScale.x, 
		MeshBoundScale.y, 
		MeshBoundScale.z));
}

void PlayerActor::Start()
{
	// 캐릭터 메쉬 로드
	FbxRenderer_ = CreateComponent<GameEngineFBXAnimationRenderer>();
	DynamicActorComponent_ = CreateComponent<PhysXDynamicActorComponent>();

	// 메쉬 로드
//FbxRenderer_->SetFBXMesh("Character.FBX", "Texture");
	FbxRenderer_->SetFBXMesh("TestIdle.fbx", "TextureAnimationCustom");
	SetCharacterAnimation();
	SetCharacterTexture();
	FbxRenderer_->GetTransform().SetWorldScale({ PLAYER_SIZE_MAGNIFICATION_RATIO });

	MeshBoundScale = FbxRenderer_->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	MeshBoundScale *= float4{ PLAYER_SIZE_MAGNIFICATION_RATIO };
	FbxRenderer_->GetTransform().SetLocalPosition({ 0.0f, -MeshBoundScale.y * 1.5f , 0.0f });
	//FbxRenderer_->GetTransform().SetLocalPosition({0.0f, 0.0f , 0.0f});

	// PhysXActor를 생성하고, 플레이어의 RigidActor를 받아와서 콜백에 사용함
	static_cast<VirtualPhysXLevel*>(GetLevel())->SetSimulationPlayer(CreatePhysXActors(dynamic_cast<StageParentLevel*>(GetLevel())->GetScene(),
		dynamic_cast<StageParentLevel*>(GetLevel())->GetPhysics()));

	//EventCol
	EventCol_ = CreateComponent<GameEngineCollision>();
	EventCol_->ChangeOrder(CollisionGroup::Player);
	EventCol_->GetTransform().SetWorldScale({ PLAYER_COL_SCALE });
	EventCol_->GetTransform().SetLocalPosition({ 0.0f, -5.0f, 0.0f });

	// TODO::충격테스트용 키
	if (false == GameEngineInput::GetInst()->IsKey("ImpulsW"))
	{
		GameEngineInput::GetInst()->CreateKey("ImpulsW", VK_UP);
		GameEngineInput::GetInst()->CreateKey("ImpulsA", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("ImpulsS", VK_DOWN);
		GameEngineInput::GetInst()->CreateKey("ImpulsD", VK_RIGHT);

		//일어서기 시험용
		GameEngineInput::GetInst()->CreateKey("StandUp", 'K');

		//체크포인트 실험용
		GameEngineInput::GetInst()->CreateKey("TestPos", 'J');
	}

	DynamicActorComponent_->TurnOnSpeedLimit();

	// 서버 메인 플레이어만 드렁모
	// 
	// CreateActor<PlayerActor> 여러번 호출하게됨, 내가 컨트롤 하지 않을 PlayerActor 제외사항
	if (false == IsMainPlayerSpawned_)
	{
		MainPlayer = this;
		IsMainPlayerSpawned_ = true;
		IsPlayerble_ = true;

		// FSM
		CreateFSMStates();
	}
}

void PlayerActor::Update(float _DeltaTime)
{
	// 서버 안켰을 때
	if (false == GetIsNetInit())
	{
		InputController(_DeltaTime);

		PlayerStateManager_.Update(_DeltaTime);

	//GetTransform().SetWorldMove(MoveDir_ * SPEED_PLAYER * _DeltaTime);
	// TODO::충격테스트코드
	ImpulseTest();
	StandUp(_DeltaTime);


		//체크포인트 실험용 나중에 지워야함
		if (GameEngineInput::GetInst()->IsDown("TestPos") == true)
		{
			DynamicActorComponent_->SetPlayerStartPos(ResetCheckPointPos());
		}

		return;
	}

	if (true == IsPlayerble_)
	{
		InputController(_DeltaTime);

		PlayerStateManager_.Update(_DeltaTime);

		//GetTransform().SetWorldMove(MoveDir_ * SPEED_PLAYER * _DeltaTime);
		// TODO::충격테스트코드
		ImpulseTest();
		StandUp(_DeltaTime);


		//체크포인트 실험용 나중에 지워야함
		if (GameEngineInput::GetInst()->IsDown("TestPos") == true)
		{
			DynamicActorComponent_->SetPlayerStartPos(ResetCheckPointPos());
		}

		// 서버에 패킷 보냄
		std::shared_ptr<ObjectUpdatePacket> Packet = std::make_shared<ObjectUpdatePacket>();
		Packet->ObjectID = GetNetID();
		Packet->Type = ServerObjectType::Player;
		Packet->State = ServerObjectBaseState::Base;
		Packet->Pos = GetTransform().GetWorldPosition();
		Packet->Rot = GetTransform().GetWorldRotation();
		GameServer::Net->SendPacket(Packet);
	}
	// 서버가 조종하는 PlayerActor
	else
	{
		while (false == IsPacketEmpty())
		{
			std::shared_ptr<GameServerPacket> Packet = PopPacket();

			ContentsPacketType PacketType = Packet->GetPacketIDToEnum<ContentsPacketType>();

			switch (PacketType)
			{
			case ContentsPacketType::ObjectUpdate:
			{
				std::shared_ptr<ObjectUpdatePacket> ObjectUpdate = std::dynamic_pointer_cast<ObjectUpdatePacket>(Packet);
				GetTransform().SetWorldPosition(ObjectUpdate->Pos);
				GetTransform().SetWorldRotation(ObjectUpdate->Rot);
				break;
			}
			case ContentsPacketType::ClientInit:
			{
				break;
			}
			case ContentsPacketType::GameState:
			{
				break;
			}
			default:
				int a = 0;
				//MsgBoxAssert("처리할수 없는 패킷이 날아왔습니다.");
				break;
			}
		}
	}
	

}

void PlayerActor::LevelStartEvent()
{



	// LevelStartEvent에서 플레이어를 생성하고 위치를 재지정하는 함수
	DynamicActorComponent_->SetPlayerStartPos(GetTransform().GetWorldPosition());
}

void PlayerActor::LevelEndEvent()
{
	MainPlayer = nullptr;
	IsMainPlayerSpawned_ = false;
}

void PlayerActor::InputController(float _DeltaTime)
{
	float4 tmpMoveSpeed = float4::ZERO;
	MoveDir_ = float4::ZERO;
	float4 RotatedActor= GetTransform().GetWorldRotation();
	float4 CamForwardRot = GetLevel()->GetMainCameraActor()->GetTransform().GetWorldRotation();
	float4 ActorRot = GetTransform().GetWorldRotation();

	if (true == GameEngineInput::GetInst()->IsPress(KEY_W))
	{
		// EX) 카메라가 보고있는 방향으로 전진
		//MoveDir_ += GetTransform().Ge(tForwardVector();
		float4 CamForwardVec = GetLevel()->GetMainCameraActor()->GetTransform().GetForwardVector();
		CamForwardVec.y = 0;
		MoveDir_ += CamForwardVec.Normalize3DReturn();


	}

	if (true == GameEngineInput::GetInst()->IsPress(KEY_A))
	{
		//MoveDir_ += GetTransform().GetLeftVector();
		//MoveDir_ += GetLevel()->GetMainCameraActor()->GetTransform().GetLeftVector();
		float4 InstMoveDir = GetLevel()->GetMainCameraActor()->GetTransform().GetLeftVector();
		InstMoveDir.y = 0;
		MoveDir_ += InstMoveDir.Normalize3DReturn();
	}

	if (true == GameEngineInput::GetInst()->IsPress(KEY_S))
	{
		//MoveDir_ += GetTransform().GetBackVector();
		//MoveDir_ += GetLevel()->GetMainCameraActor()->GetTransform().GetBackVector();
		float4 InstMoveDir = GetLevel()->GetMainCameraActor()->GetTransform().GetBackVector();
		InstMoveDir.y = 0;
		MoveDir_ += InstMoveDir.Normalize3DReturn();
	}

	if (true == GameEngineInput::GetInst()->IsPress(KEY_D))
	{
		//MoveDir_ += GetTransform().GetRightVector();
		//MoveDir_ += GetLevel()->GetMainCameraActor()->GetTransform().GetRightVector();
		float4 InstMoveDir = GetLevel()->GetMainCameraActor()->GetTransform().GetRightVector();
		InstMoveDir.y = 0;
		MoveDir_ += InstMoveDir.Normalize3DReturn();
	}

	if (true == GameEngineInput::GetInst()->IsDown(KEY_SPACEBAR))
	{

		DynamicActorComponent_->SetMoveJump();

		//static bool tmp = true;
		//if (true == tmp)
		//{
		//	DynamicActorComponent_->SetlockAxis();
		//	tmp = false;
		//}
		//else
		//{
		//	DynamicActorComponent_->SetUnlockAxis();
		//	tmp = true;
		//}
	}

	if (true == GameEngineInput::GetInst()->IsPress(KEY_MOUSELEFT))
	{
	}

	if (true == GameEngineInput::GetInst()->IsPress(KEY_MOUSERIGHT))
	{
	}

	if (true == MoveDir_.IsNearlyZero())
	{
		// TODO::실제로는 무언가와 충돌했을때 호출
		//DynamicActorComponent_->SetDynamicIdle();

		return;
	}

	// 2개 이상의 키가 동시에 눌리면 문제가 발생하므로 노말라이즈
	MoveDir_.Normalize3D();
	// TODO::바닥의 마찰을 무시할 수 있도록
	//MoveDir_ += {0.0f, 0.5f, 0.0f};

	RotatedActor = GetCameraBaseRotationAng(ActorRot, CamForwardRot, MoveDir_, _DeltaTime);

	tmpMoveSpeed = MoveDir_ * SPEED_PLAYER * _DeltaTime;
	DynamicActorComponent_->SetMoveSpeed(tmpMoveSpeed);
	DynamicActorComponent_->SetChangedRot(RotatedActor);

}

// TODO::물리 충격 테스트
void PlayerActor::ImpulseTest()
{
	float4 tmpPower = float4::ZERO;
	float tmpImpulse = 1.0f;
	
	if (true == GameEngineInput::GetInst()->IsPress("ImpulsW"))
	{
		tmpPower = { 0.0f, 0.0f, tmpImpulse };
	}
	if (true == GameEngineInput::GetInst()->IsPress("ImpulsA"))
	{
		tmpPower = { -tmpImpulse, 0.0f, 0.0f };
	}
	if (true == GameEngineInput::GetInst()->IsPress("ImpulsS"))
	{
		tmpPower = { 0.0f, 0.0f, -tmpImpulse };
	}
	if (true == GameEngineInput::GetInst()->IsPress("ImpulsD"))
	{
		tmpPower = { tmpImpulse, 0.0f, 0.0f };
	}

	if (true == tmpPower.IsNearlyZero())
	{
		return;
	}

	DynamicActorComponent_->PushImpulse(tmpPower);
}

float4 PlayerActor::ResetCheckPointPos()
{
	float4 Pos = CheckPointPos_;
	Pos.x = Pos.x + GameEngineRandom::MainRandom.RandomFloat(-20.0f, 20.0f);
	return Pos;
}


// 애니메이션 초기화
void PlayerActor::SetCharacterAnimation()
{
	FbxRenderer_->CreateFBXAnimation("Idle",
	GameEngineRenderingEvent{ "TestIdle.fbx", 0.016666666666666666666666666666666666666666667f , true }, 0);

	FbxRenderer_->CreateFBXAnimation("Run",
		GameEngineRenderingEvent{ "TestRun.fbx", 0.016666666666666666666666666666666666666666667f , true }, 0);

	FbxRenderer_->ChangeAnimation("Run");
}

// 캐릭터 스킨
void PlayerActor::SetCharacterTexture()
{
	SkinData_.BodyColor = float4(0.37f, 0.64f, 0.91f);
	{
		std::vector<std::vector<GameEngineRenderUnit>>& RenderUnits = FbxRenderer_->GetAllRenderUnit();
		for (std::vector<GameEngineRenderUnit>& RenderUnit : RenderUnits)
		{
			for (GameEngineRenderUnit& Unit : RenderUnit)
			{
				// 텍스쳐
				Unit.ShaderResources.SetTexture("DiffuseTexture", "CH_FallGuy_AM.png");

				// 색 정보
				if (true == Unit.ShaderResources.IsConstantBuffer("DiffuseData"))
				{
					Unit.ShaderResources.SetConstantBufferLink("DiffuseData", SkinData_);
				}

				// 마스킹
				if (true == Unit.ShaderResources.IsTexture("FaceEyeMskTexture"))
				{
					Unit.ShaderResources.SetTexture("FaceEyeMskTexture", "CH_FallGuy_faceEyes_MSK.png");
				}

				// 스킨
				if (true == Unit.ShaderResources.IsTexture("BodyMskTexture"))
				{
					Unit.ShaderResources.SetTexture("BodyMskTexture", "CH_FallGuy_BackToFrontGradient_PTN.png");
				}

				// 노말맵 + 빛
				if (true == Unit.ShaderResources.IsTexture("NormalTexture"))
				{
					Unit.ShaderResources.SetTexture("NormalTexture", "CH_FallGuy_NM.png");
				}

			}
		}
	}
}

float4 PlayerActor::GetCameraBaseRotationAng(float4 _ActorRot, float4 _CamForRot, float4 _MoveDir, float _DeltaTime)
{

	float CamRotAdjust = 0.0f;
	CamRotAdjust = acosf(float4::DotProduct3D(_MoveDir, float4{0.0f, 0.0f, 1.0f}));
	CamRotAdjust *= GameEngineMath::RadianToDegree;
	if (_MoveDir.x < 0.0f)
	{
		CamRotAdjust = -CamRotAdjust + 360.0f;
	}

	float AngDiff = _ActorRot.y - CamRotAdjust;
	float4 ChangedActorRot = _ActorRot;
	if (AngDiff > 0.0f)
	{
		if (AngDiff < 180.0f)
		{
			//Left

			ChangedActorRot.y = _ActorRot.y + -AngularSpeed * _DeltaTime;

			if (ChangedActorRot.y < CamRotAdjust)
			{
				ChangedActorRot.y = CamRotAdjust;
			}
		}
		else
		{
			// AngDiff - 180 Right
			ChangedActorRot.y = _ActorRot.y + AngularSpeed * _DeltaTime;

			if (ChangedActorRot.y < CamRotAdjust)
			{
				ChangedActorRot.y = CamRotAdjust;
			}
		}
	}
	else if (AngDiff < 0.0f)
	{
		if (AngDiff > -180.0f)
		{
			//Right

			ChangedActorRot.y = _ActorRot.y + AngularSpeed * _DeltaTime;

			if (ChangedActorRot.y > CamRotAdjust)
			{
				ChangedActorRot.y = CamRotAdjust;
			}
		}
		else
		{
			// AngDiff - 180 Left

			ChangedActorRot.y = _ActorRot.y + -AngularSpeed * _DeltaTime;

			if (ChangedActorRot.y > CamRotAdjust)
			{
				ChangedActorRot.y = CamRotAdjust;
			}
		}
	}

	return ChangedActorRot;
}

void PlayerActor::StandUp(float _DeltaTime)
{
	if (GameEngineInput::GetInst()->IsDown("StandUp"))
	{
		IsStanding_ = true;
	}

	if (IsStanding_ == true)
	{
		if (DynamicActorComponent_->PlayerStandUp(_DeltaTime) == true)
		{
			IsStanding_ = false;
		}
	}

}