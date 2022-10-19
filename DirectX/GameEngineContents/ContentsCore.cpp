#include "PreCompile.h"
#include "ContentsCore.h"
#include "tmpLevel.h"

#pragma comment(lib, "GameEngineBase.lib")

ContentsCore::ContentsCore() 
	: GameEngineCore()
{
}

ContentsCore::~ContentsCore() 
{
}

void ContentsCore::Start()
{
	// TODO::임시레벨생성
	CreateLevel<tmpLevel>("tmpLevel");
	ChangeLevel("tmpLevel");
}

void ContentsCore::Update(float _DeltaTime)
{
}

void ContentsCore::End()
{
}