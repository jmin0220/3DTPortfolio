#include "PreCompile.h"
#include "IntroduceGame.h"

IntroduceGame::IntroduceGame() 
	:IsLoadingEnd_(false)
	,Time_(0.0f)
{
}

IntroduceGame::~IntroduceGame() 
{
}

void IntroduceGame::Start()
{
	Game_ = CreateComponent<GameEngineUIRenderer>();
	Game_->SetTexture("Intro_DoorDash.png");
	Game_->GetTransform().SetWorldScale({ 1600.0f,900.0f });
}

void IntroduceGame::Update(float _DeltaTime)
{
	//Time_ += _DeltaTime;

	//if (Time_ >= 4.0f)//���߿� �ε��� �Ϸ�Ǹ� ������ �������� ����
	//{
	//	IsLoadingEnd_ = true;
	//}

	//if (IsLoadingEnd_ == true)
	//{
	//	Game_->Off();
	//}
}

void IntroduceGame::LevelStartEvent()
{
	/*IsLoadingEnd_ = false;
	Time_ = 0.0f;
	Game_->On();*/
}

void IntroduceGame::LevelEndEvent()
{
}
