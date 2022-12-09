#pragma once

struct LightTestData
{
	float4 DiffuseColor;
	float4 LightDirection;
};

struct DiffuseData
{
	float4 BodyTextureColor;
};

// ¼³¸í :
class TestCharacterAnimation	:	public GameEngineActor
{
public:
	// constrcuter destructer
	TestCharacterAnimation();
	~TestCharacterAnimation();

	// delete Function
	TestCharacterAnimation(const TestCharacterAnimation& _Other) = delete;
	TestCharacterAnimation(TestCharacterAnimation&& _Other) noexcept = delete;
	TestCharacterAnimation& operator=(const TestCharacterAnimation& _Other) = delete;
	TestCharacterAnimation& operator=(TestCharacterAnimation&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:
	std::shared_ptr<GameEngineFBXAnimationRenderer> Renderer;


	// ³ë¸»¸Ê + ºû
	LightTestData LightData_;
	DiffuseData DiffuseData_;
};

