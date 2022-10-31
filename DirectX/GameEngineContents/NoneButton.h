#pragma once
#include "HUDUIActor.h"

// ���� : ���콺�� ��ư ���� ���� �������� ui
class GameEngineUIRenderer;
class NoneButton : public HUDUIActor
{
public:
	// constrcuter destructer
	NoneButton();
	~NoneButton();

	// delete Function
	NoneButton(const NoneButton& _Other) = delete;
	NoneButton(NoneButton&& _Other) noexcept = delete;
	NoneButton& operator=(const NoneButton& _Other) = delete;
	NoneButton& operator=(NoneButton&& _Other) noexcept = delete;

	GameEngineUIRenderer* GetOpenParty()
	{
		return OpenParty;
	}

	GameEngineUIRenderer* GetMenu()
	{
		return Menu;
	}

	GameEngineUIRenderer* GetMoney()
	{
		return Money;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

private:
	GameEngineUIRenderer* OpenParty;
	GameEngineUIRenderer* Tab;

	GameEngineUIRenderer* Menu;
	GameEngineUIRenderer* Money;
	GameEngineUIRenderer* Renderer4;

	GameEngineFontRenderer* F_OpenParty;
};
