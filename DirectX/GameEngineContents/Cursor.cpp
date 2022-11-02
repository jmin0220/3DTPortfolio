#include "PreCompile.h"
#include "Cursor.h"

Cursor::Cursor() 
	:MouseImage_(nullptr)
{
}

Cursor::~Cursor() 
{
}

void Cursor::Start()
{
	MouseImage_ = CreateComponent<GameEngineUIRenderer>();
	
	MouseImage_->SetTexture("Cursor.png");
	MouseImage_->GetTransform().SetWorldScale({ 32,32,0 });
	MouseImage_->SetPivot(PIVOTMODE::LEFTTOP);
	MouseImage_->GetTransform().SetWorldPosition({ UICursorPos_.x,UICursorPos_.y });

	ActorCollision_ = CreateComponent<GameEngineCollision>();
	ActorCollision_->SetDebugSetting(CollisionType::CT_OBB2D, float4{ 1.0f,0.0f,0.0f,0.3f });
	ActorCollision_->GetTransform().SetWorldScale({ 4.0f, 4.0f, 100.0f });

	UICollision_ = CreateComponent<GameEngineCollision>();
	UICollision_->SetDebugSetting(CollisionType::CT_OBB2D, float4{ 0.0f,1.0f,0.0f,0.3f });
	UICollision_->GetTransform().SetWorldScale({ 4.0f, 4.0f, 100.0f });
	UICollision_->SetUIDebugCamera();
}

void Cursor::Update(float _DeltaTime)
{
	MainCursorPos_ = GetLevel()->GetMainCamera()->GetMouseWorldPositionToActor();//메인카메라용
	UICursorPos_ = GetLevel()->GetUICamera()->GetMouseWorldPositionToActor();//UI카메라용

	ActorCollision_->GetTransform().SetWorldPosition(MainCursorPos_);
	UICollision_->GetTransform().SetWorldPosition(UICursorPos_);

	MouseImage_->GetTransform().SetWorldPosition({ UICursorPos_.x ,UICursorPos_.y });

}
