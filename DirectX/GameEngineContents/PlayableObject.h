#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <list>
#include <vector>
#include "PhysicsBase.h"


// 설명 : 게임 엔진의 물리를 담당하는 클래스
class PlayableObject
{

public:
	// constrcuter destructer
	PlayableObject();
	virtual ~PlayableObject();

	// delete Function
	PlayableObject(const PlayableObject& _Other) = delete;
	PlayableObject(PlayableObject&& _Other) noexcept = delete;
	PlayableObject& operator=(const PlayableObject& _Other) = delete;
	PlayableObject& operator=(PlayableObject&& _Other) noexcept = delete;




protected:
	bool IsMoveRightOn;
	bool IsMoveLeftOn;
	bool IsMoveForwardOn;
	bool IsMoveBackwardOn;
	
	float4 MovementAccx; //움직일때의 x가속도
	float4 MovementAccz; //움직일때의 z가속도
	float4 MovementVelocity;//움직일때의 속도
	float MaxSpeed; // 움직이는 최대 속도


public:
	void InputUpdate();
	float4 CalculateMoveVel(float _DeltaTime, float InclineRate = 1.0f);
};

