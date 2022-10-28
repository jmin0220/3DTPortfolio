#include "PreCompile.h"
#include "LJM_PhysXHelloWorld.h"

#include <ctype.h>

#include <GameEngineCore/ThirdParty/inc/PhysX/PxConfig.h>
#include <GameEngineCore/ThirdParty/inc/PhysX/PxPhysicsAPI.h>

#include <PhysXSDKSnippets/SnippetUtils.h>
#include <PhysXSDKSnippets/SnippetPrint.h>
#include <PhysXSDKSnippets/SnippetPVD.h>
#include <GameEngineBase/GameEngineInput.h>

LJM_PhysXHelloWorld::LJM_PhysXHelloWorld() 
{
}

LJM_PhysXHelloWorld::~LJM_PhysXHelloWorld() 
{
	cleanupPhysics();
}

void LJM_PhysXHelloWorld::Start()
{
	initPhysics(true);

	GameEngineInput::GetInst()->CreateKey("CreateBall", VK_SPACE);
	GameEngineInput::GetInst()->CreateKey("CreateStack", 1);

	testBoxVector_.reserve(128);
}

void LJM_PhysXHelloWorld::Update(float _DeltaTime)
{
	// 물리연산 업데이트
	stepPhysics(true);

	if (true == GameEngineInput::GetInst()->IsDown("CreateBall"))
	{
		PxTransform tmpTransform(GetMainCameraActor()->GetTransform().GetWorldPosition().x
			, GetMainCameraActor()->GetTransform().GetWorldPosition().y
			, GetMainCameraActor()->GetTransform().GetWorldPosition().z);

		PxVec3 tmpVec3(GetMainCameraActorTransform().GetLocalRotation().x
			, GetMainCameraActorTransform().GetLocalRotation().y
			, 1.0f);

		createDynamic(tmpTransform, tmpVec3 * 200.0f);
	}

	if (true == GameEngineInput::GetInst()->IsDown("CreateStack"))
	{
		createStack(PxTransform(PxVec3(0, 0, stackZ -= 10.0f)), 10, 2.0f);
	}

	// Actor의 정보를 저장해둘 임시 Scene생성
	PxScene* tmpScene;
	PxGetPhysics().getScenes(&tmpScene, 1);

	// 현재 Scene에 존재하는 Dynamic, Static Rigid액터의 숫자를 취득
	PxU32 nbActors = tmpScene->getNbActors(PxActorTypeFlag::eRIGID_DYNAMIC | PxActorTypeFlag::eRIGID_STATIC);

	if (nbActors)
	{
		std::vector<PxRigidActor*> actors(nbActors);
		tmpScene->getActors(PxActorTypeFlag::eRIGID_DYNAMIC | PxActorTypeFlag::eRIGID_STATIC, reinterpret_cast<PxActor**>(&actors[0]), nbActors);
		//Snippets::renderActors(&actors[0], static_cast<PxU32>(actors.size()), true);

		// Render Start-------------------------
		const int MAX_NUM_ACTOR_SHAPES = 128;	// #define 필요
		PxShape* shapes[MAX_NUM_ACTOR_SHAPES];

		for (PxU32 i = 0; i < static_cast<PxU32>(actors.size()); i++)
		{
			std::vector<TestBox*>::iterator StartIter = testBoxVector_.begin();
			std::vector<TestBox*>::iterator EndIter = testBoxVector_.end();

			const PxU32 nbShapes = actors[i]->getNbShapes();
			PX_ASSERT(nbShapes <= MAX_NUM_ACTOR_SHAPES);
			actors[i]->getShapes(shapes, nbShapes);

			float4 tmpWorldPosition = { actors[i]->getGlobalPose().p.x
										, actors[i]->getGlobalPose().p.y
										, actors[i]->getGlobalPose().p.z };

			float4 tmpWorldScale = { 2.0f };

			float4 tmpWorldRotate = { actors[i]->getGlobalPose().q.x
							, actors[i]->getGlobalPose().q.y
							, actors[i]->getGlobalPose().q.z
							, actors[i]->getGlobalPose().q.w };

			(*StartIter)->GetTransform().SetWorldPosition(tmpWorldPosition);
			(*StartIter)->GetTransform().SetWorldScale(tmpWorldScale);
			(*StartIter)->GetTransform().SetWorldRotation(tmpWorldRotate);

			++StartIter;
		}


		// Render End --------------------------
	}
}

void LJM_PhysXHelloWorld::End()
{
}

PxRigidDynamic* LJM_PhysXHelloWorld::createDynamic(const PxTransform& t, const PxVec3& velocity)
{
	PxShape* shape = pxPhysics->createShape(PxBoxGeometry(2.0f, 2.0f, 2.0f), *pxMaterial);

	PxTransform localTm(GetMainCameraActor()->GetTransform().GetWorldPosition().x
		, GetMainCameraActor()->GetTransform().GetWorldPosition().y
		, GetMainCameraActor()->GetTransform().GetWorldPosition().z);

	PxRigidDynamic* dynamic = pxPhysics->createRigidDynamic(localTm);
	dynamic->attachShape(*shape);
	dynamic->setAngularDamping(0.5f);
	dynamic->setLinearVelocity(velocity);

	pxScene->addActor(*dynamic);

	TestBox* tmpTestBox = CreateActor<TestBox>();

	const PxBoxGeometry& boxGeom = static_cast<const PxBoxGeometry&>(shape->getGeometry().box());

	float4 tmpWorldPosition = { dynamic->getGlobalPose().p.x
							  , dynamic->getGlobalPose().p.y
							  , dynamic->getGlobalPose().p.z };

	float4 tmpWorldScale = { 2.0f };

	float4 tmpWorldRotate = { localTm.q.x
		, localTm.q.y
		, localTm.q.z
		, localTm.q.w };

	tmpTestBox->GetTransform().SetWorldPosition(tmpWorldPosition);
	tmpTestBox->GetTransform().SetWorldScale(tmpWorldScale);
	tmpTestBox->GetTransform().SetWorldRotation(tmpWorldRotate);

	testBoxVector_.push_back(tmpTestBox);

	return dynamic;
}

void LJM_PhysXHelloWorld::createStack(const PxTransform& t, PxU32 size, PxReal halfExtent)
{
	PxShape* shape = pxPhysics->createShape(PxBoxGeometry(halfExtent, halfExtent, halfExtent), *pxMaterial);
	for (PxU32 i = 0; i < size; i++)
	{
		for (PxU32 j = 0; j < size - i; j++)
		{
			PxTransform localTm(PxVec3(PxReal(j * 2) - PxReal(size - i), PxReal(i * 2 + 1), 0) * halfExtent);
			PxRigidDynamic* body = pxPhysics->createRigidDynamic(t.transform(localTm));
			body->attachShape(*shape);
			PxRigidBodyExt::updateMassAndInertia(*body, 10.0f);
			pxScene->addActor(*body);

			TestBox* tmpTestBox = CreateActor<TestBox>();

			const PxBoxGeometry& boxGeom = static_cast<const PxBoxGeometry&>(shape->getGeometry().box());

			float4 tmpWorldPosition = { body->getGlobalPose().p.x
									  , body->getGlobalPose().p.y
									  , body->getGlobalPose().p.z };

			float4 tmpWorldScale = { halfExtent };

			float4 tmpWorldRotate = { localTm.q.x
				, localTm.q.y
				, localTm.q.z
				, localTm.q.w };

			tmpTestBox->GetTransform().SetWorldPosition(tmpWorldPosition);
			tmpTestBox->GetTransform().SetWorldScale(tmpWorldScale);
			tmpTestBox->GetTransform().SetWorldRotation(tmpWorldRotate);

			testBoxVector_.push_back(tmpTestBox);
		}
	}
	shape->release();
}

void LJM_PhysXHelloWorld::initPhysics(bool _interactive)
{
	pxFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, pxDefaultAllocator, pxDefaultErrorCallback);

	pxPvd = PxCreatePvd(*pxFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	pxPvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

	pxPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *pxFoundation, PxTolerancesScale(), true, pxPvd);

	PxSceneDesc sceneDesc(pxPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);
	pxDefaultCpuDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = pxDefaultCpuDispatcher;
	sceneDesc.filterShader = PxDefaultSimulationFilterShader;
	pxScene = pxPhysics->createScene(sceneDesc);

	PxPvdSceneClient* pvdClient = pxScene->getScenePvdClient();
	if (pvdClient)
	{
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
	}

	pxMaterial = pxPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	PxRigidStatic* groundPlane = PxCreatePlane(*pxPhysics, PxPlane(0, 1, 0, 0), *pxMaterial);
	pxScene->addActor(*groundPlane);

	for (PxU32 i = 0; i < 5; i++)
		createStack(PxTransform(PxVec3(0, 0, stackZ -= 10.0f)), 10, 2.0f);
}



void LJM_PhysXHelloWorld::stepPhysics(bool /*interactive*/)
{
	pxScene->simulate(1.0f / 60.0f);
	pxScene->fetchResults(true);
}

void LJM_PhysXHelloWorld::cleanupPhysics(bool _Interactive)
{
	PX_RELEASE(pxScene);
	PX_RELEASE(pxDefaultCpuDispatcher);
	PX_RELEASE(pxPhysics);
	if (pxPvd)
	{
		PxPvdTransport* transport = pxPvd->getTransport();
		pxPvd->release();	pxPvd = NULL;
		PX_RELEASE(transport);
	}
	PX_RELEASE(pxFoundation);
}
