#pragma once
#include "VirtualPhysXActor.h"
#include "PhysXTriMeshGeometryComponent.h"
#include "PhysXBoxGeometryComponent.h"

// Ό³Έν :
class HoopsBox	: public VirtualPhysXActor
{
public:
	// constrcuter destructer
	HoopsBox();
	~HoopsBox();

	// delete Function
	HoopsBox(const HoopsBox& _Other) = delete;
	HoopsBox(HoopsBox&& _Other) noexcept = delete;
	HoopsBox& operator=(const HoopsBox& _Other) = delete;
	HoopsBox& operator=(HoopsBox&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void LevelStartEvent() override;

	//void OffEvent();
	//void OnEvent();

	void CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics) override;
private:
	std::shared_ptr<GameEngineFBXStaticRenderer> Renderer_;
	std::shared_ptr< PhysXTriMeshGeometryComponent> PhysXTriGeometry_;
	std::shared_ptr< PhysXBoxGeometryComponent> PhysXBoxGeometry_;
	std::string Name_;
public:
	void SetFBX(std::string _Name)
	{
		Name_ = _Name;
		Renderer_->SetFBXMesh(Name_, "Texture");
	}

};

