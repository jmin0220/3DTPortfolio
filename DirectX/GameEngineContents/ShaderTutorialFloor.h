#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class ShaderTutorialFloor : public GameEngineActor
{
public:
	// constrcuter destructer
	ShaderTutorialFloor();
	~ShaderTutorialFloor();

	// delete Function
	ShaderTutorialFloor(const ShaderTutorialFloor& _Other) = delete;
	ShaderTutorialFloor(ShaderTutorialFloor&& _Other) noexcept = delete;
	ShaderTutorialFloor& operator=(const ShaderTutorialFloor& _Other) = delete;
	ShaderTutorialFloor& operator=(ShaderTutorialFloor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:

	std::shared_ptr<GameEngineFBXStaticRenderer> PlatformRenderer_;
	std::shared_ptr<GameEngineFBXStaticRenderer> WallRenderer_;

};

