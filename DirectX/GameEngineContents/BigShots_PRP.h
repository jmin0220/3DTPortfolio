#pragma once
#include "VirtualPhysXActor.h"
#include "PhysXConvexDynamicComponent.h"

enum class PRPType
{
	CONTROLLER,
	MAGNET,
	NUT,
	PLANET,
	STAR,
	TETRAPOD,
	MAX
};

// 설명 :
class BigShots_PRP : public VirtualPhysXActor
{
public:
	// constrcuter destructer
	BigShots_PRP();
	~BigShots_PRP();

	// delete Function
	BigShots_PRP(const BigShots_PRP& _Other) = delete;
	BigShots_PRP(BigShots_PRP&& _Other) noexcept = delete;
	BigShots_PRP& operator=(const BigShots_PRP& _Other) = delete;
	BigShots_PRP& operator=(BigShots_PRP&& _Other) noexcept = delete;

	void CreatePhysX();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;

	void CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics) override;

private:
	std::shared_ptr<GameEngineFBXStaticRenderer> Renderer_;
	std::shared_ptr<PhysXConvexDynamicComponent> PhysXConvexDynamicComponent_;

	PRPType CurPRP_;
	std::string FBXName_;
	float4 PRPForce_;


	// 서버
public:
	void InitPRP(float4 _ShootSetting);
	

private:
	float4 SettingRot_;
	float SettingForce_; // x : 회전값, y : 회전값, z : 회전값, w : 힘
};

