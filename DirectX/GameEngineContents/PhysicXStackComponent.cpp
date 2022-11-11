#include "PreCompile.h"
#include "PhysicXStackComponent.h"

PhysicXStackComponent::PhysicXStackComponent() 
{
}

PhysicXStackComponent::~PhysicXStackComponent() 
{
	
}

void PhysicXStackComponent::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics, physx::PxVec3 _GeoMetryScale)
{
	// 부모 액터로부터 위치 생성
	physx::PxTransform localTm(ParentActor_->GetTransform().GetWorldPosition().x
		, ParentActor_->GetTransform().GetWorldPosition().y
		, ParentActor_->GetTransform().GetWorldPosition().z);

	// 표면, 마찰 등
	material_ = _physics->createMaterial(0.5f, 0.5f, 0.6f);

	// 충돌체의 형태
	// 충돌체의 크기는 절반의 크기를 설정하므로 실제 Renderer의 스케일은 충돌체의 2배로 설정되어야 함
	shape_ = _physics->createShape(physx::PxBoxGeometry(_GeoMetryScale), *material_);

	// 충돌체의 종류
	dynamic_ = _physics->createRigidDynamic(localTm);
	dynamic_->attachShape(*shape_);
	// 중력이 적용되지 않도록
	dynamic_->setActorFlag(physx::PxActorFlag::eDISABLE_GRAVITY, true);

	// RigidDynamic의 밀도를 설정
	physx::PxRigidBodyExt::updateMassAndInertia(*dynamic_, 10.0f);

	// Scene에 액터 추가
	_Scene->addActor(*dynamic_);
}

void PhysicXStackComponent::Start()
{
	// 부모의 정보의 저장
	ParentActor_ = std::dynamic_pointer_cast<GameEngineActor>(GetParent());

	//ParentActor_ = std::static_pointer_cast<GameEngineActor>(GetParent());

	//std::string tmpStackPosition = "StackPosition >> x : " + std::to_string(ParentActor_->GetTransform().GetWorldPosition().x)
	//									   + " / y : " + std::to_string(ParentActor_->GetTransform().GetWorldPosition().y);
	//GameEngineDebug::OutPutString(tmpStackPosition);
}

void PhysicXStackComponent::Update(float _DeltaTime)
{
	// TODO::디버그용 임시코드
	//if (nullptr == dynamic_)
	//{
	//	return;
	//}

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

void PhysicXStackComponent::End()
{
}
