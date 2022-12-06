#pragma once
#include "StageParentLevel.h"

// ���� :
class InGameSetUI;
class JumpClubLevel : public StageParentLevel
{
public:
	// constrcuter destructer
	JumpClubLevel();
	~JumpClubLevel();

	// delete Function
	JumpClubLevel(const JumpClubLevel& _Other) = delete;
	JumpClubLevel(JumpClubLevel&& _Other) noexcept = delete;
	JumpClubLevel& operator=(const JumpClubLevel& _Other) = delete;
	JumpClubLevel& operator=(JumpClubLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;

private:
	std::shared_ptr<InGameSetUI> UIs_;

	std::shared_ptr<GameEngineActor> BackGroundObj_;;
	std::shared_ptr<GameEngineActor> VFXWaterObj_;;

};

