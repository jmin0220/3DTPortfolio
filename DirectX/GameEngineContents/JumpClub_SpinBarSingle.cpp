#include "PreCompile.h"
#include "JumpClub_SpinBarSingle.h"
#include "VirtualPhysXLevel.h"

JumpClub_SpinBarSingle::JumpClub_SpinBarSingle() 
	: AccSpeed_(50.0f)
	, AccTime_(5.0f)
{
}

JumpClub_SpinBarSingle::~JumpClub_SpinBarSingle() 
{
}

void JumpClub_SpinBarSingle::Start()
{
	Renderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	Renderer_->SetFBXMesh("SpinBarSingle.FBX", "CustomDefferedColor");

	PhysXSpinBarComponent_ = CreateComponent<PhysXSpinBarComponent>();
}

void JumpClub_SpinBarSingle::Update(float _DeltaTime)
{
	AccTime_ += _DeltaTime;
	// 게임시작 5초 뒤 델타타임만큼 속도 증가(, 5초마다 델타타임만큼 속도 증가)
	if (5.0f < AccTime_)
	{
		//AccTime_ = 0.0f;
		AccSpeed_ += _DeltaTime;
	}

	// 속도가 100 이상이 되면 100으로 고정
	if (100.0f <= AccSpeed_)
	{
		AccSpeed_ = 100.0f;
	}



	// 서버 안켰을 때
	if (false == GameServer::GetInst()->IsServerStart())
	{
		PhysXSpinBarComponent_->SetSpinSpeedRot(AccSpeed_ * _DeltaTime);
	}

	if (true == GameServer::IsHost_)
	{
		if (true == GameServer::GetInst()->CheckServerSignal(ServerFlag::S_StagePreviewChangeOver)
			&& false == GetMoveStartActivate())
		{
			SetMoveStartActivate(true);
		}

		if (true == GetMoveStartActivate())
		{
			PhysXSpinBarComponent_->SetSpinSpeedRot(AccSpeed_ * _DeltaTime);
		}

		// 패킷 보냄
		std::shared_ptr<ObjectUpdatePacket> Packet = std::make_shared<ObjectUpdatePacket>();
		Packet->ObjectID = GetNetID();
		Packet->Type = ServerObjectType::SpinBarSingle;
		Packet->State = ServerObjectBaseState::Base;
		Packet->Scale = GetTransform().GetWorldScale();
		Packet->Pos = GetTransform().GetWorldPosition();
		Packet->Rot = PhysXSpinBarComponent_->GetCurRot();
		GameServer::Net->SendPacket(Packet);
	}
	// 유저들은 서버가 보내주는 패킷을 받아서 움직인다
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

				if (ObjectUpdate->Type == ServerObjectType::SpinBarSingle)
				{
					PhysXSpinBarComponent_->SetCurRot(ObjectUpdate->Rot.y);
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

void JumpClub_SpinBarSingle::End()
{
}

void JumpClub_SpinBarSingle::LevelStartEvent()
{

}

void JumpClub_SpinBarSingle::LevelEndEvent()
{
}

void JumpClub_SpinBarSingle::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics)
{
	physx::PxCooking* Cooking = static_cast<VirtualPhysXLevel*>(GetLevel())->GetCooking();

	PhysXSpinBarComponent_->SetPhysxMaterial(FLOOR_STATICFRICTION, 0.7f, 0.5f);
	PhysXSpinBarComponent_->SetObjectObstacle();

	float4 MeshBoundScale = Renderer_->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	//PhysXSpinBarComponent_->SetPhysxMaterial(0.7f, 0.7f, 0.5f);
	PhysXSpinBarComponent_->CreatePhysXActors("SpinBarSingle.fbx", _Scene, _physics, Cooking, true, physx::PxVec3(MeshBoundScale.x, MeshBoundScale.y, MeshBoundScale.z));

	// 회전속도
	//PhysXSpinBarComponent_->SetSpinSpeedRot(0.3f);
}

void JumpClub_SpinBarSingle::PhysXInit()
{
	CreatePhysXActors(static_cast<VirtualPhysXLevel*>(GetLevel())->GetScene(),
		static_cast<VirtualPhysXLevel*>(GetLevel())->GetPhysics());
}
