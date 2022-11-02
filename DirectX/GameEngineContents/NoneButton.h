#pragma once
#include "HUDUIActor.h"

// 설명 : 마우스나 버튼 반응 없은 랜더러용 ui
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
		return OpenParty_;
	}

	GameEngineUIRenderer* GetMenu()
	{
		return Menu_;
	}

	GameEngineUIRenderer* GetMoney()
	{
		return Money_;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

private:
	GameEngineUIRenderer* OpenParty_;
	GameEngineUIRenderer* Tab_;

	GameEngineUIRenderer* Menu_;
	GameEngineUIRenderer* Money_;

	GameEngineFontRenderer* F_OpenParty_;
};

