#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "AxisActor.h"

// 설명 :
// 실제로 Pick이 되는 X
class XAxis	:	public PickableActor
{
public:
	// constrcuter destructer
	XAxis();
	~XAxis();

	// delete Function
	XAxis(const XAxis& _Other) = delete;
	XAxis(XAxis&& _Other) noexcept = delete;
	XAxis& operator=(const XAxis& _Other) = delete;
	XAxis& operator=(XAxis&& _Other) noexcept = delete;

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

