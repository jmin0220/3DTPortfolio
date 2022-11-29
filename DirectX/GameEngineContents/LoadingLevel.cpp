#include "PreCompile.h"
#include "LoadingLevel.h"
#include "LoadingActor.h"
#include "CustomableGUI.h"

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

}

// 랜덤으로 스테이지를 시작하는게 아니라 원하는 스테이지를 선택할 수 있도록
void LoadingLevel::LevelStartEvent()
{
	LoadingGUI_ = GameEngineGUI::CreateGUIWindow<CustomableGUI>("LoadingGUI", this);
	LoadingGUI_->SetGUIDebugFunc([=]() {ShowLoadingProgress(); });

	// 엑터 생성
	Loadings_ = CreateActor<LoadingActor>();
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
		std::string Name = Loadings_->GetCurMap().data();
		ImGui::Text(("SelectedMap :" + Name).c_str());
	}

	if (true == ImGui::Button("ShuffleStage"))
	{
		Loadings_->CancelMap();
		SelectedMap_ = MapSelect::NONE;
	}

	ImGui::SameLine();
	if (true == ImGui::Button("PauseStage"))
	{
		// 스테이지 선택
		SelectedMap_ = Loadings_->SelectMap();
	}


	// Load Resources
	if (true == ImGui::Button("LoadingStage"))
	{
		if (MapSelect::NONE == SelectedMap_)
		{
			return;
		}

		// 스레드 이용 로딩 시작
		GameEngineCore::EngineThreadPool.Work(
			[=]()
			{
				ContentsCore::GetInst()->LoadLevelResource(SelectedMapToLevel());
			}
		);

	}

	// 선택한 스테이지
	{
		float Progress = ContentsCore::GetInst()->GetLoadingProgress();
		std::string Out = std::to_string(static_cast<int>(Progress * 100));
		ImGui::Text(("Loading... " + Out).c_str());
	}


	if (true == ImGui::Button("StageStart"))
	{
		// TODO : 스레드 작업 마무리 했는지 확인


		// 마무리 됐으면 레벨 변경
		ChangeLevelByMap();
	}

}

LEVELS LoadingLevel::SelectedMapToLevel()
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
	}

}
