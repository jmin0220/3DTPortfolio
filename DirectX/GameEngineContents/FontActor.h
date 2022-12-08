#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� : ��Ʈ ��¿� ����(�������� ��Ʈ������ �׳� �������� �ȵ�)
class GameEngineFontRenderer;
class FontActor : public GameEngineActor
{
public:
	// constrcuter destructer
	FontActor();
	~FontActor();

	// delete Function
	FontActor(const FontActor& _Other) = delete;
	FontActor(FontActor&& _Other) noexcept = delete;
	FontActor& operator=(const FontActor& _Other) = delete;
	FontActor& operator=(FontActor&& _Other) noexcept = delete;

	std::weak_ptr<GameEngineFontRenderer> GetFont()
	{
		return Font_;
	}

	void SetFont(std::string _Text, std::string _Font, float _Size, float4 _Pos , LeftAndRightSort _Value)
	{
		Font_->SetText(_Text, _Font);
		Font_->SetSize(_Size);
		Font_->SetScreenPostion(_Pos);
		Font_->SetLeftAndRightSort(_Value);
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};
private:
	std::shared_ptr<GameEngineFontRenderer> Font_;
};

