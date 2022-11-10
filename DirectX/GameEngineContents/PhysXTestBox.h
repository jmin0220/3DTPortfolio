#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/ThirdParty/inc/PhysX/PxConfig.h>
#include <GameEngineCore/ThirdParty/inc/PhysX/PxPhysicsAPI.h>

#include "PhysicXComponent.h"

// ���� :
class PhysXTestBox : public GameEngineActor
{
public:
	// constrcuter destructer
	PhysXTestBox();
	~PhysXTestBox();

	// delete Function
	PhysXTestBox(const PhysXTestBox& _Other) = delete;
	PhysXTestBox(PhysXTestBox&& _Other) noexcept = delete;
	PhysXTestBox& operator=(const PhysXTestBox& _Other) = delete;
	PhysXTestBox& operator=(PhysXTestBox&& _Other) noexcept = delete;

	void CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics);

protected:
	void Start() override;

private:
	std::shared_ptr<GameEngineTextureRenderer> Renderer;
	float4 ResultColor;

	// TODO::������Ʈ�� ������ ���� ���� �ٸ� Component�� �����ؾ��Ҽ� ����
	std::shared_ptr<PhysicXComponent> physicXComponent_;
};

