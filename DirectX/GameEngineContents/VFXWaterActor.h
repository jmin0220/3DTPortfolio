#pragma once

struct PatternSmpData
{
	float4 SmpInfo_;     // float2 SmpStartPos; float2 SmpScale;
};

// ???? :
class VFXWaterActor : public GameEngineActor
{
public:
	// constrcuter destructer
	VFXWaterActor();
	~VFXWaterActor();

	// delete Function
	VFXWaterActor(const VFXWaterActor& _Other) = delete;
	VFXWaterActor(VFXWaterActor&& _Other) noexcept = delete;
	VFXWaterActor& operator=(const VFXWaterActor& _Other) = delete;
	VFXWaterActor& operator=(VFXWaterActor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineFBXStaticRenderer> Renderer_;
	PatternSmpData SmpData_;
};

