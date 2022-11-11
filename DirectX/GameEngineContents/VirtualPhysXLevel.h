#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// 설명 :
class PlayerActor;
class VirtualPhysXLevel : public GameEngineLevel
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

protected:
	void Start() override;
	void Update(float _DeltaTIme) override;
	void End() override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;

	// 컨트롤 가능한 플레이어
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


	// 클래스 초기화
	void initPhysics(bool _interactive);

	// PhysX Update
	void stepPhysics(bool _Interactive = true);

	// Memory Release
	void cleanupPhysics(bool _Interactive = true);

};

