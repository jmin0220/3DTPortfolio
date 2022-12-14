#pragma once
#include "VirtualPhysXActor.h"
#include "PhysXSpinBarComponent.h"

// ???? :
class JumpClub_SpinBarDouble : public VirtualPhysXActor, public GameServerObject
{
public:
	// constrcuter destructer
	JumpClub_SpinBarDouble();
	~JumpClub_SpinBarDouble();

	// delete Function
	JumpClub_SpinBarDouble(const JumpClub_SpinBarDouble& _Other) = delete;
	JumpClub_SpinBarDouble(JumpClub_SpinBarDouble&& _Other) noexcept = delete;
	JumpClub_SpinBarDouble& operator=(const JumpClub_SpinBarDouble& _Other) = delete;
	JumpClub_SpinBarDouble& operator=(JumpClub_SpinBarDouble&& _Other) noexcept = delete;

	std::shared_ptr<PhysXSpinBarComponent>& GetPhysXSpinBarComponent()
	{
		return PhysXSpinBarComponent_;
	}

	void PhysXInit();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;

	void CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics) override;

private:
	std::shared_ptr<PhysXSpinBarComponent> PhysXSpinBarComponent_;
	std::shared_ptr<GameEngineFBXStaticRenderer> Renderer_;

};

