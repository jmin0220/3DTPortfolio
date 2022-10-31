#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "AxisActor.h"

// Ό³Έν :
class YAxis	:	public PickableActor
{
public:
	// constrcuter destructer
	YAxis();
	~YAxis();

	// delete Function
	YAxis(const YAxis& _Other) = delete;
	YAxis(YAxis&& _Other) noexcept = delete;
	YAxis& operator=(const YAxis& _Other) = delete;
	YAxis& operator=(YAxis&& _Other) noexcept = delete;

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

