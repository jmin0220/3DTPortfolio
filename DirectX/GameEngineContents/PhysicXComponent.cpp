#include "PreCompile.h"
#include "PhysicXComponent.h"

PhysicXComponent::PhysicXComponent() 
{
}

PhysicXComponent::~PhysicXComponent() 
{
}

void PhysicXComponent::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics)
{
	//physx::PxTransform localTm(GetLevel()->GetMainCameraActor()->GetTransform().GetWorldPosition().x
	//	, GetLevel()->GetMainCameraActor()->GetTransform().GetWorldPosition().y
	//	, GetLevel()->GetMainCameraActor()->GetTransform().GetWorldPosition().z);

	//physx::PxVec3 tmpVec3(GetLevel()->GetMainCameraActorTransform().GetLocalRotation().x
	//	, GetLevel()->GetMainCameraActorTransform().GetLocalRotation().y
	//	, 1.0f);

	physx::PxTransform localTm(0.0f, 0.0f, 100.0f);
	physx::PxVec3 tmpVec3(0.0f, 0.0f, 1.0f);

	// ǥ��, ���� ��
	material_ = _physics->createMaterial(0.5f, 0.5f, 0.6f);
	// �浹ü�� ����
	// �浹ü�� ũ��� ������ ũ�⸦ �����ϹǷ� ���� Renderer�� �������� �浹ü�� 2��� �����Ǿ�� ��
	shape_ = _physics->createShape(physx::PxBoxGeometry(2.0f, 2.0f, 2.0f), *material_);

	static_cast<GameEngineActor*>(GetRoot())->GetTransform().SetWorldScale({ 4.0f, 4.0f, 4.0f });

	// �浹ü�� ����
	dynamic_ = _physics->createRigidDynamic(localTm);
	dynamic_->attachShape(*shape_);

	// �ӽ� ��
	// ȸ����
	dynamic_->setAngularDamping(0.5f);
	// �ӵ�
	dynamic_->setLinearVelocity(tmpVec3 * 200.0f);

	// Scene�� ���� �߰�
	_Scene->addActor(*dynamic_);
}

void PhysicXComponent::Start()
{
}

void PhysicXComponent::Update(float _DeltaTime)
{
	// PhysX Actor�� ���¿� ���缭 Transform������ ����
	float4 tmpWorldPos = { dynamic_->getGlobalPose().p.x
	,dynamic_->getGlobalPose().p.y
	, dynamic_->getGlobalPose().p.z };

	float4 tmpWorldRot = { dynamic_->getGlobalPose().q.x
	,dynamic_->getGlobalPose().q.y
	, dynamic_->getGlobalPose().q.z };

	static_cast<GameEngineActor*>(GetRoot())->GetTransform().SetWorldPosition(tmpWorldPos);
	static_cast<GameEngineActor*>(GetRoot())->GetTransform().SetWorldRotation(tmpWorldRot);

	//std::string tmpWorldPositionString = "NowDynamicPos >> x : " + std::to_string(tmpWorldPos.x) + " / y : " + std::to_string(tmpWorldPos.y) + " / z : " + std::to_string(tmpWorldPos.z);
	//GameEngineDebug::OutPutString(tmpWorldPositionString);
}

void PhysicXComponent::End()
{
}
