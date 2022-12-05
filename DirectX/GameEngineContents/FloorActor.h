#pragma once
#include <GameEngineCore/GameEngineActor.h>
// ���� : �κ� ���̰� ������ �ٴ�
class GameEngineFBXStaticRenderer;
class FloorActor : public GameEngineActor
{
public:
	// constrcuter destructer
	FloorActor();
	~FloorActor();

	// delete Function
	FloorActor(const FloorActor& _Other) = delete;
	FloorActor(FloorActor&& _Other) noexcept = delete;
	FloorActor& operator=(const FloorActor& _Other) = delete;
	FloorActor& operator=(FloorActor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

	void LevelStartEvent() override;

private:
	std::shared_ptr<GameEngineFBXStaticRenderer> FBXRenderer_;
};

