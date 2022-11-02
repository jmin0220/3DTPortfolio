#pragma once
#include <GameEngineCore/CoreMinimal.h>

// ���� : ���콺
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

	GameEngineTextureRenderer* GetMouse()
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

	bool MainHit(GameEngineCollision* _This, GameEngineCollision* _Other);
	bool UIHit(GameEngineCollision* _This, GameEngineCollision* _Other);

protected:

private:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

	GameEngineTextureRenderer* MouseImage_;
	GameEngineCameraActor* Camera_;
	float4 MainCursorPos_;
	float4 UICursorPos_;
	GameEngineCollision* ActorCollision_;
	GameEngineCollision* UICollision_;
};

