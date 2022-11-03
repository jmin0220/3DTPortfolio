#include "PreCompile.h"
#include "LoadingActor.h"

#include <GameEngineBase/GameEngineRandom.h>

LoadingActor::LoadingActor() 
{
}

LoadingActor::~LoadingActor() 
{
}

enum class MapSelect
{
	Splash_AirTime,
	Splash_BasketFall,
	Splash_BiggestFan,
	Splash_BigShots,
	Splash_BlastBall,
	Splash_BlockParty,

};

void LoadingActor::Start()
{
	Time_ = 0.0f;

	BG_ = CreateComponent<GameEngineTextureRenderer>();
	BG_->GetTransform().SetWorldScale({ 1600.0f,900.0f });
	BG_->SetTexture("LoadingBG.png");
	BG_->SetPivot(PIVOTMODE::CENTER);
	BG_->GetTransform().SetWorldPosition({ 0.0f,0.0f });

	CreateGames();

	Game_ = CreateComponent<GameEngineTextureRenderer>();
	Game_->GetTransform().SetWorldScale({ 1000.0f,650.0f });
	Game_->SetTexture("Splash_DoorRush.png");
	Game_->SetPivot(PIVOTMODE::CENTER);
	Game_->GetTransform().SetWorldPosition({ 0.0f,0.0f });

	Font_ = CreateComponent<GameEngineFontRenderer>();
	Font_->SetSize(60.0f);
	Font_->SetText("다음은..", "Noto Sans CJK SC");
	Font_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	Font_->ChangeCamera(CAMERAORDER::UICAMERA);
	Font_->SetScreenPostion({ 800.0f, 30.0f });

	Exit_ = CreateComponent<GameEngineUIRenderer>();
	Exit_->GetTransform().SetWorldScale({ 200.0f,60.0f });
	Exit_->SetTexture("Exit.png");
	Exit_->SetPivot(PIVOTMODE::RIGHTBOT);
	Exit_->GetTransform().SetWorldPosition({800.0f,-450.0f });

	ExitButton_ = CreateComponent<GameEngineUIRenderer>();
	ExitButton_->GetTransform().SetWorldScale({ 95.0f * 0.5f,55.0f * 0.5f });
	ExitButton_->SetTexture("Tab.png");
	ExitButton_->SetPivot(PIVOTMODE::CENTER);
	ExitButton_->GetTransform().SetWorldPosition({ 670.0f,-420.0f });

	ExitFont_ = CreateComponent<GameEngineFontRenderer>();
	ExitFont_->SetSize(20.0f);
	ExitFont_->SetText("나가기", "Noto Sans CJK SC");
	ExitFont_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	ExitFont_->ChangeCamera(CAMERAORDER::UICAMERA);
	ExitFont_->SetScreenPostion({ 1530.0f, 855.0f });
}

void LoadingActor::Update(float _DeltaTime)
{
	Time_ += GameEngineTime::GetDeltaTime();
	float Speed = 1000.0f;
	
	{
		MapSelect Map;

		static_cast<int>(MapSelect::Splash_AirTime);
		
		if (Time_ > 1.0f)
		{
			Map = static_cast<MapSelect>(GameEngineRandom::MainRandom.RandomInt(0, 5));

			switch (Map)
			{
			case MapSelect::Splash_AirTime:
				Game_->SetTexture("Splash_AirTime.png");
				Time_ = 0.0f;
				break;
			case MapSelect::Splash_BasketFall:
				Game_->SetTexture("Splash_Basketfall.png");
				Time_ = 0.0f;
				break;
			case MapSelect::Splash_BiggestFan:
				Game_->SetTexture("Splash_BiggestFan.png");
				Time_ = 0.0f;
				break;
			case MapSelect::Splash_BigShots:
				Game_->SetTexture("Splash_BigShots.png");
				Time_ = 0.0f;
				break;
			case MapSelect::Splash_BlastBall:
				Game_->SetTexture("Splash_BlastBall.png");
				Time_ = 0.0f;
				break;
			case MapSelect::Splash_BlockParty:
				Game_->SetTexture("Splash_BlockParty.png");
				Time_ = 0.0f;
				break;
			default:
				Game_->SetTexture("Splash_DoorRush.png");
				Time_ = 0.0f;
				break;
			}
		}
	}

	for (int i = 0; i < 5; i++)
	{
		Games_[i]->GetTransform().SetWorldMove({ -Speed * GameEngineTime::GetDeltaTime() , 0.0f, 0.0f });
		
		LastGamesPos_ = Games_[4]->GetTransform().GetWorldPosition().x + 780.0f;//맨 마지막 그림 끝좌표 가져온다(오차 땜에 -20)

		if (Games_[i]->GetTransform().GetWorldPosition().x <= -800.0f)
		{
			Games_[i]->GetTransform().SetWorldPosition({LastGamesPos_ + (i*800.0f), 0.0f});
		}
	}
}

void LoadingActor::CreateGames()
{
	for (int i = 0; i < 5; i++)
	{
		Games_[i] = CreateComponent<GameEngineTextureRenderer>();
		Games_[i]->GetTransform().SetWorldScale({ 800,450 });
		Games_[i]->SetTexture("Splash_DoorRush.png");
		Games_[i]->SetPivot(PIVOTMODE::RIGHT);//뭐지? 피봇이 반대로 됬는데?
		Games_[i]->GetTransform().SetWorldPosition({ (800.0f * i) , 0.0f });

	}
}
