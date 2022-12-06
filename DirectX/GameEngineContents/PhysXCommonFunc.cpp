#include "PreCompile.h"
#include "PhysXCommonFunc.h"
#include <math.h>

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

float4 PhysXCommonFunc::GetQuaternionEulerAngles(float4 rot)
{
    float4 q1 = rot;
    float sqw = q1.w * q1.w;
    float sqx = q1.x * q1.x;
    float sqy = q1.y * q1.y;
    float sqz = q1.z * q1.z;
    float unit = sqx + sqy + sqz + sqw; // if normalised is one, otherwise is correction factor
    float test = q1.x * q1.w - q1.y * q1.z;
    float4 v;

    if (test > 0.4995f * unit)
    { // singularity at north pole
        v.y = 2.0f * std::atan2(q1.y, q1.x);
        v.x = GameEngineMath::PI / 2.0f;
        v.z = 0;
        return NormalizeAngles(v);
    }
    if (test < -0.4995f * unit)
    { // singularity at south pole
        v.y = -2.0f * std::atan2(q1.y, q1.x);
        v.x = -GameEngineMath::PI / 2;
        v.z = 0;
        return NormalizeAngles(v);
    }

    rot = float4(q1.w, q1.z, q1.x, q1.y);
    v.y = std::atan2(2.0f * rot.x * rot.w + 2.0f * rot.y * rot.z, 1 - 2.0f * (rot.z * rot.z + rot.w * rot.w));     // Yaw
    v.x = std::asin(2.0f * (rot.x * rot.z - rot.w * rot.y));                             // Pitch
    v.z = std::atan2(2.0f * rot.x * rot.y + 2.0f * rot.z * rot.w, 1 - 2.0f * (rot.y * rot.y + rot.z * rot.z));      // Roll
    return NormalizeAngles(v);
}

float4 PhysXCommonFunc::NormalizeAngles(float4 angles)
{
    angles.x = NormalizeAngle(angles.x);
    angles.y = NormalizeAngle(angles.y);
    angles.z = NormalizeAngle(angles.z);
    return angles;
}

float PhysXCommonFunc::NormalizeAngle(float angle)
{
    while (angle > GameEngineMath::PI * 2.0f)
        angle -= GameEngineMath::PI * 2.0f;
    while (angle < 0)
        angle += GameEngineMath::PI * 2.0f;
    return angle;
}