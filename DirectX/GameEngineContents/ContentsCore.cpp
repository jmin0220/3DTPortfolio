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
	// TODO::�ӽ÷�������
	CreateLevel<tmpLevel>("tmpLevel");
	ChangeLevel("tmpLevel");
}

void ContentsCore::Update(float _DeltaTime)
{
}

void ContentsCore::End()
{
}