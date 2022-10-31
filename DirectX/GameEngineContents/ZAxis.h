#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "AxisActor.h"

// Ό³Έν :
class ZAxis	:	public PickableActor
{
public:
	// constrcuter destructer
	ZAxis();
	~ZAxis();

	// delete Function
	ZAxis(const ZAxis& _Other) = delete;
	ZAxis(ZAxis&& _Other) noexcept = delete;
	ZAxis& operator=(const ZAxis& _Other) = delete;
	ZAxis& operator=(ZAxis&& _Other) noexcept = delete;

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

