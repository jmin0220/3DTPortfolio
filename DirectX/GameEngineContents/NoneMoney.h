#pragma once
#include "HUDUIActor.h"

// 설명 : 로비에 화폐 ui
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

	int GetMoneyCost() //돈 더하기위해 꺼내쓸때
	{
		return MoneyCost_;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};
private:
	std::shared_ptr<GameEngineUIRenderer> MoneyCount_;
	std::shared_ptr<GameEngineUIRenderer> MoneyIcon_;
	std::shared_ptr<GameEngineFontRenderer> MoneyNumber_;
	int MoneyCost_;
};

