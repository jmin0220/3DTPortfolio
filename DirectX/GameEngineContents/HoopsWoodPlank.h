#pragma once
#include "PhysXBoxGeometryComponent.h"
#include "PhysXConvexGeometryComponent.h"
#include "PhysXConvexDynamicComponent.h"
#include "VirtualPhysXActor.h"

struct MaskData
{
	float4 Data_;
};


// 설명 :
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
	static int Num;
	int MyNum;
	float Rot_;
	bool Switch;
	float Timer_;
	std::shared_ptr<PhysXBoxGeometryComponent> PhysXBoxGeometry_;
	std::shared_ptr<PhysXConvexDynamicComponent> PhysXConvexGeometry_;
	std::shared_ptr<GameEngineFBXStaticRenderer> Renderer_;


	float4 Rotation_;

	MaskData Data;

	// 서버
	bool ServerActivated_;


public:
	inline void SetRotation(float4 _Rot)
	{
		Rotation_ = _Rot;
	}
};

