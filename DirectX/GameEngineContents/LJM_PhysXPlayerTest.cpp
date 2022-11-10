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
	// To release all created character controllers at once, either release the manager object itself
	// , or use the following function if you intend to keep using the manager
	if (nullptr != CtrManager_)
	{
		CtrManager_->purgeControllers();
	}
}

void LJM_PhysXPlayerTest::Start()
{


	GameEngineInput::GetInst()->CreateKey("CreateBall", VK_SPACE);
	GameEngineInput::GetInst()->CreateKey("CreateStack", '1');
}

void LJM_PhysXPlayerTest::Update(float _DeltaTime)
{
	// �������� ������Ʈ
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

	// ���ҽ� �ε�
	ContentsCore::GetInst()->LoadLevelResource(LEVELS::PHYSX_TEST);

	Player_ = CreateActor<PhysXTestPlayer>();


	initPhysics(true);
}

void LJM_PhysXPlayerTest::LevelEndEvent()
{
	Player_->Death();

	// ���ҽ� ����
	ContentsCore::GetInst()->ReleaseCurLevelResource();
}

void LJM_PhysXPlayerTest::initPhysics(bool _interactive)
{
	// PsFoundation.cpp (165) : invalid operation : Foundation object exists already. Only one instance per process can be created.
	// ���α׷� �ϳ��� 1���� Foundation�� ���� �����Ѱ�?
	pxFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, pxDefaultAllocator, pxDefaultErrorCallback);
	pxPvd = PxCreatePvd(*pxFoundation);
	physx::PxPvdTransport* transport = physx::PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	pxPvd->connect(*transport, physx::PxPvdInstrumentationFlag::eALL);

	// Physics����
	Physics_ = PxCreatePhysics(PX_PHYSICS_VERSION, *pxFoundation, physx::PxTolerancesScale(), true, pxPvd);

	// Scene����
	physx::PxSceneDesc sceneDesc(Physics_->getTolerancesScale());
	sceneDesc.gravity = physx::PxVec3(0.0f, -9.81f, 0.0f);
	pxDefaultCpuDispatcher = physx::PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = pxDefaultCpuDispatcher;
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

	// �ӽù��� ����
	PlaneMat_ = Physics_->createMaterial(0.5f, 0.5f, 0.1f);
	//physx::PxRigidStatic* groundPlane = physx::PxCreatePlane(*Physics_, physx::PxPlane(0, 1, 0, 0), *PlaneMat_);
	//Scene_->addActor(*groundPlane);
	physx::PxTransform	boxPose = physx::PxTransform(physx::PxVec3(0.0f, -1.0f, 0.0f));
	const physx::PxVec3 boxSize = physx::PxVec3(500.0f, 1.0f, 500.0f);
	const physx::PxReal density(0.0f);
	physx::PxRigidActor* box = createRigidActor(*Scene_, *Physics_, boxPose, physx::PxBoxGeometry(boxSize), *PlaneMat_, NULL, &density, NULL, 0);


	// ��Ʈ�ѷ� �Ŵ��� ����(ControlledActor ������ ���ؼ�)
	CtrManager_ = PxCreateControllerManager(*Scene_);

	// ������Ʈ���� ��ġ�� ��� �ڵ����� ������ �� �ִ� ���
	// TODO::�Ϲ����� ��쿡�� �ʿ����� ���� �� ����
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
	PhysXTestBox* tmpTestBox = CreateActor<PhysXTestBox>();
	tmpTestBox->GetTransform().SetWorldPosition({ 0.0f, 100.0f, 2000.0f });
	tmpTestBox->CreatePhysXActors(Scene_, Physics_);
}

void LJM_PhysXPlayerTest::createStack(const physx::PxTransform& t, physx::PxU32 size, physx::PxReal halfExtent)
{
	// 1���ÿ� Actor�� 55���� ������
	for (physx::PxU32 i = 0; i < size; i++)
	{
		for (physx::PxU32 j = 0; j < size - i; j++)
		{

			PhysXTestStackBox* tmpTestStackBox = CreateActor<PhysXTestStackBox>();
			// ������ �������� ���� ������ �Ŀ� RigidDynamic�� ������
			tmpTestStackBox->GetTransform().SetWorldPosition({ (j * 2.0f - (size - i)) * halfExtent, (i * 2.0f + 1.0f) * halfExtent, t.p.z });
			tmpTestStackBox->CreatePhysXActors(Scene_, Physics_);
		}
	}
	//shape->release();
}