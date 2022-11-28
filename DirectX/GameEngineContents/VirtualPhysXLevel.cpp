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
	// 물리연산 업데이트
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


// PhysX기반 초기화
void VirtualPhysXLevel::initPhysics(bool _interactive)
{
	if (Scene_ != nullptr || Physics_ != nullptr)
	{
		return;
	}

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
	sceneDesc.gravity = physx::PxVec3(0.0f, PHYSX_GRAVITY, 0.0f);

	// EventCallback 세팅
	SimulationEventCallback_ = new CustomSimulationEventCallback();
	sceneDesc.simulationEventCallback = SimulationEventCallback_;
	// callback을 호출 처리할 filtershader 세팅
	//sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;
	sceneDesc.filterShader = CustomFilterShader;

	DefaultCpuDispatcher_ = physx::PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = DefaultCpuDispatcher_;

	// Scene 생성
	Scene_ = Physics_->createScene(sceneDesc);
	
	// PVD연결
	physx::PxPvdSceneClient* pvdClient = Scene_->getScenePvdClient();
	if (pvdClient)
	{
		pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
		pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
		pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
	}

	//// 컨트롤러 매니저 생성(CCTActor 생성을 위해서)
	//CtrManager_ = PxCreateControllerManager(*Scene_);

	//// 지오메트리가 겹치는 경우 자동으로 복구될 수 있는 모드
	//// TODO::일반적인 경우에는 필요하지 않을 수 있음
	//CtrManager_->setOverlapRecoveryModule(true);
	//CtrManager_->setPreciseSweeps(true);

	Cooking_ = PxCreateCooking(PX_PHYSICS_VERSION, *Foundation_, physx::PxCookingParams(Physics_->getTolerancesScale()));
	if (!Cooking_)
	{
		MsgBox("PxCreateCooking failed!");
	}

}

// PhysX 업데이트
void VirtualPhysXLevel::stepPhysics(bool _Interactive)
{
	float simulateRatio = 144.0f;
#ifndef DEBUG
	simulateRatio = 60.0f;
#endif
	// TODO::현재프레임 만큼 수정할 필요가 있을지도
	Scene_->simulate(1.0f / simulateRatio);
	Scene_->fetchResults(true);
}

// PhysX 메모리 Release
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

	//릴리즈 순서가 중요하다

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

void CustomSimulationEventCallback::onContact(const physx::PxContactPairHeader& pairHeader, const physx::PxContactPair* pairs, physx::PxU32 nbPairs)
{
	for (physx::PxU32 i = 0; i < nbPairs; i++)
	{
		const physx::PxContactPair& cp = pairs[i];

		if (cp.events & physx::PxPairFlag::eNOTIFY_TOUCH_FOUND)
		{
			// 충돌체중에 Player가 존재하는지 체크
			if ((pairHeader.actors[0] == PlayerDynamic_) || (pairHeader.actors[1] == PlayerDynamic_))
			{
				// 플레이어가 아닌 액터를 판별 -> 딱히 필요없을지도?
				physx::PxActor* otherActor = (PlayerDynamic_ == pairHeader.actors[0]) ? pairHeader.actors[1] : pairHeader.actors[0];

				// TODO::바닥과 플레이어 충돌했을때 해야할일추가

				break;
			}
		}
	}
}


physx::PxFilterFlags CustomFilterShader(physx::PxFilterObjectAttributes attributes0, physx::PxFilterData filterData0, physx::PxFilterObjectAttributes attributes1, physx::PxFilterData filterData1, physx::PxPairFlags& pairFlags, const void* constantBlock, physx::PxU32 constantBlockSize)
{
	// SampleSubmarineFilterShader로부터 가져옴
	// 
	// let triggers through
	if (physx::PxFilterObjectIsTrigger(attributes0) || physx::PxFilterObjectIsTrigger(attributes1))
	{
		pairFlags = physx::PxPairFlag::eTRIGGER_DEFAULT;
		return physx::PxFilterFlag::eDEFAULT;
	}
	// generate contacts for all that were not filtered above
	pairFlags = physx::PxPairFlag::eCONTACT_DEFAULT;

	// trigger the contact callback for pairs (A,B) where 
	// the filtermask of A contains the ID of B and vice versa.
	if ((filterData0.word0 & filterData1.word1) && (filterData1.word0 & filterData0.word1))
		pairFlags |= physx::PxPairFlag::eNOTIFY_TOUCH_FOUND;

	return physx::PxFilterFlag::eDEFAULT;
}

