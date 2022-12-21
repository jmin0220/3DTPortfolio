#pragma once
#include "VirtualPhysXActor.h"
#include "PhysXSpinBarComponent.h"

// 설명 :
class JumpClub_SpinBarSingle : public VirtualPhysXActor, public GameServerObject
{
public:
	// constrcuter destructer
	JumpClub_SpinBarSingle();
	~JumpClub_SpinBarSingle();

	// delete Function
	JumpClub_SpinBarSingle(const JumpClub_SpinBarSingle& _Other) = delete;
	JumpClub_SpinBarSingle(JumpClub_SpinBarSingle&& _Other) noexcept = delete;
	JumpClub_SpinBarSingle& operator=(const JumpClub_SpinBarSingle& _Other) = delete;
	JumpClub_SpinBarSingle& operator=(JumpClub_SpinBarSingle&& _Other) noexcept = delete;

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

	float AccSpeed_;
	float AccTime_;

	// 서버
public:
	void PhysXInit();

	std::shared_ptr<PhysXSpinBarComponent>& GetPhysXSpinBarComponent()
	{
		return PhysXSpinBarComponent_;
	}
};

