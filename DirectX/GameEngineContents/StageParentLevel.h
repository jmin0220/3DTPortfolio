#pragma once
#include <GameEngineCore/GameEngineLevel.h>

enum class StageNum
{
	STAGE1,
	STAGE2,
	STAGE3,
	STAGE4,
};

enum class Stage_MeshEnum
{
	START,	// ���� ����
	axis,
	Character,
	Rainbow,
	TestMap,
	END, // ���� ������
};

struct StageObject
{
	std::string Name_;
	std::string Dir_;
	std::weak_ptr<GameEngineActor> Actor_;
};

// ���� :
class StageParentLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	StageParentLevel();
	~StageParentLevel();

	// delete Function
	StageParentLevel(const StageParentLevel& _Other) = delete;
	StageParentLevel(StageParentLevel&& _Other) noexcept = delete;
	StageParentLevel& operator=(const StageParentLevel& _Other) = delete;
	StageParentLevel& operator=(StageParentLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;

	StageNum MyStage_;

private:
	std::vector<StageObject> StageObjects_;
	void LevelStartLoad();
};

