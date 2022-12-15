#include "PreCompile.h"
#include "HoopsStageObjects.h"
#include "VirtualPhysXLevel.h"

HoopsStageObjects::HoopsStageObjects()
{
}

HoopsStageObjects::~HoopsStageObjects()
{
}

void HoopsStageObjects::Start()
{
	// 2. �޽����� Static renderer
	FloorRenderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	FloorRenderer_->SetFBXMesh("HoopsFloor.FBX", "Texture");

	PlatformRenderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	PlatformRenderer_->SetFBXMesh("HoopsObjectPlatform.FBX", "MaskShader");

	Data.Data_ = float4(0, 0, 1.0f, 1.0f);


	//std::vector<std::vector<GameEngineRenderUnit>>& UnitSets = PlatformRenderer_->GetAllRenderUnit();
	std::vector<std::vector< std::shared_ptr<GameEngineRenderUnit>>>& UnitSets = PlatformRenderer_->GetAllRenderUnit();
	for (std::vector< std::shared_ptr<GameEngineRenderUnit>>& Units : UnitSets)
	{
		for (std::shared_ptr<GameEngineRenderUnit>& Unit : Units)
		{
			if (true == Unit->ShaderResources.IsConstantBuffer("MaskingData"))
			{
				Unit->ShaderResources.SetConstantBufferLink("MaskingData", Data);
			}

			if (true == Unit->ShaderResources.IsTexture("MaskTexture"))
			{
				Unit->ShaderResources.SetTexture("MaskTexture", "ENV_S02_MedievalPattern_MSK.png");
			}

			if (true == Unit->ShaderResources.IsTexture("DiffuseTexture"))
			{
				Unit->ShaderResources.SetTexture("DiffuseTexture", "HoopPurple3.png");
			}
		}
	}


	WallRenderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	WallRenderer_->SetFBXMesh("HoopsObjectWall.FBX", "Texture");

	Renderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	Renderer_->SetFBXMesh("HoopsBackGround.FBX", "Texture");


	WallPhysXTriMeshGeometry_ = CreateComponent<PhysXTriMeshGeometryComponent>();
	FloorPhysXTriMeshGeometry_ = CreateComponent<PhysXTriMeshGeometryComponent>();
	PlatformPhysXTriMeshGeometry_ = CreateComponent<PhysXTriMeshGeometryComponent>();
}

void HoopsStageObjects::Update(float _DeltaTime)
{
}

void HoopsStageObjects::End()
{
}

void HoopsStageObjects::LevelStartEvent()
{
	// 4. CreatePhysXActors�� ȣ���Ͽ� PhysX ��ü�� ����
	CreatePhysXActors(static_cast<VirtualPhysXLevel*>(GetLevel())->GetScene(),
		static_cast<VirtualPhysXLevel*>(GetLevel())->GetPhysics());
}

void HoopsStageObjects::LevelEndEvent()
{
}

void HoopsStageObjects::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics)
{
	physx::PxCooking* Cooking = static_cast<VirtualPhysXLevel*>(GetLevel())->GetCooking();
	// Tip..3��° �Ű������� GeometryScale�� ���Ͱ� ���� ������ü�� ũ��
	float4 MeshBoundScale = WallRenderer_->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	WallPhysXTriMeshGeometry_->CreatePhysXActors("HoopsObjectWall.fbx", _Scene, _physics, Cooking, true, physx::PxVec3(MeshBoundScale.x, MeshBoundScale.y, MeshBoundScale.z));


	float4 MeshBoundScale2 = PlatformRenderer_->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	PlatformPhysXTriMeshGeometry_->SetPhysxMaterial(1.5f, 1.0f, FLOOR_RESISTUTION);
	PlatformPhysXTriMeshGeometry_->CreatePhysXActors("HoopsObjectPlatform.fbx", _Scene, _physics, Cooking, true, physx::PxVec3(MeshBoundScale2.x, MeshBoundScale2.y, MeshBoundScale2.z));


	float4 MeshBoundScale3 = FloorRenderer_->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	FloorPhysXTriMeshGeometry_->SetPhysxMaterial(1.5f, 1.0f, FLOOR_RESISTUTION);
	FloorPhysXTriMeshGeometry_->CreatePhysXActors("HoopsFloor.fbx", _Scene, _physics, Cooking, true, physx::PxVec3(MeshBoundScale3.x, MeshBoundScale3.y, MeshBoundScale3.z));
}
