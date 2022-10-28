#include "PreCompile.h"
#include "LJM_PhysXHelloWorld.h"

#include <ctype.h>

#include <GameEngineCore/ThirdParty/inc/PhysX/PxConfig.h>
#include <GameEngineCore/ThirdParty/inc/PhysX/PxPhysicsAPI.h>

#include <PhysXSDKSnippets/SnippetUtils.h>
#include <PhysXSDKSnippets/SnippetPrint.h>
#include <PhysXSDKSnippets/SnippetPVD.h>

LJM_PhysXHelloWorld::LJM_PhysXHelloWorld() 
{
}

LJM_PhysXHelloWorld::~LJM_PhysXHelloWorld() 
{
}

void LJM_PhysXHelloWorld::Start()
{
	initPhysics(true);
}

void LJM_PhysXHelloWorld::Update(float _DeltaTime)
{
}

void LJM_PhysXHelloWorld::End()
{
}



PxRigidDynamic* LJM_PhysXHelloWorld::createDynamic(const PxTransform& t, const PxGeometry& geometry, const PxVec3& velocity)
{
	PxRigidDynamic* dynamic = PxCreateDynamic(*pxPhysics, t, geometry, *pxMaterial, 10.0f);
	dynamic->setAngularDamping(0.5f);
	dynamic->setLinearVelocity(velocity);
	pxScene->addActor(*dynamic);

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
