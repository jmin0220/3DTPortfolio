#pragma once
#include "VirtualPhysXActor.h"
#include "PhysXTriMeshGeometryComponent.h"

// Ό³Έν :
class HoopsRamp	:	public VirtualPhysXActor
{
public:
	// constrcuter destructer
	HoopsRamp();
	~HoopsRamp();

	// delete Function
	HoopsRamp(const HoopsRamp& _Other) = delete;
	HoopsRamp(HoopsRamp&& _Other) noexcept = delete;
	HoopsRamp& operator=(const HoopsRamp& _Other) = delete;
	HoopsRamp& operator=(HoopsRamp&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void LevelStartEvent() override;

	//void OffEvent();
	//void OnEvent();

	void CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics) override;
private:
	std::shared_ptr<GameEngineFBXStaticRenderer> Renderer_;
	std::shared_ptr<GameEngineFBXStaticRenderer> Renderer2_;
	std::shared_ptr< PhysXTriMeshGeometryComponent> PhysXTriGeometry_;
	std::shared_ptr< PhysXTriMeshGeometryComponent> PhysXTriGeometry2_;

	std::string Name_;
	std::string Name2_;

public:
	void SetFBX(std::string _Name, std::string _Name2)
	{
		Name_ = _Name;
		Renderer_->SetFBXMesh(Name_, "CustomDefferedColor");
		{
			std::vector<std::vector< std::shared_ptr<GameEngineRenderUnit>>>& UnitSet = Renderer_->GetAllRenderUnit();
			for (std::vector< std::shared_ptr<GameEngineRenderUnit>>& Units : UnitSet)
			{
				for (std::shared_ptr<GameEngineRenderUnit> Unit : Units)
				{
					Unit->GetRenderer()->RenderOptionInst.IsNormal = 0;
				}
			}
		}
		Name2_ = _Name2;
		Renderer2_->SetFBXMesh(Name2_, "CustomDefferedColor");
		{
			std::vector<std::vector< std::shared_ptr<GameEngineRenderUnit>>>& UnitSet = Renderer2_->GetAllRenderUnit();
			for (std::vector< std::shared_ptr<GameEngineRenderUnit>>& Units : UnitSet)
			{
				for (std::shared_ptr<GameEngineRenderUnit> Unit : Units)
				{
					Unit->GetRenderer()->RenderOptionInst.IsNormal = 0;
				}
			}
		}
	}

};

