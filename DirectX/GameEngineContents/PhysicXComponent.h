#pragma once

// ���� :
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

	void CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	// Phys���� ������ �ʿ��� ����
	physx::PxPhysics* physics_;
	physx::PxScene* scene_;

	physx::PxMaterial* material_;
	physx::PxShape* shape_;
	physx::PxRigidDynamic* dynamic_;

};

