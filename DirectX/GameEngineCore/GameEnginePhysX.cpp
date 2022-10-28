#include "PreCompile.h"
#include "GameEnginePhysX.h"


GameEnginePhysX::GameEnginePhysX()
{
}

GameEnginePhysX::~GameEnginePhysX() 
{
}

void GameEnginePhysX::Initialize()
{
	// Foundation�� ����� �ݴϴ�.
	m_pFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gAllocator, gErrorCallback);
	// PhysX�� ����� �ݴϴ�.
	m_pPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *m_pFoundation, PxTolerancesScale(), true);

	// Scene�� Set ���ݴϴ�.
	PxSceneDesc sceneDesc(m_pPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f); // �߷� ����
	// Dispatcher�� Set ����� �ݴϴ�.
	m_pDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = m_pDispatcher;
	sceneDesc.filterShader = PxDefaultSimulationFilterShader;
	// ������ �����Ѵ�� Scene�� ����� �ݴϴ�.
	m_pScene = m_pPhysics->createScene(sceneDesc);
	// Material�� ����� �ݴϴ�.
	m_pMaterial = m_pPhysics->createMaterial(0.5f, 0.5f, 0.6f); // �浹ü ������,Dynamic������, ź����

	// ������ ����� �ݴϴ�.
	PxRigidStatic* groundPlane = PxCreatePlane(*m_pPhysics, PxPlane(0, 1, 0, 0), *m_pMaterial);
	m_pScene->addActor(*groundPlane);
}
