#include "PreCompile.h"
#include "HoopsScoreRing.h"
#include "VirtualPhysXLevel.h"
#include "GameEngineBase/GameEngineRandom.h"

HoopsScoreRing::HoopsScoreRing()	:	
	IsCol_(false),
	Flag_(false),
	Timer_(3.0f)
{
}

HoopsScoreRing::~HoopsScoreRing()
{
}

void HoopsScoreRing::Start()
{
	Renderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	Renderer_->SetFBXMesh("HoopsScoreRing2.FBX", "CustomDefferedColor");

	//PhysXConvexGeometry_ = CreateComponent<PhysXConvexDynamicComponent>();

	PhysXTriGeometry_ = CreateComponent<PhysXTriMeshGeometryComponent>();

	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->GetTransform().SetLocalScale({ 10.0f,10.0f,1.0f, });
	Collision_->ChangeOrder(CollisionGroup::Trigger);

	float Rot = GameEngineRandom::MainRandom.RandomFloat(0, 360.0f);

	Dir_ = GameEngineRandom::MainRandom.RandomInt(0, 1);

	GetTransform().SetLocalRotate({ 0,Rot ,0 });
}

void HoopsScoreRing::Update(float _DeltaTime)
{
	if (IsCol_ == true)
	{
		Timer_ -= _DeltaTime;
		if (Timer_ <= 0)
		{
			if (GetTransform().GetWorldPosition().y <= 200.0f)
			{
				GetTransform().SetWorldUpMove(50.0f, _DeltaTime);
			}
			else
			{
				Renderer_->Off();
				Collision_->On();
				IsCol_ = false;
				Timer_ = 3.0f;
			}
		}
		return;
	}

	if (Flag_ == true)
	{

		GetTransform().SetWorldDownMove(50.0f, _DeltaTime);

		if (GetTransform().GetWorldPosition().y <= PrevPos.y)
		{
			Flag_ = false;
		}
	}

	if (Dir_ == 0)
	{
		GetTransform().SetLocalRotate({ 0, 7.0f * _DeltaTime  ,0 });
	}
	else
	{
		GetTransform().SetLocalRotate({ 0, -7.0f * _DeltaTime  ,0 });
	}
	Collision_->IsCollision(CollisionType::CT_OBB, CollisionGroup::PlayerCheck, CollisionType::CT_OBB,
		std::bind(&HoopsScoreRing::CheckCollision, this, std::placeholders::_1, std::placeholders::_2));
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
	PhysXTriGeometry_->SetPhysxMaterial(0, 0, 0);
	PhysXTriGeometry_->CreatePhysXActors("HoopsScoreRing2.FBX", _Scene, _physics, Cooking, true, physx::PxVec3(MeshBoundScale.x, MeshBoundScale.y, MeshBoundScale.z), 0.0f);
	PhysXTriGeometry_->SetPositionSetFromParentFlag(true);
}

CollisionReturn HoopsScoreRing::CheckCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{
	_This->Off();
	IsCol_ = true;
	//스코어증가



	return CollisionReturn::Break;
}

