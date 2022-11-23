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

	void CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics, physx::PxVec3 _GeoMetryScale = physx::PxVec3(2.0f), float4 _GeoMetryRot = {0.0f});

	inline void ReleasePhysX()
	{
		if (true == rigidStatic_->isReleasable())
		{
			rigidStatic_->release();
			ParentActor_.lock()->Death();
		}
	}

	inline void SetPositionSetFromParentFlag(bool _Flag)
	{
		PositionSetFromParentFlag_ = _Flag;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	// Phys액터 생성에 필요한 정보
	physx::PxPhysics* physics_;
	physx::PxScene* scene_;

	physx::PxMaterial* material_;
	physx::PxShape* shape_;
	physx::PxRigidStatic* rigidDynamic_;

	// 이 컴포넌트를 가지고 있는 Parent에 대한 정보
	std::weak_ptr<GameEngineActor> ParentActor_;

	bool PositionSetFromParentFlag_;
};

