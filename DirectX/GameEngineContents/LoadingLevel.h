#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// 설명 : 로딩중 촤라락 돌아가는 화면
class LoadingActor;
class LoadingLevel : public GameEngineLevel
{
public:
	static void SetLoadingStage(std::string_view _Level);

private:
	static LEVELS CurLoadingLevel_;
	static std::string_view StrCurLoadingLevel_;

public:
	// constrcuter destructer
	LoadingLevel();
	~LoadingLevel();

	// delete Function
	LoadingLevel(const LoadingLevel& _Other) = delete;
	LoadingLevel(LoadingLevel&& _Other) noexcept = delete;
	LoadingLevel& operator=(const LoadingLevel& _Other) = delete;
	LoadingLevel& operator=(LoadingLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

	void LevelStartEvent() override;
	void LevelEndEvent() override;

	// UI
private:
	std::shared_ptr<LoadingActor> Loadings_;
	MapSelect SelectedMap_;

	// 스테이지 로딩, 진행 정도 관련
private:
	void ShowLoadingProgress();
	LEVELS MapSelectToLevels();
	void ChangeLevelByMap();
	class std::shared_ptr<CustomableGUI> LoadingGUI_;

	float LoadingProgress_;
};