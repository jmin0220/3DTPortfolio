#include "PreCompile.h"
#include "VirtualPhysXLevel.h"
#include "PlayerActor.h"


physx::PxScene* VirtualPhysXLevel::Scene_ = nullptr;
physx::PxPhysics* VirtualPhysXLevel::Physics_ = nullptr;

physx::PxFilterFlags CustomFilterShader(physx::PxFilterObjectAttributes attributes0, physx::PxFilterData filterData0, physx::PxFilterObjectAttributes attributes1, physx::PxFilterData filterData1, physx::PxPairFlags& pairFlags, const void* constantBlock, physx::PxU32 constantBlockSize);

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
	stepPhysics(_DeltaTIme, true);
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

	// EventCallback ����
	SimulationEventCallback_ = new CustomSimulationEventCallback();
	sceneDesc.simulationEventCallback = SimulationEventCallback_;

	// callback�� ȣ�� ó���� filtershader ����
	//sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;
	sceneDesc.filterShader = CustomFilterShader;

	DefaultCpuDispatcher_ = physx::PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = DefaultCpuDispatcher_;
	sceneDesc.flags |= physx::PxSceneFlag::eENABLE_CCD;
	// sceneDesc.broadPhaseType = physx::PxBroadPhaseType::eABP;

	// Scene ����
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

	Cooking_ = PxCreateCooking(PX_PHYSICS_VERSION, *Foundation_, physx::PxCookingParams(Physics_->getTolerancesScale()));
	if (!Cooking_)
	{
		MsgBox("PxCreateCooking failed!");
	}

}

// PhysX ������Ʈ
void VirtualPhysXLevel::stepPhysics(float _DeltaTime, bool _Interactive)
{
	float simulateRatio = 60.0f;

//#ifndef DEBUG
//	 simulateRatio = 60.0f;
//#endif
// 
	// TODO::���������� ��ŭ ������ �ʿ䰡 ��������
	Scene_->simulate(1 / simulateRatio);
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

	if (nullptr != SimulationEventCallback_)
	{
		delete SimulationEventCallback_;
		SimulationEventCallback_ = nullptr;
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

void CustomSimulationEventCallback::onTrigger(physx::PxTriggerPair* pairs, physx::PxU32 count)
{
	while(count--)
	{
		physx::PxTriggerPair& current = *pairs++;

		// ���Ͱ� ������ �ִ� �������� ��� ������
		physx::PxRigidActor& tmpOtherActor = *current.otherActor;
		physx::PxFilterData OtherFilterdata = current.otherShape->getSimulationFilterData();
		physx::PxFilterData TriggerFilterdata  = current.triggerShape->getSimulationFilterData();
		physx::PxU16 tmpnbShape = current.otherActor->getNbShapes();

			// C26813  : ��Ʈ�÷��׷� ���� enum������ �񱳴� == �� �ƴ� bitwise and(&)�� ���ϴ� ���� ����
			// WARNING : resultFd.word0 == static_cast<physx::PxU32>(PhysXFilterGroup::Ground
			// �浹ü�� filterData�� ground�̸鼭 ����� ���
			if (OtherFilterdata.word0 & static_cast<physx::PxU32>(PhysXFilterGroup::Ground) && 
				TriggerFilterdata.word0 & static_cast<physx::PxU32>(PhysXFilterGroup::Player) &&
				current.status & physx::PxPairFlag::eNOTIFY_TOUCH_FOUND )
			{
				if (CommonPlayer_ != nullptr)
				{
					CommonPlayer_->TouchGroundOn();
  					CommonPlayer_->DetachGroundOff();
  					CommonPlayer_->Setwaitphysx(true);
					return;
				}

			}

			// �浹ü�� filterData�� ground�̸鼭 �������� ���
			if (OtherFilterdata.word0 & static_cast<physx::PxU32>(PhysXFilterGroup::Ground) &&
				TriggerFilterdata.word0 & static_cast<physx::PxU32>(PhysXFilterGroup::Player) &&
				current.status & physx::PxPairFlag::eNOTIFY_TOUCH_LOST )
			{
				if (CommonPlayer_ != nullptr)
				{
					CommonPlayer_->TouchGroundOff();
					CommonPlayer_->DetachGroundOn();
					//CommonPlayer_->Setwaitphysx(true);
					return;

				}
			}

			if (OtherFilterdata.word0 & static_cast<physx::PxU32>(PhysXFilterGroup::Ground) &&
				TriggerFilterdata.word0 & static_cast<physx::PxU32>(PhysXFilterGroup::PlayerFace) &&
				current.status & physx::PxPairFlag::eNOTIFY_TOUCH_FOUND)
			{
				if (CommonPlayer_ != nullptr)
				{
					CommonPlayer_->SetIsStandingReady(true);
					return;
				}
			}

			if (OtherFilterdata.word0 & static_cast<physx::PxU32>(PhysXFilterGroup::Obstacle) &&
				TriggerFilterdata.word0 & static_cast<physx::PxU32>(PhysXFilterGroup::Player) &&
				current.status & physx::PxPairFlag::eNOTIFY_TOUCH_FOUND)
			{
				if (CommonPlayer_ != nullptr)
				{
					CommonPlayer_->SetIsStandingReady(true);
					return;
				}
			}
	}
}

void CustomSimulationEventCallback::onContact(const physx::PxContactPairHeader& pairHeader, const physx::PxContactPair* pairs, physx::PxU32 nbPairs)
{
	while (nbPairs--)
	{
		physx::PxContactPair current = *pairs++;
		// ���Ͱ� ������ �ִ� �������� ��� ������
		physx::PxShape* tmpContactActor = current.shapes[0];
		physx::PxShape* tmpOtherActor = current.shapes[1];
		physx::PxFilterData OtherFilterdata = tmpOtherActor->getSimulationFilterData();
		physx::PxFilterData TriggerFilterdata = tmpContactActor->getSimulationFilterData();

		if (OtherFilterdata.word0 & static_cast<physx::PxU32>(PhysXFilterGroup::Ground) &&
			TriggerFilterdata.word0 & static_cast<physx::PxU32>(PhysXFilterGroup::PlayerDynamic) && 
			current.events & physx::PxPairFlag::eNOTIFY_TOUCH_FOUND)
		{
			CommonPlayer_->TouchGroundOn();
			CommonPlayer_->DetachGroundOff();
			CommonPlayer_->Setwaitphysx(true);
		}
	}
}


physx::PxFilterFlags CustomFilterShader(physx::PxFilterObjectAttributes attributes0, physx::PxFilterData filterData0, physx::PxFilterObjectAttributes attributes1, physx::PxFilterData filterData1, physx::PxPairFlags& pairFlags, const void* constantBlock, physx::PxU32 constantBlockSize)
{
	// SampleSubmarineFilterShader�κ��� ������
	// 
	// let triggers through
	if (physx::PxFilterObjectIsTrigger(attributes0) || physx::PxFilterObjectIsTrigger(attributes1))
	{
		pairFlags = physx::PxPairFlag::eTRIGGER_DEFAULT;
		return physx::PxFilterFlag::eDEFAULT;
	}
	 //generate contacts for all that were not filtered above
	pairFlags = physx::PxPairFlag::eCONTACT_DEFAULT;

	if ((filterData0.word0 & filterData1.word1) && (filterData1.word0 & filterData0.word1))
		pairFlags |= physx::PxPairFlag::eNOTIFY_TOUCH_FOUND;

	return physx::PxFilterFlag::eDEFAULT;
}

