#pragma once

// ���� :
class ControlledActor;
class PhysXTestPlayer;
class LJM_PhysXPlayerTest : public GameEngineLevel
{
public:
	// constrcuter destructer
	LJM_PhysXPlayerTest();
	~LJM_PhysXPlayerTest();

	// delete Function
	LJM_PhysXPlayerTest(const LJM_PhysXPlayerTest& _Other) = delete;
	LJM_PhysXPlayerTest(LJM_PhysXPlayerTest&& _Other) noexcept = delete;
	LJM_PhysXPlayerTest& operator=(const LJM_PhysXPlayerTest& _Other) = delete;
	LJM_PhysXPlayerTest& operator=(LJM_PhysXPlayerTest&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	physx::PxScene* Scene_;
	physx::PxPhysics* Physics_;
	physx::PxFoundation* pxFoundation = NULL;
	physx::PxControllerManager* CtrManager_;
	physx::PxMaterial* PlaneMat_;

	physx::PxPvd* pxPvd = NULL;
	physx::PxDefaultCpuDispatcher* pxDefaultCpuDispatcher = NULL;

	ControlledActor*			mActor;


	// Foundation�� �����ϴµ� �ʿ��� ����
	physx::PxDefaultAllocator		pxDefaultAllocator;
	physx::PxDefaultErrorCallback	pxDefaultErrorCallback;


	// Ŭ���� �ʱ�ȭ
	void initPhysics(bool _interactive);

	void stepPhysics(bool _Interactive = true);

	void cleanupPhysics(bool _Interactive = true);

private:
	PhysXTestPlayer* Player_;
};

