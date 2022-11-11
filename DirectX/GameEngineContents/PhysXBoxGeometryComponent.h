#pragma once
#include <GameEngineCore/GameEngineComponent.h>

// 설명 :
class PhysXBoxGeometryComponent : public GameEngineComponent
{
public:
	// constrcuter destructer
	PhysXBoxGeometryComponent();
	~PhysXBoxGeometryComponent();

	// delete Function
	PhysXBoxGeometryComponent(const PhysXBoxGeometryComponent& _Other) = delete;
	PhysXBoxGeometryComponent(PhysXBoxGeometryComponent&& _Other) noexcept = delete;
	PhysXBoxGeometryComponent& operator=(const PhysXBoxGeometryComponent& _Other) = delete;
	PhysXBoxGeometryComponent& operator=(PhysXBoxGeometryComponent&& _Other) noexcept = delete;

	void CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	physx::PxMaterial* material_;
	physx::PxShape* shape_;
	physx::PxRigidDynamic* dynamic_;

	// 이 컴포넌트를 가지고 있는 Parent에 대한 정보
	std::shared_ptr<GameEngineActor> ParentActor_;

};

