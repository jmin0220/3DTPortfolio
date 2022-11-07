#include "PreCompile.h"
#include "LJM_PhysXPlayerTest.h"
#include "PhysXTestPlayer.h"

#include "PhysXTestBox.h"
#include "PhysXTestStackBox.h"
#include <GameEngineCore/ThirdParty/inc/PhysX/PxConfig.h>
#include <GameEngineCore/ThirdParty/inc/PhysX/PxPhysicsAPI.h>

//#include <GameEngineCore/ThirdParty/inc/PhysX/PxConfig.h>
//#include <GameEngineCore/ThirdParty/inc/PhysX/PxPhysicsAPI.h>
//#include <PhysX/characterkinematic/PxControllerManager.h>
#include <PhysXSDKSnippets/SnippetPVD.h>

LJM_PhysXPlayerTest::LJM_PhysXPlayerTest() 
{
}

LJM_PhysXPlayerTest::~LJM_PhysXPlayerTest() 
{
	// To release all created character controllers at once, either release the manager object itself
	// , or use the following function if you intend to keep using the manager
	if (nullptr != CtrManager_)
	{
		CtrManager_->purgeControllers();
	}
}

void LJM_PhysXPlayerTest::Start()
{
	Player_ = CreateActor<PhysXTestPlayer>();

	GameEngineInput::GetInst()->CreateKey("CreateBall", VK_SPACE);
	GameEngineInput::GetInst()->CreateKey("CreateStack", '1');
}

void LJM_PhysXPlayerTest::Update(float _DeltaTime)
{
	// 물리연산 업데이트
	stepPhysics(true);


	if (true == GameEngineInput::GetInst()->IsDown("CreateBall"))
	{
		physx::PxTransform tmpTransform(GetMainCameraActor()->GetTransform().GetWorldPosition().x
			, GetMainCameraActor()->GetTransform().GetWorldPosition().y
			, GetMainCameraActor()->GetTransform().GetWorldPosition().z);

		physx::PxVec3 tmpVec3(GetMainCameraActorTransform().GetLocalRotation().x
			, GetMainCameraActorTransform().GetLocalRotation().y
			, 1.0f);

		createDynamic(tmpTransform, tmpVec3 * 200.0f);
	}

	if (true == GameEngineInput::GetInst()->IsDown("CreateStack"))
	{
		createStack(physx::PxTransform(physx::PxVec3(0, 0, stackZ -= 10.0f)), 10, 2.0f);
	}
}

void LJM_PhysXPlayerTest::End()
{
}

void LJM_PhysXPlayerTest::LevelStartEvent()
{
	initPhysics(true);
}

void LJM_PhysXPlayerTest::initPhysics(bool _interactive)
{
	// PsFoundation.cpp (165) : invalid operation : Foundation object exists already. Only one instance per process can be created.
	// 프로그램 하나에 1개의 Foundation만 생성 가능한가?
	pxFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, pxDefaultAllocator, pxDefaultErrorCallback);
	pxPvd = PxCreatePvd(*pxFoundation);
	physx::PxPvdTransport* transport = physx::PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	pxPvd->connect(*transport, physx::PxPvdInstrumentationFlag::eALL);

	// Physics생성
	Physics_ = PxCreatePhysics(PX_PHYSICS_VERSION, *pxFoundation, physx::PxTolerancesScale(), true, pxPvd);

	// Scene생성
	physx::PxSceneDesc sceneDesc(Physics_->getTolerancesScale());
	sceneDesc.gravity = physx::PxVec3(0.0f, -9.81f, 0.0f);
	pxDefaultCpuDispatcher = physx::PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = pxDefaultCpuDispatcher;
	sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;
	Scene_ = Physics_->createScene(sceneDesc);

	// PVD연결
	physx::PxPvdSceneClient* pvdClient = Scene_->getScenePvdClient();
	if (pvdClient)
	{
		pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
		pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
		pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
	}

	// 임시발판 생성
	PlaneMat_ = Physics_->createMaterial(0.5f, 0.5f, 0.6f);
	physx::PxRigidStatic* groundPlane = physx::PxCreatePlane(*Physics_, physx::PxPlane(0, 1, 0, 0), *PlaneMat_);
	Scene_->addActor(*groundPlane);

	CtrManager_ = PxCreateControllerManager(*Scene_);

	// 지오메트리가 겹치는 경우 자동으로 복구될 수 있는 모드
	// TODO::일반적인 경우에는 필요하지 않을 수 있음
	CtrManager_->setOverlapRecoveryModule(true);
	CtrManager_->setPreciseSweeps(true);

	Player_->CreatePhysXActors(Scene_, Physics_, CtrManager_);
}

void LJM_PhysXPlayerTest::stepPhysics(bool _Interactive)
{
	Scene_->simulate(1.0f / 60.0f);
	Scene_->fetchResults(true);
}

void LJM_PhysXPlayerTest::cleanupPhysics(bool _Interactive)
{
}



void LJM_PhysXPlayerTest::createDynamic(const physx::PxTransform& t, const physx::PxVec3& velocity)
{
	PhysXTestBox* tmpTestBox = CreateActor<PhysXTestBox>();
	tmpTestBox->GetTransform().SetWorldPosition({ 0.0f, 100.0f, 2000.0f });
	tmpTestBox->CreatePhysXActors(Scene_, Physics_);
}

void LJM_PhysXPlayerTest::createStack(const physx::PxTransform& t, physx::PxU32 size, physx::PxReal halfExtent)
{
	// 1스택에 Actor가 55개씩 생성됨
	for (physx::PxU32 i = 0; i < size; i++)
	{
		for (physx::PxU32 j = 0; j < size - i; j++)
		{

			PhysXTestStackBox* tmpTestStackBox = CreateActor<PhysXTestStackBox>();
			// 액터의 포지션을 먼저 조정한 후에 RigidDynamic을 생성★
			tmpTestStackBox->GetTransform().SetWorldPosition({ (j * 2.0f - (size - i)) * halfExtent, (i * 2.0f + 1.0f) * halfExtent, t.p.z });
			tmpTestStackBox->CreatePhysXActors(Scene_, Physics_);
		}
	}
	//shape->release();
}