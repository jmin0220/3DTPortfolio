#include "PreCompile.h"
#include "LJM_PhysXHelloWorld.h"
#include "PhysXTestBox.h"
#include "PhysXTestStackBox.h"

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
	//GetMainCamera()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);

	initPhysics(true);

	GameEngineInput::GetInst()->CreateKey("CreateBall", VK_SPACE);
	GameEngineInput::GetInst()->CreateKey("CreateStack", '1');
}

void LJM_PhysXHelloWorld::Update(float _DeltaTime)
{
	// �������� ������Ʈ
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

	//// Actor�� ������ �����ص� �ӽ� Scene����
	//PxScene* tmpScene;
	//PxGetPhysics().getScenes(&tmpScene, 1);

	//// ���� Scene�� �����ϴ� Dynamic, Static Rigid������ ���ڸ� ���
	//PxU32 nbActors = tmpScene->getNbActors(PxActorTypeFlag::eRIGID_DYNAMIC | PxActorTypeFlag::eRIGID_STATIC);

	//if (nbActors)
	//{
	//	std::vector<PxRigidActor*> actors(nbActors);
	//	tmpScene->getActors(PxActorTypeFlag::eRIGID_DYNAMIC | PxActorTypeFlag::eRIGID_STATIC, reinterpret_cast<PxActor**>(&actors[0]), nbActors);
	//	//Snippets::renderActors(&actors[0], static_cast<PxU32>(actors.size()), true);

	//	// Render Start-------------------------
	//	const int MAX_NUM_ACTOR_SHAPES = 128;	// #define �ʿ�
	//	PxShape* shapes[MAX_NUM_ACTOR_SHAPES];


	//	//std::string tmpSizeActor = "PxRigidActor  Size >> " + std::to_string(actors.size());
	//	//std::string tmpSizeTestBox = "TestBoxVector Size >> " + std::to_string(testBoxVector_.size());
	//	//GameEngineDebug::OutPutString(tmpSizeActor);
	//	//GameEngineDebug::OutPutString(tmpSizeTestBox);


	//	for (PxU32 i = 0; i < static_cast<PxU32>(actors.size()); i++)
	//	{
	//		//std::vector<PhysXTestBox*>::iterator StartIter = testBoxVector_.begin();
	//		//std::vector<PhysXTestBox*>::iterator EndIter = testBoxVector_.end();

	//		const PxU32 nbShapes = actors[i]->getNbShapes();
	//		PX_ASSERT(nbShapes <= MAX_NUM_ACTOR_SHAPES);
	//		actors[i]->getShapes(shapes, nbShapes);

	//		// Shape�κ��� Shape�� �������� ���
	//		// Shapes�ȿ� ���빰�� ������, ���ڵ忡���� �ϰ������� 0��°�� ����ϰ� �����Ƿ� ����
	//		const PxMat44 shapePose(PxShapeExt::getGlobalPose(*shapes[0], *actors[i]));
	//		const PxGeometryHolder h = shapes[0]->getGeometry();

	//		//float4 tmpWorldPosition = { actors[i]->getGlobalPose().p.x
	//		//							, actors[i]->getGlobalPose().p.y
	//		//							, actors[i]->getGlobalPose().p.z };

	//		// shape�κ��� �������� ����
	//		float4 tmpWorldPosition = { shapePose.getPosition().x
	//								  , shapePose.getPosition().y
	//								  , shapePose.getPosition().z };

	//		

	//		//if ((*StartIter)->GetNameCopy() == "Dynamic")
	//		//{
	//		//	std::string tmp = "shapePose >> x : " + std::to_string(shapePose.getPosition().x) + " / y : " + std::to_string(shapePose.getPosition().y) + " / z : " + std::to_string(shapePose.getPosition().z);
	//		//	GameEngineDebug::OutPutString(tmp);
	//		//}

	//		float4 tmpWorldScale = { 2.0f };

	//		// TODO::shape�κ��� ȸ������ ����?
	//		float4 tmpWorldRotate = { actors[i]->getGlobalPose().q.x
	//						, actors[i]->getGlobalPose().q.y

	//						, actors[i]->getGlobalPose().q.z
	//						, actors[i]->getGlobalPose().q.w };

	//		CurDynamicPos_ = tmpWorldPosition;
	//	}


		// Render End --------------------------
	//	}

	if (GetAccTime() >= 1.0f)
	{
		ReSetAccTime();
		std::string tmpWorldPositionString = "MainCameraPos >> x : " + std::to_string(GetMainCameraActorTransform().GetWorldPosition().x)
			+ " / y : " + std::to_string(GetMainCameraActorTransform().GetWorldPosition().y)
			+ " / z : " + std::to_string(GetMainCameraActorTransform().GetWorldPosition().z);

		GameEngineDebug::OutPutString(tmpWorldPositionString);
	}
}

void LJM_PhysXHelloWorld::End()
{
	// PhysicX �޸� ����
	cleanupPhysics();
}

void LJM_PhysXHelloWorld::createDynamic(const PxTransform& t, const PxVec3& velocity)
{
	PhysXTestBox* tmpTestBox = CreateActor<PhysXTestBox>();
	tmpTestBox->GetTransform().SetWorldPosition({ 0.0f, 100.0f, 2000.0f });
	tmpTestBox->CreatePhysXActors(pxScene
		, pxPhysics);
}

void LJM_PhysXHelloWorld::createStack(const PxTransform& t, PxU32 size, PxReal halfExtent)
{
	// 1���ÿ� Actor�� 55���� ������
	for (PxU32 i = 0; i < size; i++)
	{
		for (PxU32 j = 0; j < size - i; j++)
		{

			PhysXTestStackBox* tmpTestStackBox = CreateActor<PhysXTestStackBox>();
			// ������ �������� ���� ������ �Ŀ� RigidDynamic�� ������
			tmpTestStackBox->GetTransform().SetWorldPosition({ (j * 2.0f - (size - i)) * halfExtent, (i * 2.0f + 1.0f) * halfExtent, t.p.z });
			tmpTestStackBox->CreatePhysXActors(pxScene, pxPhysics);
		}
	}
	//shape->release();
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

	float4 tmpWorldPosition = { groundPlane->getGlobalPose().p.x
									  , groundPlane->getGlobalPose().p.y
									  , groundPlane->getGlobalPose().p.z };

	for (PxU32 i = 0; i < 5; i++)
		createStack(PxTransform(PxVec3(0, 0, stackZ -= 10.0f)), 10, 2.0f);
}


// ������ ���������� ����
void LJM_PhysXHelloWorld::stepPhysics(bool /*interactive*/)
{
	pxScene->simulate(1.0f / 60.0f);
	pxScene->fetchResults(true);
}

// �޸�����
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
