#pragma once
#include "VirtualPhysXActor.h"
#include "PhysXConvexDynamicComponent.h"
#include "PhysXTriMeshGeometryComponent.h"
#include "PhysXBoxGeometryComponent.h"

// Ό³Έν :
class HoopsScythe	:	public VirtualPhysXActor
{
public:
	// constrcuter destructer
	HoopsScythe();
	~HoopsScythe();

	// delete Function
	HoopsScythe(const HoopsScythe& _Other) = delete;
	HoopsScythe(HoopsScythe&& _Other) noexcept = delete;
	HoopsScythe& operator=(const HoopsScythe& _Other) = delete;
	HoopsScythe& operator=(HoopsScythe&& _Other) noexcept = delete;

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
	std::shared_ptr<PhysXTriMeshGeometryComponent> PhysXTriGeometry_;
	std::shared_ptr<PhysXConvexDynamicComponent> PhysXConvexGeometry_;
	std::shared_ptr< PhysXBoxGeometryComponent> PhysXBoxGeometry_;
	std::shared_ptr<GameEngineFBXStaticRenderer> Renderer_;
};

