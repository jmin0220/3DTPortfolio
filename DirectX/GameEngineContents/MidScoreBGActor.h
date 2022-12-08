#pragma once
#include <GameEngineCore/GameEngineActor.h>
// Ό³Έν :
class MidScoreBGActor : public GameEngineActor
{
public:
	// constrcuter destructer
	MidScoreBGActor();
	~MidScoreBGActor();

	// delete Function
	MidScoreBGActor(const MidScoreBGActor& _Other) = delete;
	MidScoreBGActor(MidScoreBGActor&& _Other) noexcept = delete;
	MidScoreBGActor& operator=(const MidScoreBGActor& _Other) = delete;
	MidScoreBGActor& operator=(MidScoreBGActor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

	void LevelStartEvent() override;
private:
	std::shared_ptr<GameEngineTextureRenderer> BG_;
	std::shared_ptr<GameEngineTextureRenderer> Pattern_;

	float4 SlicePos_;
};

