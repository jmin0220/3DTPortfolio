#include "PreCompile.h"
#include "TestActor_Character.h"

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
	// 캐릭터 메쉬 로드 테스트용
	FBXRenderer_ = CreateComponent<GameEngineFBXRenderer>();

	// 기본적인 정육면체
	float4 BoxSize = float4(100, 100, 100);
	BoxRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	BoxRenderer_->SetMesh("Box");
	BoxRenderer_->SetPipeLine("Color");
	BoxColor_ = float4(0.0f, 0.7f, 0.7f, 0.9f);
	BoxRenderer_->GetShaderResources().SetConstantBufferLink("ResultColor", BoxColor_);
	BoxRenderer_->GetTransform().SetWorldScale(BoxSize);

	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->ChangeOrder(CollisionGroup::Player);
	Collision_->SetDebugSetting(CollisionType::CT_OBB, float4(1.0f, 0.0f, 0.0f, 0.5f));
	Collision_->GetTransform().SetWorldScale(BoxSize);

	// 카메라 암
	CameraArm_ = GetLevel()->CreateActor<CameraArm>();
	CameraArm_->SetFollowCamera(GetLevel()->GetMainCameraActor(), this);

}

void TestActor_Character::Update(float _DeltaTime)
{
	PlayerInputController();
	ApplyGravity();
	GetTransform().SetWorldMove(MoveDir_ * MoveSpeed * _DeltaTime);

	// 움직이는 방향으로 몸체 회전

}

void TestActor_Character::End()
{
}

void TestActor_Character::PlayerInputController()
{
	MoveDir_ = float4::ZERO;

	if (true == GameEngineInput::GetInst()->IsPress("W"))
	{
		// 카메라가 바라보는 방향을 앞으로
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
	// 바닥이 없으면 (y축)
	bool IsGround = Collision_->IsCollision(CollisionType::CT_OBB, CollisionGroup::Map, CollisionType::CT_OBB,
		[=](GameEngineCollision* _This, GameEngineCollision* _Other)
		{
			return CollisionReturn::ContinueCheck;
		});

	// 내려간다
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