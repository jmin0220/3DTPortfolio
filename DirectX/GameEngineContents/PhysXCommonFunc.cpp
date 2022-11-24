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
