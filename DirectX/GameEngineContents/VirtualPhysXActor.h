#pragma once

// Ό³Έν :
class VirtualPhysXActor : public GameEngineActor
{
public:
	// constrcuter destructer
	VirtualPhysXActor();
	~VirtualPhysXActor();

	// delete Function
	VirtualPhysXActor(const VirtualPhysXActor& _Other) = delete;
	VirtualPhysXActor(VirtualPhysXActor&& _Other) noexcept = delete;
	VirtualPhysXActor& operator=(const VirtualPhysXActor& _Other) = delete;
	VirtualPhysXActor& operator=(VirtualPhysXActor&& _Other) noexcept = delete;


protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	virtual void CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics) = 0;
private:

};

