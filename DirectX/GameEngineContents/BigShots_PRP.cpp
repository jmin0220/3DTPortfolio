#include "PreCompile.h"
#include "BigShots_PRP.h"
#include "VirtualPhysXLevel.h"
#include <GameEngineBase/GameEngineRandom.h>

BigShots_PRP::BigShots_PRP() 
{
}

BigShots_PRP::~BigShots_PRP() 
{
}

void BigShots_PRP::Start()
{
	GameEngineRandom RandomValue_;
	int RandomIntNum = GameEngineRandom::MainRandom.RandomInt(0, 5);
	
	CurPRP_ = static_cast<PRPType>(RandomIntNum);

	Renderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	
	float4 ThrowRot = float4::DegreeToDirection2D(20.0f);

	// 각 PRP 마다 최대 최소 포스 지정 필요
	switch (CurPRP_)
	{
	case PRPType::CONTROLLER:
	{
		FBXName_ = "Controller.FBX";
		int RandomForce = GameEngineRandom::MainRandom.RandomInt(2300000, 2800000);
		//ThrowRot *= 2300000.0f; 최소
		//ThrowRot *= 2800000.0f; 최대
		ThrowRot *= static_cast<float>(RandomForce);
		PRPForce_ = float4(0.0f, ThrowRot.y, ThrowRot.x);
		break;
	}
	case PRPType::MAGNET:
	{
		FBXName_ = "Magnet.FBX";
		int RandomForce = GameEngineRandom::MainRandom.RandomInt(780000, 920000);
		//ThrowRot *= 780000.0f; 최소
		//ThrowRot *= 920000.0f; 최대
		ThrowRot *= static_cast<float>(RandomForce);
		PRPForce_ = float4(0.0f, ThrowRot.y, ThrowRot.x);
		break;
	}
	case PRPType::NUT:
	{
		FBXName_ = "Nut.FBX";
		int RandomForce = GameEngineRandom::MainRandom.RandomInt(188000, 220000);
		//ThrowRot *= 188000.0f; 최소
		//ThrowRot *= 220000.0f; 최대
		ThrowRot *= static_cast<float>(RandomForce);
		PRPForce_ = float4(0.0f, ThrowRot.y, ThrowRot.x);
		break;
	}
	case PRPType::PLANET:
	{
		FBXName_ = "Planet.FBX";
		int RandomForce = GameEngineRandom::MainRandom.RandomInt(3200000, 3800000);
		//ThrowRot *= 3200000.0f; 최소
		//ThrowRot *= 3800000.0f; 최대
		ThrowRot *= static_cast<float>(RandomForce);
		PRPForce_ = float4(0.0f, ThrowRot.y, ThrowRot.x);
		break;
	}
	case PRPType::STAR:
	{
		FBXName_ = "Star.FBX";
		int RandomForce = GameEngineRandom::MainRandom.RandomInt(165000, 195000);
		//ThrowRot *= 165000.0f; 최소
		//ThrowRot *= 195000.0f; 최대
		ThrowRot *= static_cast<float>(RandomForce);
		PRPForce_ = float4(0.0f, ThrowRot.y, ThrowRot.x);
		break;
	}
	case PRPType::TETRAPOD:
	{
		FBXName_ = "Tetrapod.FBX";
		int RandomForce = GameEngineRandom::MainRandom.RandomInt(1820000, 2180000);
		//ThrowRot *= 1820000.0f; 최소
		//ThrowRot *= 2180000.0f; 최대
		ThrowRot *= static_cast<float>(RandomForce);
		PRPForce_ = float4(0.0f, ThrowRot.y, ThrowRot.x);
		break;
	}
	default:
		break;
	}

	Renderer_->SetFBXMesh(FBXName_, "Texture");
	PhysXConvexDynamicComponent_ = CreateComponent< PhysXConvexDynamicComponent>();

	Death(20.0f);
}

void BigShots_PRP::Update(float _DeltaTime)
{
}

void BigShots_PRP::End()
{
}

void BigShots_PRP::LevelStartEvent()
{

}

void BigShots_PRP::LevelEndEvent()
{
}

void BigShots_PRP::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics)
{
	physx::PxCooking* Cooking = static_cast<VirtualPhysXLevel*>(GetLevel())->GetCooking();
	// Tip..3번째 매개변수인 GeometryScale은 액터가 가질 물리강체의 크기
	float4 MeshBoundScale = Renderer_->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	PhysXConvexDynamicComponent_->CreatePhysXActors(FBXName_, _Scene, _physics, Cooking, false, physx::PxVec3(MeshBoundScale.x, MeshBoundScale.y, MeshBoundScale.z));
	PhysXConvexDynamicComponent_->AddForce(PRPForce_);
	
	float RandomRot = GameEngineRandom::MainRandom.RandomFloat(-10.0f, 10.0f);
	PhysXConvexDynamicComponent_->AddAngularVelocity(float4(RandomRot, RandomRot, RandomRot));

	GameEngineDebug::OutPutString(FBXName_ + " Mass Value >> " +std::to_string(static_cast<float>(PhysXConvexDynamicComponent_->GetMass())));
}

void BigShots_PRP::CreatePhysX()
{
	CreatePhysXActors(static_cast<VirtualPhysXLevel*>(GetLevel())->GetScene(),
		static_cast<VirtualPhysXLevel*>(GetLevel())->GetPhysics());
}