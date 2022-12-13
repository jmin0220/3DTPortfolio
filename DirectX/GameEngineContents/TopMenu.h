#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class MenuState
{
	Home,
	Option,
	Skin,
	Shop,
	Fall
};

// ���� : ��� �޴�
class GameEngineUIRenderer;
class TopMenu : public GameEngineActor
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

	void MyMenuUpdate();
	void MenuAnimation();

	MenuState MyState_;
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};
private:
	std::shared_ptr<GameEngineUIRenderer> BG_;
	std::shared_ptr<GameEngineUIRenderer> LeftKey_;
	std::shared_ptr<GameEngineUIRenderer> RightKey_;

	std::shared_ptr<GameEngineUIRenderer> Panel1_;
	std::shared_ptr<GameEngineUIRenderer> Panel2_;
	std::shared_ptr<GameEngineUIRenderer> Panel3_;
	std::shared_ptr<GameEngineUIRenderer> Panel4_;

	std::shared_ptr<GameEngineCollision> PanelCol1_;
	std::shared_ptr<GameEngineCollision> PanelCol2_;
	std::shared_ptr<GameEngineCollision> PanelCol3_;
	std::shared_ptr<GameEngineCollision> PanelCol4_;

	std::shared_ptr<GameEngineUIRenderer> Home_;
	std::shared_ptr<GameEngineUIRenderer> Event_;
	std::shared_ptr<GameEngineUIRenderer> Custom_;
	std::shared_ptr<GameEngineUIRenderer> Store_;

	bool ButtonCheck1_;
	bool ButtonCheck2_;
	bool ButtonCheck3_;
	bool ButtonCheck4_;

	
};

