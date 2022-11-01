#pragma once
#include "HUDUIActor.h"

// 설명 : 상단 메뉴
class GameEngineUIRenderer;
class TopMenu : public HUDUIActor
{
public:
	// constrcuter destructer
	TopMenu();
	~TopMenu();

	// delete Function
	TopMenu(const TopMenu& _Other) = delete;
	TopMenu(TopMenu&& _Other) noexcept = delete;
	TopMenu& operator=(const TopMenu& _Other) = delete;
	TopMenu& operator=(TopMenu&& _Other) noexcept = delete;

	CollisionReturn ButtonOn(GameEngineCollision* _This, GameEngineCollision* _Other);
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};
private:
	GameEngineUIRenderer* BG;
	GameEngineUIRenderer* LeftKey;
	GameEngineUIRenderer* RightKey;

	GameEngineUIRenderer* Panel1;
	GameEngineUIRenderer* Panel2;
	GameEngineUIRenderer* Panel3;
	GameEngineUIRenderer* Panel4;

	GameEngineCollision* PanelCol1;
	GameEngineCollision* PanelCol2;
	GameEngineCollision* PanelCol3;
	GameEngineCollision* PanelCol4;

	GameEngineUIRenderer* Home;
	GameEngineUIRenderer* Event;
	GameEngineUIRenderer* Custom;
	GameEngineUIRenderer* Store;

	bool ButtonCheck;
};

