#pragma once

// 설명 : PhysX 모듈에서 공통으로 사용할 함수들
class PlayerActor;
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

	//정지마찰계수설정
	inline void SetStaticFriction(float _staticfriction)
	{
		staticfriction_ = _staticfriction;
	}
	//운동마찰계수설정
	inline void SetDynamicFriction(float _dynamicfriction)
	{
		dynamicfriction_ = _dynamicfriction;
	}
	//반발계수설정
	inline void SetRestitution(float _resitution)
	{
		resitution_ = _resitution;
	}
	//순서대로 정지마찰계수설정, 운동마찰계수설정, 반발계수설정을 넣기
	inline void SetPhysxMaterial(float _staticfriction, float _dynamicfriction, float _resitution)
	{
		staticfriction_ = _staticfriction;
		dynamicfriction_ = _dynamicfriction;
		resitution_ = _resitution;
	}

	//피벗설정
	inline void SetDynamicPivot(float4 _Pivot)
	{
		DynamicPivot_ = _Pivot;
	}

	//오브젝트의 필터데이터를 넣기위한 boo값을 설정하는 함수
	inline void SetObjectObstacle()
	{
		IsObstacle_ = true;
	}
	
	//오브젝트의 필터데이터를 넣기위한 boo값을 설정하는 함수
	inline void SetObjectGround()
	{
		IsGround_ = true;
	}

	//쿼터니언 관련 함수
	float4 GetQuaternionEulerAngles(float4 rot);
	float4 GetQuaternionEulerAngles(physx::PxQuat rot);
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

	float4 DynamicPivot_ = {0.0f, 0.0f, 0.0f};
	PlayerActor* CommonPlayer_;
	bool IsObstacle_;
	bool IsGround_;
private:
};

