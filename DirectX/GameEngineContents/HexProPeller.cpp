#include "PreCompile.h"
#include "HexProPeller.h"

int HexProPeller::Num = 0;


HexProPeller::HexProPeller() :
	JumboNum(0)
{
}

HexProPeller::~HexProPeller()
{
}

void HexProPeller::Start()
{
	Renderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
}

void HexProPeller::Update(float _DeltaTime)
{
	if (JumboNum % 2 == 0)
	{
		Renderer_->GetTransform().SetLocalRotate({ 0,180.0f * _DeltaTime });
	}
	else
	{
		Renderer_->GetTransform().SetLocalRotate({ 0,180.0f * -_DeltaTime });
	}
}

