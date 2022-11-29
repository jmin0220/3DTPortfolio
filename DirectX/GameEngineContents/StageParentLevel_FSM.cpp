#include "PreCompile.h"
#include "StageParentLevel.h"

#include "InGameSetUI.h"

void StageParentLevel::IdleStart(const StateInfo& _Info)
{
}

void StageParentLevel::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	// 테스트용
	// 추후 서버에서 레이스 시작 호출해주면 ReadyUpdate 에서 <UI> 321땅 시작
	
	if (true == GameEngineInput::GetInst()->IsDown(KEY_ENTER))
	{
		//UIs_-> 카운트다운 스타트
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
