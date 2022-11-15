#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� : ���콺�� ��ư ���� ���� �������� ui
class GameEngineUIRenderer;
class NoneButton : public GameEngineActor
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

	std::shared_ptr<GameEngineUIRenderer> GetOpenParty()
	{
		return OpenParty_;
	}

	std::shared_ptr<GameEngineUIRenderer> GetMenu()
	{
		return Menu_;
	}

	std::shared_ptr<GameEngineUIRenderer> GetMoney()
	{
		return Money_;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

private:
	std::shared_ptr<GameEngineUIRenderer> OpenParty_;
	std::shared_ptr<GameEngineUIRenderer> Tab_;

	std::shared_ptr<GameEngineUIRenderer> Menu_;
	std::shared_ptr<GameEngineUIRenderer> Money_;

	std::shared_ptr<GameEngineFontRenderer> F_OpenParty_;
};

