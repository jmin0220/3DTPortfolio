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
		StartInfo.TIME = 0.0f;
		StartInfo.SPEED = 1.0f;
		QueueInfo_.push(StartInfo);
		
		// ���� ����
		CinemachineInfo TmpInfo;
		TmpInfo.POS = float4{ 0,-10,-520 };
		TmpInfo.ROT = float4{ 16,0,0 };
		TmpInfo.TIME = 0.0f;
		TmpInfo.SPEED = 0.002f;
		QueueInfo_.push(TmpInfo);
		break;
	}
	case StageNum::STAGE2:
		break;
	case StageNum::STAGE3:
		break;
	case StageNum::STAGE4:
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
	if (0 < CurInfo_.TIME)
	{
		CurInfo_.TIME -= _DeltaTime;
		return;
	}
	
	float LertTime = _Info.StateTime * CurInfo_.SPEED;
	float4 NextPos = float4::Lerp(CurCamInfo_->GetTransform().GetWorldPosition(), CurInfo_.POS, LertTime);
	CurCamInfo_->GetTransform().SetWorldPosition(NextPos);

	float4 NextRot = float4::Lerp(CurCamInfo_->GetTransform().GetWorldRotation(), CurInfo_.ROT, LertTime);
	CurCamInfo_->GetTransform().SetWorldRotation(NextRot);

	// TODO::�������� �����ϸ� Inter�� ��ȯ
	if (true == CurCamInfo_->GetTransform().GetWorldPosition().CompareInt3D(CurInfo_.POS))
	{
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

void Cinemachine::EndUpdate(float _DeltaTime, const StateInfo& _Info)
{
	// TODO::����ó��
}
