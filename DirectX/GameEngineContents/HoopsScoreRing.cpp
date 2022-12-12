#include "PreCompile.h"
#include "HoopsScoreRing.h"
#include "VirtualPhysXLevel.h"
#include "GameEngineBase/GameEngineRandom.h"

HoopsScoreRing::HoopsScoreRing()
{
}

HoopsScoreRing::~HoopsScoreRing()
{
}

void HoopsScoreRing::Start()
{
	Renderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	Renderer_->SetFBXMesh("HoopsScoreRing2.FBX", "Texture");

	//PhysXConvexGeometry_ = CreateComponent<PhysXConvexDynamicComponent>();

	PhysXTriGeometry_ = CreateComponent<PhysXTriMeshGeometryComponent>();

	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->GetTransform().SetLocalScale({ 5.0f,5.0f,2.0f, });

	float Rot = GameEngineRandom::MainRandom.RandomFloat(0, 360.0f);


	Renderer_->GetTransform().SetLocalRotate({ 0,Rot ,0 });
}

void HoopsScoreRing::Update(float _DeltaTime)
{

}

void HoopsScoreRing::LevelStartEvent()
{
	CreatePhysXActors(static_cast<VirtualPhysXLevel*>(GetLevel())->GetScene(),
		static_cast<VirtualPhysXLevel*>(GetLevel())->GetPhysics());
}

void HoopsScoreRing::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics)
{
	physx::PxCooking* Cooking = static_cast<VirtualPhysXLevel*>(GetLevel())->GetCooking();
	float4 MeshBoundScale = Renderer_->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	PhysXTriGeometry_->SetDynamicPivot(Renderer_->GetTransform().GetLocalPosition());
	PhysXTriGeometry_->CreatePhysXActors("HoopsScoreRing2.FBX", _Scene, _physics, Cooking, true, physx::PxVec3(MeshBoundScale.x, MeshBoundScale.y, MeshBoundScale.z), 0.0f);
	PhysXTriGeometry_->SetPhysxMaterial(FLOOR_STATICFRICTION, FLOOR_DYNAMICFRICTION, FLOOR_RESISTUTION);
	PhysXTriGeometry_->SetPositionSetFromParentFlag(true);
}
