#pragma once
#include <GameEngineCore/GameEngineActor.h>


// 설명 : 로딩화면용 액터
class GameEngineTextureRenderer;
class GameEngineUIRenderer;
class LoadingActor : public GameEngineActor
{
public:
	// constrcuter destructer
	LoadingActor();
	~LoadingActor();

	// delete Function
	LoadingActor(const LoadingActor& _Other) = delete;
	LoadingActor(LoadingActor&& _Other) noexcept = delete;
	LoadingActor& operator=(const LoadingActor& _Other) = delete;
	LoadingActor& operator=(LoadingActor&& _Other) noexcept = delete;
	
	void CreateGames();
	void MainGameImage(float _DeltaTime);
	void SelectMainGame();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};
private:
	std::shared_ptr<GameEngineTextureRenderer> BG_;
	std::shared_ptr<GameEngineTextureRenderer> Games_[5];
	std::shared_ptr<GameEngineTextureRenderer> Game_;
	std::shared_ptr<GameEngineUIRenderer> Exit_;
	std::shared_ptr<GameEngineUIRenderer> ExitButton_;
	std::shared_ptr<GameEngineFontRenderer> Font_;
	std::shared_ptr<GameEngineFontRenderer> ExitFont_;
	float LastGamesPos_;
	float Time_;
	int RandomNum_;

	// LoadingLevel에서 맵 선택
public:
	MapSelect SelectMap()
	{
		Select_ = true;

		return SelectedMap_;
	}

	void CancelMap()
	{
		Select_ = false;
	}

	std::string_view GetCurMap();

	void GetShuffledNumbers(std::vector<int>& _Numbers);

private:
	// 맵 셔플
	std::vector<int> MapIndexs_;
	int Idx_;
	float SuffleTime_;

	// 선택한 맵
	MapSelect SelectedMap_;
	bool Select_;
};

