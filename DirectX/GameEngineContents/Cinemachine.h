#pragma once
#include <queue>

struct CinemachineInfo
{
	float4 POS;
	float4 ROT;
	float TIME;
	float SPEED;
};

// ���� :
class Cinemachine 
{
public:
	// constrcuter destructer
	Cinemachine();
	~Cinemachine();

	// delete Function
	Cinemachine(const Cinemachine& _Other) = delete;
	Cinemachine(Cinemachine&& _Other) noexcept = delete;
	Cinemachine& operator=(const Cinemachine& _Other) = delete;
	Cinemachine& operator=(Cinemachine&& _Other) noexcept = delete;

	void Init(std::shared_ptr<GameEngineCameraActor> _MainCamera);
	void Activate();
	void Update();

	inline void SetStage(StageNum _Stage)
	{
		CurStage_ = _Stage;
	}

protected:

private:
	GameEngineStateManager					FSM_;
	CinemachineInfo							CurInfo_;		// ù ���� ���� �ܿ� �������� ������ ������ ����?
	std::shared_ptr<GameEngineCameraActor>	CurCamInfo_;
	std::queue<CinemachineInfo>				QueueInfo_;

	StageNum CurStage_;
	float InterTime_;

	void IdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void MoveUpdate(float _DeltaTime, const StateInfo& _Info);
	void InterUpdate(float _DeltaTime, const StateInfo& _Info);
	void EndUpdate(float _DeltaTime, const StateInfo& _Info);

};

