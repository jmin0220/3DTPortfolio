#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� : �κ� ȭ�� ui
class GameEngineUIRenderer;
class GameEngineFontRenderer;
class NoneMoney : public GameEngineActor
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
	std::shared_ptr<GameEngineUIRenderer> MoneyCount_;
	std::shared_ptr<GameEngineUIRenderer> MoneyIcon_;
	std::shared_ptr<GameEngineFontRenderer> MoneyNumber_;
	int MoneyCost_;
};

