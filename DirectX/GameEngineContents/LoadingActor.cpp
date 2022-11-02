#include "PreCompile.h"
#include "LoadingActor.h"

LoadingActor::LoadingActor() 
{
}

LoadingActor::~LoadingActor() 
{
}

void LoadingActor::Start()
{
	Time_ = 0.0f;

	BG_ = CreateComponent<GameEngineTextureRenderer>();
	BG_->GetTransform().SetWorldScale({ 1600,900 });
	BG_->SetTexture("LoadingBG.png");
	BG_->SetPivot(PIVOTMODE::CENTER);
	BG_->GetTransform().SetWorldPosition({ 0,0 });

	CreateGames();
}

void LoadingActor::Update(float _DeltaTime)
{
	Time_ += GameEngineTime::GetDeltaTime();
	for (int i = 0; i < 5; i++)
	{
		Games_[i]->GetTransform().SetWorldPosition({ (800.0f * i) - (Time_ * 1000.0f) , 0.0f });
	}
}

void LoadingActor::CreateGames()
{
	for (int i = 0; i < 5; i++)
	{
		Games_[i] = CreateComponent<GameEngineTextureRenderer>();
		Games_[i]->GetTransform().SetWorldScale({ 800,450 });
		Games_[i]->SetTexture("Splash_DoorRush.png");
		Games_[i]->SetPivot(PIVOTMODE::RIGHT);//����? �Ǻ��� �ݴ�� ��µ�?
		Games_[i]->GetTransform().SetWorldPosition({ (800.0f * i) , 0.0f });

		//i��°�� �׸��� x��ǥ�� -800�� �����ϸ� i+10(��������ȣ)�ڷ� ���δ�
	}
}
