#pragma once
#include "HUDUIActor.h"
// 설명 : 로비에 크라운 획득 개수 ui
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
	std::shared_ptr<GameEngineUIRenderer> Renderer_;
	std::shared_ptr<GameEngineUIRenderer> Face_;
	std::shared_ptr<GameEngineUIRenderer> CountBG_;
	std::shared_ptr<GameEngineUIRenderer> Icon_;
	std::shared_ptr<GameEngineFontRenderer> Font_;

	int CurrentCrownCount_;
	int RewardCrownCount_;
};

