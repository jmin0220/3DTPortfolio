#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "AxisActor.h"

// Ό³Έν :
class ZAxisRot	:	public GameEngineActor
{
public:
	// constrcuter destructer
	ZAxisRot();
	~ZAxisRot();

	// delete Function
	ZAxisRot(const ZAxisRot& _Other) = delete;
	ZAxisRot(ZAxisRot&& _Other) noexcept = delete;
	ZAxisRot& operator=(const ZAxisRot& _Other) = delete;
	ZAxisRot& operator=(ZAxisRot&& _Other) noexcept = delete;

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

