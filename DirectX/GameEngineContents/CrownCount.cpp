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
	CurrentCrownCount = 0;
	RewardCrownCount = 1;

	Renderer = CreateComponent<GameEngineUIRenderer>();
	Renderer->GetTransform().SetLocalScale({ 194*0.5f,264 * 0.5f });
	Renderer->SetTexture("CrownReward.png");
	Renderer->SetPivot(PIVOTMODE::CENTER);
	Renderer->GetTransform().SetLocalPosition({ -735,380 });

	Face = CreateComponent<GameEngineUIRenderer>();
	Face->GetTransform().SetLocalScale({ 111 * 0.5f,111 * 0.5f });
	Face->SetTexture("PlayerLevelFace.png");
	Face->SetPivot(PIVOTMODE::CENTER);
	Face->GetTransform().SetLocalPosition({ -735,380 });

	CountBG = CreateComponent<GameEngineUIRenderer>();
	CountBG->GetTransform().SetLocalScale({ 111 ,34 });
	CountBG->SetTexture("CrownBG.png");
	CountBG->SetPivot(PIVOTMODE::CENTER);
	CountBG->GetTransform().SetLocalPosition({ -735,335 });

	Icon = CreateComponent<GameEngineUIRenderer>();
	Icon->GetTransform().SetLocalScale({ 69*0.7f ,68 * 0.7f });
	Icon->SetTexture("UI_CrownIcon.png");
	Icon->SetPivot(PIVOTMODE::CENTER);
	Icon->GetTransform().SetLocalPosition({ -765,335 });

	Font = CreateComponent<GameEngineFontRenderer>();
	Font->ChangeCamera(CAMERAORDER::UICAMERA);
	Font->SetSize(20.0f);
	Font->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	Font->SetColor({ 1.0f,1.0f,1.0f });
	Font->SetScreenPostion({ 87,103 });
	Font->SetText(std::to_string(CurrentCrownCount)+"/" + std::to_string(RewardCrownCount),"Titan One");
}

void CrownCount::Update(float _DeltaTime)
{
}

