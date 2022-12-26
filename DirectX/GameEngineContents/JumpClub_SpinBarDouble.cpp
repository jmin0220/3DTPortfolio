#include "PreCompile.h"
#include "JumpClub_SpinBarDouble.h"
#include "VirtualPhysXLevel.h"

JumpClub_SpinBarDouble::JumpClub_SpinBarDouble() 
{
}

JumpClub_SpinBarDouble::~JumpClub_SpinBarDouble() 
{
}

void JumpClub_SpinBarDouble::PhysXInit()
{
	CreatePhysXActors(static_cast<VirtualPhysXLevel*>(GetLevel())->GetScene(),
	static_cast<VirtualPhysXLevel*>(GetLevel())->GetPhysics());
}

void JumpClub_SpinBarDouble::Start()
{
	Renderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	Renderer_->SetFBXMesh("SpinBarDouble.FBX", "CustomDefferedColor");

	PhysXSpinBarComponent_ = CreateComponent<PhysXSpinBarComponent>();
}

void JumpClub_SpinBarDouble::Update(float _DeltaTime)
{

	
	// 서버 안켰을 때
	if (false == GameServer::GetInst()->IsServerStart())
	{
		PhysXSpinBarComponent_->SetSpinSpeedRot(50.0f * _DeltaTime);
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
			PhysXSpinBarComponent_->SetSpinSpeedRot(50.0f * _DeltaTime);
		}

		// 패킷 보냄
		std::shared_ptr<ObjectUpdatePacket> Packet = std::make_shared<ObjectUpdatePacket>();
		Packet->ObjectID = GetNetID();
		Packet->Type = ServerObjectType::SpinBarDouble;
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

				if (ObjectUpdate->Type == ServerObjectType::SpinBarDouble)
				{
					//ObjectUpdate->Rot;
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

void JumpClub_SpinBarDouble::End()
{
}

void JumpClub_SpinBarDouble::LevelStartEvent()
{

}

void JumpClub_SpinBarDouble::LevelEndEvent()
{
}

void JumpClub_SpinBarDouble::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics)
{
	physx::PxCooking* Cooking = static_cast<VirtualPhysXLevel*>(GetLevel())->GetCooking();
	
	float4 MeshBoundScale = Renderer_->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	PhysXSpinBarComponent_->CreatePhysXActors("SpinBarDouble.fbx", _Scene, _physics, Cooking, true, physx::PxVec3(MeshBoundScale.x, MeshBoundScale.y, MeshBoundScale.z));

	// 회전속도
	//PhysXSpinBarComponent_->SetSpinSpeedRot(0.5f);
}
