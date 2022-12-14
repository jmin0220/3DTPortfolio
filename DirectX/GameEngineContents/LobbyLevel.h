#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// 설명 : 로비 대기실 레벨
class Cursor;
class FontActor;
class LobbyBackgroundActor;
class LobbySetUI;
class LobbyPlayer;
class FloorActor;
class Bingle;
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
	//std::shared_ptr<FontActor> Font;

	std::shared_ptr<LobbyPlayer> Player_;
	std::shared_ptr<FloorActor> Chair_;

	std::shared_ptr<LobbySetUI> LobbySet_;

	std::shared_ptr<FontActor> NumberFont_;
	std::shared_ptr<FontActor> UserFont_;
	std::shared_ptr<FontActor> WaitingFont_;

	std::shared_ptr<Bingle> Bingle_;

	bool Swap;

	float FallTime_;

	std::shared_ptr<GlobalBGM> bgm_;
	// FSM
private:
	GameEngineStateManager StateManager_;

	void LobbyStart(const StateInfo& _Info);
	void LobbyUpdate(float _DeltaTime, const StateInfo& _Info);

	void FallingStart(const StateInfo& _Info);
	void FallingUpdate(float _DeltaTime, const StateInfo& _Info);

	// ★★★ 서버 ★★★
	int PrevUserCount_;

	// ~~~ 서버 ~~~
};

