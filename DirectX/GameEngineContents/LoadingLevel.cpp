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

// �������� ���������� �����ϴ°� �ƴ϶� ���ϴ� ���������� ������ �� �ֵ���
void LoadingLevel::LevelStartEvent()
{
	LoadingGUI_ = GameEngineGUI::CreateGUIWindow<CustomableGUI>("LoadingGUI", this);
	LoadingGUI_->SetGUIDebugFunc([=]() {ShowLoadingProgress(); });

	// ���� ����
	Loadings_ = CreateActor<LoadingActor>();
}

void LoadingLevel::LevelEndEvent()
{
	// ���� ����
	Loadings_->Death();

	LoadingGUI_->Death();
}

void LoadingLevel::ShowLoadingProgress()
{
	// ������ ��������
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
		// �������� ����
		SelectedMap_ = Loadings_->SelectMap();
	}


	// Load Resources
	if (true == ImGui::Button("LoadingStage"))
	{
		if (MapSelect::NONE == SelectedMap_)
		{
			return;
		}

		// ������ �̿� �ε� ����
		GameEngineCore::EngineThreadPool.Work(
			[=]()
			{
				ContentsCore::GetInst()->LoadLevelResource(SelectedMapToLevel());
			}
		);

	}

	// ������ ��������
	{
		float Progress = ContentsCore::GetInst()->GetLoadingProgress();
		std::string Out = std::to_string(static_cast<int>(Progress * 100));
		ImGui::Text(("Loading... " + Out).c_str());
	}


	if (true == ImGui::Button("StageStart"))
	{
		// TODO : ������ �۾� ������ �ߴ��� Ȯ��


		// ������ ������ ���� ����
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
