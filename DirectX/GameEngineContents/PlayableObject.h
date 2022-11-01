#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <list>
#include <vector>
#include "PhysicsBase.h"


// ���� : ���� ������ ������ ����ϴ� Ŭ����
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
	
	float4 MovementAccx; //�����϶��� x���ӵ�
	float4 MovementAccz; //�����϶��� z���ӵ�
	float4 MovementVelocity;//�����϶��� �ӵ�
	float MaxSpeed; // �����̴� �ִ� �ӵ�


public:
	void InputUpdate();
	float4 CalculateMoveVel(float _DeltaTime, float InclineRate = 1.0f);
};

