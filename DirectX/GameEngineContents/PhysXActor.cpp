#include "PreCompile.h"
#include "PhysXActor.h"
#include "VirtualPhysXLevel.h"

PhysXActor::PhysXActor() 
{
}

PhysXActor::~PhysXActor() 
{
}

void PhysXActor::Start()
{

}

void PhysXActor::LevelStartEvent()
{
	// 1. ����� PhysX������Ʈ�� Create
	PhysXBoxGeometry_ = CreateComponent<PhysXBoxGeometryComponent>();

	// 2. �޽����� Static renderer
	Renderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	Renderer_->SetFBXMesh("floor.FBX", "Texture");

	// 3. ���� Actor�� �������� ����
	this->GetTransform().SetWorldPosition({ 0.0f });

	// 4. CreatePhysXActors�� ȣ���Ͽ� PhysX ��ü�� ����
	CreatePhysXActors(static_cast<VirtualPhysXLevel*>(GetLevel())->GetScene(),
					  static_cast<VirtualPhysXLevel*>(GetLevel())->GetPhysics());

}

void PhysXActor::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics)
{
	// 5. ����� ������Ʈ�� CreatePhysXActors�Լ��� ȣ��
	// Component�� ������ ���� �Լ��� �Ű������� �޶��� �� ����.

	// Tip..3��° �Ű������� GeometryScale�� ���Ͱ� ���� ������ü�� ũ��
	float4 MeshBoundScale = Renderer_->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	PhysXBoxGeometry_->CreatePhysXActors(_Scene, _physics, physx::PxVec3(MeshBoundScale.x, MeshBoundScale.y, MeshBoundScale.z));
}