#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// ���� :
class TitleActor;
class Cursor;
class FontActor;
class NamePlate;
class NoneButton;
class NoneMoney;
class SelectShowButton;
class PlayButton;
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
	FontActor* Font;
	NamePlate* Name;
	NoneButton* Button;
	NoneMoney* MoneyUI;
	SelectShowButton* ShowButton;
	PlayButton* StartButton;
};

