#include "PreCompile.h"
#include "LoadingActor.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/magic_enum.hpp>

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
	Splash_BlueJay,
	Splash_BounceParty,
	Splash_BubbleTrouble,
	Splash_Buttonbashers,
	Splash_ChompChomp,
	Splash_CosmicHighway,
	Splash_CoY_DoorDash,
	Splash_CoY_HitParade,
	Splash_CoY_SkiFall,
	Splash_CoY_WallGuys,
	Splash_DoorRush,
	Splash_EggGrab,
	Splash_EggSiege,
	Splash_FallBall,
	Splash_FallMountain,
	Splash_FloorIsLava,
	Splash_FranticFactory,
	Splash_FreezyPeak,
	Splash_FruitBowl,
	Splash_FruitChute,
	Splash_FullTilt,
	Splash_Gauntlet,
	Splash_Hexagone,
	Splash_HexARing,
	Splash_HexaTerrestrial,
	Splash_Hoarders,
	Splash_HoopsieDaisy,
	Splash_HoopsLegends,
	Splash_HoverboardHeroes,
	Splash_HyperdriveHeroes,
	Splash_Invisibeans,
	Splash_InvisibeansHalloween,
	Splash_Jinxed,
	Splash_JumpClub,
	Splash_JumpShowdown,
	Splash_KnightFever,
	Splash_LeadingLight,
	Splash_LilyLeapers,
	Splash_LostTemple,
	Splash_MatchFall,
	Splash_PartyPromenade,
	Splash_PegwinPoolParty,
	Splash_PenguinPursuit,
	Splash_PipeDream,
	Splash_PixelPerfect,
	Splash_PowerTrip,
	Splash_RockandRoll,
	Splash_RollOff,
	Splash_RollOn,
	Splash_RollOut,
	Splash_Rotatonator,
	Splash_RoyalRumble,
	Splash_SeeSaw,
	Splash_ShortCircuit,
	Splash_ShortCircuit2,
	Splash_Skifall,
	Splash_SkylineStumble,
	Splash_Slimescraper,
	Splash_SnowballSurvival,
	Splash_SnowyScrap,
	Splash_SpaceRace,
	Splash_Starchart,
	Splash_StompinGround,
	Splash_TailTag,
	Splash_TeamTailTag,
	Splash_TheSwiveller,
	Splash_Thinice,
	Splash_TipToe,
	Splash_TipToeFinale,
	Splash_TrackAttack,
	Splash_TreetopTumble,
	Splash_TundraRun,
	Splash_VolleyFall,
	Splash_WallGuys,
	Splash_Whirligig
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
	
	MainGameImage();	

	for (int i = 0; i < 5; i++)
	{
		Games_[i]->GetTransform().SetWorldMove({ -Speed * GameEngineTime::GetDeltaTime() , 0.0f, 0.0f });
		
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

void LoadingActor::MainGameImage()
{
	MapSelect Map;

	static_cast<int>(MapSelect::Splash_AirTime);

	if (Time_ > 1.0f)
	{
		Map = static_cast<MapSelect>(GameEngineRandom::MainRandom.RandomInt(0, 80));

		switch (Map)
		{
		case MapSelect::Splash_AirTime:
			Game_->SetTexture("Splash_AirTime.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_BasketFall:
			Game_->SetTexture("Splash_BasketFall.png");
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
		case MapSelect::Splash_BlueJay:
			Game_->SetTexture("Splash_BlueJay.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_BounceParty:
			Game_->SetTexture("Splash_BounceParty.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_BubbleTrouble:
			Game_->SetTexture("Splash_BubbleTrouble.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_Buttonbashers:
			Game_->SetTexture("Splash_Buttonbashers.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_ChompChomp:
			Game_->SetTexture("Splash_ChompChomp.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_CosmicHighway:
			Game_->SetTexture("Splash_CosmicHighway.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_CoY_DoorDash:
			Game_->SetTexture("Splash_CoY_DoorDash.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_CoY_HitParade:
			Game_->SetTexture("Splash_CoY_HitParade.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_CoY_SkiFall:
			Game_->SetTexture("Splash_CoY_SkiFall.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_CoY_WallGuys:
			Game_->SetTexture("Splash_CoY_WallGuys.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_DoorRush:
			Game_->SetTexture("Splash_DoorRush.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_EggGrab:
			Game_->SetTexture("Splash_EggGrab.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_EggSiege:
			Game_->SetTexture("Splash_EggSiege.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_FallBall:
			Game_->SetTexture("Splash_FallBall.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_FallMountain:
			Game_->SetTexture("Splash_FallMountain.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_FloorIsLava:
			Game_->SetTexture("Splash_FloorIsLava.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_FranticFactory:
			Game_->SetTexture("Splash_FranticFactory.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_FreezyPeak:
			Game_->SetTexture("Splash_FreezyPeak.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_FruitBowl:
			Game_->SetTexture("Splash_FruitBowl.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_FruitChute:
			Game_->SetTexture("Splash_FruitChute.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_FullTilt:
			Game_->SetTexture("Splash_FullTilt.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_Gauntlet:
			Game_->SetTexture("Splash_Gauntlet.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_Hexagone:
			Game_->SetTexture("Splash_Hexagone.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_HexARing:
			Game_->SetTexture("Splash_HexARing.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_HexaTerrestrial:
			Game_->SetTexture("Splash_HexaTerrestrial.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_Hoarders:
			Game_->SetTexture("Splash_Hoarders.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_HoopsieDaisy:
			Game_->SetTexture("Splash_HoopsieDaisy.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_HoopsLegends:
			Game_->SetTexture("Splash_HoopsLegends.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_HoverboardHeroes:
			Game_->SetTexture("Splash_HoverboardHeroes.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_HyperdriveHeroes:
			Game_->SetTexture("Splash_HyperdriveHeroes.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_Invisibeans:
			Game_->SetTexture("Splash_Invisibeans.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_InvisibeansHalloween:
			Game_->SetTexture("Splash_InvisibeansHalloween.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_Jinxed:
			Game_->SetTexture("Splash_Jinxed.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_JumpClub:
			Game_->SetTexture("Splash_JumpClub.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_JumpShowdown:
			Game_->SetTexture("Splash_JumpShowdown.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_KnightFever:
			Game_->SetTexture("Splash_KnightFever.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_LeadingLight:
			Game_->SetTexture("Splash_LeadingLight.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_LilyLeapers:
			Game_->SetTexture("Splash_LilyLeapers.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_LostTemple:
			Game_->SetTexture("Splash_LostTemple.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_MatchFall:
			Game_->SetTexture("Splash_MatchFall.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_PartyPromenade:
			Game_->SetTexture("Splash_PartyPromenade.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_PegwinPoolParty:
			Game_->SetTexture("Splash_PegwinPoolParty.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_PenguinPursuit:
			Game_->SetTexture("Splash_PenguinPursuit.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_PipeDream:
			Game_->SetTexture("Splash_PipeDream.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_PixelPerfect:
			Game_->SetTexture("Splash_PixelPerfect.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_PowerTrip:
			Game_->SetTexture("Splash_PowerTrip.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_RockandRoll:
			Game_->SetTexture("Splash_RockandRoll.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_RollOff:
			Game_->SetTexture("Splash_RollOff.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_RollOn:
			Game_->SetTexture("Splash_RollOn.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_RollOut:
			Game_->SetTexture("Splash_RollOut.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_Rotatonator:
			Game_->SetTexture("Splash_Rotatonator.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_RoyalRumble:
			Game_->SetTexture("Splash_RoyalRumble.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_SeeSaw:
			Game_->SetTexture("Splash_SeeSaw.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_ShortCircuit:
			Game_->SetTexture("Splash_ShortCircuit.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_ShortCircuit2:
			Game_->SetTexture("Splash_ShortCircuit2.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_Skifall:
			Game_->SetTexture("Splash_Skifall.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_SkylineStumble:
			Game_->SetTexture("Splash_SkylineStumble.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_Slimescraper:
			Game_->SetTexture("Splash_Slimescraper.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_SnowballSurvival:
			Game_->SetTexture("Splash_SnowballSurvival.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_SnowyScrap:
			Game_->SetTexture("Splash_SnowyScrap.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_SpaceRace:
			Game_->SetTexture("Splash_SpaceRace.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_Starchart:
			Game_->SetTexture("Splash_Starchart.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_StompinGround:
			Game_->SetTexture("Splash_StompinGround.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_TailTag:
			Game_->SetTexture("Splash_TailTag.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_TeamTailTag:
			Game_->SetTexture("Splash_TeamTailTag.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_TheSwiveller:
			break;
			Game_->SetTexture("Splash_TheSwiveller.png");
			Time_ = 0.0f;
		case MapSelect::Splash_Thinice:
			Game_->SetTexture("Splash_Thinice.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_TipToe:
			Game_->SetTexture("Splash_TipToe.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_TipToeFinale:
			Game_->SetTexture("Splash_TipToeFinale.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_TrackAttack:
			Game_->SetTexture("Splash_TrackAttack.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_TreetopTumble:
			Game_->SetTexture("Splash_TreetopTumble.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_TundraRun:
			Game_->SetTexture("Splash_TundraRun.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_VolleyFall:
			Game_->SetTexture("Splash_VolleyFall.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_WallGuys:
			Game_->SetTexture("Splash_WallGuys.png");
			Time_ = 0.0f;
			break;
		case MapSelect::Splash_Whirligig:
			Game_->SetTexture("Splash_Whirligig.png");
			Time_ = 0.0f;
			break;
		default:
			Game_->SetTexture("Splash_BasketFall.png");
			Time_ = 0.0f;
			break;
		}

	}
}