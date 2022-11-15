#pragma once

// ���� :
class PhysXPendulaComponent : public GameEngineComponent
{
public:
	// constrcuter destructer
	PhysXPendulaComponent();
	~PhysXPendulaComponent();

	// delete Function
	PhysXPendulaComponent(const PhysXPendulaComponent& _Other) = delete;
	PhysXPendulaComponent(PhysXPendulaComponent&& _Other) noexcept = delete;
	PhysXPendulaComponent& operator=(const PhysXPendulaComponent& _Other) = delete;
	PhysXPendulaComponent& operator=(PhysXPendulaComponent&& _Other) noexcept = delete;

	void CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics, physx::PxVec3 _GeoMetryScale = physx::PxVec3(2.0f), float4 _GeoMetryRot = { 0.0f });

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	// Phys���� ������ �ʿ��� ����
	physx::PxPhysics* physics_;
	physx::PxScene* scene_;

	physx::PxMaterial* material_;
	physx::PxShape* shape_;
	physx::PxRigidDynamic* dynamic_;
	physx::PxRigidStatic* rigidStatic_;

	// �� ������Ʈ�� ������ �ִ� Parent�� ���� ����
	std::weak_ptr<GameEngineActor> ParentActor_;
};

