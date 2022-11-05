#include "PreCompile.h"
#include "SampleCCTJump.h"

static physx::PxF32 gJumpGravity = -50.0f;

SampleCCTJump::SampleCCTJump() 
{
}

SampleCCTJump::~SampleCCTJump() 
{
}

SampleCCTJump::Jump::Jump() :
	mV0(0.0f),
	mJumpTime(0.0f),
	mJump(false)
{
}

void SampleCCTJump::Jump::startJump(physx::PxF32 v0)
{
	if (mJump)	return;
	mJumpTime = 0.0f;
	mV0 = v0;
	mJump = true;
}

void SampleCCTJump::Jump::stopJump()
{
	if (!mJump)	return;
	mJump = false;
	//mJumpTime = 0.0f;
	//mV0	= 0.0f;
}

physx::PxF32 SampleCCTJump::Jump::getHeight(physx::PxF32 elapsedTime)
{
	if (!mJump)	return 0.0f;
	mJumpTime += elapsedTime;
	const physx::PxF32 h = gJumpGravity * mJumpTime * mJumpTime + mV0 * mJumpTime;
	return h * elapsedTime;
}
