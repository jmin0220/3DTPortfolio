#include "PreCompile.h"
#include "StageParentLevel.h"
#include "PlayerActor.h"
#include "InGameSetUI.h"
#include "Cinemachine.h"
#include "IntroduceGame.h"

///////////////////////////
// 스테이지 시작전 준비 단계
///////////////////////////
void StageParentLevel::IdleStart(const StateInfo& _Info)
{
	// 카메라암 -> 플레이어에게 세팅(나중이 이 줄 지워야됨)
	CameraArm_->SetFollowCamera(GetMainCameraActor(), Player_);

	IntroduceGame_->SetStageTexture(MyStage_);
	IntroduceGame_->On();
}

void StageParentLevel::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	SpawnServerObjects();

	if (true == GameEngineInput::GetInst()->IsDown(KEY_ENTER))
	{
		//StageStateManager_.ChangeState("StagePreView");
		return;
	}
}

///////////////////////////
// 카메라 시네머신
///////////////////////////
//void StageParentLevel::StagePreViewStart(const StateInfo& _Info)
//{
//	MainCam_->OnFreeCameraMode();
//	MainCam_->GetTransform().SetWorldRotation({ 0, 0, 0 });
//	MainCam_->GetTransform().SetWorldPosition({ 0, -60, 200 });
//}
//
//void StageParentLevel::StagePreViewUpdate(float _DeltaTime, const StateInfo& _Info)
//{
//	float4 NextPos = float4::Lerp(MainCam_->GetTransform().GetWorldPosition(), float4{ 0, -10, -520 }, _Info.StateTime * 0.002f);
//	MainCam_->GetTransform().SetWorldPosition(NextPos);
//
//	float4 NextRot = float4::Lerp(MainCam_->GetTransform().GetWorldRotation(), float4{ 16, 0, 0 }, _Info.StateTime * 0.002f);
//	MainCam_->GetTransform().SetWorldRotation(NextRot);
//}

///////////////////////////
// 3, 2, 1, GO!
///////////////////////////
void StageParentLevel::ReadyStart(const StateInfo& _Info)
{
	// 카메라암 -> 플레이어에게 세팅
	CameraArm_->SetFollowCamera(GetMainCameraActor(), Player_);
}

void StageParentLevel::ReadyUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsDown(KEY_ENTER))
	{
		//UIs_-> 카운트다운 스타트
		UIs_->CountdownStart();
		StageStateManager_.ChangeState("Race");
		return;
	}
}

///////////////////////////
// 지금부터 달릴 수 있음
///////////////////////////
void StageParentLevel::RaceStart(const StateInfo& _Info)
{
	UIs_->OnOffSuccessCount();
}

void StageParentLevel::RaceUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsDown(KEY_ENTER))
	{
		UIs_->OnOffSuccessCount();
		StageStateManager_.ChangeState("End");
		return;
	}
}

///////////////////////////
// 종료 
///////////////////////////
void StageParentLevel::EndStart(const StateInfo& _Info)
{
	UIs_->OnOffEnd();
}

void StageParentLevel::EndUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsDown(KEY_ENTER))
	{
		return;
	}
}

