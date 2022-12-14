#include "PreCompile.h"
#include "CrownCount.h"

CrownCount::CrownCount() 
{
}

CrownCount::~CrownCount() 
{
}

void CrownCount::Start()
{
	CurrentCrownCount_ = 0;
	RewardCrownCount_ = 1;

	Renderer_ = CreateComponent<GameEngineUIRenderer>();
	Renderer_->GetTransform().SetLocalScale({ 194*0.5f,264 * 0.5f });
	Renderer_->SetTexture("CrownReward.png");
	Renderer_->SetPivot(PIVOTMODE::CENTER);
	Renderer_->GetTransform().SetLocalPosition({ -735.0f, 380.0f });

	Face_ = CreateComponent<GameEngineUIRenderer>();
	Face_->GetTransform().SetLocalScale({ 111 * 0.5f,111 * 0.5f });
	Face_->SetTexture("PlayerLevelFace.png");
	Face_->SetPivot(PIVOTMODE::CENTER);
	Face_->GetTransform().SetLocalPosition({ -735.0f, 380.0f });

	CountBG_ = CreateComponent<GameEngineUIRenderer>();
	CountBG_->GetTransform().SetLocalScale({ 111.0f ,34.0f });
	CountBG_->SetTexture("CrownBG.png");
	CountBG_->SetPivot(PIVOTMODE::CENTER);
	CountBG_->GetTransform().SetLocalPosition({ -735.0f, 335.0f });

	Icon_ = CreateComponent<GameEngineUIRenderer>();
	Icon_->GetTransform().SetLocalScale({ 69*0.7f ,68 * 0.7f });
	Icon_->SetTexture("UI_CrownIcon.png");
	Icon_->SetPivot(PIVOTMODE::CENTER);
	Icon_->GetTransform().SetLocalPosition({ -765.0f, 335.0f });

	Font_ = CreateComponent<GameEngineFontRenderer>();
	//Font_->ChangeCamera(CAMERAORDER::UICAMERA);
	Font_->SetSize(20.0f);
	Font_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	Font_->SetColor({ 1.0f,1.0f,1.0f });
	Font_->SetScreenPostion({ 87.0f, 103.0f });
	Font_->SetText(std::to_string(CurrentCrownCount_)+"/" + std::to_string(RewardCrownCount_),"Titan One");
}

void CrownCount::Update(float _DeltaTime)
{
}

