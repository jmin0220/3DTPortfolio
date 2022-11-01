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
	Loadings = CreateActor<LoadingActor>();
}

void LoadingLevel::Update(float _DeltaTime)
{
}

void LoadingLevel::LevelStartEvent()
{
}

void LoadingLevel::LevelEndEvent()
{
}
