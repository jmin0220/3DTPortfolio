#include "PreCompile.h"
#include "Bingle.h"

Bingle::Bingle() 
	:BingleTime_(0.0f)
{
}

Bingle::~Bingle() 
{
}

void Bingle::Start()
{
	Loading_ = CreateComponent<GameEngineUIRenderer>();
	Loading_->GetTransform().SetWorldScale({ 64.0f,64.0f });
	Loading_->SetTexture("UI_SPINNER.png");
	Loading_->SetPivot(PIVOTMODE::CENTER);
	Loading_->GetTransform().SetWorldPosition({ -760.0f,-410.0f });

	Face_ = CreateComponent<GameEngineUIRenderer>();
	Face_->GetTransform().SetWorldScale({ 54.0f,54.0f });
	Face_->SetTexture("VFX_Mask_FG_Face_01.png");
	Face_->SetPivot(PIVOTMODE::CENTER);
	Face_->GetTransform().SetWorldPosition({ -760.0f,-410.0f });
}

void Bingle::Update(float _DeltaTime)
{
	BingleTime_ -= _DeltaTime * 200.0f;
	Loading_->GetTransform().SetWorldRotation({0,0,BingleTime_});
}

void Bingle::LevelStartEvent()
{
	BingleTime_ = 0.0f;
}

