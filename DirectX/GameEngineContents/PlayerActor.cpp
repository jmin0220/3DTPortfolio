#include "PreCompile.h"
#include "PlayerActor.h"
#include <GameEngineBase/GameEngineRandom.h>
#include "StageParentLevel.h"
#include "VirtualPhysXLevel.h"

#include "CameraArm.h"
#include "ServerPacket.h"

float SPEED_PLAYER = 10000.0f;
float AngularSpeed = 520.0f;

PlayerActor* PlayerActor::MainPlayer = nullptr;
bool PlayerActor::IsMainPlayerSpawned_ = false;

void PlayerActor::SetNetPlayerColor(unsigned int _Color)
{
	if (true == IsNetPlayerColorExist_)
	{
		return;
	}

	float4 Color = GameServer::GetInst()->GetPlayerColorReturn(_Color);

	SkinData_.BodyColor = Color;
	IsNetPlayerColorExist_ = true;
}

void PlayerActor::SetNetPlayerAnimation(const std::string& _Animation)
{
	if (PrevAnimation_ == _Animation)
	{
		return;
	}

	FbxRenderer_->ChangeAnimation(_Animation);
	PrevAnimation_ = _Animation;
}

PlayerActor::PlayerActor() :
	CheckPointFlag_(false),
	PlayerXZSpeed_(0.0f),
	Velocity_(float4::ZERO),
	IsDetachGround(false),
	IsTouchGround(false),
	IsOnGround(false),
	CheckPointPos_({ 0,200.0f,0 }),
	IsGoal_(false),
	IsStanding_(false),
	StandUpDelay_(0.0f),
	UnControlableTime_(0.0f),
	IsUnControlable_(false),
	IsStandingReady_(false),
	IsDiving_(false),
	IsPlayerble_(false),
	IsInputOn_(true),
	IsPlayerFrozen_(false),
	IsNetPlayerColorExist_(false),
	PrevAnimation_("")
{
}

PlayerActor::~PlayerActor() 
{
}


physx::PxRigidDynamic* PlayerActor::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics)
{
	DynamicActorComponent_->SetPhysxMaterial(0.0f,0.0f,0.0f);
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

}

void PlayerActor::PlayerInit()
{
	// 메쉬 로드
//FbxRenderer_->SetFBXMesh("Character.FBX", "Texture");
	FbxRenderer_->SetFBXMesh("Character_Idle_A.fbx", "TextureAnimationCustom");
	SetCharacterAnimation();
	SetCharacterTexture();
	FbxRenderer_->GetTransform().SetWorldScale({ PLAYER_SIZE_MAGNIFICATION_RATIO });

	MeshBoundScale = FbxRenderer_->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	MeshBoundScale *= float4{ PLAYER_SIZE_MAGNIFICATION_RATIO };
	FbxRenderer_->GetTransform().SetLocalPosition({ 0.0f, -MeshBoundScale.z * 1.3f , 0.0f });
	//FbxRenderer_->GetTransform().SetLocalPosition({0.0f, 0.0f , 0.0f});

	// PhysXActor를 생성하고, 플레이어의 RigidActor를 받아와서 콜백에 사용함
	static_cast<VirtualPhysXLevel*>(GetLevel())->SetSimulationPlayer(CreatePhysXActors(dynamic_cast<StageParentLevel*>(GetLevel())->GetScene(),
		dynamic_cast<StageParentLevel*>(GetLevel())->GetPhysics()));

	//EventCol
	EventCol_ = CreateComponent<GameEngineCollision>();
	EventCol_->ChangeOrder(CollisionGroup::Player);
	EventCol_->GetTransform().SetWorldScale({ PLAYER_COL_SCALE });
	EventCol_->GetTransform().SetLocalPosition({ 0.0f, -5.0f, 0.0f });

	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->ChangeOrder(CollisionGroup::PlayerCheck);
	Collision_->GetTransform().SetWorldScale({ 1.0f,1.0f,1.0f });

	CheckPointPos_ = GetTransform().GetWorldPosition();

	// TODO::충격테스트용 키
	if (false == GameEngineInput::GetInst()->IsKey("ImpulsW"))
	{
		GameEngineInput::GetInst()->CreateKey("ImpulsW", VK_UP);
		GameEngineInput::GetInst()->CreateKey("ImpulsA", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("ImpulsS", VK_DOWN);
		GameEngineInput::GetInst()->CreateKey("ImpulsD", VK_RIGHT);

		//플레이어 멈추기 실험용
		GameEngineInput::GetInst()->CreateKey("Freeze", 'K');

		//체크포인트 실험용
		GameEngineInput::GetInst()->CreateKey("TestPos", 'J');
	}

	DynamicActorComponent_->TurnOnSpeedLimit();

	DynamicActorComponent_->SetPhysxMaterial(0.0f, 0.0f, 0.0f);

	// LevelStartEvent에서 플레이어를 생성하고 위치를 재지정하는 함수
	DynamicActorComponent_->SetPlayerStartPos(GetTransform().GetWorldPosition());

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
		CreateAnimationFSMStates();
	}
	//충돌체크를 위한 CommonPlayer 에 Player 넣기
	{
		dynamic_cast<VirtualPhysXLevel*>(GetLevel())->SetCommonPlayer(this);
	}
}

void PlayerActor::Update(float _DeltaTime)
{
	// 서버 안켰을 때
	if (false == GetIsNetInit())
	{	
		//physx의 다이내믹의 속도를 가져옴
		Velocity_ = DynamicActorComponent_->GetDynamicVelocity();
		//xz 속도를 체크함 (걷기 멈춤 뛰기 애니메이션 구분용)
		CheckXZSpeed();

		PlayerStateManager_.Update(_DeltaTime);
		PlayerAniStateManager_.Update(_DeltaTime);

		if (IsPlayerFrozen_ == true)
		{
			IsInputOn_ = false;
			DynamicActorComponent_->FreezeDynamic();
			FbxRenderer_->PauseSwtich();
		}

	//GetTransform().SetWorldMove(MoveDir_ * SPEED_PLAYER * _DeltaTime);
	// TODO::충격테스트코드
	ImpulseTest();
	//StandUp(_DeltaTime);



		//체크포인트 실험용 나중에 지워야함
		if (GameEngineInput::GetInst()->IsDown("TestPos") == true)
		{
			DynamicActorComponent_->SetPlayerStartPos(ResetCheckPointPos());
		}


		////플레이어 떨어지면 지정한 위치에 재소환
		//if (GetTransform().GetWorldPosition().y <= -140.0f)
		//{
		//	DynamicActorComponent_->SetPlayerStartPos(CheckPointPos_);
		//}

		return;
	}

	// 서버 켰을 때
	if (true == IsPlayerble_)
	{
		//physx의 다이내믹의 속도를 가져옴
		Velocity_ = DynamicActorComponent_->GetDynamicVelocity();

		//xz 속도를 체크함 (걷기 멈춤 뛰기 애니메이션 구분용)
		CheckXZSpeed();

		PlayerStateManager_.Update(_DeltaTime);
		PlayerAniStateManager_.Update(_DeltaTime);

		//GetTransform().SetWorldMove(MoveDir_ * SPEED_PLAYER * _DeltaTime);
		// TODO::충격테스트코드
		//ImpulseTest();
		//일어서는 코드
		//StandUp(_DeltaTime);

		//플레이어 떨어지면 지정한 위치에 재소환
		//if (GetTransform().GetWorldPosition().y <= -140.0f)
		//{
		//	DynamicActorComponent_->SetPlayerStartPos(CheckPointPos_);
		//}

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
		Packet->Scale = GetTransform().GetWorldScale();
		Packet->Pos = GetTransform().GetWorldPosition();
		Packet->Rot = GetTransform().GetWorldRotation();
		Packet->PlayerColor = GameServer::GetInst()->PlayerColorID_;
		Packet->Animation = PlayerAniStateManager_.GetCurStateStateName();
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
				// Player
				std::shared_ptr<ObjectUpdatePacket> ObjectUpdate = std::dynamic_pointer_cast<ObjectUpdatePacket>(Packet);

				// 스킨
				SetNetPlayerColor(ObjectUpdate->PlayerColor);

				// 애니메이션
				SetNetPlayerAnimation(ObjectUpdate->Animation);

				GetTransform().SetWorldScale(ObjectUpdate->Scale);
				GetTransform().SetWorldPosition(ObjectUpdate->Pos);
				GetTransform().SetWorldRotation(ObjectUpdate->Rot);

				DynamicActorComponent_->SetPlayerStartPos(ObjectUpdate->Pos);
				DynamicActorComponent_->SetChangedRot(ObjectUpdate->Rot);

				GameEngineDebug::OutPutString("NetID : " + std::to_string(GetNetID()));
				GameEngineDebug::OutPutString("NetPos : " + std::to_string(ObjectUpdate->Pos.x) + "|"
					+ std::to_string(ObjectUpdate->Pos.y) + "|" + std::to_string(ObjectUpdate->Pos.z));

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

}

void PlayerActor::LevelEndEvent()
{
	MainPlayer = nullptr;
	IsMainPlayerSpawned_ = false;
}

PlayerActType PlayerActor::InputDetect()
{

	if (IsInputOn_ == false)
	{
		return PlayerActType::Idle;
	}

	if (true == GameEngineInput::GetInst()->IsPress(KEY_MOUSERIGHT))
	{
		return PlayerActType::Dive;
	}

	if (true == GameEngineInput::GetInst()->IsDown(KEY_SPACEBAR))
	{
		return PlayerActType::Jump;
	}

	if (true == GameEngineInput::GetInst()->IsPress(KEY_W))
	{
		return PlayerActType::Run;
	}

	if (true == GameEngineInput::GetInst()->IsPress(KEY_A))
	{
		return PlayerActType::Run;
	}

	if (true == GameEngineInput::GetInst()->IsPress(KEY_S))
	{
		return PlayerActType::Run;
	}

	if (true == GameEngineInput::GetInst()->IsPress(KEY_D))
	{
		return PlayerActType::Run;
	}


	//if (true == GameEngineInput::GetInst()->IsPress(KEY_MOUSELEFT))
	//{
	//	return PlayerActType::Run;
	//}
	return PlayerActType::Idle;
}

void PlayerActor::InputControllerMove(float _DeltaTime)
{
	if (IsInputOn_ == false)
	{
		return;
	}
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

void PlayerActor::InputControllerJump(float _DeltaTime)
{

	if (true == GameEngineInput::GetInst()->IsDown(KEY_SPACEBAR))
	{
 		DynamicActorComponent_->SetMoveJump();
	}
}

void PlayerActor::InputControllerDive(float _DeltaTime)
{
	float4 tmpMoveSpeed = float4::ZERO;
	MoveDir_ = float4::ZERO;
	float4 RotatedActor = GetTransform().GetWorldRotation();
	float4 CamForwardRot = GetLevel()->GetMainCameraActor()->GetTransform().GetWorldRotation();
	float4 ActorRot = GetTransform().GetWorldRotation();
	if (true == GameEngineInput::GetInst()->IsPress(KEY_MOUSELEFT))
	{
	}

	if (true == GameEngineInput::GetInst()->IsPress(KEY_MOUSERIGHT))
	{
		DynamicActorComponent_->SetMoveDive(ActorRot.y);
		DynamicActorComponent_->SetChangedRot(float4{ 90.0f, ActorRot.y , 0.0f });
	}

	// 2개 이상의 키가 동시에 눌리면 문제가 발생하므로 노말라이즈
	MoveDir_.Normalize3D();


	RotatedActor = GetCameraBaseRotationAng(ActorRot, CamForwardRot, MoveDir_, _DeltaTime);

	tmpMoveSpeed = MoveDir_ * SPEED_PLAYER * _DeltaTime;
	//DynamicActorComponent_->SetMoveSpeed(tmpMoveSpeed);
	//DynamicActorComponent_->SetChangedRot(RotatedActor);

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
	GameEngineRenderingEvent{ "Character_Idle_A.fbx", ANIMATION_FRAME_TIME , true }, 0);

	FbxRenderer_->CreateFBXAnimation("Run",
		GameEngineRenderingEvent{ "Character_Run_A.fbx", ANIMATION_FRAME_TIME , true }, 0);

	FbxRenderer_->CreateFBXAnimation("Walk",
	GameEngineRenderingEvent{ "Character_Walk_A.fbx", ANIMATION_FRAME_TIME , true }, 0);

	FbxRenderer_->CreateFBXAnimation("Jump_Start",
	GameEngineRenderingEvent{ "Character_Jump_Start_A.fbx", ANIMATION_FRAME_TIME , false }, 0);

	FbxRenderer_->CreateFBXAnimation("Jump_MidAir",
	GameEngineRenderingEvent{ "Character_Jump_MidAir_A.fbx", ANIMATION_FRAME_TIME , true }, 0);

	FbxRenderer_->CreateFBXAnimation("Jump_Landing",
		GameEngineRenderingEvent{ "Character_Landing_A.fbx", ANIMATION_FRAME_TIME , false }, 0);

	FbxRenderer_->CreateFBXAnimation("Dive_Loop",
		GameEngineRenderingEvent{ "Character_Dive_Loop.fbx", ANIMATION_FRAME_TIME , true }, 0);

	FbxRenderer_->CreateFBXAnimation("Dive_GetUp",
		GameEngineRenderingEvent{ "Character_Dive_GetUp.fbx", ANIMATION_FRAME_TIME , false }, 0);

	FbxRenderer_->CreateFBXAnimation("Ragdoll",
		GameEngineRenderingEvent{ "Character_RagDoll_A.fbx", ANIMATION_FRAME_TIME , true }, 0);


	FbxRenderer_->AnimationBindEnd("Jump_Start",
		[&](const GameEngineRenderingEvent& _Info) {
			//FbxRenderer_->CastThis<GameEngineFBXAnimationRenderer>()->GetCurAni()->bOnceEnd = false;
			PlayerAniStateManager_.ChangeState("Jump_MidAir");
		});

	FbxRenderer_->AnimationBindEnd("Jump_Landing",
		[&](const GameEngineRenderingEvent& _Info) {
			//FbxRenderer_->CastThis<GameEngineFBXAnimationRenderer>()->GetCurAni()->bOnceEnd = false;
			PlayerAniStateManager_.ChangeState("Idle");
		});

	FbxRenderer_->ChangeAnimation("Idle");
}

// 캐릭터 스킨
void PlayerActor::SetCharacterTexture()
{
	SkinData_.BodyColor = GameServer::GetInst()->PlayerColor_;
	{
		//std::vector<std::vector<GameEngineRenderUnit>>& RenderUnits = FbxRenderer_->GetAllRenderUnit();
		std::vector<std::vector< std::shared_ptr<GameEngineRenderUnit>>>& RenderUnits = FbxRenderer_->GetAllRenderUnit();
		for (std::vector< std::shared_ptr<GameEngineRenderUnit>>& RenderUnit : RenderUnits)
		{
			for (std::shared_ptr<GameEngineRenderUnit>& Unit : RenderUnit)
			{
				// 텍스쳐
				Unit->ShaderResources.SetTexture("DiffuseTexture", "CH_FallGuy_AM.png");

				// 색 정보
				if (true == Unit->ShaderResources.IsConstantBuffer("DiffuseData"))
				{
					Unit->ShaderResources.SetConstantBufferLink("DiffuseData", SkinData_);
				}

				// 마스킹
				if (true == Unit->ShaderResources.IsTexture("FaceEyeMskTexture"))
				{
					Unit->ShaderResources.SetTexture("FaceEyeMskTexture", "CH_FallGuy_faceEyes_MSK.png");
				}

				// 스킨
				if (true == Unit->ShaderResources.IsTexture("BodyMskTexture"))
				{
					Unit->ShaderResources.SetTexture("BodyMskTexture", "CH_FallGuy_BackToFrontGradient_PTN.png");
				}

				// 노말맵 + 빛
				if (true == Unit->ShaderResources.IsTexture("NormalTexture"))
				{
					Unit->ShaderResources.SetTexture("NormalTexture", "CH_FallGuy_NM.png");
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

bool PlayerActor::StandUp(float _DeltaTime)
{
	if (DynamicActorComponent_->StandUp2(_DeltaTime, IsStandingReady_) == true)
	{	
		//DynamicActorComponent_->TurnOnGravity();
		DynamicActorComponent_->SetlockAxis();
		IsStandingReady_ = false;
		IsStanding_ = false;
		return true;
	}
	return false;
}

void PlayerActor::CheckXZSpeed()
{
	float4 XZVelo = float4{ Velocity_.x, 0.0f, Velocity_.z };

	PlayerXZSpeed_ = XZVelo.Length();
}

bool PlayerActor::CheckOnGround()
{
	if (IsTouchGround == true && IsDetachGround == false)
	{
		return true;
	}
	else
	{
		return false;
	}
}