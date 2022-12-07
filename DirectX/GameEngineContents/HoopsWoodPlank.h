#pragma once
#include "PhysXBoxGeometryComponent.h"
#include "PhysXConvexGeometryComponent.h"
#include "VirtualPhysXActor.h"

struct MaskData
{
	float4 Data_;
};


// Ό³Έν :
class HoopsWoodPlank	:	public VirtualPhysXActor
{
public:
	// constrcuter destructer
	HoopsWoodPlank();
	~HoopsWoodPlank();

	// delete Function
	HoopsWoodPlank(const HoopsWoodPlank& _Other) = delete;
	HoopsWoodPlank(HoopsWoodPlank&& _Other) noexcept = delete;
	HoopsWoodPlank& operator=(const HoopsWoodPlank& _Other) = delete;
	HoopsWoodPlank& operator=(HoopsWoodPlank&& _Other) noexcept = delete;


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
	std::shared_ptr<PhysXBoxGeometryComponent> PhysXBoxGeometry_;
	std::shared_ptr<PhysXConvexGeometryComponent> PhysXConvexGeometry_;
	std::shared_ptr<GameEngineFBXStaticRenderer> Renderer_;


	float4 Rotation_;




	MaskData Data;
public:
	inline void SetRotation(float4 _Rot)
	{
		Rotation_ = _Rot;
	}
};

