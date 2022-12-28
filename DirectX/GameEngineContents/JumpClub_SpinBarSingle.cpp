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
	// ���ӽ��� 5�� �� ��ŸŸ�Ӹ�ŭ �ӵ� ����(, 5�ʸ��� ��ŸŸ�Ӹ�ŭ �ӵ� ����)
	if (5.0f < AccTime_)
	{
		//AccTime_ = 0.0f;
		AccSpeed_ += _DeltaTime;
	}

	// �ӵ��� 100 �̻��� �Ǹ� 100���� ����
	if (100.0f <= AccSpeed_)
	{
		AccSpeed_ = 100.0f;
	}



	// ���� ������ ��
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

		// ��Ŷ ����
		std::shared_ptr<ObjectUpdatePacket> Packet = std::make_shared<ObjectUpdatePacket>();
		Packet->ObjectID = GetNetID();
		Packet->Type = ServerObjectType::SpinBarSingle;
		Packet->State = ServerObjectBaseState::Base;
		Packet->Scale = GetTransform().GetWorldScale();
		Packet->Pos = GetTransform().GetWorldPosition();
		Packet->Rot = PhysXSpinBarComponent_->GetCurRot();
		GameServer::Net->SendPacket(Packet);
	}
	// �������� ������ �����ִ� ��Ŷ�� �޾Ƽ� �����δ�
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

	// ȸ���ӵ�
	//PhysXSpinBarComponent_->SetSpinSpeedRot(0.3f);
}

void JumpClub_SpinBarSingle::PhysXInit()
{
	CreatePhysXActors(static_cast<VirtualPhysXLevel*>(GetLevel())->GetScene(),
		static_cast<VirtualPhysXLevel*>(GetLevel())->GetPhysics());
}
