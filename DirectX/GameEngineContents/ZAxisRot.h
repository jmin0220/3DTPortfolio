#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "AxisActor.h"

// Ό³Έν :
class ZAxisRot	:	public PickableActor
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
	GameEngineCollision* Collision;
public:
	GameEngineCollision* GetCollision()
	{
		return Collision;
	}
};

