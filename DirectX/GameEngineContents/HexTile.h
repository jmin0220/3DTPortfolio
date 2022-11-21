#pragma once
#include "VirtualPhysXActor.h"
#include "PhysXBoxGeometryComponent.h"


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
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void LevelStartEvent() override;

	void OffEvent();
	void OnEvent();

	void CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics) override;

private:
	std::shared_ptr<PhysXBoxGeometryComponent> PhysXBoxGeometry_;
	std::shared_ptr<GameEngineFBXStaticRenderer> Renderer_;
	std::shared_ptr<GameEngineCollision> Collision_;   //트리거 콜리전
	std::string TexName;

	bool Trigger_;

public:
	inline std::shared_ptr<GameEngineFBXStaticRenderer> GetRenderer()
	{
		return Renderer_;
	}

	//CollisionReturn CheckCol(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);
};

