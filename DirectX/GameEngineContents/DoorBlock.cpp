#include "PreCompile.h"
#include "DoorBlock.h"
#include "VirtualPhysXLevel.h"

int DoorBlock::Num = 0;

DoorBlock::DoorBlock() :
	Switch_(false),
	Speed_(20.0f)
{
	Num++; //Num�� 1���� ��ŸƮ���ο� ĳ���� ���� ���Ͽ��ʺ��� 1 ����
}

DoorBlock::~DoorBlock() 
{
}

void DoorBlock::Start()
{

	PhysXBoxGeometry_ = CreateComponent<PhysXBoxGeometryComponent>();

	// 2. �޽����� Static renderer
	Renderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	Renderer_->SetFBXMesh("DoorBlock.FBX", "Texture");
}

void DoorBlock::Update(float _DeltaTime)
{
	if (Switch_ == false)
	{
		GetTransform().SetWorldDownMove(Speed_, _DeltaTime);
		if (GetTransform().GetWorldPosition().y <= YPos)
		{
			Switch_ = true;
		}
	}
	else if (Switch_ == true)
	{
		GetTransform().SetWorldUpMove(Speed_, _DeltaTime);
		if (GetTransform().GetWorldPosition().y >= Pos)
		{
			Switch_ = false;
		}
	}

}

void DoorBlock::LevelStartEvent()
{

	YPos = GetTransform().GetWorldPosition().y - 15.0f;
	Pos = GetTransform().GetWorldPosition().y;

	CreatePhysXActors(static_cast<VirtualPhysXLevel*>(GetLevel())->GetScene(),
		static_cast<VirtualPhysXLevel*>(GetLevel())->GetPhysics());
}

void DoorBlock::OffEvent()
{
}

void DoorBlock::OnEvent()
{
}

void DoorBlock::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics)
{

	float4 Scale = GetTransform().GetWorldScale();


	float4 MeshBoundScale = Renderer_->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	MeshBoundScale *= Scale;
	PhysXBoxGeometry_->CreatePhysXActors(_Scene, _physics, physx::PxVec3(MeshBoundScale.x - 2.0f , MeshBoundScale.y, MeshBoundScale.z));

	PhysXBoxGeometry_->SetPositionSetFromParentFlag(true);
}
