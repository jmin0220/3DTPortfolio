#include "PreCompile.h"
#include "HoopsScythe.h"
#include "VirtualPhysXLevel.h"
#include "GameEngineBase/GameEngineRandom.h"

HoopsScythe::HoopsScythe() 
{
}

HoopsScythe::~HoopsScythe() 
{
}

void HoopsScythe::Start()
{
	Renderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	Renderer_->SetFBXMesh("HoopsScythe.FBX", "Texture");
	Renderer_->GetTransform().SetLocalPosition({ 0,-19.0f,0 });


	ColRenderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	ColRenderer_->SetFBXMesh("ScytheCol.FBX", "Texture");
	ColRenderer_->Off();

	PhysXConvexGeometry_ = CreateComponent<PhysXConvexDynamicComponent>();

	Speed_ = GameEngineRandom::MainRandom.RandomFloat(20.0f, 60.0f);
	Dir_ = GameEngineRandom::MainRandom.RandomInt(0, 1);
}

void HoopsScythe::Update(float _DeltaTime)
{
	if (Dir_ == 0)
	{
		GetTransform().SetLocalRotate({ 0,0,Speed_ * _DeltaTime });
	}
	else
	{
		GetTransform().SetLocalRotate({ 0,0,-Speed_ * _DeltaTime });
	}
}

void HoopsScythe::LevelStartEvent()
{
	Rotation_ = GetTransform().GetWorldRotation();
	CreatePhysXActors(static_cast<VirtualPhysXLevel*>(GetLevel())->GetScene(),
		static_cast<VirtualPhysXLevel*>(GetLevel())->GetPhysics());
}

void HoopsScythe::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics)
{
	physx::PxCooking* Cooking = static_cast<VirtualPhysXLevel*>(GetLevel())->GetCooking();
	float4 MeshBoundScale = ColRenderer_->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	PhysXConvexGeometry_->SetDynamicPivot(Renderer_->GetTransform().GetLocalPosition());
	PhysXConvexGeometry_->SetPhysxMaterial(0, 0, 10.0f);
	PhysXConvexGeometry_->CreatePhysXActors("ScytheCol.FBX", _Scene, _physics, Cooking,false, physx::PxVec3(MeshBoundScale.x, MeshBoundScale.y, MeshBoundScale.z) ,0.0f , true);
	PhysXConvexGeometry_->SetPositionSetFromParentFlag(true);
}
