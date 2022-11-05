#pragma once

#ifndef SAMPLE_CCT_JUMP_H
#define SAMPLE_CCT_JUMP_H

#include <PhysX/common/PxPhysXCommonConfig.h>
// Ό³Έν :
class SampleCCTJump
{
public:
	// constrcuter destructer
	SampleCCTJump();
	~SampleCCTJump();

	// delete Function
	SampleCCTJump(const SampleCCTJump& _Other) = delete;
	SampleCCTJump(SampleCCTJump&& _Other) noexcept = delete;
	SampleCCTJump& operator=(const SampleCCTJump& _Other) = delete;
	SampleCCTJump& operator=(SampleCCTJump&& _Other) noexcept = delete;

	class Jump : public physx::PxDefaultAllocator
	{
	public:
		Jump();

		physx::PxF32		mV0;
		physx::PxF32		mJumpTime;
		bool				mJump;

		void				startJump(physx::PxF32 v0);
		void				stopJump();
		physx::PxF32		getHeight(physx::PxF32 elapsedTime);
	};
};


#endif