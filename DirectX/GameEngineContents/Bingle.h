#pragma once
#include <GameEngineCore/GameEngineActor.h>
// 설명 : 로딩중 빙글빙글 도는 이미지
class GameEngineUIRenderer;
class Bingle : public GameEngineActor
{
public:
	// constrcuter destructer
	Bingle();
	~Bingle();

	// delete Function
	Bingle(const Bingle& _Other) = delete;
	Bingle(Bingle&& _Other) noexcept = delete;
	Bingle& operator=(const Bingle& _Other) = delete;
	Bingle& operator=(Bingle&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

	void LevelStartEvent() override;
private:
	std::shared_ptr<GameEngineUIRenderer> Loading_;
	std::shared_ptr<GameEngineUIRenderer> Face_;

	float BingleTime_;
};

