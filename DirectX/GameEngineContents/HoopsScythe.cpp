#include "PreCompile.h"
#include "HoopsScythe.h"
#include "VirtualPhysXLevel.h"
#include "GameEngineBase/GameEngineRandom.h"

HoopsScythe::HoopsScythe() :
	ServerActivated_(false)
{
}

HoopsScythe::~HoopsScythe() 
{
}

void HoopsScythe::Start()
{
	Renderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	Renderer_->SetFBXMesh("HoopsScythe.FBX", "CustomDefferedColor");
	Renderer_->GetTransform().SetLocalPosition({ 0,-19.0f,0 });

	std::vector<std::vector< std::shared_ptr<GameEngineRenderUnit>>>& UnitSet = Renderer_->GetAllRenderUnit();
	for (std::vector< std::shared_ptr<GameEngineRenderUnit>>& Units : UnitSet)
	{
		for (std::shared_ptr<GameEngineRenderUnit> Unit : Units)
		{
			Unit->GetRenderer()->RenderOptionInst.IsNormal = 0;
		}
	}

	ColRenderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	ColRenderer_->SetFBXMesh("ScytheCol.FBX", "CustomDefferedColor");
	ColRenderer_->Off();

	PhysXConvexGeometry_ = CreateComponent<PhysXConvexDynamicComponent>();

	Speed_ = GameEngineRandom::MainRandom.RandomFloat(80.0f, 140.0f);
	Dir_ = GameEngineRandom::MainRandom.RandomInt(0, 1);
}

void HoopsScythe::Update(float _DeltaTime)
{

	if (true == GameServer::GetInst()->CheckServerSignal(ServerFlag::S_StageIdleChangeOver))
	{
		ServerActivated_ = true;
	}

	if (false == ServerActivated_)
	{
		return;
	}

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
	PhysXConvexGeometry_->SetAggregateObj(true);

	physx::PxCooking* Cooking = static_cast<VirtualPhysXLevel*>(GetLevel())->GetCooking();
	float4 MeshBoundScale = ColRenderer_->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	PhysXConvexGeometry_->SetDynamicPivot(Renderer_->GetTransform().GetLocalPosition());
	PhysXConvexGeometry_->SetPhysxMaterial(0, 0, 10.0f);
	PhysXConvexGeometry_->SetObjectObstacle();
	PhysXConvexGeometry_->CreatePhysXActors("ScytheCol.FBX", _Scene, _physics, Cooking,false, physx::PxVec3(MeshBoundScale.x, MeshBoundScale.y, MeshBoundScale.z) ,0.0f , true);
	PhysXConvexGeometry_->SetPositionSetFromParentFlag(true);
}
