#include "PreCompile.h"
#include "VirtualPhysXLevel.h"
#include "HexTile.h"
#include <GameEngineBase/GameEngineRandom.h>

HexTile::HexTile() :
	Trigger_(false)
{
}

HexTile::~HexTile() 
{
}

void HexTile::Start()
{
	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->GetTransform().SetWorldScale({ 9.0f,3.0f,9.0f });


	// 1. 사용할 PhysX컴포넌트를 Create
	PhysXBoxGeometry_ = CreateComponent<PhysXBoxGeometryComponent>();

	// 2. 메쉬세팅 Static renderer
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
	if(true == Collision_->IsCollision(CollisionType::CT_OBB, CollisionGroup::Player, CollisionType::CT_OBB))
	{
		Collision_->Off();
		Trigger_ = true;
	}

	if (Trigger_ == true)
	{
		PhysXBoxGeometry_->ReleasePhysX();
		float YVector = GameEngineMath::Lerp(GetTransform().GetWorldPosition().y, GetTransform().GetWorldPosition().y - 10.0f, 7.0f * _DeltaTime);

		GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x,YVector,GetTransform().GetWorldPosition().z });
	}

}

void HexTile::OnEvent()
{

}


void HexTile::OffEvent()
{
	
}


void HexTile::LevelStartEvent()
{


	// 3. 현재 Actor의 포지션을 설정
	//this->GetTransform().SetWorldPosition({ 0.0f,0.0f,0 });

	// 4. CreatePhysXActors를 호출하여 PhysX 객체를 생성
	CreatePhysXActors(static_cast<VirtualPhysXLevel*>(GetLevel())->GetScene(),
		static_cast<VirtualPhysXLevel*>(GetLevel())->GetPhysics());
}

void HexTile::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics)
{
	float4 MeshBoundScale = Renderer_->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	PhysXBoxGeometry_->CreatePhysXActors(_Scene, _physics, physx::PxVec3(MeshBoundScale.x, MeshBoundScale.y, MeshBoundScale.z));
}

//CollisionReturn HexTile::CheckCol(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
//{
//	_This->Off();
//	Trigger_ = true;
//	return CollisionReturn::Break;
//}
