#include "PreCompile.h"
#include "BigShots_Cannon.h"
#include "BigShots_PRP.h"
#include "BigShots_Puff.h"
#include <GameEngineBase/GameEngineRandom.h>

BigShots_Cannon::BigShots_Cannon()
	: ShootingTime_(5.0f)
	, SumShootingTime_(ShootingTime_)
{
}

BigShots_Cannon::~BigShots_Cannon() 
{
}

void BigShots_Cannon::Start()
{
	FbxRenderer_ = CreateComponent<GameEngineFBXAnimationRenderer>();
	FbxFloatingRenderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	FbxSpinnerRenderer_ = CreateComponent<GameEngineFBXStaticRenderer>();

	FbxRenderer_->SetFBXMesh("PRP_CanonLip.fbx", "TextureAnimation");

	FbxRenderer_->CreateFBXAnimation("Idle",
		GameEngineRenderingEvent{ "PRP_CanonLip.fbx", ANIMATION_FRAME_TIME , false }, 0);
	FbxRenderer_->ChangeAnimation("Idle");


	//std::vector<std::vector<GameEngineRenderUnit>>& RenderUnits = FbxRenderer_->GetAllRenderUnit();
	std::vector<std::vector< std::shared_ptr<GameEngineRenderUnit>>>& RenderUnits = FbxRenderer_->GetAllRenderUnit();

	for (std::vector<std::shared_ptr<GameEngineRenderUnit>>& RenderUnit : RenderUnits)
	{
		for (std::shared_ptr<GameEngineRenderUnit>& Unit : RenderUnit)
		{
			// 텍스쳐
			Unit->ShaderResources.SetTexture("DiffuseTexture", "PRP_S04_Cannon_AM.png");
		}
	}

	FbxRenderer_->GetTransform().SetWorldScale({ 2.5f,2.5f,2.5f });

	FbxFloatingRenderer_->SetFBXMesh("ENV_S04_FloatingCannonTubes.fbx", "Texture");
	FbxFloatingRenderer_->GetTransform().SetWorldRotation(GetTransform().GetWorldRotation() + float4(10.0f, 0.0f, 0.0f));

	FbxSpinnerRenderer_->SetFBXMesh("ENV_S04_Spinner.fbx", "Texture");
	FbxSpinnerRenderer_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition() + float4(0.0f, 40.0f, 0.0f));
	FbxSpinnerRenderer_->GetTransform().SetWorldRotation(GetTransform().GetWorldRotation() + float4(10.0f, 0.0f, 0.0f));

	// 무한반복 X
	FbxRenderer_->CastThis<GameEngineFBXAnimationRenderer>()->GetCurAni()->bOnceEnd = false;
	FbxRenderer_->AnimationBindFrame("Idle", [=](const GameEngineRenderingEvent& _Info)
		{
			if (_Info.CurFrame == 3)
			{
				//연기 효과
				/*std::shared_ptr<GameEngineActor> Puff = GetLevel()->CreateActor<BigShots_Puff>();
				Puff->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition() + float4{ 0.0f,0.0f,30.0f });*/
				for (int i = 0; i < 8; i++)
				{
					GameEngineRandom RandomValue_;
					float RandomFloatNum = GameEngineRandom::MainRandom.RandomFloat(45.0f * i, 45.0f * (i + 1));

					std::shared_ptr<BigShots_Puff> Puff = GetLevel()->CreateActor<BigShots_Puff>();
					Puff->SetRenderingOrder(10 + i);
					Puff->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition() + float4{ 0.0f,5.0f,30.0f + 0.1f * i });
					Puff->GetTransform().SetLocalRotation(float4{ 0.0f,0.0f,RandomFloatNum });
				}

				std::shared_ptr<BigShots_PRP> PRP = GetLevel()->CreateActor<BigShots_PRP>();
				PRP->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition() + float4{ 0.0f,0.0f,15.0f });
				
				// 물리 세팅하면서 힘, 방향 정해짐
				PRP->InitPRP(CurShootSetting_);
				PRP->CreatePhysX();
			}

		});

}

void BigShots_Cannon::Update(float _DeltaTime)
{

	// 호스트 : 캐논 발사, 대포알 상태 결정
	// 유저 : 패킷만 읽어서 캐논 발사
	if (true == GameServer::GetInst()->IsServerStart())
	{
		if (true == GameServer::GetInst()->CheckServerSignal(ServerFlag::S_StagePreviewChangeOver)
			&& false == GetMoveStartActivate())
		{
			SetMoveStartActivate(true);
		}

		if (true == GameServer::IsHost_)
		{

			if (false == GetMoveStartActivate())
			{
				std::shared_ptr<ObjectUpdatePacket> Packet = std::make_shared<ObjectUpdatePacket>();
				Packet->ObjectID = GetNetID();
				Packet->Type = ServerObjectType::Cannon;
				Packet->State = ServerObjectBaseState::Base;
				Packet->Scale = GetTransform().GetWorldScale();
				Packet->Pos = GetTransform().GetWorldPosition();
				Packet->Rot = GetTransform().GetWorldRotation();
				Packet->PlayerColor = static_cast<unsigned int>(false);
				GameServer::Net->SendPacket(Packet);
				return;
			}

			SumShootingTime_ += _DeltaTime;

			if (SumShootingTime_ >= InterTime_)
			{
				IsShoot_ = true;
				SumShootingTime_ = 0.0f;
				InterTime_ = GameEngineRandom::MainRandom.RandomFloat(3.0f, 5.0f);
			}


			if (true == IsShoot_)
			{
				// 발사설정
				SetShootSetting();

				// 유저들에게 패킷 보냄
				std::shared_ptr<ObjectUpdatePacket> Packet = std::make_shared<ObjectUpdatePacket>();
				Packet->ObjectID = GetNetID();
				Packet->Type = ServerObjectType::Cannon;
				Packet->State = ServerObjectBaseState::Base;
				Packet->Scale = GetTransform().GetWorldScale();
				Packet->Pos = GetTransform().GetWorldPosition();
				Packet->Rot = GetTransform().GetWorldRotation();
				Packet->CannonInfo = CurShootSetting_;
				Packet->PlayerColor = static_cast<unsigned int>(IsShoot_);
				//Packet->Option = 0;
				GameServer::Net->SendPacket(Packet);

				IsShoot_ = false;

				// 대포발사
				FbxRenderer_->ChangeAnimation("Idle");
			}

		}
		else
		{
			// 유저들의 대포
			while (false == IsPacketEmpty())
			{
				std::shared_ptr<GameServerPacket> Packet = PopPacket();

				ContentsPacketType PacketType = Packet->GetPacketIDToEnum<ContentsPacketType>();

				switch (PacketType)
				{
				case ContentsPacketType::ObjectUpdate:
				{
					std::shared_ptr<ObjectUpdatePacket> ObjectUpdate = std::dynamic_pointer_cast<ObjectUpdatePacket>(Packet);

					if (ObjectUpdate->Type == ServerObjectType::Cannon)
					{
						bool Signal = static_cast<bool>(ObjectUpdate->PlayerColor);
						if (true == Signal)
						{
							// 대포발사
							CurShootSetting_ = ObjectUpdate->CannonInfo;
							FbxRenderer_->ChangeAnimation("Idle");
						}
							
					}
					else
					{
						continue;
					}

					break;
				}
				default:
					break;
				}
			}

		}
	}
	// 서버 안켰을 때
	else
	{
		if (true == GameEngineInput::GetInst()->IsDown(KEY_ENTER))
		{
			// 발사
			SetShootSetting();
			FbxRenderer_->ChangeAnimation("Idle");
		}

	}

}

void BigShots_Cannon::LevelStartEvent()
{

}

void BigShots_Cannon::LevelEndEvent()
{
}

void BigShots_Cannon::SetShootSetting()
{
	//float SettingForce_; // x : 회전값, y : 회전값, z : 회전값, w : 힘
	// 힘 : 430 ~ 470
	float4 RandomRot = GameEngineRandom::MainRandom.RandomFloat4(-9.0f, 9.0f);
	float RandomPower = GameEngineRandom::MainRandom.RandomFloat(430, 470);
	CurShootSetting_ = RandomRot;
	CurShootSetting_.w = RandomPower;
}
