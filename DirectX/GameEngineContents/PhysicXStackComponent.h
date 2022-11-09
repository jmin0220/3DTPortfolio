#pragma once

// 설명 :
class PhysicXStackComponent : public GameEngineComponent
{
public:
	// constrcuter destructer
	PhysicXStackComponent();
	~PhysicXStackComponent();

	// delete Function
	PhysicXStackComponent(const PhysicXStackComponent& _Other) = delete;
	PhysicXStackComponent(PhysicXStackComponent&& _Other) noexcept = delete;
	PhysicXStackComponent& operator=(const PhysicXStackComponent& _Other) = delete;
	PhysicXStackComponent& operator=(PhysicXStackComponent&& _Other) noexcept = delete;

	void CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics, physx::PxVec3 _GeoMetryScale = physx::PxVec3(2.0f));

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	// Phys액터 생성에 필요한 정보
	physx::PxPhysics* physics_;
	physx::PxScene* scene_;

	physx::PxMaterial* material_;
	physx::PxShape* shape_;
	physx::PxRigidDynamic* dynamic_;

	// 이 컴포넌트를 가지고 있는 Parent에 대한 정보
	GameEngineActor* ParentActor_;

};

