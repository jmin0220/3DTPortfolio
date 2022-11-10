#include "PreCompile.h"
#include "NamePlate.h"

NamePlate::NamePlate() 
	:Renderer_(nullptr)
	,Font_(nullptr)
{
}

NamePlate::~NamePlate() 
{
}

void NamePlate::Start()
{
	Renderer_ = CreateComponent<GameEngineUIRenderer>();
	Renderer_->GetTransform().SetLocalScale({606 * 0.6f,166 * 0.6f});
	Renderer_->SetTexture("NamePlate.png");
	Renderer_->SetPivot(PIVOTMODE::LEFTTOP);
	Renderer_->GetTransform().SetLocalPosition({ -670.0f,425.0f });

	Font_ = CreateComponent<GameEngineFontRenderer>();
	Font_->ChangeCamera(CAMERAORDER::UICAMERA);
	Font_->SetSize(30.0f);
	Font_->SetColor({ 1.0f,1.0f,1.0f });
	Font_->SetParent(Renderer_.get());
	Font_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	Font_->SetScreenPostion({ 330.0f, 50.0f });
	Font_->SetText("FallGuy", "Noto Sans CJK SC");
}

void NamePlate::Update(float _DeltaTime)
{
}

