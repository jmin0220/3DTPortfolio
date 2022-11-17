#pragma once
#include "VirtualPhysXActor.h"
#include "PhysXBoxGeometryComponent.h"


// Ό³Έν :
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

	std::string TexName;

public:
	inline std::shared_ptr<GameEngineFBXStaticRenderer> GetRenderer()
	{
		return Renderer_;
	}
};

