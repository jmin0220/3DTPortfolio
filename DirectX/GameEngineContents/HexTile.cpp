#include "PreCompile.h"
#include "VirtualPhysXLevel.h"
#include "HexTile.h"
#include <GameEngineBase/GameEngineRandom.h>

HexTile::HexTile() 
{
}

HexTile::~HexTile() 
{
}

void HexTile::Start()
{
	// 1. ����� PhysX������Ʈ�� Create
	PhysXBoxGeometry_ = CreateComponent<PhysXBoxGeometryComponent>();

	// 2. �޽����� Static renderer
	Renderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	Renderer_->SetFBXMesh("HexTile.FBX", "Texture");
	//Renderer_->GetTransform().SetWorldScale({ 10.0f,10.0f,10.0f });
	std::vector<std::vector<GameEngineRenderUnit>>& UnitSet = Renderer_->GetAllRenderUnit();
	for (std::vector<GameEngineRenderUnit>& Units : UnitSet)
	{
		for (GameEngineRenderUnit& Unit : Units)
		{
			if (true == Unit.ShaderResources.IsTexture("DiffuseTexture"))
			{
				int RanNum = GameEngineRandom::MainRandom.RandomInt(0, 4);
				if (RanNum == 0)
				{
					TexName = "ENV_TerrainFoam_AM_S04";
				}
				else if (RanNum == 1)
				{
					TexName = "HexAGoneBlue";
				}
				else if (RanNum == 2)
				{
					TexName = "HexAGoneBlue2";
				}
				else if (RanNum == 3)
				{
					TexName = "ENV_DarkerYellow";
				}
				else if (RanNum == 4)
				{
					TexName = "HexAGoneBlue3";
				}
				Unit.ShaderResources.SetTexture("DiffuseTexture", TexName + ".png");
			}
		}
	}


}

void HexTile::Update(float _DeltaTime)
{


}

void HexTile::OnEvent()
{

}


void HexTile::OffEvent()
{
	
}


void HexTile::LevelStartEvent()
{


	// 3. ���� Actor�� �������� ����
	//this->GetTransform().SetWorldPosition({ 0.0f,0.0f,0 });

	// 4. CreatePhysXActors�� ȣ���Ͽ� PhysX ��ü�� ����
	CreatePhysXActors(static_cast<VirtualPhysXLevel*>(GetLevel())->GetScene(),
		static_cast<VirtualPhysXLevel*>(GetLevel())->GetPhysics());
}

void HexTile::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics)
{
	float4 MeshBoundScale = Renderer_->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	PhysXBoxGeometry_->CreatePhysXActors(_Scene, _physics, physx::PxVec3(MeshBoundScale.x, MeshBoundScale.y, MeshBoundScale.z));
}
