#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 : 플레이 버튼
class GameEngineUIRenderer;
class PlayButton : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayButton();
	~PlayButton();

	// delete Function
	PlayButton(const PlayButton& _Other) = delete;
	PlayButton(PlayButton&& _Other) noexcept = delete;
	PlayButton& operator=(const PlayButton& _Other) = delete;
	PlayButton& operator=(PlayButton&& _Other) noexcept = delete;

	CollisionReturn ButtonOn(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};
private:
	std::shared_ptr<GameEngineUIRenderer> Button_;
	std::shared_ptr<GameEngineUIRenderer> Key_;
	std::shared_ptr<GameEngineFontRenderer> Font_;

	std::shared_ptr<GameEngineCollision> ButtonCol_;

	bool ButtonCheck_;
	bool IsPop_;
	bool IsEnd_;
};

