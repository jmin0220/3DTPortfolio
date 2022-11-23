#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 : 쇼 선택 버튼(마우스 상호작용함)
class GameEngineUIRenderer;
class SelectShowButton : public GameEngineActor
{
public:
	// constrcuter destructer
	SelectShowButton();
	~SelectShowButton();

	// delete Function
	SelectShowButton(const SelectShowButton& _Other) = delete;
	SelectShowButton(SelectShowButton&& _Other) noexcept = delete;
	SelectShowButton& operator=(const SelectShowButton& _Other) = delete;
	SelectShowButton& operator=(SelectShowButton&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};
private:
	std::shared_ptr<GameEngineUIRenderer> Button_;
	std::shared_ptr<GameEngineCollision> ButtonCol_;
	std::shared_ptr<GameEngineUIRenderer> Key_;
	std::shared_ptr<GameEngineFontRenderer> Font_;

	bool ButtonCheck_;
	bool IsPop_;
	bool IsEnd_;
};

