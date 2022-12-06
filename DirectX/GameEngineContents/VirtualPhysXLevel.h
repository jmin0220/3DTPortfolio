#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "PhysXCommonFunc.h"

// callback 이벤트를 재정의할 클래스
class CustomSimulationEventCallback : public physx::PxSimulationEventCallback
{
public:
	void SetPlayer(physx::PxRigidDynamic* _Dynamic)
	{
		PlayerDynamic_ = _Dynamic;
	}

	void onContact(const physx::PxContactPairHeader& pairHeader, const physx::PxContactPair* pairs, physx::PxU32 nbPairs) override {};

	void onConstraintBreak(physx::PxConstraintInfo* constraints, physx::PxU32 count) override {};
	void onWake(physx::PxActor** actors, physx::PxU32 count) override {};
	void onSleep(physx::PxActor** actors, physx::PxU32 count) override {};
	void onTrigger(physx::PxTriggerPair* pairs, physx::PxU32 count) override;
	void onAdvance(const physx::PxRigidBody* const* bodyBuffer, const physx::PxTransform* poseBuffer, const physx::PxU32 count) override {};

private:
	physx::PxRigidDynamic* PlayerDynamic_ = nullptr;
};


// 설명 :
class PlayerActor;
class VirtualPhysXLevel : public GameEngineLevel, public PhysXCommonFunc
{
public:
	// constrcuter destructer
	VirtualPhysXLevel();
	~VirtualPhysXLevel();

	// delete Function
	VirtualPhysXLevel(const VirtualPhysXLevel& _Other) = delete;
	VirtualPhysXLevel(VirtualPhysXLevel&& _Other) noexcept = delete;
	VirtualPhysXLevel& operator=(const VirtualPhysXLevel& _Other) = delete;
	VirtualPhysXLevel& operator=(VirtualPhysXLevel&& _Other) noexcept = delete;

	inline physx::PxScene* GetScene()
	{
		return Scene_;
	}

	inline physx::PxPhysics* GetPhysics()
	{
		return Physics_;
	}

	inline physx::PxCooking* GetCooking()
	{
		return Cooking_;
	}

	inline void SetSimulationPlayer(physx::PxRigidDynamic* _PlayerDynamic)
	{
		SimulationEventCallback_->SetPlayer(_PlayerDynamic);
	}

protected:
	void Start() override;
	void Update(float _DeltaTIme) override;
	void End() override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;

	std::shared_ptr<PlayerActor> Player_;
private:
	static physx::PxScene* Scene_;
	static physx::PxPhysics* Physics_;
	physx::PxFoundation* Foundation_ = NULL;
	physx::PxControllerManager* CtrManager_;

	physx::PxPvd* Pvd_ = NULL;
	physx::PxDefaultCpuDispatcher* DefaultCpuDispatcher_ = NULL;

	// Foundation을 생성하는데 필요한 변수
	physx::PxDefaultAllocator		DefaultAllocator_;
	physx::PxDefaultErrorCallback	DefaultErrorCallback_;
	physx::PxCooking* Cooking_;

	CustomSimulationEventCallback* SimulationEventCallback_;

	// 클래스 초기화
	void initPhysics(bool _interactive);

	// PhysX Update
	void stepPhysics(bool _Interactive = true);

	// Memory Release
	void cleanupPhysics(bool _Interactive = true);
};