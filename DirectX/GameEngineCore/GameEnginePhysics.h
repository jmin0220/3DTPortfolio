#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include "GameEngineUpdateObject.h"
#include <list>
#include "GameEngineTransformBase.h"


// ���� : ���� ������ ������ ����ϴ� Ŭ���� (�ݵ�� ���Ͱ� ��ӹ޾ƾ� ��)
class GameEnginePhysics 
{

public:
	// constrcuter destructer
	GameEnginePhysics();
	virtual ~GameEnginePhysics();

	// delete Function
	GameEnginePhysics(const GameEnginePhysics& _Other) = delete;
	GameEnginePhysics(GameEnginePhysics&& _Other) noexcept = delete;
	GameEnginePhysics& operator=(const GameEnginePhysics& _Other) = delete;
	GameEnginePhysics& operator=(GameEnginePhysics&& _Other) noexcept = delete;

};

