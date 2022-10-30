#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� : ��� UI�� �Ѱ��ϴ� ����?
class HUDUIActor : public GameEngineActor
{
public:
	// constrcuter destructer
	HUDUIActor();
	~HUDUIActor();

	// delete Function
	HUDUIActor(const HUDUIActor& _Other) = delete;
	HUDUIActor(HUDUIActor&& _Other) noexcept = delete;
	HUDUIActor& operator=(const HUDUIActor& _Other) = delete;
	HUDUIActor& operator=(HUDUIActor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};
private:

};

