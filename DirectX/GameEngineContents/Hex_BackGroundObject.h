#pragma once

// Ό³Έν :
class Hex_BackGroundObject	:	public GameEngineActor
{
public:
	// constrcuter destructer
	Hex_BackGroundObject();
	~Hex_BackGroundObject();

	// delete Function
	Hex_BackGroundObject(const Hex_BackGroundObject& _Other) = delete;
	Hex_BackGroundObject(Hex_BackGroundObject&& _Other) noexcept = delete;
	Hex_BackGroundObject& operator=(const Hex_BackGroundObject& _Other) = delete;
	Hex_BackGroundObject& operator=(Hex_BackGroundObject&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:
	std::shared_ptr<GameEngineFBXStaticRenderer> Renderer_;
	std::shared_ptr<GameEngineFBXStaticRenderer> Renderer2_;
};

