#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include "GameEngineUpdateObject.h"
#include <list>
#include "GameEngineTransformBase.h"


// 설명 : 게임 엔진의 물리를 담당하는 클래스 (반드시 액터가 상속받아야 함)
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

