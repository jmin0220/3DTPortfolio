#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 : 폰트 출력용 액터(레벨에다 폰트렌더러 그냥 넣으려니 안됨)
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

	GameEngineFontRenderer* GetFont()
	{
		return Font_;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};
private:
	GameEngineFontRenderer* Font_;
};

