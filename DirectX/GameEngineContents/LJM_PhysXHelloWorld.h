#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/ThirdParty/inc/PhysX/PxConfig.h>
#include <GameEngineCore/ThirdParty/inc/PhysX/PxPhysicsAPI.h>

#include "PhysXTestBox.h"

using namespace physx;

// ���� :
class LJM_PhysXHelloWorld : public GameEngineLevel
{
public:
	// constrcuter destructer
	LJM_PhysXHelloWorld();
	~LJM_PhysXHelloWorld();

	// delete Function
	LJM_PhysXHelloWorld(const LJM_PhysXHelloWorld& _Other) = delete;
	LJM_PhysXHelloWorld(LJM_PhysXHelloWorld&& _Other) noexcept = delete;
	LJM_PhysXHelloWorld& operator=(const LJM_PhysXHelloWorld& _Other) = delete;
	LJM_PhysXHelloWorld& operator=(LJM_PhysXHelloWorld&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;
	
	// ���� ����� ������ Actor Vector
	// std::vector<PhysXTestBox*> testBoxVector_;

	float4 CurDynamicPos_;
	
	// Foundation�� �����ϴµ� �ʿ��� ����
	PxDefaultAllocator		pxDefaultAllocator;
	PxDefaultErrorCallback	pxDefaultErrorCallback;

	PxFoundation* pxFoundation = NULL;

	PxPhysics* pxPhysics = NULL;

	PxDefaultCpuDispatcher* pxDefaultCpuDispatcher = NULL;
	PxScene* pxScene = NULL;

	PxMaterial* pxMaterial = NULL;

	PxPvd* pxPvd = NULL;

	PxReal stackZ = 10.0f;

	// RigidDynamic���� - ��������
	void createDynamic(const PxTransform& t, const PxVec3& velocity = PxVec3(0));
	
	// RigidDynamic���� �� �ױ�
	void createStack(const PxTransform& t, PxU32 size, PxReal halfExtent);
	
	// Ŭ���� �ʱ�ȭ
	void initPhysics(bool _interactive);

	void stepPhysics(bool _Interactive = true);

	void cleanupPhysics(bool _Interactive = true);
};

