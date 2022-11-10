#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "AxisActor.h"

// ���� :
// ������ Pick�� �Ǵ� X
class XAxisRot	:	public PickableActor
{
public:
	// constrcuter destructer
	XAxisRot();
	~XAxisRot();

	// delete Function
	XAxisRot(const XAxisRot& _Other) = delete;
	XAxisRot(XAxisRot&& _Other) noexcept = delete;
	XAxisRot& operator=(const XAxisRot& _Other) = delete;
	XAxisRot& operator=(XAxisRot&& _Other) noexcept = delete;

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

