#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/ThirdParty/inc/PhysX/PxConfig.h>
#include <GameEngineCore/ThirdParty/inc/PhysX/PxPhysicsAPI.h>

#include "PhysXTestBox.h"

using namespace physx;

// 설명 :
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
	
	// 물리 결과를 저장할 Actor Vector
	// std::vector<PhysXTestBox*> testBoxVector_;

	float4 CurDynamicPos_;
	
	// Foundation을 생성하는데 필요한 변수
	PxDefaultAllocator		pxDefaultAllocator;
	PxDefaultErrorCallback	pxDefaultErrorCallback;

	PxFoundation* pxFoundation = NULL;

	PxPhysics* pxPhysics = NULL;

	PxDefaultCpuDispatcher* pxDefaultCpuDispatcher = NULL;
	PxScene* pxScene = NULL;

	PxMaterial* pxMaterial = NULL;

	PxPvd* pxPvd = NULL;

	PxReal stackZ = 10.0f;

	// RigidDynamic생성 - 공던지기
	void createDynamic(const PxTransform& t, const PxVec3& velocity = PxVec3(0));
	
	// RigidDynamic으로 벽 쌓기
	void createStack(const PxTransform& t, PxU32 size, PxReal halfExtent);
	
	// 클래스 초기화
	void initPhysics(bool _interactive);

	void stepPhysics(bool _Interactive = true);

	void cleanupPhysics(bool _Interactive = true);
};

