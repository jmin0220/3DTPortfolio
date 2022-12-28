#pragma once
#include "VirtualPhysXActor.h"
#include "PhysXConvexDynamicComponent.h"
#include "PhysXTriMeshGeometryComponent.h"

// 설명 :
class HoopsScoreRing	:	public VirtualPhysXActor, public GameServerObject
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
	bool Flag_;;
	float Timer_;
	bool IsCol_;

	int Dir_;

	float4 PrevPos;
	
	std::shared_ptr<GameEngineFBXStaticRenderer> Renderer_;
	std::shared_ptr< PhysXTriMeshGeometryComponent> PhysXTriGeometry_;
	std::shared_ptr<GameEngineCollision> Collision_;

	CollisionReturn CheckCollision(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);
public:
	void SetFBX(std::string _Name)
	{
		Renderer_->SetFBXMesh(_Name, "Texture");
	}

	std::shared_ptr<GameEngineFBXStaticRenderer> GetRenderer()
	{
		return Renderer_;
	}

	inline void SetRenderer()
	{
		Renderer_->On();
	}
	
	inline void SetFlag()
	{
		Flag_ = !Flag_;
	}

	inline void SetPrevPos(float4 _Pos)
	{
		PrevPos = _Pos;
	}

	inline bool GetFlag()
	{
		return Flag_;
	}

	// 서버
public:
	void PhysXInit();
	void UpdateHoops(float _DeltaTime);

	bool ServerActivated_;
};

