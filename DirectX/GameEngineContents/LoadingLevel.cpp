#include "PreCompile.h"
#include "LoadingLevel.h"
#include "LoadingActor.h"
#include "CustomableGUI.h"

#include <GameEngineBase/magic_enum.hpp>
#include "GameServerGUI.h"

LEVELS LoadingLevel::CurLoadingLevel_(LEVELS::NONE);
std::string_view LoadingLevel::StrCurLoadingLevel_;
bool LoadingLevel::AllPlayersReady_ = false;

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
	// 서버 안켰을때도 스테이지 입장 가능하도록
	if (false == GameServer::GetInst()->IsServerStart())
	{
		if (LoadingProgress_ >= 0.999f)
		{
			GEngine::ChangeLevel(StrCurLoadingLevel_.data());
			return;
		}
	}

	// 3. 각자 상태변경
	// 호스트
	if (true == GameServer::GetInst()->CheckServerSignal(ServerFlag::S_LoadingChangeReady))
	{

		if (true == GameServer::IsHost_)
		{
			// 호스트는 유저들이 다 바꾼 뒤에 바꿈
			if (true == GameServer::GetInst()->CheckOtherPlayersFlag(PlayerFlag::P_LoadingChangeOver))
			{
				GEngine::ChangeLevel(StrCurLoadingLevel_.data());
				return;
			}
		}
		// 유저
		else
		{
			if (true == GameServer::GetInst()->CheckPlayerSignal(PlayerFlag::P_LoadingChangeReady))
			{
				GEngine::ChangeLevel(StrCurLoadingLevel_.data());
				return;
			}
		}

	}

	
	// 2. 서버는 서버신호 변경 (호스트)
	if (!GameServer::GetInst()->CheckServerSignal(ServerFlag::S_LoadingChangeReady) && true == GameServer::IsHost_)
	{
		// 플레이어 모두, 자기자신 상태 확인
		if (true == GameServer::GetInst()->CheckOtherPlayersFlag(PlayerFlag::P_LoadingChangeReady)
			&& true == GameServer::GetInst()->CheckPlayerSignal(PlayerFlag::P_LoadingChangeReady))
		{
			GameServer::GetInst()->SetServerSignal(ServerFlag::S_LoadingChangeReady);
			return;
		}
	}



	// 1. 로딩 완료시 상태변경 준비(호스트, 유저)
	if (LoadingProgress_ >= 0.999f && !GameServer::GetInst()->CheckPlayerSignal(PlayerFlag::P_LoadingChangeReady))
	{
		GameServer::GetInst()->SetPlayerSignal(PlayerFlag::P_LoadingChangeReady);
	}
}

// 랜덤으로 스테이지를 시작하는게 아니라 원하는 스테이지를 선택할 수 있도록
void LoadingLevel::LevelStartEvent()
{
	LevelChangeReady_ = false;
	LoadingComplete_ = false;

	// 서버 
	// 유저들 로딩레벨에 다 들어왔으면 호스트도 넘어오라고 해주어야함
	if (false == GameServer::IsHost_)
	{
		GameServer::GetInst()->SetPlayerSignal(PlayerFlag::P_GameStartChangeOver);
	}
	// 호스트
	else
	{
		GameServer::GetInst()->SetServerSignal(ServerFlag::S_GameStartChangeOver);
	}
	// ~~ 서버

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
