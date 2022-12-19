#include "PreCompile.h"
#include "Cinemachine.h"

Cinemachine::Cinemachine() 
	: InterTime_(0.0f)
	, FSM_()
	, Activated_(false)
	, End_(false)
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
	FSM_.CreateStateMember("End", std::bind(&Cinemachine::EndUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Cinemachine::EndStart, this, std::placeholders::_1));

	CurCamInfo_ = _MainCamera;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// QueueInfo_ ���� ������ ����(Activate�Լ����� front�� ���µ� ����ִ°� ���� ����). ��� �������������� stage1�� �ν�.
	// �� ������������ ��ŸƮ���� MyStage_������ StageParentLevel::Start();���� �� ���� �־���� �� �������� ���� �ν�.
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	switch (CurStage_)
	{
	case StageNum::STAGE1:
	{
		// Test�� ���Ƿ� �ο��� ��
		// ���� ����
		CinemachineInfo StartInfo;
		StartInfo.POS = float4{ 0,-60,200 };
		StartInfo.ROT = float4{ 16,0,0 };
		StartInfo.INTERTIME = 0.0f;
		StartInfo.MOVETIME = 0.0f;
		StartInfo.SPEED = 1.0f;
		QueueInfo_.push(StartInfo);
		
		// ���� ����
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
		// ���� ����
		CinemachineInfo StartInfo;
		StartInfo.POS = float4{ -205,680,860 };
		StartInfo.ROT = float4{ 40,155,0 };
		StartInfo.INTERTIME = 0.0f;
		StartInfo.MOVETIME = 0.0f;
		StartInfo.SPEED = 0.002f;
		QueueInfo_.push(StartInfo);

		// ���� ����
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
		// ���� ����
		CinemachineInfo StartInfo;
		StartInfo.POS = float4{ 20,65,445 };
		StartInfo.ROT = float4{ 5,185,0 };
		StartInfo.INTERTIME = 0.0f;
		StartInfo.MOVETIME = 0.0f;
		StartInfo.SPEED = 0.002f;
		QueueInfo_.push(StartInfo);

		// ���� ����
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
	{
		CinemachineInfo StartInfo;
		StartInfo.POS = float4{ 276.19,71.43f,159.49f };
		StartInfo.ROT = float4{ 14.15f,239.0f,0 };
		QueueInfo_.push(StartInfo);

		StartInfo.POS = float4{ 276.19,433.78f,159.49f };
		StartInfo.ROT = float4{ 14.15f,239.0f,0 };
		StartInfo.INTERTIME = 0.0f;
		StartInfo.MOVETIME = 9.0f;
		StartInfo.SPEED = 0.002f;
		QueueInfo_.push(StartInfo);

		StartInfo.POS = float4{ -82.0f,264.25f,87.28f };
		StartInfo.ROT = float4{ -0.64f, 97.5f,0 };
		StartInfo.ResetPos = true;
		QueueInfo_.push(StartInfo);

		StartInfo.POS = float4{ -110.81,209.62f,31.53f };
		StartInfo.ROT = float4{ 1.07f, 134.16f,0 };
		StartInfo.INTERTIME = 0.0f;
		StartInfo.MOVETIME = 20.0f;
		StartInfo.SPEED = 0.0005f;
		StartInfo.ResetPos = false;
		QueueInfo_.push(StartInfo);

		StartInfo.POS = float4{ 222.6f,425.0f,128.0f };
		StartInfo.ROT = float4{ 4.5f, 240.16f,0 };
		StartInfo.ResetPos = true;
		QueueInfo_.push(StartInfo);

		StartInfo.POS = float4{ 222.6f,425.0f,128.0f };
		StartInfo.ROT = float4{ 13.3f, 239.73f,0 };
		StartInfo.INTERTIME = 0.0f;
		StartInfo.MOVETIME = 15.0f;
		StartInfo.SPEED = 0.0005f;
		StartInfo.ResetPos = false;
		QueueInfo_.push(StartInfo);

		break;
	}
	case StageNum::STAGE5:
	{
		CinemachineInfo StartInfo;
		StartInfo.POS = float4{ -308.0f,248.5f,110.3f };
		StartInfo.ROT = float4{ 35.3f,102.42f,0 };
		StartInfo.INTERTIME = 0.0f;
		StartInfo.MOVETIME = 0.0f;
		StartInfo.SPEED = 0.002f;
		QueueInfo_.push(StartInfo);


		StartInfo.POS = float4{ -29.5f,248.5f,-72.8f };
		StartInfo.ROT = float4{ 74.5f,30.18f,0 };
		StartInfo.INTERTIME = 0.0f;
		StartInfo.MOVETIME = 10.0f;
		StartInfo.SPEED = 0.0005f;
		QueueInfo_.push(StartInfo);

		StartInfo.POS = float4{ 55.22f,192.51f,235.64f };
		StartInfo.ROT = float4{ 33.54f,-152.0f,0 };
		StartInfo.INTERTIME = 0.0f;
		StartInfo.MOVETIME = 0.0f;
		StartInfo.SPEED = 0.0005f;
		StartInfo.ResetPos = true;
		QueueInfo_.push(StartInfo);

		StartInfo.POS = float4{ 320.0f,248.5f,-156.6f };
		StartInfo.ROT = float4{ 21.91f,-58.41f,0 };
		StartInfo.INTERTIME = 0.0f;
		StartInfo.MOVETIME = 15.0f;
		StartInfo.SPEED = 0.0005f;
		StartInfo.ResetPos = false;
		QueueInfo_.push(StartInfo);
		break; 
	}
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
	if (true == Activated_)
	{
		// ù ���� ���� ����
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
	
	if (CurInfo_.ResetPos == true)
	{
		CurCamInfo_->GetTransform().SetWorldPosition(CurInfo_.POS);
		CurCamInfo_->GetTransform().SetWorldRotation(CurInfo_.ROT);
		FSM_.ChangeState("Inter");
		return;
	}
	
	float LertTime = _Info.StateTime * CurInfo_.SPEED;
	float4 NextPos = float4::Lerp(CurCamInfo_->GetTransform().GetWorldPosition(), CurInfo_.POS, LertTime);
	CurCamInfo_->GetTransform().SetWorldPosition(NextPos);

	float4 NextRot = float4::Lerp(CurCamInfo_->GetTransform().GetWorldRotation(), CurInfo_.ROT, LertTime);
	CurCamInfo_->GetTransform().SetWorldRotation(NextRot);

	// TODO::�������� �����ϸ� Inter�� ��ȯ
	if (CurInfo_.MOVETIME <= _Info.StateTime/*true == CurCamInfo_->GetTransform().GetWorldPosition().CompareInt3D(CurInfo_.POS)*/)
	{
		//GameEngineDebug::OutPutString(std::to_string(_Info.StateTime));
		FSM_.ChangeState("Inter");
		return;
	}
}

void Cinemachine::InterUpdate(float _DeltaTime, const StateInfo& _Info)
{
	// �ó׸ӽ� ������ ��� ť�� ����ִٸ� End
	if (QueueInfo_.empty())
	{
		FSM_.ChangeState("End");
		return;
	}
	// ������� �ʴٸ� ���� ������ �� ������ �����ϰ� ���� �� Move
	else
	{
		CurInfo_ = QueueInfo_.front();
		QueueInfo_.pop();
		FSM_.ChangeState("Move");
		return;
	}
}

void Cinemachine::EndStart(const StateInfo& _Info)
{
	End_ = true;
}

void Cinemachine::EndUpdate(float _DeltaTime, const StateInfo& _Info)
{

}

