#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class TitleActor;
class Cursor;
class tmpLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	tmpLevel();
	~tmpLevel();

	// delete Function
	tmpLevel(const tmpLevel& _Other) = delete;
	tmpLevel(tmpLevel&& _Other) noexcept = delete;
	tmpLevel& operator=(const tmpLevel& _Other) = delete;
	tmpLevel& operator=(tmpLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	TitleActor* TitleLogo;
	Cursor* Mouse;
};

