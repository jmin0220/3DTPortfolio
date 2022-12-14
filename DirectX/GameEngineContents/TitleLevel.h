#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// 설명 : 게임 맨처음 로고 화면
class TitleActor;
class Cursor;
class TitleLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	TitleLevel();
	~TitleLevel();

	// delete Function
	TitleLevel(const TitleLevel& _Other) = delete;
	TitleLevel(TitleLevel&& _Other) noexcept = delete;
	TitleLevel& operator=(const TitleLevel& _Other) = delete;
	TitleLevel& operator=(TitleLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;
private:
	std::shared_ptr<TitleActor> TitleLogo;
	std::shared_ptr<Cursor> Mouse;

	bool EnterDown_;
};

