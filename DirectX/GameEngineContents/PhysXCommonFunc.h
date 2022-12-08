#pragma once

// 설명 : PhysX 모듈에서 공통으로 사용할 함수들
class PhysXCommonFunc
{
	typedef struct {
		float x, y, z;
	} vector;

	typedef struct {
		vector i, j, k;
	} matrix;

public:
	// constrcuter destructer
	PhysXCommonFunc();
	~PhysXCommonFunc();

	// delete Function
	PhysXCommonFunc(const PhysXCommonFunc& _Other) = delete;
	PhysXCommonFunc(PhysXCommonFunc&& _Other) noexcept = delete;
	PhysXCommonFunc& operator=(const PhysXCommonFunc& _Other) = delete;
	PhysXCommonFunc& operator=(PhysXCommonFunc&& _Other) noexcept = delete;

	// 필터링 셋팅
	void SetupFiltering(physx::PxShape* _Shape, physx::PxU32 _FilterGroup, physx::PxU32 _FilterMask);
	float4 ToEulerAngles(const physx::PxQuat& q);

	inline void SetStaticFriction(float _staticfriction)
	{
		staticfriction_ = _staticfriction;
	}

	inline void SetDynamicFriction(float _dynamicfriction)
	{
		dynamicfriction_ = _dynamicfriction;
	}

	inline void RestitutionFriction(float _resitution)
	{
		resitution_ = _resitution;
	}

	//쿼터니언 관련 함수
	float4 GetQuaternionEulerAngles(float4 rot);
	float4 NormalizeAngles(float4 angles);
	float NormalizeAngle(float angle);
	
	//로드리게스 회전 관련 함수
	float4 RodriguesRotate(vector p, vector v, float a);
	double dotProduct(vector v1, vector v2);
	vector matrixMultiply(matrix m, vector v);

protected:
	float staticfriction_ = 0.0f;
	float dynamicfriction_ = 0.0f;
	float resitution_ = 0.0f;
private:

};

