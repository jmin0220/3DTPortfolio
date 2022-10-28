#pragma once
#include <GameEngineCore/GameEngineTransformComponent.h>

#pragma warning(disable : 4996)
#include <../inc/PhysX/PxConfig.h>
#include <../inc/PhysX/PxPhysicsAPI.h>
//#include <PxPhysicsAPI.h>


using namespace physx;

#pragma comment (lib, "PhysX_static_64.lib")
#pragma comment (lib, "PhysXCommon_static_64.lib")
#pragma comment (lib, "PhysXExtensions_static_64.lib")
#pragma comment (lib, "PhysXFoundation_static_64.lib")
#pragma comment (lib, "PhysXPvdSDK_static_64.lib")


// ���� :
class GameEnginePhysX : public GameEngineTransformComponent
{
public:
	void Initialize();

public:
	// constrcuter destructer
	GameEnginePhysX();
	~GameEnginePhysX();

	// delete Function
	GameEnginePhysX(const GameEnginePhysX& _Other) = delete;
	GameEnginePhysX(GameEnginePhysX&& _Other) noexcept = delete;
	GameEnginePhysX& operator=(const GameEnginePhysX& _Other) = delete;
	GameEnginePhysX& operator=(GameEnginePhysX&& _Other) noexcept = delete;

protected:

private:

	// Foundation�� �����ϴµ� �ʿ��� ����
	PxDefaultAllocator		gAllocator;
	PxDefaultErrorCallback	gErrorCallback;
	PxFoundation* m_pFoundation = NULL;

	// PxFoundation�� �־�� gPhysics�� ������ �� �ִ�.
	PxPhysics* m_pPhysics = NULL;

	// CPU ���ҽ��� ȿ�������� ������ �� �ֵ��� �ϱ� ���� �����ϴ� ���� ��õ
	PxDefaultCpuDispatcher* m_pDispatcher = NULL;
	// Scene
	PxScene* m_pScene = NULL;
	// m_pPhysics�� ����� createMaterial�ؼ� ���
	// �浹ü ������, Dynamic ������, ź������ �����Ͽ� ���
	PxMaterial* m_pMaterial = NULL;

	////Visual Debugger
	//PxPvd*                  gPvd = NULL;
};

