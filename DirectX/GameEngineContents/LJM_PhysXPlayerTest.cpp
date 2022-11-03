#include "PreCompile.h"
#include "LJM_PhysXPlayerTest.h"
#include "PhysXTestPlayer.h"

LJM_PhysXPlayerTest::LJM_PhysXPlayerTest() 
{
}

LJM_PhysXPlayerTest::~LJM_PhysXPlayerTest() 
{
}

void LJM_PhysXPlayerTest::Start()
{
	Player_ = CreateActor<PhysXTestPlayer>();
}

void LJM_PhysXPlayerTest::Update(float _DeltaTime)
{
}

void LJM_PhysXPlayerTest::End()
{
}