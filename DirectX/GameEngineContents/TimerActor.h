#pragma once

// ���� : �ΰ��ӿ��� �ð��� ��� Ÿ�̸�
class TimerActor : public GameEngineActor
{
public:
	// constrcuter destructer
	TimerActor();
	~TimerActor();

	// delete Function
	TimerActor(const TimerActor& _Other) = delete;
	TimerActor(TimerActor&& _Other) noexcept = delete;
	TimerActor& operator=(const TimerActor& _Other) = delete;
	TimerActor& operator=(TimerActor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

	void LevelStartEvent() override;
private:
	std::shared_ptr<GameEngineFontRenderer> FontOneSecond_;
	std::shared_ptr<GameEngineFontRenderer> FontTenSecond_;
	std::shared_ptr<GameEngineFontRenderer> FontOneMinute_;
	std::shared_ptr<GameEngineFontRenderer> Colon_;

	int OneSecond_;
	int TenSecond_;
	int OneMinute_;
	float Time_;

	std::shared_ptr<GameEngineUIRenderer> Plate_;
};

