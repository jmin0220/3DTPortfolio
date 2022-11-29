#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 : 승리자 네임텍
class GameEngineUIRenderer;
class GameEngineFontRenderer;
class Winner : public GameEngineActor
{
public:
	// constrcuter destructer
	Winner();
	~Winner();

	// delete Function
	Winner(const Winner& _Other) = delete;
	Winner(Winner&& _Other) noexcept = delete;
	Winner& operator=(const Winner& _Other) = delete;
	Winner& operator=(Winner&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

	void LevelStartEvent() override;
	void LevelEndEvent() override;

private:
	std::shared_ptr<GameEngineUIRenderer> BGRenderer_;
	std::shared_ptr<GameEngineUIRenderer> FontRenderer_;
	std::shared_ptr<GameEngineUIRenderer> CrownRenderer_;
	std::shared_ptr<GameEngineFontRenderer> Font_;

};

