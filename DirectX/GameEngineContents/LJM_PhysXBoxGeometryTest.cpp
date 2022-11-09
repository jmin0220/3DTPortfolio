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
	// �������� ������Ʈ
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
	// ���α׷� �ϳ��� 1���� Foundation�� ���� �����Ѱ�?
	Foundation_ = PxCreateFoundation(PX_PHYSICS_VERSION, DefaultAllocator_, DefaultErrorCallback_);
	Pvd_ = PxCreatePvd(*Foundation_);
	physx::PxPvdTransport* transport = physx::PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	Pvd_->connect(*transport, physx::PxPvdInstrumentationFlag::eALL);

	// Physics����
	Physics_ = PxCreatePhysics(PX_PHYSICS_VERSION, *Foundation_, physx::PxTolerancesScale(), true, Pvd_);

	// Scene����
	physx::PxSceneDesc sceneDesc(Physics_->getTolerancesScale());
	sceneDesc.gravity = physx::PxVec3(0.0f, -9.81f, 0.0f);
	DefaultCpuDispatcher_ = physx::PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = DefaultCpuDispatcher_;
	sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;
	Scene_ = Physics_->createScene(sceneDesc);

	// PVD����
	physx::PxPvdSceneClient* pvdClient = Scene_->getScenePvdClient();
	if (pvdClient)
	{
		pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
		pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
		pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
	}

	// ��Ʈ�ѷ� �Ŵ��� ����(CCTActor ������ ���ؼ�)
	CtrManager_ = PxCreateControllerManager(*Scene_);

	// ������Ʈ���� ��ġ�� ��� �ڵ����� ������ �� �ִ� ���
	// TODO::�Ϲ����� ��쿡�� �ʿ����� ���� �� ����
	CtrManager_->setOverlapRecoveryModule(true);
	CtrManager_->setPreciseSweeps(true);
}

void LJM_PhysXBoxGeometryTest::stepPhysics(bool _Interactive)
{
	// TODO::���������� ��ŭ ������ �ʿ䰡 ��������
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
