#pragma once


// 설명 :
class PhysicXComponent : public GameEngineComponent
{
public:
	// constrcuter destructer
	PhysicXComponent();
	~PhysicXComponent();

	// delete Function
	PhysicXComponent(const PhysicXComponent& _Other) = delete;
	PhysicXComponent(PhysicXComponent&& _Other) noexcept = delete;
	PhysicXComponent& operator=(const PhysicXComponent& _Other) = delete;
	PhysicXComponent& operator=(PhysicXComponent&& _Other) noexcept = delete;

	void CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics, physx::PxVec3 _GeoMetryScale = physx::PxVec3(2.0f));

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	physx::PxMaterial* material_;
	physx::PxShape* shape_;
	physx::PxRigidDynamic* dynamic_;

	// 이 컴포넌트를 가지고 있는 Parent에 대한 정보
	GameEngineActor* ParentActor_;
};

