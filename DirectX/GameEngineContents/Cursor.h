#pragma once
#include <GameEngineCore/CoreMinimal.h>

// 설명 : 마우스
class GameEngineTextureRenderer;
class Cursor : public GameEngineActor
{
public:
	// constrcuter destructer
	Cursor();
	~Cursor();

	// delete Function
	Cursor(const Cursor& _Other) = delete;
	Cursor(Cursor&& _Other) noexcept = delete;
	Cursor& operator=(const Cursor& _Other) = delete;
	Cursor& operator=(Cursor&& _Other) noexcept = delete;

	std::shared_ptr<GameEngineTextureRenderer> GetMouse()
	{
		return MouseImage_;
	}

	float4 GetCursorPos1()
	{
		return MainCursorPos_;
	}

	float4 GetCursorPos2()
	{
		return UICursorPos_;
	}

	bool MainHit(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);
	bool UIHit(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);

protected:

private:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

	std::shared_ptr<GameEngineTextureRenderer> MouseImage_;
	GameEngineCameraActor* Camera_;
	float4 MainCursorPos_;
	float4 UICursorPos_;
	std::shared_ptr<GameEngineCollision> ActorCollision_;
	std::shared_ptr<GameEngineCollision> UICollision_;
};

