#pragma once
#include "HUDUIActor.h"

// ���� : �� ���� ��ư(���콺 ��ȣ�ۿ���)
class GameEngineUIRenderer;
class SelectShowButton : public HUDUIActor
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
	GameEngineUIRenderer* Button_;
	GameEngineUIRenderer* Key_;
	GameEngineFontRenderer* Font_;
};

