#pragma once
#include "VirtualPhysXActor.h"
#include "PhysXBoxGeometryComponent.h"

// Ό³Έν :
class MovingBar	:	public VirtualPhysXActor
{
public:
	// constrcuter destructer
	MovingBar();
	~MovingBar();

	// delete Function
	MovingBar(const MovingBar& _Other) = delete;
	MovingBar(MovingBar&& _Other) noexcept = delete;
	MovingBar& operator=(const MovingBar& _Other) = delete;
	MovingBar& operator=(MovingBar&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void LevelStartEvent() override;

	//void OffEvent();
	//void OnEvent();

	void CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics) override;
private:
	float Speed_;
	static int Num;
	int MyNum;
	std::shared_ptr<PhysXBoxGeometryComponent> PhysXBoxGeometry_;
	std::shared_ptr<GameEngineFBXStaticRenderer> Renderer_;

	bool Switch_;

	void Move(float _DeltaTime);

private:
	bool ServerActivated_;
};

