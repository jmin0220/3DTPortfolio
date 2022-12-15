#pragma once
#include <GameEngineCore/CoreMinimal.h>

// Ό³Έν :
class BigShots_Puff : public GameEngineActor
{
public:
	// constrcuter destructer
	BigShots_Puff();
	~BigShots_Puff();

	// delete Function
	BigShots_Puff(const BigShots_Puff& _Other) = delete;
	BigShots_Puff(BigShots_Puff&& _Other) noexcept = delete;
	BigShots_Puff& operator=(const BigShots_Puff& _Other) = delete;
	BigShots_Puff& operator=(BigShots_Puff&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);

private:
	std::shared_ptr<GameEngineTextureRenderer> PuffRenderer_;
	bool IsTransTexture_;
	float SumTime_;
	float SumValue_;
};

