#include "PreCompile.h"
#include "HexProPeller.h"

int HexProPeller::Num = 0;


HexProPeller::HexProPeller() :
	JumboNum(0),
	ServerActivated_(false)
{
}

HexProPeller::~HexProPeller()
{
}

void HexProPeller::Start()
{
	Renderer_ = CreateComponent<GameEngineFBXStaticRenderer>();

	std::vector<std::vector< std::shared_ptr<GameEngineRenderUnit>>>& UnitSet = Renderer_->GetAllRenderUnit();
	for (std::vector< std::shared_ptr<GameEngineRenderUnit>>& Units : UnitSet)
	{
		for (std::shared_ptr<GameEngineRenderUnit> Unit : Units)
		{
			Unit->GetRenderer()->RenderOptionInst.IsNormal = 0;
		}
	}
}

void HexProPeller::Update(float _DeltaTime)
{
	if (true == GameServer::GetInst()->CheckServerSignal(ServerFlag::S_StageIdleChangeOver))
	{
		ServerActivated_ = true;
	}

	if (false == ServerActivated_)
	{
		return;
	}

	if (JumboNum % 2 == 0)
	{
		Renderer_->GetTransform().SetLocalRotate({ 0,180.0f * _DeltaTime });
	}
	else
	{
		Renderer_->GetTransform().SetLocalRotate({ 0,180.0f * -_DeltaTime });
	}
}

