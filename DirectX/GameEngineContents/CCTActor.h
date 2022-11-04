#pragma once
#include <PhysX/characterkinematic/PxExtended.h>
#include <PhysX/characterkinematic/PxController.h>

// Ό³Έν :
class CCTActor
{
public:
	// constrcuter destructer
	CCTActor();
	~CCTActor();

	// delete Function
	CCTActor(const CCTActor& _Other) = delete;
	CCTActor(CCTActor&& _Other) noexcept = delete;
	CCTActor& operator=(const CCTActor& _Other) = delete;
	CCTActor& operator=(CCTActor&& _Other) noexcept = delete;

protected:

private:

};

