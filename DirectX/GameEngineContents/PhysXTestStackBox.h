#pragma once
#include <GameEngineCore/ThirdParty/inc/PhysX/PxConfig.h>
#include <GameEngineCore/ThirdParty/inc/PhysX/PxPhysicsAPI.h>

#include "PhysicXStackComponent.h"

// 설명 :
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

	// TODO::오브젝트의 종류에 따라서 각기 다른 Component를 제공해야할수 있음
	PhysicXStackComponent* physicXStackComponent_;
};

