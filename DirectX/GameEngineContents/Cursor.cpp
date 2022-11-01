#include "PreCompile.h"
#include "Cursor.h"

Cursor::Cursor() 
	:MouseImage(nullptr)
{
}

Cursor::~Cursor() 
{
}

void Cursor::Start()
{
	MouseImage = CreateComponent<GameEngineUIRenderer>();
	
	MouseImage->SetTexture("Cursor.png");
	MouseImage->GetTransform().SetWorldScale({ 32,32,0 });
	MouseImage->SetPivot(PIVOTMODE::LEFTTOP);
	MouseImage->GetTransform().SetWorldPosition({ UICursorPos.x,UICursorPos.y });

	ActorCollision = CreateComponent<GameEngineCollision>();
	ActorCollision->SetDebugSetting(CollisionType::CT_OBB2D, float4{ 1.0f,0.0f,0.0f,0.3f });
	ActorCollision->GetTransform().SetWorldScale({ 4.0f, 4.0f, 100.0f });

	UICollision = CreateComponent<GameEngineCollision>();
	UICollision->SetDebugSetting(CollisionType::CT_OBB2D, float4{ 0.0f,0.0f,1.0f,0.3f });
	UICollision->GetTransform().SetWorldScale({ 4.0f, 4.0f, 100.0f });
	UICollision->SetUIDebugCamera();
}

void Cursor::Update(float _DeltaTime)
{
	MainCursorPos = GetLevel()->GetMainCamera()->GetMouseWorldPositionToActor();//메인카메라용
	UICursorPos = GetLevel()->GetUICamera()->GetMouseWorldPositionToActor();//UI카메라용

	ActorCollision->GetTransform().SetWorldPosition(MainCursorPos);
	UICollision->GetTransform().SetWorldPosition(UICursorPos);

	MouseImage->GetTransform().SetWorldPosition({ UICursorPos.x ,UICursorPos.y });

}
