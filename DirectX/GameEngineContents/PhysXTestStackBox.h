#pragma once
#include <GameEngineCore/ThirdParty/inc/PhysX/PxConfig.h>
#include <GameEngineCore/ThirdParty/inc/PhysX/PxPhysicsAPI.h>

#include "PhysicXStackComponent.h"

// ���� :
class PhysXTestStackBox : public GameEngineActor
{
public:
	// constrcuter destructer
	PhysXTestStackBox();
	~PhysXTestStackBox();

	// delete Function
	PhysXTestStackBox(const PhysXTestStackBox& _Other) = delete;
	PhysXTestStackBox(PhysXTestStackBox&& _Other) noexcept = delete;
	PhysXTestStackBox& operator=(const PhysXTestStackBox& _Other) = delete;
	PhysXTestStackBox& operator=(PhysXTestStackBox&& _Other) noexcept = delete;

	void CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics);

protected:
	void Start() override;

private:
	GameEngineTextureRenderer* Renderer;
	float4 ResultColor;

	// TODO::������Ʈ�� ������ ���� ���� �ٸ� Component�� �����ؾ��Ҽ� ����
	PhysicXStackComponent* physicXStackComponent_;
};

