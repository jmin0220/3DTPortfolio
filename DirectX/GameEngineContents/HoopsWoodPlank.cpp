#include "PreCompile.h"
#include "HoopsWoodPlank.h"
#include "VirtualPhysXLevel.h"

HoopsWoodPlank::HoopsWoodPlank() :
	Switch(false),
	Rot_(90)
{
}

HoopsWoodPlank::~HoopsWoodPlank() 
{
}

void HoopsWoodPlank::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics)
{
	physx::PxCooking* Cooking = static_cast<VirtualPhysXLevel*>(GetLevel())->GetCooking();
	float4 MeshBoundScale = Renderer_->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	PhysXBoxGeometry_->CreatePhysXActors(_Scene, _physics, physx::PxVec3(MeshBoundScale.x, MeshBoundScale.y  , MeshBoundScale.z));

	PhysXBoxGeometry_->SetPositionSetFromParentFlag(true);

	//PhysXConvexGeometry_->CreatePhysXActors("WoodPlank.fbx", _Scene, _physics, Cooking, physx::PxVec3(MeshBoundScale.x, MeshBoundScale.y, MeshBoundScale.z));
}

void HoopsWoodPlank::Start()
{
	Renderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	Renderer_->SetFBXMesh("WoodPlank.fbx", "MaskShader");

	PhysXBoxGeometry_ = CreateComponent<PhysXBoxGeometryComponent>();
	//PhysXConvexGeometry_ = CreateComponent<PhysXConvexGeometryComponent>();

	Data.Data_ = float4(0, 0, 1.0f, 1.0f);

	std::vector<std::vector<GameEngineRenderUnit>>& UnitSets = Renderer_->GetAllRenderUnit();

	//WaterData_.WaterColor = float4::RED;
	//WaterData_.WaterColor = float4{0.99f,0.63f,0.79f};

	for (std::vector<GameEngineRenderUnit>& Units : UnitSets)
	{
		for (GameEngineRenderUnit& Unit : Units)
		{
			if (true == Unit.ShaderResources.IsConstantBuffer("MaskingData"))
			{
				Unit.ShaderResources.SetConstantBufferLink("MaskingData", Data);
			}

			if (true == Unit.ShaderResources.IsTexture("MaskTexture"))
			{
				Unit.ShaderResources.SetTexture("MaskTexture", "ENV_S02_WoodPattern_MSK.png");
			}

			if (true == Unit.ShaderResources.IsTexture("DiffuseTexture"))
			{
				Unit.ShaderResources.SetTexture("DiffuseTexture", "WoodTex.png");
			}
		}
	}



}

void HoopsWoodPlank::Update(float _DeltaTime)
{

	if (Switch==false)
	{
		Rotation_.x = Rotation_.x +_DeltaTime * 10.0f;
		GetTransform().SetLocalRotation(Rotation_);

		if (Rotation_.x >= 130.0f)
		{
			Switch = true;
		}
	}
	else
	{
		Rotation_.x -= _DeltaTime * 10.0f;
		GetTransform().SetLocalRotation(Rotation_);

		if (Rotation_.x <= 90.0f)
		{
			Switch = false;
		}
	}


}

void HoopsWoodPlank::LevelStartEvent()
{
	CreatePhysXActors(static_cast<VirtualPhysXLevel*>(GetLevel())->GetScene(),
		static_cast<VirtualPhysXLevel*>(GetLevel())->GetPhysics());

}
