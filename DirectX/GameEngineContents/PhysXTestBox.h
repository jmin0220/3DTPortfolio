#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/ThirdParty/inc/PhysX/PxConfig.h>
#include <GameEngineCore/ThirdParty/inc/PhysX/PxPhysicsAPI.h>

#include "PhysicXComponent.h"

// 설명 :
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

	// TODO::오브젝트의 종류에 따라서 각기 다른 Component를 제공해야할수 있음
	std::shared_ptr<PhysicXComponent> physicXComponent_;
};

