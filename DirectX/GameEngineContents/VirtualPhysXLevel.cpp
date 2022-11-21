#include "PreCompile.h"
#include "VirtualPhysXLevel.h"
#include "PlayerActor.h"


physx::PxScene* VirtualPhysXLevel::Scene_ = nullptr;
physx::PxPhysics* VirtualPhysXLevel::Physics_ = nullptr;

VirtualPhysXLevel::VirtualPhysXLevel() 
	: Player_(nullptr)
	, CtrManager_(nullptr)
{
}

VirtualPhysXLevel::~VirtualPhysXLevel() 
{
	cleanupPhysics(true);
}


void VirtualPhysXLevel::Start()
{
}

void VirtualPhysXLevel::Update(float _DeltaTIme)
{
	// �������� ������Ʈ
	stepPhysics(true);
}

void VirtualPhysXLevel::End()
{
}

void VirtualPhysXLevel::LevelStartEvent()
{
	initPhysics(true);
}

void VirtualPhysXLevel::LevelEndEvent()
{
	cleanupPhysics(true);
}


// PhysX��� �ʱ�ȭ
void VirtualPhysXLevel::initPhysics(bool _interactive)
{
	if (Scene_ != nullptr || Physics_ != nullptr)
	{
		return;
	}

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
	sceneDesc.gravity = physx::PxVec3(0.0f, PHYSX_GRAVITY, 0.0f);
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

	//// ��Ʈ�ѷ� �Ŵ��� ����(CCTActor ������ ���ؼ�)
	//CtrManager_ = PxCreateControllerManager(*Scene_);

	//// ������Ʈ���� ��ġ�� ��� �ڵ����� ������ �� �ִ� ���
	//// TODO::�Ϲ����� ��쿡�� �ʿ����� ���� �� ����
	//CtrManager_->setOverlapRecoveryModule(true);
	//CtrManager_->setPreciseSweeps(true);

	// �÷��̾ �����ϸ� ����
	if (nullptr != Player_)
	{
		Player_->CreatePhysXActors(Scene_, Physics_);
	}

	Cooking_ = PxCreateCooking(PX_PHYSICS_VERSION, *Foundation_, physx::PxCookingParams(Physics_->getTolerancesScale()));
	if (!Cooking_)
	{
		MsgBox("PxCreateCooking failed!");
	}

}

// PhysX ������Ʈ
void VirtualPhysXLevel::stepPhysics(bool _Interactive)
{
	// TODO::���������� ��ŭ ������ �ʿ䰡 ��������
	Scene_->simulate(1.0f / 60.0f);
	Scene_->fetchResults(true);
}

// PhysX �޸� Release
void VirtualPhysXLevel::cleanupPhysics(bool _Interactive)
{
	// To release all created character controllers at once, either release the manager object itself
	// , or use the following function if you intend to keep using the manager
	if (nullptr != CtrManager_)
	{
		//CtrManager_->purgeControllers();
		CtrManager_->release();
		CtrManager_ = nullptr;
	}

	//������ ������ �߿��ϴ�

	if (nullptr != Cooking_)
	{
		PX_RELEASE(Cooking_);
	}

	if (nullptr != Scene_)
	{
		PX_RELEASE(Scene_);
	}

	if (nullptr != DefaultCpuDispatcher_)
	{
		PX_RELEASE(DefaultCpuDispatcher_);
	}

	if (nullptr != Physics_)
	{
		PX_RELEASE(Physics_);
	}

	if (Pvd_)
	{
		physx::PxPvdTransport* transport = Pvd_->getTransport();
		Pvd_->release();	Pvd_ = NULL;
		PX_RELEASE(transport);
	}

	if (nullptr != Foundation_)
	{
		PX_RELEASE(Foundation_);
	}

	Scene_ = nullptr;
	Physics_ = nullptr;
	DefaultCpuDispatcher_ = nullptr;
	Foundation_ = nullptr;
}
