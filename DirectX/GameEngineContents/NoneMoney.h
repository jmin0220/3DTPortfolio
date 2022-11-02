#pragma once
#include "HUDUIActor.h"

// ���� : �κ� ȭ�� ui
class GameEngineUIRenderer;
class GameEngineFontRenderer;
class NoneMoney : public HUDUIActor
{
public:
	// constrcuter destructer
	NoneMoney();
	~NoneMoney();

	// delete Function
	NoneMoney(const NoneMoney& _Other) = delete;
	NoneMoney(NoneMoney&& _Other) noexcept = delete;
	NoneMoney& operator=(const NoneMoney& _Other) = delete;
	NoneMoney& operator=(NoneMoney&& _Other) noexcept = delete;

	int GetMoneyCost() //�� ���ϱ����� ��������
	{
		return MoneyCost_;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};
private:
	GameEngineUIRenderer* MoneyCount_;
	GameEngineUIRenderer* MoneyIcon_;
	GameEngineFontRenderer* MoneyNumber_;
	int MoneyCost_;
};

