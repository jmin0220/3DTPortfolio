#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 : 폰트 출력용 액터(레벨에다 폰트렌더러 그냥 넣으려니 안됨)=레벨에 직접 쓸 폰트용
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

	std::shared_ptr<GameEngineFontRenderer> GetFont()
	{
		return Font_;
	}

	void SetFont(std::string _Text, std::string _Font)
	{
		Font_->SetText(_Text, _Font);
	}

	void SetFont(std::string _Text, std::string _Font, float4 _Pos)
	{
		Font_->SetText(_Text, _Font);
		Font_->SetScreenPostion(_Pos);
	}
	
	void SetFont(std::string _Text, std::string _Font, float _Size, float4 _Pos , LeftAndRightSort _Value)
	{
		Font_->SetText(_Text, _Font);
		Font_->SetSize(_Size);
		Font_->SetScreenPostion(_Pos);
		Font_->SetLeftAndRightSort(_Value);
	}

	void SetFont(std::string _Text, std::string _Font, float _Size, LeftAndRightSort _Value)
	{
		Font_->SetText(_Text, _Font);
		Font_->SetSize(_Size);
		Font_->SetLeftAndRightSort(_Value);
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};
private:
	std::shared_ptr<GameEngineFontRenderer> Font_;
};

