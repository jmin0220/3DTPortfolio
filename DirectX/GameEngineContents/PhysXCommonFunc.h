#pragma once

// ���� : PhysX ��⿡�� �������� ����� �Լ���
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

	// ���͸� ����
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

	//���ʹϾ� ���� �Լ�
	float4 GetQuaternionEulerAngles(float4 rot);
	float4 NormalizeAngles(float4 angles);
	float NormalizeAngle(float angle);
	
	//�ε帮�Խ� ȸ�� ���� �Լ�
	float4 RodriguesRotate(vector p, vector v, float a);
	double dotProduct(vector v1, vector v2);
	vector matrixMultiply(matrix m, vector v);

protected:
	float staticfriction_ = 0.0f;
	float dynamicfriction_ = 0.0f;
	float resitution_ = 0.0f;
private:

};

