#pragma once
#include "VirtualPhysXActor.h"
#include "PhysXConvexDynamicComponent.h"

// Ό³Έν :
class HoopsScoreRing	:	public VirtualPhysXActor
{
public:
	// constrcuter destructer
	HoopsScoreRing();
	~HoopsScoreRing();

	// delete Function
	HoopsScoreRing(const HoopsScoreRing& _Other) = delete;
	HoopsScoreRing(HoopsScoreRing&& _Other) noexcept = delete;
	HoopsScoreRing& operator=(const HoopsScoreRing& _Other) = delete;
	HoopsScoreRing& operator=(HoopsScoreRing&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void LevelStartEvent() override;

	//void OffEvent();
	//void OnEvent();

	void CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics) override;
private:
	float Rot_;
	bool Switch;
	//std::shared_ptr<PhysXBoxGeometryComponent> PhysXBoxGeometry_;
	//std::shared_ptr<PhysXConvexGeometryComponent> PhysXConvexGeometry_;
	std::shared_ptr<GameEngineFBXStaticRenderer> Renderer_;

public:
	void SetFBX(std::string _Name)
	{
		Renderer_->SetFBXMesh(_Name, "Texture");
	}
};

