#include "PreCompile.h"
#include "StageParentLevel.h"

#include "InGameSetUI.h"

void StageParentLevel::IdleStart(const StateInfo& _Info)
{
}

void StageParentLevel::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	// �׽�Ʈ��
	// ���� �������� ���̽� ���� ȣ�����ָ� ReadyUpdate ���� <UI> 321�� ����
	
	if (true == GameEngineInput::GetInst()->IsDown(KEY_ENTER))
	{
		//UIs_-> ī��Ʈ�ٿ� ��ŸƮ
		UIs_->CountdownStart();
	}
}

void StageParentLevel::ReadyStart(const StateInfo& _Info)
{

}

void StageParentLevel::ReadyUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void StageParentLevel::RaceStart(const StateInfo& _Info)
{
}

void StageParentLevel::RaceUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void StageParentLevel::EndStart(const StateInfo& _Info)
{
}

void StageParentLevel::EndUpdate(float _DeltaTime, const StateInfo& _Info)
{
}
