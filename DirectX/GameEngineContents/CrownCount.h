#pragma once
#include "HUDUIActor.h"
// ���� : �κ� ũ��� ȹ�� ���� ui
class GameEngineUIRenderer;
class CrownCount : public HUDUIActor
{
public:
	// constrcuter destructer
	CrownCount();
	~CrownCount();

	// delete Function
	CrownCount(const CrownCount& _Other) = delete;
	CrownCount(CrownCount&& _Other) noexcept = delete;
	CrownCount& operator=(const CrownCount& _Other) = delete;
	CrownCount& operator=(CrownCount&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};
private:
	GameEngineUIRenderer* Renderer;
	GameEngineUIRenderer* Face;
	GameEngineUIRenderer* CountBG;
	GameEngineUIRenderer* Icon;
	GameEngineFontRenderer* Font;

	int CurrentCrownCount;
	int RewardCrownCount;
};

