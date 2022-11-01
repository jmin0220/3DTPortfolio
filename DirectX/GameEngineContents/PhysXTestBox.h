#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/ThirdParty/inc/PhysX/PxConfig.h>
#include <GameEngineCore/ThirdParty/inc/PhysX/PxPhysicsAPI.h>

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
	void Update(float _DeltaTime) override;
	void End() override {};

private:
	GameEngineTextureRenderer* Renderer;
	float4 ResultColor;

	// Phys액터 생성에 필요한 정보
	//physx::PxPhysics* pxPhysics_;
	//physx::PxScene* pxScene_;

	physx::PxMaterial* material_;
	physx::PxShape* shape_;
	physx::PxRigidDynamic* dynamic_;
};

