#include "PreCompile.h"
#include "PhysicXComponent.h"

PhysicXComponent::PhysicXComponent() 
{
}

PhysicXComponent::~PhysicXComponent() 
{
}

void PhysicXComponent::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics, physx::PxVec3 _GeoMetryScale)
{
	// 부모 액터로부터 위치 생성
	physx::PxTransform localTm(ParentActor_->GetTransform().GetWorldPosition().x
		, ParentActor_->GetTransform().GetWorldPosition().y
		, ParentActor_->GetTransform().GetWorldPosition().z);

	// 표면, 마찰 등
	material_ = _physics->createMaterial(0.5f, 0.5f, 0.6f);

	// 충돌체의 형태
	// 충돌체의 크기는 절반의 크기를 설정하므로 실제 Renderer의 스케일은 충돌체의 2배로 설정되어야 함
	//shape_ = _physics->createShape(physx::PxBoxGeometry(2.0f, 2.0f, 2.0f), *material_);

	ParentActor_->GetTransform().SetWorldScale({ 4.0f, 4.0f, 4.0f });

	// 충돌체의 종류
	//dynamic_ = _physics->createRigidDynamic(physx::PxTransform(0.0f, 0.0f, 0.0f));
	dynamic_ = physx::PxCreateDynamic(*_physics, physx::PxTransform(0.0f, 0.0f, 0.0f), physx::PxBoxGeometry(_GeoMetryScale), *material_, 10.0f);
	//dynamic_->attachShape(*shape_);

	// 임시 값
	// 회전값
	dynamic_->setAngularDamping(0.5f);
	// 속도
	dynamic_->setLinearVelocity(physx::PxVec3(0.0f, 0.0f, -200.0f));

	// Scene에 액터 추가
	_Scene->addActor(*dynamic_);
}

void PhysicXComponent::Start()
{
	// 부모의 정보 저장
	ParentActor_ = std::dynamic_pointer_cast<GameEngineActor>(GetParent());
}

void PhysicXComponent::Update(float _DeltaTime)
{
	// PhysX Actor의 상태에 맞춰서 부모의 Transform정보를 갱신
	float4 tmpWorldPos = { dynamic_->getGlobalPose().p.x
	,dynamic_->getGlobalPose().p.y
	, dynamic_->getGlobalPose().p.z };

	float4 tmpWorldRot = { dynamic_->getGlobalPose().q.x
	,dynamic_->getGlobalPose().q.y
	, dynamic_->getGlobalPose().q.z }; 

	ParentActor_->GetTransform().SetWorldPosition(tmpWorldPos);
	ParentActor_->GetTransform().SetWorldRotation(tmpWorldRot);

}

void PhysicXComponent::End()
{
}
