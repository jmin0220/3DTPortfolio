#pragma once
#include "HUDUIActor.h"

// 설명 : 이름 판
class GameEngineUIRenderer;
class FontActor;
class NamePlate : public HUDUIActor
{
public:
	// constrcuter destructer
	NamePlate();
	~NamePlate();

	// delete Function
	NamePlate(const NamePlate& _Other) = delete;
	NamePlate(NamePlate&& _Other) noexcept = delete;
	NamePlate& operator=(const NamePlate& _Other) = delete;
	NamePlate& operator=(NamePlate&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};
private:
	std::shared_ptr<GameEngineUIRenderer> Renderer_;
	std::shared_ptr<GameEngineFontRenderer> Font_;
};

