#include "PreCompile.h"
#include "PhysXCommonFunc.h"

PhysXCommonFunc::PhysXCommonFunc() 
{
}

PhysXCommonFunc::~PhysXCommonFunc() 
{
}

void PhysXCommonFunc::SetupFiltering(physx::PxShape* _Shape, physx::PxU32 _FilterGroup, physx::PxU32 _FilterMask)
{
	physx::PxFilterData filterData;
	filterData.word0 = _FilterGroup; // word0 = own ID
	filterData.word1 = _FilterMask;	// word1 = ID mask to filter pairs that trigger a contact callback;

	_Shape->setSimulationFilterData(filterData);
}

float4 PhysXCommonFunc::ToEulerAngles(const physx::PxQuat& q) {
	float4 angles;    //yaw pitch roll
	const float x = q.x;
	const float y = q.y;
	const float z = q.z;
	const float w = q.w;

	// roll (y-axis rotation)
	double sinr_cosp = 2 * (w * x + y * z);
	double cosr_cosp = 1 - 2 * (x * x + y * y);
	angles.x = std::atan2(sinr_cosp, cosr_cosp);

	// pitch (x-axis rotation)
	double sinp = 2 * (w * y - z * x);
	if (std::abs(sinp) >= 1)
	{
		angles.y = std::copysign(GameEngineMath::PI / 2, sinp); // use 90 degrees if out of range
	}

	else
	{
		angles.y = std::asin(sinp);
	}

	// yaw (z-axis rotation)
	double siny_cosp = 2 * (w * z + x * y);
	double cosy_cosp = 1 - 2 * (y * y + z * z);
	angles.z = std::atan2(siny_cosp, cosy_cosp);
	return angles;
}
