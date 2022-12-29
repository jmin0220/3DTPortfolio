#include "PreCompile.h"
#include "BigShots_PRP.h"
#include "VirtualPhysXLevel.h"
#include <GameEngineBase/GameEngineRandom.h>

BigShots_PRP::BigShots_PRP()
	: SettingRot_(float4::ZERO)
	, SettingForce_(0)
{
}

BigShots_PRP::~BigShots_PRP() 
{
}

void BigShots_PRP::Start()
{
	//GameEngineRandom RandomValue_;
	//int RandomIntNum = GameEngineRandom::MainRandom.RandomInt(0, 5);
	
	//CurPRP_ = static_cast<PRPType>(RandomIntNum);

	Renderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	
	PhysXConvexDynamicComponent_ = CreateComponent< PhysXConvexDynamicComponent>();
	//PhysXConvexDynamicComponent_->SetRestitution(0.3f);

}

void BigShots_PRP::Update(float _DeltaTime)
{
	if (this->GetTransform().GetWorldPosition().y < -80.0f)
	{
		this->Death();
		PhysXConvexDynamicComponent_->ReleaseRigidBody();

		return;
	}
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
	
	PhysXConvexDynamicComponent_->SetPhysxMaterial(FLOOR_STATICFRICTION, FLOOR_DYNAMICFRICTION, 0.3f);
	PhysXConvexDynamicComponent_->SetObjectObstacle();
	
	// Tip..3��° �Ű������� GeometryScale�� ���Ͱ� ���� ������ü�� ũ��
	float4 MeshBoundScale = Renderer_->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	PhysXConvexDynamicComponent_->CreatePhysXActors(FBXName_, _Scene, _physics, Cooking, false, physx::PxVec3(MeshBoundScale.x, MeshBoundScale.y, MeshBoundScale.z));


	// ���⼭ ���� ������
	// FBXName_�� �´� �е�
	float tmpMass = static_cast<float>(PhysXConvexDynamicComponent_->GetMass());

	// �� * �е�
	// BigShots_Cannon::SetShootSetting()���κ��� SettingForce_�� �Է¹���
	int RandomForce = SettingForce_ * tmpMass;

	// �е��� ���� y,z�� �̵� �߰�
	PhysXConvexDynamicComponent_->SetUpdateForce(physx::PxVec3(0.0f, -300.0f * tmpMass, 700.0f * tmpMass));
	// �������� ���� ����
	float4 ThrowRot = float4::DegreeToDirection2D(3.0f);
	// ������ ���Ͱ� * (�� * �е�)
	ThrowRot *= static_cast<float>(RandomForce);
	PRPForce_ = float4(0.0f, ThrowRot.y, ThrowRot.x);
	
	// ���������� ������ prp�� ���� * �� * �е��� ��ġ�� ������
	PhysXConvexDynamicComponent_->AddForce(PRPForce_);
	
	// �������� PRP�� ȸ�� �� �ο�->������ ���� �� ����
	//if (GameEngineRandom::MainRandom.RandomInt(0, 1))
	//{
	//	RandomRot_ = GameEngineRandom::MainRandom.RandomFloat(4.0f, 9.0f);
	//}
	//else
	//{
	//	RandomRot_ = GameEngineRandom::MainRandom.RandomFloat(-9.0f, -4.0f);
	//}


	PhysXConvexDynamicComponent_->AddAngularVelocity(float4(SettingRot_.x, SettingRot_.y, SettingRot_.z));

	//GameEngineDebug::OutPutString(FBXName_ + " Mass Value >> " +std::to_string(static_cast<float>(PhysXConvexDynamicComponent_->GetMass())));
}

void BigShots_PRP::CreatePhysX()
{
	CreatePhysXActors(static_cast<VirtualPhysXLevel*>(GetLevel())->GetScene(),
		static_cast<VirtualPhysXLevel*>(GetLevel())->GetPhysics());
}

void BigShots_PRP::InitPRP(float4 _ShootSetting)
{
	SettingRot_.x = _ShootSetting.x;
	SettingRot_.y = _ShootSetting.y;
	SettingRot_.z = _ShootSetting.z;
	SettingForce_ = _ShootSetting.w;

	// �Ŀ��� ����������
	int EnumIdx = static_cast<int>(SettingForce_) % static_cast<int>(PRPType::MAX);
	
	CurPRP_ = static_cast<PRPType>(EnumIdx);

	switch (CurPRP_)
	{
	case PRPType::CONTROLLER:
	{
		FBXName_ = "Controller.FBX";
		break;
	}
	case PRPType::MAGNET:
	{
		FBXName_ = "Magnet.FBX";
		PhysXConvexDynamicComponent_->SetRestitution(0.8f);
		break;
	}
	case PRPType::NUT:
	{
		FBXName_ = "Nut.FBX";
		break;
	}
	case PRPType::PLANET:
	{
		FBXName_ = "Planet.FBX";
		break;
	}
	case PRPType::STAR:
	{
		FBXName_ = "Star.FBX";
		break;
	}
	case PRPType::TETRAPOD:
	{
		FBXName_ = "Tetrapod.FBX";
		break;
	}
	default:
		break;
	}

	Renderer_->SetFBXMesh(FBXName_, "Texture");
}