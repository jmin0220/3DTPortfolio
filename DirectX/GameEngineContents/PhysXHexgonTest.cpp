#include "PreCompile.h"
#include "PhysXHexgonTest.h"
#include "VirtualPhysXLevel.h"

PhysXHexgonTest::PhysXHexgonTest() 
{
}

PhysXHexgonTest::~PhysXHexgonTest() 
{
}

void PhysXHexgonTest::Start()
{

}

void PhysXHexgonTest::LevelStartEvent()
{
	// 1. ����� PhysX������Ʈ�� Create
	PhysXHexTileGeometry_ = CreateComponent<PhysXHexTileGeometryComponent>();

	// 2. �޽����� Static renderer
	Renderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	Renderer_->SetFBXMesh("HexTile.FBX", "Texture");

	// 3. ���� Actor�� �������� ����
	this->GetTransform().SetWorldPosition({ 0.0f });

	// 4. CreatePhysXHexgonTests�� ȣ���Ͽ� PhysX ��ü�� ����
	CreatePhysXActors(static_cast<VirtualPhysXLevel*>(GetLevel())->GetScene(),
					  static_cast<VirtualPhysXLevel*>(GetLevel())->GetPhysics());

}

void PhysXHexgonTest::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics) 
{
	// 5. ����� ������Ʈ�� CreatePhysXHexgonTests�Լ��� ȣ��
	// Component�� ������ ���� �Լ��� �Ű������� �޶��� �� ����.

	physx::PxCooking* Cooking = static_cast<VirtualPhysXLevel*>(GetLevel())->GetCooking();
	// Tip..3��° �Ű������� GeometryScale�� ���Ͱ� ���� ������ü�� ũ��
	float4 MeshBoundScale = Renderer_->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	PhysXHexTileGeometry_->CreatePhysXActors(_Scene, _physics, Cooking, physx::PxVec3(MeshBoundScale.x, MeshBoundScale.y, MeshBoundScale.z));
}

void CreateHexaTileActor(physx::PxScene* _Scene, physx::PxPhysics* _physics, physx::PxVec3 _GeoMetryScale, float4 _GeoMetryRot)
{

}