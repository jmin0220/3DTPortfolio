#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "AxisActor.h"

// Ό³Έν :
class YAxisRot	:	public PickableActor
{
public:
	// constrcuter destructer
	YAxisRot();
	~YAxisRot();

	// delete Function
	YAxisRot(const YAxisRot& _Other) = delete;
	YAxisRot(YAxisRot&& _Other) noexcept = delete;
	YAxisRot& operator=(const YAxisRot& _Other) = delete;
	YAxisRot& operator=(YAxisRot&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:
	std::shared_ptr<GameEngineCollision> Collision;
public:
	std::shared_ptr<GameEngineCollision> GetCollision()
	{
		return Collision;
	}
};

