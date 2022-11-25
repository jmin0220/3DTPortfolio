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
	// 임시 레벨 로딩
	/////////////////


}

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
		// 스레드 이용 로딩 시작
		
		// 로딩 마무리되면 그 스테이지로 ChangeLevel

	}

}
