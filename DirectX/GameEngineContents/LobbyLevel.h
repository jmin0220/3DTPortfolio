#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :

class Cursor;
class FontActor;
class LobbyBackgroundActor;
class LobbySetUI;
class InGameSetUI;
class LobbyPlayer;
class LobbyLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	LobbyLevel();
	~LobbyLevel();

	// delete Function
	LobbyLevel(const LobbyLevel& _Other) = delete;
	LobbyLevel(LobbyLevel&& _Other) noexcept = delete;
	LobbyLevel& operator=(const LobbyLevel& _Other) = delete;
	LobbyLevel& operator=(LobbyLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;

private:
	std::shared_ptr<Cursor> Mouse;
	std::shared_ptr<FontActor> Font;

	std::shared_ptr<InGameSetUI> InGameSetUI_;
	std::shared_ptr<LobbyPlayer> Player_;

	std::shared_ptr<LobbySetUI> LobbySet_;

	bool Swap;
};

