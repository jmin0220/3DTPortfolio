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
	TETRAPOD
};

// Ό³Έν :
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
};

