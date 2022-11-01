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
	Time = 0.0f;

	BG = CreateComponent<GameEngineTextureRenderer>();
	BG->GetTransform().SetWorldScale({ 1600,900 });
	BG->SetTexture("LoadingBG.png");
	BG->SetPivot(PIVOTMODE::CENTER);
	BG->GetTransform().SetWorldPosition({ 0,0 });

	CreateGames();
}

void LoadingActor::Update(float _DeltaTime)
{
	Time += GameEngineTime::GetDeltaTime();
	for (int i = 0; i < 5; i++)
	{
		Games[i]->GetTransform().SetWorldPosition({ (800.0f * i) - (Time * 1000.0f) , 0.0f });
	}
}

void LoadingActor::CreateGames()
{
	for (int i = 0; i < 5; i++)
	{
		Games[i] = CreateComponent<GameEngineTextureRenderer>();
		Games[i]->GetTransform().SetWorldScale({ 800,450 });
		Games[i]->SetTexture("Splash_DoorRush.png");
		Games[i]->SetPivot(PIVOTMODE::RIGHT);//뭐지? 피봇이 반대로 됬는데?
		Games[i]->GetTransform().SetWorldPosition({ (800.0f * i) , 0.0f });

		//i번째의 그림의 x좌표가 -800에 도달하면 i+10(마지막번호)뒤로 붙인다
	}
}
