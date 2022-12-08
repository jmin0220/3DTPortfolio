#pragma once
#include <GameEngineCore/GameEngineActor.h>
// Ό³Έν :
class WinnerBG : public GameEngineActor
{
public:
	// constrcuter destructer
	WinnerBG();
	~WinnerBG();

	// delete Function
	WinnerBG(const WinnerBG& _Other) = delete;
	WinnerBG(WinnerBG&& _Other) noexcept = delete;
	WinnerBG& operator=(const WinnerBG& _Other) = delete;
	WinnerBG& operator=(WinnerBG&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

	void LevelStartEvent() override;
	void LevelEndEvent() override;
private:
	std::shared_ptr<GameEngineFBXStaticRenderer> Mesh_;
};

