#pragma once

// ���� : PhysX ��⿡�� �������� ����� �Լ���
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

	// ���͸� ����
	void SetupFiltering(physx::PxShape* _Shape, physx::PxU32 _FilterGroup, physx::PxU32 _FilterMask);
	float4 ToEulerAngles(const physx::PxQuat& q);

	//���������������
	inline void SetStaticFriction(float _staticfriction)
	{
		staticfriction_ = _staticfriction;
	}
	//������������
	inline void SetDynamicFriction(float _dynamicfriction)
	{
		dynamicfriction_ = _dynamicfriction;
	}
	//�ݹ߰������
	inline void SetRestitution(float _resitution)
	{
		resitution_ = _resitution;
	}
	//������� ���������������, ������������, �ݹ߰�������� �ֱ�
	inline void SetPhysxMaterial(float _staticfriction, float _dynamicfriction, float _resitution)
	{
		staticfriction_ = _staticfriction;
		dynamicfriction_ = _dynamicfriction;
		resitution_ = _resitution;
	}

	//�ǹ�����
	inline void SetDynamicPivot(float4 _Pivot)
	{
		DynamicPivot_ = _Pivot;
	}

	//������Ʈ�� ���͵����͸� �ֱ����� boo���� �����ϴ� �Լ�
	inline void SetObjectObstacle()
	{
		IsObstacle_ = true;
	}
	
	//������Ʈ�� ���͵����͸� �ֱ����� boo���� �����ϴ� �Լ�
	inline void SetObjectGround()
	{
		IsGround_ = true;
	}

	//���ʹϾ� ���� �Լ�
	float4 GetQuaternionEulerAngles(float4 rot);
	float4 GetQuaternionEulerAngles(physx::PxQuat rot);
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

	float4 DynamicPivot_ = {0.0f, 0.0f, 0.0f};
	PlayerActor* CommonPlayer_;
	bool IsObstacle_;
	bool IsGround_;
private:
};

