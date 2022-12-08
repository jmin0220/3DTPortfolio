#include "PreCompile.h"
#include "HoopsWoodPlank.h"
#include "VirtualPhysXLevel.h"

int HoopsWoodPlank::Num = 0;

HoopsWoodPlank::HoopsWoodPlank() :
	Switch(false),
	Rot_(90),
	Timer_(3.0f)
{
	MyNum = Num;
	Num++;
}

HoopsWoodPlank::~HoopsWoodPlank() 
{
}

void HoopsWoodPlank::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics)
{
	physx::PxCooking* Cooking = static_cast<VirtualPhysXLevel*>(GetLevel())->GetCooking();
	float4 MeshBoundScale = Renderer_->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	PhysXBoxGeometry_->SetDynamicPivot(Renderer_->GetTransform().GetLocalPosition());
	PhysXBoxGeometry_->CreatePhysXActors(_Scene, _physics, physx::PxVec3(MeshBoundScale.x, MeshBoundScale.y  , MeshBoundScale.z));

	PhysXBoxGeometry_->SetPositionSetFromParentFlag(true);

	//PhysXConvexGeometry_->CreatePhysXActors("WoodPlank.fbx", _Scene, _physics, Cooking, false, physx::PxVec3(MeshBoundScale.x, MeshBoundScale.y, MeshBoundScale.z) , 0.0f, true );

	//PhysXConvexGeometry_->SetDynamicFriction(FLOOR_DYNAMICFRICTION);
	//PhysXConvexGeometry_->SetStaticFriction(FLOOR_STATICFRICTION);
	//PhysXConvexGeometry_->SetDynamicFriction(FLOOR_DYNAMICFRICTION);
}

void HoopsWoodPlank::Start()
{
	Renderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	Renderer_->SetFBXMesh("WoodPlank.fbx", "MaskShader");

	Renderer_->GetTransform().SetLocalPosition({ 0,-18.0f,0 });

	//PhysXConvexGeometry_ = CreateComponent<PhysXConvexDynamicComponent>();
	PhysXBoxGeometry_ = CreateComponent<PhysXBoxGeometryComponent>();

	Data.Data_ = float4(0, 0, 1.0f, 1.0f);

	std::vector<std::vector<GameEngineRenderUnit>>& UnitSets = Renderer_->GetAllRenderUnit();

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
		if (Rotation_.x >= 130.0f)
		{
			Timer_ -= _DeltaTime;
			if (Timer_ <= 0)
			{
				Switch = true;
				Timer_ = 3.0f;
			}
			return;
		}


		Rotation_.x = Rotation_.x +_DeltaTime * 3.0f;
		GetTransform().SetLocalRotation(Rotation_);

	}
	else
	{
		if (Rotation_.x <= 90.0f)
		{
			Timer_ -= _DeltaTime;
			if (Timer_ <= 0)
			{
				Switch = false;
				Timer_ = 3.0f;
			}
			return;
		}
		Rotation_.x -= _DeltaTime * 3.0f;
		GetTransform().SetLocalRotation(Rotation_);

	}


}

void HoopsWoodPlank::LevelStartEvent()
{
	CreatePhysXActors(static_cast<VirtualPhysXLevel*>(GetLevel())->GetScene(),
		static_cast<VirtualPhysXLevel*>(GetLevel())->GetPhysics());

}
