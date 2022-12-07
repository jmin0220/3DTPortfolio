#include "PreCompile.h"
#include "LoadingLevel.h"
#include "LoadingActor.h"
#include "CustomableGUI.h"

#include <GameEngineBase/magic_enum.hpp>

LEVELS LoadingLevel::CurLoadingLevel_(LEVELS::NONE);
std::string_view LoadingLevel::StrCurLoadingLevel_;

void LoadingLevel::SetLoadingStage(std::string_view _Level)
{
	CurLoadingLevel_ = ContentsCore::GetInst()->StringLevelToLEVELS(_Level);
	StrCurLoadingLevel_ = ContentsCore::GetInst()->StringLevelToStringSetLevel(_Level);
}

LoadingLevel::LoadingLevel()
	: SelectedMap_(MapSelect::NONE)
{
}

LoadingLevel::~LoadingLevel() 
{
}

void LoadingLevel::Start()
{
	
}

void LoadingLevel::Update(float _DeltaTime)
{
	//if (LoadingProgress_ >= 0.999f)
	//{
	//	GEngine::ChangeLevel(StrCurLoadingLevel_.data());
	//}

	if (false == LoadingComplete_ && LoadingProgress_ >= 0.999f)
	{
		LoadingComplete_ = true;
		GameServer::PlayerReady_ = 1;
	}



	if (false == GameServer::IsHost_)
	{
		if (1 == GameServer::StateChangeSignal_)
		{
			GEngine::ChangeLevel(StrCurLoadingLevel_.data());
			GameServer::StateChangeSignal_ = 0;
		}
	}
	

}

// 랜덤으로 스테이지를 시작하는게 아니라 원하는 스테이지를 선택할 수 있도록
void LoadingLevel::LevelStartEvent()
{
	LoadingGUI_ = GameEngineGUI::CreateGUIWindow<CustomableGUI>("LoadingGUI", this);
	LoadingGUI_->SetGUIDebugFunc([=]() {ShowLoadingProgress(); });

	// 엑터 생성
	Loadings_ = CreateActor<LoadingActor>();


	// 스레드 이용 로딩 시작
	LoadingProgress_ = 0.0f;
	if (CurLoadingLevel_ != LEVELS::NONE)
	{
		GameEngineCore::EngineThreadPool.Work(
			[=]()
			{
				ContentsCore::GetInst()->LoadLevelResource(CurLoadingLevel_);
			}
		);
	}

	LoadingComplete_ = false;
}

void LoadingLevel::LevelEndEvent()
{
	// 엑터 제거
	Loadings_->Death();

	LoadingGUI_->Death();
}

void LoadingLevel::ShowLoadingProgress()
{
	// 선택한 스테이지
	{
		std::string MapName = magic_enum::enum_name(CurLoadingLevel_).data();
		ImGui::Text(("SelectedMap :" + MapName).c_str());
	}

	// 선택한 스테이지 로딩 정도
	{
		LoadingProgress_ = ContentsCore::GetInst()->GetLoadingProgress();
		std::string Out = "Loading... " + std::to_string(static_cast<int>(LoadingProgress_ * 100)) + " %";
		ImGui::Text(Out.c_str());
	}


}

LEVELS LoadingLevel::MapSelectToLevels()
{
	switch (SelectedMap_)
	{
	case MapSelect::Splash_CoY_DoorDash:
		return LEVELS::STAGE01_DOORDASH;
		break;
	case MapSelect::Splash_JumpClub:
		return LEVELS::STAGE02_JUMPCLUB;
		break;
	case MapSelect::Splash_Hexagone:
		return LEVELS::STAGE04_HEX_A_GONE;
		break;
	case MapSelect::Splash_HoopsLegends:
		return LEVELS::STAGE05_HOOPS_LEGENDS;
		break;
	default:
		return LEVELS::NONE;
		break;
	}
}

void LoadingLevel::ChangeLevelByMap()
{
	switch (SelectedMap_)
	{
	case MapSelect::Splash_CoY_DoorDash:
		GEngine::ChangeLevel(LEVEL_NAME_DOORDASH);
		break;
	case MapSelect::Splash_JumpClub:
		GEngine::ChangeLevel(LEVEL_NAME_JUMPCLUB);
		break;
	case MapSelect::Splash_Hexagone:
		GEngine::ChangeLevel(LEVEL_NAME_HEXAGONE);
		break;
	case MapSelect::Splash_HoopsLegends:
		GEngine::ChangeLevel(LEVEL_NAME_HOOPSLEGENDS);
		break;
	default:
		break;
	}

}
