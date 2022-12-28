#include "PreCompile.h"
#include "DoorDashStage.h"
#include "VirtualPhysXLevel.h"

DoorDashStage::DoorDashStage() 
{
}

DoorDashStage::~DoorDashStage() 
{
}

void DoorDashStage::Start()
{
	// 2. 메쉬세팅 Static renderer
	PlatformRenderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	PlatformRenderer_->SetFBXMesh("DoorDashPlatformCollisionMesh.FBX", "CustomDefferedColor");

	WallRenderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	WallRenderer_->SetFBXMesh("DoorDashWallCollisionMesh.FBX", "CustomDefferedColor");

	Renderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	Renderer_->SetFBXMesh("DoodrDashEnv.FBX", "CustomDefferedColor");

	BlocksRenderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	BlocksRenderer_->SetFBXMesh("DoorDashWallBlocks.FBX", "CustomDefferedColor");

	{
		std::vector<std::vector< std::shared_ptr<GameEngineRenderUnit>>>& UnitSet = WallRenderer_->GetAllRenderUnit();
		for (std::vector< std::shared_ptr<GameEngineRenderUnit>>& Units : UnitSet)
		{
			for (std::shared_ptr<GameEngineRenderUnit> Unit : Units)
			{
				Unit->GetRenderer()->RenderOptionInst.IsNormal = 0;
			}
		}
	}

	{
		std::vector<std::vector< std::shared_ptr<GameEngineRenderUnit>>>& UnitSet = Renderer_->GetAllRenderUnit();
		for (std::vector< std::shared_ptr<GameEngineRenderUnit>>& Units : UnitSet)
		{
			for (std::shared_ptr<GameEngineRenderUnit> Unit : Units)
			{
				Unit->GetRenderer()->RenderOptionInst.IsNormal = 0;
			}
		}
	}

	{
		std::vector<std::vector< std::shared_ptr<GameEngineRenderUnit>>>& UnitSet = PlatformRenderer_->GetAllRenderUnit();
		for (std::vector< std::shared_ptr<GameEngineRenderUnit>>& Units : UnitSet)
		{
			for (std::shared_ptr<GameEngineRenderUnit> Unit : Units)
			{
				Unit->GetRenderer()->RenderOptionInst.IsNormal = 0;
			}
		}
	}




	WallPhysXTriMeshGeometry_ = CreateComponent<PhysXTriMeshGeometryComponent>();

	PlatformPhysXTriMeshGeometry_ = CreateComponent<PhysXTriMeshGeometryComponent>();

	BlocksPhysXTriMeshGeometry_ = CreateComponent<PhysXTriMeshGeometryComponent>();
}

void DoorDashStage::Update(float _DeltaTime)
{
}

void DoorDashStage::End()
{
}

void DoorDashStage::LevelStartEvent()
{
	// 4. CreatePhysXActors를 호출하여 PhysX 객체를 생성
	CreatePhysXActors(static_cast<VirtualPhysXLevel*>(GetLevel())->GetScene(),
		static_cast<VirtualPhysXLevel*>(GetLevel())->GetPhysics());
}

void DoorDashStage::LevelEndEvent()
{
}

void DoorDashStage::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics)
{
	physx::PxCooking* Cooking = static_cast<VirtualPhysXLevel*>(GetLevel())->GetCooking();
	// Tip..3번째 매개변수인 GeometryScale은 액터가 가질 물리강체의 크기
	float4 MeshBoundScale = WallRenderer_->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	WallPhysXTriMeshGeometry_->SetPhysxMaterial(0, 0, 0);
	WallPhysXTriMeshGeometry_->CreatePhysXActors("DoorDashWallCollisionMesh.fbx", _Scene, _physics, Cooking, false, physx::PxVec3(MeshBoundScale.x, MeshBoundScale.y, MeshBoundScale.z));

	float4 MeshBoundScale3 = BlocksRenderer_->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	BlocksPhysXTriMeshGeometry_->SetPhysxMaterial(0, 0, 0);
	BlocksPhysXTriMeshGeometry_->CreatePhysXActors("DoorDashWallBlocks.fbx", _Scene, _physics, Cooking, false, physx::PxVec3(MeshBoundScale3.x, MeshBoundScale3.y, MeshBoundScale3.z));


	float4 MeshBoundScale2 = PlatformRenderer_->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	PlatformPhysXTriMeshGeometry_->SetPhysxMaterial(FLOOR_STATICFRICTION, FLOOR_DYNAMICFRICTION, FLOOR_RESISTUTION);
	PlatformPhysXTriMeshGeometry_->SetObjectGround();
	PlatformPhysXTriMeshGeometry_->CreatePhysXActors("DoorDashPlatformCollisionMesh.fbx", _Scene, _physics, Cooking, false, physx::PxVec3(MeshBoundScale2.x, MeshBoundScale2.y, MeshBoundScale2.z));



	//
	//SetObjectGround    -> 땅 
	//SetObjectObstacle  -> 닿으면 넘어진다


}
