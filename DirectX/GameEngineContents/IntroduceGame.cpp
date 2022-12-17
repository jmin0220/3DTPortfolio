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
	Game_->GetTransform().SetWorldScale({ 1600.0f,900.0f, 1.0f });
}

void IntroduceGame::Update(float _DeltaTime)
{

}

void IntroduceGame::LevelStartEvent()
{

}

void IntroduceGame::LevelEndEvent()
{
}
