#include "PreCompile.h"
#include "LoadingLevel.h"
#include "LoadingActor.h"

LoadingLevel::LoadingLevel() 
{
}

LoadingLevel::~LoadingLevel() 
{
}

void LoadingLevel::Start()
{
	
}

void LoadingLevel::Update(float _DeltaTime)
{
}

void LoadingLevel::LevelStartEvent()
{
	// ���� ����
	Loadings = CreateActor<LoadingActor>();
}

void LoadingLevel::LevelEndEvent()
{
	// ���� ����
	Loadings->Death();
}
