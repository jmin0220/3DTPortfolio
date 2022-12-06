#include "PreCompile.h"
#include "LJM_PhysXPlayerTest.h"
#include "PhysXTestPlayer.h"

#include "PhysXTestBox.h"
#include "PhysXTestStackBox.h"

LJM_PhysXPlayerTest::LJM_PhysXPlayerTest() 
{
}

LJM_PhysXPlayerTest::~LJM_PhysXPlayerTest() 
{
}

void LJM_PhysXPlayerTest::Start()
{

}

void LJM_PhysXPlayerTest::Update(float _DeltaTime)
{
}

void LJM_PhysXPlayerTest::End()
{
}

void LJM_PhysXPlayerTest::LevelStartEvent()
{

}

void LJM_PhysXPlayerTest::LevelEndEvent()
{
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
	PlaneMat_ = Physics_->createMaterial(0.5f, 0.5f, 0.1f);
	//physx::PxRigidStatic* groundPlane = physx::PxCreatePlane(*Physics_, physx::PxPlane(0, 1, 0, 0), *PlaneMat_);
	//Scene_->addActor(*groundPlane);
	physx::PxTransform	boxPose = physx::PxTransform(physx::PxVec3(0.0f, -1.0f, 0.0f));
	const physx::PxVec3 boxSize = physx::PxVec3(500.0f, 1.0f, 500.0f);
	const physx::PxReal density(0.0f);
	physx::PxRigidActor* box = createRigidActor(*Scene_, *Physics_, boxPose, physx::PxBoxGeometry(boxSize), *PlaneMat_, NULL, &density, NULL, 0);


	// 컨트롤러 매니저 생성(ControlledActor 생성을 위해서)
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
	PX_RELEASE(Scene_);
	PX_RELEASE(pxDefaultCpuDispatcher);
	PX_RELEASE(Physics_);
	if (pxPvd)
	{
		physx::PxPvdTransport* transport = pxPvd->getTransport();
		pxPvd->release();	pxPvd = NULL;
		PX_RELEASE(transport);
	}
	PX_RELEASE(pxFoundation);
}

physx::PxRigidActor* LJM_PhysXPlayerTest::createRigidActor(physx::PxScene& scene, physx::PxPhysics& physics, const physx::PxTransform& pose, const physx::PxGeometry& geometry, physx::PxMaterial& material, const physx::PxFilterData* fd, const physx::PxReal* density, const physx::PxReal* mass, physx::PxU32 flags)
{
	const bool isDynamic = (density && *density) || (mass && *mass);

	physx::PxRigidActor* actor = isDynamic ? static_cast<physx::PxRigidActor*>(physics.createRigidDynamic(pose))
		: static_cast<physx::PxRigidActor*>(physics.createRigidStatic(pose));
	if (!actor)
		return NULL;

	physx::PxShape* shape = physx::PxRigidActorExt::createExclusiveShape(*actor, geometry, material);
	if (!shape)
	{
		actor->release();
		return NULL;
	}

	if (fd)
		shape->setSimulationFilterData(*fd);

	if (isDynamic)
	{
		physx::PxRigidDynamic* body = static_cast<physx::PxRigidDynamic*>(actor);
		{
			if (density)
				physx::PxRigidBodyExt::updateMassAndInertia(*body, *density);
			else
				physx::PxRigidBodyExt::setMassAndUpdateInertia(*body, *mass);
		}
	}

	scene.addActor(*actor);

	return actor;
}



void LJM_PhysXPlayerTest::createDynamic(const physx::PxTransform& t, const physx::PxVec3& velocity)
{
	std::shared_ptr<PhysXTestBox> tmpTestBox = CreateActor<PhysXTestBox>();
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

			std::shared_ptr<PhysXTestStackBox> tmpTestStackBox = CreateActor<PhysXTestStackBox>();
			// 액터의 포지션을 먼저 조정한 후에 RigidDynamic을 생성★
			tmpTestStackBox->GetTransform().SetWorldPosition({ (j * 2.0f - (size - i)) * halfExtent, (i * 2.0f + 1.0f) * halfExtent, t.p.z });
			tmpTestStackBox->CreatePhysXActors(Scene_, Physics_);
		}
	}
	//shape->release();
}