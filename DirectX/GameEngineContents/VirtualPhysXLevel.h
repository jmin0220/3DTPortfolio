#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// ���� :
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

	// ��Ʈ�� ������ �÷��̾�
	std::shared_ptr<PlayerActor> Player_;

private:
	static physx::PxScene* Scene_;
	static physx::PxPhysics* Physics_;
	physx::PxFoundation* Foundation_ = NULL;
	physx::PxControllerManager* CtrManager_;

	physx::PxPvd* Pvd_ = NULL;
	physx::PxDefaultCpuDispatcher* DefaultCpuDispatcher_ = NULL;

	// Foundation�� �����ϴµ� �ʿ��� ����
	physx::PxDefaultAllocator		DefaultAllocator_;
	physx::PxDefaultErrorCallback	DefaultErrorCallback_;


	// Ŭ���� �ʱ�ȭ
	void initPhysics(bool _interactive);

	// PhysX Update
	void stepPhysics(bool _Interactive = true);

	// Memory Release
	void cleanupPhysics(bool _Interactive = true);

};

