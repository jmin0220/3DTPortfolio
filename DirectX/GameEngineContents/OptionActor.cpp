#include "PreCompile.h"
#include "OptionActor.h"

OptionActor::OptionActor() 
{
}

OptionActor::~OptionActor() 
{
}

void OptionActor::Start()
{
	Renderer_ = CreateComponent<GameEngineUIRenderer>();
	Renderer_->SetTexture("OptionUI.png");
	Renderer_->GetTransform().SetWorldScale({838,783});
	//Renderer_->GetTransform().SetWorldPosition({380.0f,-10});

	Ball_ = CreateComponent<GameEngineUIRenderer>();
	Ball_->SetTexture("SoccerBall.png");
	Ball_->GetTransform().SetWorldScale({52,50});
	Ball_->GetTransform().SetWorldPosition({330,88});

	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->SetDebugSetting(CollisionType::CT_OBB2D, float4{ 0.0f,1.0f,0.0f,0.3f });
	Collision_->GetTransform().SetWorldScale({675.0f, 30.0f});
	Collision_->SetUIDebugCamera();
	Collision_->GetTransform().SetWorldPosition({ -10.0f, 88 });
	Collision_->ChangeOrder(UICOLLISION::Sound);
}

void OptionActor::Update(float _DeltaTime)
{
	ColCheck_ = Collision_->IsCollision(CollisionType::CT_OBB2D, UICOLLISION::Mouse, CollisionType::CT_OBB2D,
		[=](std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
		{
			MousePos_ = _Other->GetTransform().GetWorldPosition();
			RealPos_ = MousePos_.x - 30.0f;
			VolumeRatio_ = RealPos_ / 675;
			if (true == GameEngineInput::GetInst()->IsPress("Click"))
			{
				Ball_->GetTransform().SetWorldPosition({ (677* MousePos_.x +30)/675,88 });
				GlobalBGM::GetInst()->GetBGM().Volume(VolumeRatio_);
			}
				return CollisionReturn::Break;
		});

}

void OptionActor::LevelStartEvent()
{
}

void OptionActor::LevelEndEvent()
{
}
