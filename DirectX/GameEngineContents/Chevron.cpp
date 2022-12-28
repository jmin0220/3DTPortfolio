#include "PreCompile.h"
#include "Chevron.h"

int Chevron::Num = 0;

Chevron::Chevron() :
	RotY(420.0f),
	ServerActivated_(false)
{

	Num++;
	MyNum = Num;
}

Chevron::~Chevron() 
{
}

void Chevron::Start()
{
	ChevronRenderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	ChevronRenderer_->SetFBXMesh("Chevron.FBX","CustomDefferedColor");

	PropellerRenderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	PropellerRenderer_->SetFBXMesh("Propeller.FBX", "CustomDefferedColor");
	PropellerRenderer_->GetTransform().SetLocalScale({ 3,3,3  });
	PropellerRenderer_->GetTransform().SetLocalPosition({ 0,-2.5f,0 });

	{
		std::vector<std::vector< std::shared_ptr<GameEngineRenderUnit>>>& UnitSet = ChevronRenderer_->GetAllRenderUnit();
		for (std::vector< std::shared_ptr<GameEngineRenderUnit>>& Units : UnitSet)
		{
			for (std::shared_ptr<GameEngineRenderUnit> Unit : Units)
			{
				Unit->GetRenderer()->RenderOptionInst.IsNormal = 0;
			}
		}
	}

	{
		std::vector<std::vector< std::shared_ptr<GameEngineRenderUnit>>>& UnitSet = PropellerRenderer_->GetAllRenderUnit();
		for (std::vector< std::shared_ptr<GameEngineRenderUnit>>& Units : UnitSet)
		{
			for (std::shared_ptr<GameEngineRenderUnit> Unit : Units)
			{
				Unit->GetRenderer()->RenderOptionInst.IsNormal = 0;
			}
		}
	}
}

void Chevron::Update(float _DeltaTime)
{

	if (true == GameServer::GetInst()->CheckServerSignal(ServerFlag::S_StageIdleChangeOver))
	{
		ServerActivated_ = true;
	}

	if (false == ServerActivated_)
	{
		return;
	}

	if (MyNum >= 7)
	{
		PropellerRenderer_->GetTransform().SetLocalRotate({ 0,RotY * -_DeltaTime ,0 });
	}
	else
	{
		PropellerRenderer_->GetTransform().SetLocalRotate({ 0,RotY * _DeltaTime ,0 });
	}
}

