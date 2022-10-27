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

	GameEngineTextureRenderer* GetMouse()
	{
		return MouseImage;
	}

	float4 GetCursorPos1()
	{
		return MainCursorPos;
	}

	float4 GetCursorPos2()
	{
		return UICursorPos;
	}

	bool MainHit(GameEngineCollision* _This, GameEngineCollision* _Other);
	bool UIHit(GameEngineCollision* _This, GameEngineCollision* _Other);

protected:

private:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

	GameEngineTextureRenderer* MouseImage;
	GameEngineCameraActor* Camera;
	float4 MainCursorPos;
	float4 UICursorPos;
	GameEngineCollision* ActorCollision;
	GameEngineCollision* UICollision;
};

