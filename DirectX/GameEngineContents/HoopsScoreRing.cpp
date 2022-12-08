#include "PreCompile.h"
#include "HoopsScoreRing.h"
#include "VirtualPhysXLevel.h"

HoopsScoreRing::HoopsScoreRing()
{
}

HoopsScoreRing::~HoopsScoreRing()
{
}

void HoopsScoreRing::Start()
{
	Renderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
}

void HoopsScoreRing::Update(float _DeltaTime)
{
}

void HoopsScoreRing::LevelStartEvent()
{
}

void HoopsScoreRing::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics)
{
}
