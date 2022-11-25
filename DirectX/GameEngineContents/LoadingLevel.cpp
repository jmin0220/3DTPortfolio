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
	/////////////////
	// �ӽ� ���� �ε�
	/////////////////


}

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
		// ������ �̿� �ε� ����
		
		// �ε� �������Ǹ� �� ���������� ChangeLevel

	}

}
