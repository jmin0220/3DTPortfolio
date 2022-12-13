#include "PreCompile.h"
#include "Cinemachine.h"

Cinemachine::Cinemachine() 
	: InterTime_(0.0f)
	, FSM_()
{
}

Cinemachine::~Cinemachine() 
{
}

void Cinemachine::Init(std::shared_ptr<GameEngineCameraActor> _MainCamera)
{
	FSM_.CreateStateMember("Idle", std::bind(&Cinemachine::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2));
	FSM_.CreateStateMember("Move", std::bind(&Cinemachine::MoveUpdate, this, std::placeholders::_1, std::placeholders::_2));
	FSM_.CreateStateMember("Inter", std::bind(&Cinemachine::InterUpdate, this, std::placeholders::_1, std::placeholders::_2));
	FSM_.CreateStateMember("End", std::bind(&Cinemachine::EndUpdate, this, std::placeholders::_1, std::placeholders::_2));

	CurCamInfo_ = _MainCamera;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// QueueInfo_ 값이 없으면 터짐(Activate함수에서 front를 쓰는데 들어있는게 없기 때문). 모든 스테이지레벨을 stage1로 인식.
	// 각 스테이지레벨 스타트에서 MyStage_설정을 StageParentLevel::Start();보다 그 전에 넣어줘야 각 스테이지 별로 인식.
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	switch (CurStage_)
	{
	case StageNum::STAGE1:
	{
		// Test용 임의로 부여한 값
		// 시작 정보
		CinemachineInfo StartInfo;
		StartInfo.POS = float4{ 0,-60,200 };
		StartInfo.ROT = float4{ 16,0,0 };
		StartInfo.INTERTIME = 0.0f;
		StartInfo.MOVETIME= 0.0f;
		StartInfo.SPEED = 1.0f;
		QueueInfo_.push(StartInfo);
		
		// 다음 정보
		CinemachineInfo TmpInfo;
		TmpInfo.POS = float4{ 0,-10,-520 };
		TmpInfo.ROT = float4{ 16,0,0 };
		TmpInfo.INTERTIME = 0.0f;
		TmpInfo.MOVETIME = 20.0f;
		TmpInfo.SPEED = 0.002f;
		QueueInfo_.push(TmpInfo);
		break;
	}
	case StageNum::STAGE2:
	{
		// 시작 정보
		CinemachineInfo StartInfo;
		StartInfo.POS = float4{ -205,680,860};
		StartInfo.ROT = float4{ 40,155,0 };
		StartInfo.INTERTIME = 0.0f;
		StartInfo.MOVETIME = 0.0f;
		StartInfo.SPEED = 0.002f;
		QueueInfo_.push(StartInfo);

		// 다음 정보
		CinemachineInfo TmpInfo;
		TmpInfo.POS = float4{ -95,385,315 };
		TmpInfo.ROT = float4{ 45,160,0 };
		TmpInfo.INTERTIME = 0.0f;
		TmpInfo.MOVETIME = 9.5f;
		TmpInfo.SPEED = 0.002f;
		QueueInfo_.push(TmpInfo);

		TmpInfo.POS = float4{ -140,240,-45 };
		TmpInfo.ROT = float4{ 50,70,0 };
		TmpInfo.INTERTIME = 0.0f;
		TmpInfo.MOVETIME = 10.0f;
		TmpInfo.SPEED = 0.002f;
		QueueInfo_.push(TmpInfo);
		break;
	}
	case StageNum::STAGE3:
	{
		// 시작 정보
		CinemachineInfo StartInfo;
		StartInfo.POS = float4{ 20,65,445 };
		StartInfo.ROT = float4{ 5,185,0 };
		StartInfo.INTERTIME = 0.0f;
		StartInfo.MOVETIME = 0.0f;
		StartInfo.SPEED = 0.002f;
		QueueInfo_.push(StartInfo);

		// 다음 정보
		CinemachineInfo TmpInfo;
		TmpInfo.POS = float4{ 510,130,3 }/*float4{ 385,65,5 }*/;
		TmpInfo.ROT = float4{ 13,270,0 }/*float4{ 10,270,0 }*/;
		TmpInfo.INTERTIME = 0.0f;
		TmpInfo.MOVETIME = 8.5f;
		TmpInfo.SPEED = 0.002f;
		QueueInfo_.push(TmpInfo);

		TmpInfo.POS = float4{ 0,45,-255 }/*float4{ 0,45,-285 }*/;
		TmpInfo.ROT = float4{ 15,360,0 }/*float4{ 15,360,0 }*/;
		TmpInfo.INTERTIME = 0.0f;
		TmpInfo.MOVETIME = 13.0f;
		TmpInfo.SPEED = 0.002f;
		QueueInfo_.push(TmpInfo);
		break;
	}
	case StageNum::STAGE4:
		break;
	case StageNum::STAGE5:
		break; 
	default:
	{
		int a = 0;
		break;
	}
	}

	FSM_.ChangeState("Idle");
}

void Cinemachine::Activate()
{
	if (true == GameEngineInput::GetInst()->IsDown(KEY_ENTER))
	{
		// 첫 시작 정보 대입
		CurInfo_ = QueueInfo_.front();
		CurCamInfo_->OnFreeCameraMode();
		CurCamInfo_->GetTransform().SetWorldPosition(CurInfo_.POS);
		CurCamInfo_->GetTransform().SetWorldRotation(CurInfo_.ROT);
		QueueInfo_.pop();
		FSM_.ChangeState("Inter");
		return;
	}
}

void Cinemachine::Update()
{
	FSM_.Update(GameEngineTime::GetDeltaTime());
}

void Cinemachine::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	this->Activate();
}

void Cinemachine::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (0 < CurInfo_.INTERTIME)
	{
		CurInfo_.INTERTIME -= _DeltaTime;
		return;
	}
	
	float LertTime = _Info.StateTime * CurInfo_.SPEED;
	float4 NextPos = float4::Lerp(CurCamInfo_->GetTransform().GetWorldPosition(), CurInfo_.POS, LertTime);
	CurCamInfo_->GetTransform().SetWorldPosition(NextPos);

	float4 NextRot = float4::Lerp(CurCamInfo_->GetTransform().GetWorldRotation(), CurInfo_.ROT, LertTime);
	CurCamInfo_->GetTransform().SetWorldRotation(NextRot);

	// TODO::목적지에 도달하면 Inter로 전환
	if (CurInfo_.MOVETIME <= _Info.StateTime/*true == CurCamInfo_->GetTransform().GetWorldPosition().CompareInt3D(CurInfo_.POS)*/)
	{
		//GameEngineDebug::OutPutString(std::to_string(_Info.StateTime));
		FSM_.ChangeState("Inter");
		return;
	}
}

void Cinemachine::InterUpdate(float _DeltaTime, const StateInfo& _Info)
{
	// 시네머신 정보가 담긴 큐가 비어있다면 End
	if (QueueInfo_.empty())
	{
		FSM_.ChangeState("End");
		return;
	}
	// 비어있지 않다면 현재 정보에 새 정보를 대입하고 삭제 후 Move
	else
	{
		CurInfo_ = QueueInfo_.front();
		QueueInfo_.pop();
		FSM_.ChangeState("Move");
		return;
	}
}

void Cinemachine::EndUpdate(float _DeltaTime, const StateInfo& _Info)
{
	// TODO::서버처리
}
