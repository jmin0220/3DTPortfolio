#include "PreCompile.h"
#include "LJM_PhysXBoxGeometryTest.h"

LJM_PhysXBoxGeometryTest::LJM_PhysXBoxGeometryTest() 
{
}

LJM_PhysXBoxGeometryTest::~LJM_PhysXBoxGeometryTest() 
{
}

void LJM_PhysXBoxGeometryTest::Start()
{
}

void LJM_PhysXBoxGeometryTest::Update(float _DeltaTIme)
{
	// 물리연산 업데이트
	stepPhysics(true);
}

void LJM_PhysXBoxGeometryTest::End()
{
}

void LJM_PhysXBoxGeometryTest::LevelStartEvent()
{
	initPhysics(true);
}

void LJM_PhysXBoxGeometryTest::LevelEndEvent()
{
	cleanupPhysics(true);
}

void LJM_PhysXBoxGeometryTest::initPhysics(bool _interactive)
{
	// PsFoundation.cpp (165) : invalid operation : Foundation object exists already. Only one instance per process can be created.
	// 프로그램 하나에 1개의 Foundation만 생성 가능한가?
	Foundation_ = PxCreateFoundation(PX_PHYSICS_VERSION, DefaultAllocator_, DefaultErrorCallback_);
	Pvd_ = PxCreatePvd(*Foundation_);
	physx::PxPvdTransport* transport = physx::PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	Pvd_->connect(*transport, physx::PxPvdInstrumentationFlag::eALL);

	// Physics생성
	Physics_ = PxCreatePhysics(PX_PHYSICS_VERSION, *Foundation_, physx::PxTolerancesScale(), true, Pvd_);

	// Scene생성
	physx::PxSceneDesc sceneDesc(Physics_->getTolerancesScale());
	sceneDesc.gravity = physx::PxVec3(0.0f, -9.81f, 0.0f);
	DefaultCpuDispatcher_ = physx::PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = DefaultCpuDispatcher_;
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

	// 컨트롤러 매니저 생성(CCTActor 생성을 위해서)
	CtrManager_ = PxCreateControllerManager(*Scene_);

	// 지오메트리가 겹치는 경우 자동으로 복구될 수 있는 모드
	// TODO::일반적인 경우에는 필요하지 않을 수 있음
	CtrManager_->setOverlapRecoveryModule(true);
	CtrManager_->setPreciseSweeps(true);
}

void LJM_PhysXBoxGeometryTest::stepPhysics(bool _Interactive)
{
	// TODO::현재프레임 만큼 수정할 필요가 있을지도
	Scene_->simulate(1.0f / 60.0f);
	Scene_->fetchResults(true);
}

void LJM_PhysXBoxGeometryTest::cleanupPhysics(bool _Interactive)
{
	PX_RELEASE(Scene_);
	PX_RELEASE(DefaultCpuDispatcher_);
	PX_RELEASE(Physics_);
	if (Pvd_)
	{
		physx::PxPvdTransport* transport = Pvd_->getTransport();
		Pvd_->release();	Pvd_ = NULL;
		PX_RELEASE(transport);
	}
	PX_RELEASE(Foundation_);


	// To release all created character controllers at once, either release the manager object itself
	// , or use the following function if you intend to keep using the manager
	if (nullptr != CtrManager_)
	{
		CtrManager_->purgeControllers();
	}
}
