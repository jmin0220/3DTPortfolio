#pragma once
#include "VirtualPhysXActor.h"
#include "PhysXConvexDynamicComponent.h"
#include "PhysXTriMeshGeometryComponent.h"

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
	
	std::shared_ptr<GameEngineFBXStaticRenderer> Renderer_;
	std::shared_ptr<PhysXConvexDynamicComponent> PhysXConvexGeometry_;
	std::shared_ptr< PhysXTriMeshGeometryComponent> PhysXTriGeometry_;
	std::shared_ptr<GameEngineCollision> Collision_;
public:
	void SetFBX(std::string _Name)
	{
		Renderer_->SetFBXMesh(_Name, "Texture");
	}
};

