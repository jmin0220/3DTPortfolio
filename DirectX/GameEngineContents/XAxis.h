#pragma once

// ���� :
// ������ Pick�� �Ǵ� X
class XAxis	: public GameEngineActor
{
public:
	// constrcuter destructer
	XAxis();
	~XAxis();

	// delete Function
	XAxis(const XAxis& _Other) = delete;
	XAxis(XAxis&& _Other) noexcept = delete;
	XAxis& operator=(const XAxis& _Other) = delete;
	XAxis& operator=(XAxis&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:
	std::shared_ptr<GameEngineCollision> Collision;
public:
	std::shared_ptr<GameEngineCollision> GetCollision()
	{
		return Collision;
	}
};

