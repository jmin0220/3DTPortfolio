#include "PreCompile.h"
#include "LobbySetUI.h"
#include "CrownCount.h"
#include "NamePlate.h"
#include "NoneButton.h"
#include "NoneMoney.h"
#include "PlayButton.h"
#include "SelectShowButton.h"
#include "TopMenu.h"
#include "Cursor.h"

LobbySetUI::LobbySetUI() 
{
}

LobbySetUI::~LobbySetUI() 
{
}

void LobbySetUI::Start()
{
}

void LobbySetUI::Update(float _DeltaTime)
{
}

void LobbySetUI::LevelStartEvent()
{
	BG_ = CreateComponent<GameEngineTextureRenderer>();
	BG_->SetTexture("LobbyBG.png");
	BG_->SetPivot(PIVOTMODE::CENTER);
	BG_->GetTransform().SetWorldScale({ 1600,900 });
	BG_->GetTransform().SetWorldPosition({ 0,0,1500 });//1500이 맥스거리..? 그 이상하면 퍼런배경 드러남

	Circle1_ = CreateComponent<GameEngineTextureRenderer>();
	Circle1_->SetTexture("Circle1.png");
	Circle1_->SetPivot(PIVOTMODE::CENTER);
	Circle1_->GetTransform().SetWorldScale({ 1600,900 });

	Circle1_->GetRenderUnit().SetPipeLine("TextureLoop");
	Circle1_->GetRenderUnit().EngineShaderResourcesSetting(Circle1_);
	Circle1_->GetRenderUnit().ShaderResources.SetTexture("Tex", "Circle1.png");
	float4 SlicePos_ = float4(1, 0, 0, 0);
	if (true == Circle1_->GetRenderUnit().ShaderResources.IsConstantBuffer("SliceData"))
	{
		Circle1_->GetRenderUnit().ShaderResources.SetConstantBufferLink("SliceData", SlicePos_);
	}
	Circle1_->GetRenderUnit().ShaderResources.SetTexture("Mask", "LobbyBG.png");

	CrownCount_ = GetLevel()->CreateActor<CrownCount>();
	NamePlate_ = GetLevel()->CreateActor<NamePlate>();
	NoneButton_ = GetLevel()->CreateActor<NoneButton>();
	NoneMoney_ = GetLevel()->CreateActor<NoneMoney>();
	PlayButton_ = GetLevel()->CreateActor<PlayButton>();
	SelectShowButton_ = GetLevel()->CreateActor<SelectShowButton>();
	TopMenu_ = GetLevel()->CreateActor<TopMenu>();
	Mouse_ = GetLevel()->CreateActor<Cursor>();
}

void LobbySetUI::LevelEndEvent()
{
	CrownCount_->GetLevel()->Death();
	NamePlate_->GetLevel()->Death();
	NoneButton_->GetLevel()->Death();
	NoneMoney_->GetLevel()->Death();
	PlayButton_->GetLevel()->Death();
	SelectShowButton_->GetLevel()->Death();
	TopMenu_->GetLevel()->Death();
	Mouse_->GetLevel()->Death();
}

