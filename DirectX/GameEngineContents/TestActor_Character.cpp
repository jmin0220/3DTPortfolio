#include "PreCompile.h"
#include "TestActor_Character.h"
#include <GameEngineCore/CoreMinimal.h>

#include "CameraArm.h"

const float MoveSpeed = 300;

TestActor_Character::TestActor_Character() 
{
}

TestActor_Character::~TestActor_Character() 
{
}

void TestActor_Character::Start()
{
	// �⺻���� ������ü
	float4 BoxSize(100, 200, 100);

	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->ChangeOrder(CollisionGroup::Player);
	Collision_->SetDebugSetting(CollisionType::CT_OBB, float4(1.0f, 0.0f, 0.0f, 0.5f));
	Collision_->GetTransform().SetWorldScale(BoxSize);
	Collision_->GetTransform().SetLocalMove({ 0, 100, 0 });

	// ī�޶� ��
	CameraArm_ = GetLevel()->CreateActor<CameraArm>();
	CameraArm_->SetFollowCamera(GetLevel()->GetMainCameraActor(), this);
	CameraArm_->On();

	// ĳ���� �޽� �ε� �׽�Ʈ��
	FBXRenderer_ = CreateComponent<GameEngineFBXRenderer>();
	FBXRenderer_->SetFBXMesh("Character.FBX", "TextureCustom");
	FBXRenderer_->GetTransform().SetWorldScale({ 100, 100, 100 });

}

void TestActor_Character::Update(float _DeltaTime)
{
	PlayerInputController();
	ApplyGravity();
	GetTransform().SetWorldMove(MoveDir_ * MoveSpeed * _DeltaTime);

}

void TestActor_Character::End()
{
	CameraArm_->Off();
}

void TestActor_Character::PlayerInputController()
{
	MoveDir_ = float4::ZERO;

	if (true == GameEngineInput::GetInst()->IsPress("W"))
	{
		// ī�޶� �ٶ󺸴� ������ ������
		MoveDir_ += GetLevel()->GetMainCameraActor()->GetTransform().GetForwardVector();
	}

	if (true == GameEngineInput::GetInst()->IsPress("A"))
	{
		MoveDir_ += float4(-1.0f, 0.0f, 0.0f, 0.0f);
	}

	if (true == GameEngineInput::GetInst()->IsPress("S"))
	{
		MoveDir_ += float4(0.0f, 0.0f, -1.0f, 0.0f);
	}

	if (true == GameEngineInput::GetInst()->IsPress("D"))
	{
		MoveDir_ += float4(1.0f, 0.0f, 0.0f, 0.0f);
	}

	if (true == GameEngineInput::GetInst()->IsPress("SpaceBar"))
	{
		GetTransform().SetWorldMove({ 0, 10, 0 });
	}
}

void TestActor_Character::ApplyGravity()
{
	// �ٴ��� ������ (y��)
	bool IsGround = Collision_->IsCollision(CollisionType::CT_OBB, CollisionGroup::Map, CollisionType::CT_OBB,
		[=](GameEngineCollision* _This, GameEngineCollision* _Other)
		{
			return CollisionReturn::ContinueCheck;
		});

	// ��������
	if (false == IsGround)
	{
		MoveDir_.y = -1.0f;
	}
	else
	{
		MoveDir_.y = 0.0f;
	}
}

void TestActor_Character::RotateCharacterForward()
{
	float4 Forward = GetTransform().GetForwardVector();
	float4 Target = MoveDir_;
	float YAxisDegree = acosf(float4::DotProduct3D(Forward, Target.Normalize3DReturn()))* GameEngineMath::RadianToDegree;
}

