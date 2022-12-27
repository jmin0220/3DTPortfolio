#pragma once
#include "VirtualPhysXActor.h"
#include "PhysXBoxGeometryComponent.h"
#include "PhysXConvexGeometryComponent.h"

// 설명 :
class HexTile :public VirtualPhysXActor
{
public:
	// constrcuter destructer
	HexTile();
	~HexTile();

	// delete Function
	HexTile(const HexTile& _Other) = delete;
	HexTile(HexTile&& _Other) noexcept = delete;
	HexTile& operator=(const HexTile& _Other) = delete;
	HexTile& operator=(HexTile&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void LevelStartEvent() override;

	void OffEvent();
	void OnEvent();

	void CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics) override;

private:
	HexTileState Mode_;

	std::shared_ptr<PhysXConvexGeometryComponent> PhysXHexTileGeometry_;
	std::shared_ptr<PhysXBoxGeometryComponent> PhysXBoxGeometry_;
	std::shared_ptr<GameEngineFBXStaticRenderer> Renderer_;
	std::shared_ptr<GameEngineCollision> Collision_;   //트리거 콜리전
	std::string TexName;

	float4 CurPos;
	float4 MyPos;

	MeshPixelData MeshPixelData_;

	LightData Data;

	float Speed_;
	bool Trigger_;
	bool Shake_;
	bool Flag_;

	GameEngineStateManager StateManager_;

	// 서버
	bool ServerActivated_;

	void MoveStart(const StateInfo& _Info);
	void MoveUpdate(float _DeltaTime, const StateInfo& _Info);

	void ShakeStart(const StateInfo& _Info);
	void ShakeUpdate(float _DeltaTime, const StateInfo& _Info);
public:
	inline std::shared_ptr<GameEngineFBXStaticRenderer> GetRenderer()
	{
		return Renderer_;
	}

	void SetTex(std::string _Name);
	//CollisionReturn CheckCol(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);
};

