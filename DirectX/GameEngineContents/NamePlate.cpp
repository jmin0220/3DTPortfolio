#include "PreCompile.h"
#include "NamePlate.h"

NamePlate::NamePlate() 
	:Renderer(nullptr)
	,Font(nullptr)
{
}

NamePlate::~NamePlate() 
{
}

void NamePlate::Start()
{
	Renderer = CreateComponent<GameEngineUIRenderer>();
	Renderer->GetTransform().SetLocalScale({606 * 0.6f,166 * 0.6f});
	Renderer->SetTexture("NamePlate.png");
	Renderer->SetPivot(PIVOTMODE::LEFTTOP);
	Renderer->GetTransform().SetLocalPosition({ -670,430 });

	Font = CreateComponent<GameEngineFontRenderer>();
	Font->ChangeCamera(CAMERAORDER::UICAMERA);
	Font->SetSize(30.0f);
	Font->SetColor({ 1.0f,1.0f,1.0f });
	Font->SetParent(Renderer);
	Font->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	Font->SetScreenPostion({ 330,45 });
	Font->SetText("플레이어", "Noto Sans CJK SC");
}

void NamePlate::Update(float _DeltaTime)
{
}

