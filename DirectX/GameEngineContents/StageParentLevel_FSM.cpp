#include "PreCompile.h"
#include "StageParentLevel.h"
#include "PlayerActor.h"
#include "InGameSetUI.h"
#include "Cinemachine.h"
#include "IntroduceGame.h"

///////////////////////////
// �������� ������ �غ� �ܰ�
///////////////////////////
void StageParentLevel::IdleStart(const StateInfo& _Info)
{
	// ī�޶�� -> �÷��̾�� ����(������ �� �� �����ߵ�)
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
// ī�޶� �ó׸ӽ�
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
	// ī�޶�� -> �÷��̾�� ����
	CameraArm_->SetFollowCamera(GetMainCameraActor(), Player_);
}

void StageParentLevel::ReadyUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsDown(KEY_ENTER))
	{
		//UIs_-> ī��Ʈ�ٿ� ��ŸƮ
		UIs_->CountdownStart();
		StageStateManager_.ChangeState("Race");
		return;
	}
}

///////////////////////////
// ���ݺ��� �޸� �� ����
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
// ���� 
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

