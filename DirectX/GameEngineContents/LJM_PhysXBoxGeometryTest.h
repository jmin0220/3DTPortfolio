#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// ���� :
class LJM_PhysXBoxGeometryTest : public GameEngineLevel
{
public:
	// constrcuter destructer
	LJM_PhysXBoxGeometryTest();
	~LJM_PhysXBoxGeometryTest();

	// delete Function
	LJM_PhysXBoxGeometryTest(const LJM_PhysXBoxGeometryTest& _Other) = delete;
	LJM_PhysXBoxGeometryTest(LJM_PhysXBoxGeometryTest&& _Other) noexcept = delete;
	LJM_PhysXBoxGeometryTest& operator=(const LJM_PhysXBoxGeometryTest& _Other) = delete;
	LJM_PhysXBoxGeometryTest& operator=(LJM_PhysXBoxGeometryTest&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTIme) override;
	void End() override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;

	physx::PxScene* Scene_;
	physx::PxPhysics* Physics_;
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
private:

};

