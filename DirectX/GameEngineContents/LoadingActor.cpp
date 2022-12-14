#include "PreCompile.h"
#include "LoadingActor.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/magic_enum.hpp>
#include <GameEngineBase/GameEngineRandom.h>

LoadingActor::LoadingActor() 
{
}

LoadingActor::~LoadingActor() 
{
}


void LoadingActor::Start()
{
	Time_ = 0.0f;
	SuffleTime_ = 0.0f;

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
	//Font_->ChangeCamera(CAMERAORDER::UICAMERA);
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
	//ExitFont_->ChangeCamera(CAMERAORDER::UICAMERA);
	ExitFont_->SetScreenPostion({ 1530.0f, 855.0f });

	// 맵 셔플
	MapIndexs_ = { 0, 1, 2 };
	GetShuffledNumbers(MapIndexs_);
	Idx_ = 0;
	SelectedMap_ = static_cast<MapSelect>(MapIndexs_[Idx_]);
}

void LoadingActor::Update(float _DeltaTime)
{
	float Speed = 1000.0f;
	
	MainGameImage(_DeltaTime);

	for (int i = 0; i < 5; i++)
	{
		Games_[i]->GetTransform().SetWorldMove({ -Speed * _DeltaTime , 0.0f, 0.0f });
		
		LastGamesPos_ = Games_[4]->GetTransform().GetWorldPosition().x + 780.0f;//맨 마지막 그림 끝좌표 가져온다(오차 땜에 -20)

		if (Games_[i]->GetTransform().GetWorldPosition().x <= -800.0f)
		{
			MapSelect Map;
			Map = static_cast<MapSelect>(GameEngineRandom::MainRandom.RandomInt(0, 80));
			std::string picturename = magic_enum::enum_name(Map).data();
			//↑매직이넘을 사용해 이넘들을 string으로 저장

			Games_[i]->GetTransform().SetWorldPosition({LastGamesPos_ + (i*800.0f), 0.0f});
			Games_[i]->SetTexture(picturename + ".png");
			//밖으로넘어간 그림들을 다시 앞으로 오게하면서 이미지 새로 세팅
		}
	}

	// 6초마다 한번씩 맵 셔플
	{
		SuffleTime_ += _DeltaTime;
		if (SuffleTime_ > 6.0f)
		{
			GetShuffledNumbers(MapIndexs_);
			SuffleTime_ = 0.0f;
		}
	}
}

std::string_view LoadingActor::GetCurMap()
{
	std::string_view Data = magic_enum::enum_name(SelectedMap_);

	if (Data.empty())
	{
		Data = "";
	}

	return Data;
}

// 랜덤한 중복되지 않는 숫자 뽑기
void LoadingActor::GetShuffledNumbers(std::vector<int>& _Numbers)
{
	std::shuffle(_Numbers.begin(), _Numbers.end(), GameEngineRandom::MainRandom.GetFunc());
}

void LoadingActor::CreateGames()
{
	for (int i = 0; i < 5; i++)
	{
		MapSelect Map;
		Map = static_cast<MapSelect>(GameEngineRandom::MainRandom.RandomInt(0, 80));
		std::string picturename = magic_enum::enum_name(Map).data();
		//↑매직이넘을 사용해 이넘들을 string으로 저장

		Games_[i] = CreateComponent<GameEngineTextureRenderer>();
		Games_[i]->GetTransform().SetWorldScale({ 800,450 });
		Games_[i]->SetTexture(picturename + ".png");
		Games_[i]->SetPivot(PIVOTMODE::RIGHT);//뭐지? 피봇이 반대로 됬는데?
		Games_[i]->GetTransform().SetWorldPosition({ (800.0f * i) , 0.0f });

	}
}

// 메인게임인 큰 이미지를 1초 지나면 바꾼다
void LoadingActor::MainGameImage(float _DeltaTime)
{
	if (true == Select_)
	{
		//SelectedMap_ = static_cast<MapSelect>(GameEngineRandom::MainRandom.RandomInt(0, 2)); // 유효한 레벨
		Time_ = 0;
		return;
	}

	Time_ += _DeltaTime;
	
	if (Time_ < 1.0f)
	{
		return;
	}

	SelectMainGame();
	Time_ = 0.0f;
}


void LoadingActor::SelectMainGame()
{
	SelectedMap_ = static_cast<MapSelect>(MapIndexs_[Idx_++]);
	if (Idx_ == MapIndexs_.size())
	{
		Idx_ = 0;
	}

	switch (SelectedMap_)
	{
	case MapSelect::Splash_CoY_DoorDash:
		Game_->SetTexture("Splash_CoY_DoorDash.png");
		break;
	case MapSelect::Splash_JumpClub:
		Game_->SetTexture("Splash_JumpClub.png");
		break;
	case MapSelect::Splash_Hexagone:
		Game_->SetTexture("Splash_Hexagone.png");
		break;
	//case MapSelect::Splash_AirTime:
	//	Game_->SetTexture("Splash_AirTime.png");
	//	break;
	//case MapSelect::Splash_BasketFall:
	//	Game_->SetTexture("Splash_BasketFall.png");
	//	break;
	//case MapSelect::Splash_BiggestFan:
	//	Game_->SetTexture("Splash_BiggestFan.png");
	//	break;
	//case MapSelect::Splash_BigShots:
	//	Game_->SetTexture("Splash_BigShots.png");
	//	break;
	//case MapSelect::Splash_BlastBall:
	//	Game_->SetTexture("Splash_BlastBall.png");
	//	break;
	//case MapSelect::Splash_BlockParty:
	//	Game_->SetTexture("Splash_BlockParty.png");
	//	break;
	//case MapSelect::Splash_BlueJay:
	//	Game_->SetTexture("Splash_BlueJay.png");
	//	break;
	//case MapSelect::Splash_BounceParty:
	//	Game_->SetTexture("Splash_BounceParty.png");
	//	break;
	//case MapSelect::Splash_BubbleTrouble:
	//	Game_->SetTexture("Splash_BubbleTrouble.png");
	//	break;
	//case MapSelect::Splash_Buttonbashers:
	//	Game_->SetTexture("Splash_Buttonbashers.png");
	//	break;
	//case MapSelect::Splash_ChompChomp:
	//	Game_->SetTexture("Splash_ChompChomp.png");
	//	break;
	//case MapSelect::Splash_CosmicHighway:
	//	Game_->SetTexture("Splash_CosmicHighway.png");
	//	break;
	//case MapSelect::Splash_CoY_HitParade:
	//	Game_->SetTexture("Splash_CoY_HitParade.png");
	//	break;
	//case MapSelect::Splash_CoY_SkiFall:
	//	Game_->SetTexture("Splash_CoY_SkiFall.png");
	//	break;
	//case MapSelect::Splash_CoY_WallGuys:
	//	Game_->SetTexture("Splash_CoY_WallGuys.png");
	//	break;
	//case MapSelect::Splash_DoorRush:
	//	Game_->SetTexture("Splash_DoorRush.png");
	//	break;
	//case MapSelect::Splash_EggGrab:
	//	Game_->SetTexture("Splash_EggGrab.png");
	//	break;
	//case MapSelect::Splash_EggSiege:
	//	Game_->SetTexture("Splash_EggSiege.png");
	//	break;
	//case MapSelect::Splash_FallBall:
	//	Game_->SetTexture("Splash_FallBall.png");
	//	break;
	//case MapSelect::Splash_FallMountain:
	//	Game_->SetTexture("Splash_FallMountain.png");
	//	break;
	//case MapSelect::Splash_FloorIsLava:
	//	Game_->SetTexture("Splash_FloorIsLava.png");
	//	break;
	//case MapSelect::Splash_FranticFactory:
	//	Game_->SetTexture("Splash_FranticFactory.png");
	//	break;
	//case MapSelect::Splash_FreezyPeak:
	//	Game_->SetTexture("Splash_FreezyPeak.png");
	//	break;
	//case MapSelect::Splash_FruitBowl:
	//	Game_->SetTexture("Splash_FruitBowl.png");
	//	break;
	//case MapSelect::Splash_FruitChute:
	//	Game_->SetTexture("Splash_FruitChute.png");
	//	break;
	//case MapSelect::Splash_FullTilt:
	//	Game_->SetTexture("Splash_FullTilt.png");
	//	break;
	//case MapSelect::Splash_Gauntlet:
	//	Game_->SetTexture("Splash_Gauntlet.png");
	//	break;
	//case MapSelect::Splash_HexARing:
	//	Game_->SetTexture("Splash_HexARing.png");
	//	break;
	//case MapSelect::Splash_HexaTerrestrial:
	//	Game_->SetTexture("Splash_HexaTerrestrial.png");
	//	break;
	//case MapSelect::Splash_Hoarders:
	//	Game_->SetTexture("Splash_Hoarders.png");
	//	break;
	//case MapSelect::Splash_HoopsieDaisy:
	//	Game_->SetTexture("Splash_HoopsieDaisy.png");
	//	break;
	//case MapSelect::Splash_HoopsLegends:
	//	Game_->SetTexture("Splash_HoopsLegends.png");
	//	break;
	//case MapSelect::Splash_HoverboardHeroes:
	//	Game_->SetTexture("Splash_HoverboardHeroes.png");
	//	break;
	//case MapSelect::Splash_HyperdriveHeroes:
	//	Game_->SetTexture("Splash_HyperdriveHeroes.png");
	//	break;
	//case MapSelect::Splash_Invisibeans:
	//	Game_->SetTexture("Splash_Invisibeans.png");
	//	break;
	//case MapSelect::Splash_InvisibeansHalloween:
	//	Game_->SetTexture("Splash_InvisibeansHalloween.png");
	//	break;
	//case MapSelect::Splash_Jinxed:
	//	Game_->SetTexture("Splash_Jinxed.png");
	//	break;
	//case MapSelect::Splash_JumpShowdown:
	//	Game_->SetTexture("Splash_JumpShowdown.png");
	//	break;
	//case MapSelect::Splash_KnightFever:
	//	Game_->SetTexture("Splash_KnightFever.png");
	//	break;
	//case MapSelect::Splash_LeadingLight:
	//	Game_->SetTexture("Splash_LeadingLight.png");
	//	break;
	//case MapSelect::Splash_LilyLeapers:
	//	Game_->SetTexture("Splash_LilyLeapers.png");
	//	break;
	//case MapSelect::Splash_LostTemple:
	//	Game_->SetTexture("Splash_LostTemple.png");
	//	break;
	//case MapSelect::Splash_MatchFall:
	//	Game_->SetTexture("Splash_MatchFall.png");
	//	break;
	//case MapSelect::Splash_PartyPromenade:
	//	Game_->SetTexture("Splash_PartyPromenade.png");
	//	break;
	//case MapSelect::Splash_PegwinPoolParty:
	//	Game_->SetTexture("Splash_PegwinPoolParty.png");
	//	break;
	//case MapSelect::Splash_PenguinPursuit:
	//	Game_->SetTexture("Splash_PenguinPursuit.png");
	//	break;
	//case MapSelect::Splash_PipeDream:
	//	Game_->SetTexture("Splash_PipeDream.png");
	//	break;
	//case MapSelect::Splash_PixelPerfect:
	//	Game_->SetTexture("Splash_PixelPerfect.png");
	//	break;
	//case MapSelect::Splash_PowerTrip:
	//	Game_->SetTexture("Splash_PowerTrip.png");
	//	break;
	//case MapSelect::Splash_RockandRoll:
	//	Game_->SetTexture("Splash_RockandRoll.png");
	//	break;
	//case MapSelect::Splash_RollOff:
	//	Game_->SetTexture("Splash_RollOff.png");
	//	break;
	//case MapSelect::Splash_RollOn:
	//	Game_->SetTexture("Splash_RollOn.png");
	//	break;
	//case MapSelect::Splash_RollOut:
	//	Game_->SetTexture("Splash_RollOut.png");
	//	break;
	//case MapSelect::Splash_Rotatonator:
	//	Game_->SetTexture("Splash_Rotatonator.png");
	//	break;
	//case MapSelect::Splash_RoyalRumble:
	//	Game_->SetTexture("Splash_RoyalRumble.png");
	//	break;
	//case MapSelect::Splash_SeeSaw:
	//	Game_->SetTexture("Splash_SeeSaw.png");
	//	break;
	//case MapSelect::Splash_ShortCircuit:
	//	Game_->SetTexture("Splash_ShortCircuit.png");
	//	break;
	//case MapSelect::Splash_ShortCircuit2:
	//	Game_->SetTexture("Splash_ShortCircuit2.png");
	//	break;
	//case MapSelect::Splash_Skifall:
	//	Game_->SetTexture("Splash_Skifall.png");
	//	break;
	//case MapSelect::Splash_SkylineStumble:
	//	Game_->SetTexture("Splash_SkylineStumble.png");
	//	break;
	//case MapSelect::Splash_Slimescraper:
	//	Game_->SetTexture("Splash_Slimescraper.png");
	//	break;
	//case MapSelect::Splash_SnowballSurvival:
	//	Game_->SetTexture("Splash_SnowballSurvival.png");
	//	break;
	//case MapSelect::Splash_SnowyScrap:
	//	Game_->SetTexture("Splash_SnowyScrap.png");
	//	break;
	//case MapSelect::Splash_SpaceRace:
	//	Game_->SetTexture("Splash_SpaceRace.png");
	//	break;
	//case MapSelect::Splash_Starchart:
	//	Game_->SetTexture("Splash_Starchart.png");
	//	break;
	//case MapSelect::Splash_StompinGround:
	//	Game_->SetTexture("Splash_StompinGround.png");
	//	break;
	//case MapSelect::Splash_TailTag:
	//	Game_->SetTexture("Splash_TailTag.png");
	//	break;
	//case MapSelect::Splash_TeamTailTag:
	//	Game_->SetTexture("Splash_TeamTailTag.png");
	//	break;
	//case MapSelect::Splash_TheSwiveller:
	//	Game_->SetTexture("Splash_TheSwiveller.png");
	//	break;
	//case MapSelect::Splash_Thinice:
	//	Game_->SetTexture("Splash_Thinice.png");
	//	break;
	//case MapSelect::Splash_TipToe:
	//	Game_->SetTexture("Splash_TipToe.png");
	//	break;
	//case MapSelect::Splash_TipToeFinale:
	//	Game_->SetTexture("Splash_TipToeFinale.png");
	//	break;
	//case MapSelect::Splash_TrackAttack:
	//	Game_->SetTexture("Splash_TrackAttack.png");
	//	break;
	//case MapSelect::Splash_TreetopTumble:
	//	Game_->SetTexture("Splash_TreetopTumble.png");
	//	break;
	//case MapSelect::Splash_TundraRun:
	//	Game_->SetTexture("Splash_TundraRun.png");
	//	break;
	//case MapSelect::Splash_VolleyFall:
	//	Game_->SetTexture("Splash_VolleyFall.png");
	//	break;
	//case MapSelect::Splash_WallGuys:
	//	Game_->SetTexture("Splash_WallGuys.png");
	//	break;
	//case MapSelect::Splash_Whirligig:
	//	Game_->SetTexture("Splash_Whirligig.png");
	//	break;
	//default:
	//	Game_->SetTexture("Splash_BasketFall.png");
	//	break;
	}

}
