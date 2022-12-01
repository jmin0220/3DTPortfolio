#pragma once

// Ό³Έν :
class JumboTron	:public GameEngineActor
{
public:
	// constrcuter destructer
	JumboTron();
	~JumboTron();

	// delete Function
	JumboTron(const JumboTron& _Other) = delete;
	JumboTron(JumboTron&& _Other) noexcept = delete;
	JumboTron& operator=(const JumboTron& _Other) = delete;
	JumboTron& operator=(JumboTron&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:
	std::shared_ptr<GameEngineFBXStaticRenderer> Renderer_;


public:
	void SetMesh(std::string _Name)
	{
		Renderer_->SetFBXMesh(_Name, "Texture");
	}
};

