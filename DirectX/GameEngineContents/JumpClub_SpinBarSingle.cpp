#include "PreCompile.h"
#include "JumpClub_SpinBarSingle.h"
#include "VirtualPhysXLevel.h"

JumpClub_SpinBarSingle::JumpClub_SpinBarSingle() 
	: AccSpeed_(50.0f)
	, AccTime_(5.0f)
{
}

JumpClub_SpinBarSingle::~JumpClub_SpinBarSingle() 
{
}

void JumpClub_SpinBarSingle::Start()
{
	Renderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	Renderer_->SetFBXMesh("SpinBarSingle.FBX", "Texture");

	PhysXSpinBarComponent_ = CreateComponent<PhysXSpinBarComponent>();
}

void JumpClub_SpinBarSingle::Update(float _DeltaTime)
{
	AccTime_ += _DeltaTime;
	// ���ӽ��� 5�� �� ��ŸŸ�Ӹ�ŭ �ӵ� ����(, 5�ʸ��� ��ŸŸ�Ӹ�ŭ �ӵ� ����)
	if (5.0f < AccTime_)
	{
		//AccTime_ = 0.0f;
		AccSpeed_ += _DeltaTime;
	}

	// �ӵ��� 100 �̻��� �Ǹ� 100���� ����
	if (100.0f <= AccSpeed_)
	{
		AccSpeed_ = 100.0f;
	}

	PhysXSpinBarComponent_->SetSpinSpeedRot(AccSpeed_ * _DeltaTime);
}

void JumpClub_SpinBarSingle::End()
{
}

void JumpClub_SpinBarSingle::LevelStartEvent()
{
	CreatePhysXActors(static_cast<VirtualPhysXLevel*>(GetLevel())->GetScene(),
		static_cast<VirtualPhysXLevel*>(GetLevel())->GetPhysics());
}

void JumpClub_SpinBarSingle::LevelEndEvent()
{
}

void JumpClub_SpinBarSingle::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics)
{
	physx::PxCooking* Cooking = static_cast<VirtualPhysXLevel*>(GetLevel())->GetCooking();

	float4 MeshBoundScale = Renderer_->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	PhysXSpinBarComponent_->CreatePhysXActors("SpinBarSingle.fbx", _Scene, _physics, Cooking, true, physx::PxVec3(MeshBoundScale.x, MeshBoundScale.y, MeshBoundScale.z));

	// ȸ���ӵ�
	//PhysXSpinBarComponent_->SetSpinSpeedRot(0.3f);
}
