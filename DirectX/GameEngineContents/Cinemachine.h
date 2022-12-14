#pragma once
#include <queue>

struct CinemachineInfo
{
	float4 POS;
	float4 ROT;
	float INTERTIME;		// 이동 후 멈추는 시간
	float MOVETIME;			// 이동하는 시간 ex)MOVETIME = 3.0f이면, 3.0f초 동안 움직여라.
	float SPEED;
	bool ResetPos = false;
};

// 설명 :
class Cinemachine 
{
	// 서버
public:
	void SetActivated()
	{
		Activated_ = true;
	}

	bool IsEnd()
	{
		return End_;
	}

private:
	bool Activated_;
	bool End_;

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
	CinemachineInfo							CurInfo_;		// 첫 정보 대입 외에 나머지는 다음에 도달할 정보?
	std::shared_ptr<GameEngineCameraActor>	CurCamInfo_;
	std::queue<CinemachineInfo>				QueueInfo_;

	StageNum CurStage_;
	float InterTime_;

	void IdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void MoveUpdate(float _DeltaTime, const StateInfo& _Info);
	void InterUpdate(float _DeltaTime, const StateInfo& _Info);
	void EndUpdate(float _DeltaTime, const StateInfo& _Info);
	void EndStart(const StateInfo& _Info);

};

