#include "PreCompile.h"
#include "VirtualPhysXLevel.h"
#include "HexTile.h"
#include "PhysXConvexGeometryComponent.h"
#include <GameEngineBase/GameEngineRandom.h>

HexTile::HexTile() :
	Trigger_(false),
	Shake_(false),
	Flag_(false),
	Speed_(3.0f)
{
}

HexTile::~HexTile() 
{
}

void HexTile::Start()
{
	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->GetTransform().SetWorldScale({ 8.0f,3.0f,8.0f });


	// 1. 사용할 PhysX컴포넌트를 Create
	//PhysXBoxGeometry_ = CreateComponent<PhysXBoxGeometryComponent>();
	PhysXHexTileGeometry_ = CreateComponent<PhysXConvexGeometryComponent>();

	// 2. 메쉬세팅 Static renderer
	Renderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	Renderer_->SetFBXMesh("HexTile.FBX", "HexDefferedColor");
	//Renderer_->GetTransform().SetWorldScale({ 10.0f,10.0f,10.0f });
	 
	//std::vector<std::vector<GameEngineRenderUnit>>& UnitSet = Renderer_->GetAllRenderUnit();
	

	StateManager_.CreateStateMember("Move"
		, std::bind(&HexTile::MoveUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&HexTile::MoveStart, this, std::placeholders::_1));

	StateManager_.CreateStateMember("Shake"
		, std::bind(&HexTile::ShakeUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&HexTile::ShakeStart, this, std::placeholders::_1));

	StateManager_.ChangeState("Move");

	Mode_ = HexTileState::Move;

}

void HexTile::Update(float _DeltaTime)
{
	if(true == Collision_->IsCollision(CollisionType::CT_OBB, CollisionGroup::Player, CollisionType::CT_OBB))
	{
		Collision_->Off();
		Trigger_ = true;
		MyPos = GetTransform().GetWorldPosition();
		CurPos = GetTransform().GetWorldPosition();
		CurPos.y -= 0.9f;
	}

	if (Trigger_ == true)
	{
		StateManager_.Update(_DeltaTime);

		//PhysXBoxGeometry_->ReleasePhysX();
		/*if (GetTransform().GetWorldPosition().y >= CurPos.y)
		{
			GetTransform().SetWorldDownMove(10.0f, _DeltaTime);
			if (GetTransform().GetWorldPosition().y <= CurPos.y)
			{
				Trigger_ = false;
				Shake_ = true;
			}
		}*/
	}

	if (Flag_ == true)
	{
		MeshPixelData_.MulColor = 0.7f;
		MeshPixelData_.PlusColor += 1.0f * _DeltaTime;

		if (MeshPixelData_.PlusColor.x >= 2.0f)
		{
		
			PhysXHexTileGeometry_->ReleasePhysX();
			//PhysXBoxGeometry_->ReleasePhysX();
			
		}
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
	physx::PxCooking* Cooking = static_cast<VirtualPhysXLevel*>(GetLevel())->GetCooking();
	// Tip..3번째 매개변수인 GeometryScale은 액터가 가질 물리강체의 크기
	float4 MeshBoundScale = Renderer_->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	PhysXHexTileGeometry_->CreatePhysXActors("HexTile.fbx", _Scene, _physics, Cooking, physx::PxVec3(MeshBoundScale.x, MeshBoundScale.y, MeshBoundScale.z));

	//float4 MeshBoundScale = Renderer_->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	//PhysXBoxGeometry_->CreatePhysXActors(_Scene, _physics, physx::PxVec3(MeshBoundScale.x, MeshBoundScale.y, MeshBoundScale.z));
}



void HexTile::MoveStart(const StateInfo& _Info)
{

}

void HexTile::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (Shake_ == true)
	{
		if (GetTransform().GetWorldPosition().y <= MyPos.y)
		{
			GetTransform().SetWorldUpMove(Speed_ + 0.3f, _DeltaTime);
		}

		if (GetTransform().GetWorldPosition().y >= MyPos.y)
		{
			Trigger_ = false;
			Flag_ = true;
		}

		return;
	}


	if (GetTransform().GetWorldPosition().y >= CurPos.y)
	{
		GetTransform().SetWorldDownMove(Speed_ + 0.3f, _DeltaTime);
		if (GetTransform().GetWorldPosition().y <= CurPos.y)
		{
			StateManager_.ChangeState("Shake");
		}
	}


}

void HexTile::ShakeStart(const StateInfo& _Info)
{
	CurPos.y += 0.3f;
}

void HexTile::ShakeUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (GetTransform().GetWorldPosition().y <= CurPos.y && Shake_==false)
	{
		GetTransform().SetWorldUpMove(Speed_, _DeltaTime);
		if (GetTransform().GetWorldPosition().y >= CurPos.y)
		{
			Shake_ = true;
			CurPos.y -= 0.3f;
		}
	}

	if (Shake_ == true)
	{
		if (GetTransform().GetWorldPosition().y >= CurPos.y)
		{
			GetTransform().SetWorldDownMove(Speed_, _DeltaTime);
		}
		else
		{
			StateManager_.ChangeState("Move");
		}
	}
}

void HexTile::SetTex(std::string _Name)
{
	std::vector<std::vector< std::shared_ptr<GameEngineRenderUnit>>>& UnitSet = Renderer_->GetAllRenderUnit();
	for (std::vector< std::shared_ptr<GameEngineRenderUnit>>& Units : UnitSet)
	{
		for (std::shared_ptr<GameEngineRenderUnit> Unit : Units)
		{
			Unit->ShaderResources.SetConstantBufferLink("MeshPixelData", MeshPixelData_);
			if (true == Unit->ShaderResources.IsTexture("DiffuseTexture"))
			{
				int RanNum = GameEngineRandom::MainRandom.RandomInt(1, 3);

				if (RanNum == 1)
				{
					TexName = "Hex" + _Name + std::to_string(RanNum);
				}
				else if (RanNum == 2)
				{
					TexName = "Hex" + _Name + std::to_string(RanNum);
				}
				else if (RanNum == 3)
				{
					TexName = "Hex" + _Name + std::to_string(RanNum);
				}

				Unit->ShaderResources.SetTexture("DiffuseTexture", TexName + ".png");
			}
		}
	}
}

//CollisionReturn HexTile::CheckCol(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
//{
//	_This->Off();
//	Trigger_ = true;
//	return CollisionReturn::Break;
//}
