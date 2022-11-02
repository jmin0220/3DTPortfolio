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
	GameEngineUIRenderer* BG_;
	GameEngineUIRenderer* LeftKey_;
	GameEngineUIRenderer* RightKey_;

	GameEngineUIRenderer* Panel1_;
	GameEngineUIRenderer* Panel2_;
	GameEngineUIRenderer* Panel3_;
	GameEngineUIRenderer* Panel4_;

	GameEngineCollision* PanelCol1_;
	GameEngineCollision* PanelCol2_;
	GameEngineCollision* PanelCol3_;
	GameEngineCollision* PanelCol4_;

	GameEngineUIRenderer* Home_;
	GameEngineUIRenderer* Event_;
	GameEngineUIRenderer* Custom_;
	GameEngineUIRenderer* Store_;

	bool ButtonCheck_;
};

