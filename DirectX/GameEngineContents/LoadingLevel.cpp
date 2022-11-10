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
	// ¿¢ÅÍ »ý¼º
	Loadings = CreateActor<LoadingActor>();
}

void LoadingLevel::LevelEndEvent()
{
	// ¿¢ÅÍ Á¦°Å
	Loadings->Death();
}
