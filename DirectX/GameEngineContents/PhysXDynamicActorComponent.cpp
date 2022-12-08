#include "PreCompile.h"
#include "PhysXDynamicActorComponent.h"


PhysXDynamicActorComponent::PhysXDynamicActorComponent() 
	:IsSpeedLimit_(false)
{
}

PhysXDynamicActorComponent::~PhysXDynamicActorComponent() 
{
}

physx::PxRigidDynamic* PhysXDynamicActorComponent::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics, physx::PxVec3 _GeoMetryScale, float4 _GeoMetryRot)
{
	Scene_ = _Scene;
	physics_ = _physics;

	float4 tmpQuat = _GeoMetryRot.DegreeRotationToQuaternionReturn();

	// �θ� ���ͷκ��� ��ġ ����
	physx::PxTransform localTm(physx::PxVec3(ParentActor_.lock()->GetTransform().GetWorldPosition().x
		, ParentActor_.lock()->GetTransform().GetWorldPosition().y
		, ParentActor_.lock()->GetTransform().GetWorldPosition().z),
		physx::PxQuat(tmpQuat.x, tmpQuat.y, tmpQuat.z, tmpQuat.w));

	// ����, ź�����
	//material_ = _physics->createMaterial(0.0f, 0.0f, 0.0f);

	material_ = _physics->createMaterial(staticfriction_, dynamicfriction_, resitution_);

	// TODO::������ ������ ��� ���� �ڵ带 ���
	//float4 tmpMagnification = { SIZE_MAGNIFICATION_RATIO };
	//physx::PxVec3 tmpGeoMetryScale(_GeoMetryScale.x * tmpMagnification.x * 0.5f, 
	//							   _GeoMetryScale.y * tmpMagnification.y * 0.5f, 
	//							   _GeoMetryScale.z * tmpMagnification.z * 0.5f);

	GeoMetryScale_ = _GeoMetryScale;

	physx::PxVec3 tmpGeoMetryScale(_GeoMetryScale.x * 0.5f,
		_GeoMetryScale.y * 0.5f,
		_GeoMetryScale.z * 0.5f);

	//// �浹ü�� ����
	dynamic_ = _physics->createRigidDynamic(localTm);

	// TODO::�����ӷ¿� ������ ��ħ. �������� �ۼ��� �ڼ��� ��ġ�� ���߿� ����
	// �÷��̾� �ִ� �ӷ�
	// dynamic_->setMaxLinearVelocity(PLAYER_MAX_SPEED);

	dynamic_->setRigidDynamicLockFlags(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_X | physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y |
		physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z);

	float ScaledRadius = _GeoMetryScale.z;
	float ScaledHeight = _GeoMetryScale.y;

	// ���� ĸ�� �ݶ��̴�
	shape_ = physx::PxRigidActorExt::createExclusiveShape(*dynamic_, physx::PxCapsuleGeometry(ScaledRadius * 1.3f, ScaledHeight * 0.9f), *material_);
	float CapsuleHeight = (ScaledHeight * 0.9f);
	physx::PxVec3 DynamicCenter(0.0f, CapsuleHeight, 0.0f );

	shape_->setSimulationFilterData(physx::PxFilterData(static_cast<physx::PxU32>(PhysXFilterGroup::Player)
		, static_cast<physx::PxU32>(PhysXFilterGroup::Ground), 0, 0));
	//�ǹ�����
	physx::PxTransform relativePose(physx::PxQuat(physx::PxHalfPi, physx::PxVec3(0, 0, 1)));
	relativePose.p = DynamicCenter;
	//physx::PxTransform relativePose(physx::PxQuat(physx::PxHalfPi, physx::PxVec3(0, 0, 1)));
	shape_->setLocalPose(relativePose);

	physx::PxRigidBodyExt::updateMassAndInertia(*dynamic_, 0.01f);
	
	physx::PxShape* Instshape_;
	Instshape_ = physx::PxRigidActorExt::createExclusiveShape(*dynamic_, physx::PxCapsuleGeometry(ScaledRadius * 1.3f, ScaledHeight * 0.9f), *material_);
	// �浹���� �ݹ��� ���� ����
	Instshape_->setSimulationFilterData(physx::PxFilterData(static_cast<physx::PxU32>(PhysXFilterGroup::Player)
		, static_cast<physx::PxU32>(PhysXFilterGroup::Ground), 0, 0));
	Instshape_->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, false);
	Instshape_->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, true);

	//�ݹ��ǹ����� 
	Instshape_->setLocalPose(relativePose);
	// 
	physx::PxTransform LocalPose = dynamic_->getCMassLocalPose();

	// ����?
	dynamic_->setLinearDamping(physx::PxReal(0.5f));
	dynamic_->setAngularDamping(physx::PxReal(0.5f));

	// Scene�� ���� �߰�
	_Scene->addActor(*dynamic_);
	
	// TODO::virtualPhysXLevel���� Callback �Լ��� ȣ���ϱ� ���� Dynamic ����
	return dynamic_;
}

void PhysXDynamicActorComponent::SetMoveSpeed(float4 _MoveSpeed)
{
	// RigidDynamic�� ���� �����ϴ� Flag -> ĳ���Ͱ� �������� �ʰ� ������ �� �ֵ���
	// ���𰡿� �浹�ؼ� �������� �Ұ�쿡�� setRigidDynamicLockFlag({flag}, false)�� flag�� �����ؾ���.
	dynamic_->setRigidDynamicLockFlags(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_X | physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y |physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z);

	// ĳ������ ������ ������ ����
	dynamic_->addForce(physx::PxVec3(_MoveSpeed.x, _MoveSpeed.y, _MoveSpeed.z), physx::PxForceMode::eFORCE);
}

void PhysXDynamicActorComponent::SetMoveJump()
{
	dynamic_->addForce(physx::PxVec3(0.0f, PLAYER_JUMP_FORCE, 0.0f), physx::PxForceMode::eIMPULSE);
}

void PhysXDynamicActorComponent::SetDynamicIdle()
{
	// ������ ���� ����
	dynamic_->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_X, false);
	dynamic_->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y, false);
	dynamic_->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z, false);
	


	// Kinematic�� ������� ���, RigidDynamic���� ���ư� �� �ֵ��� Flag����
	//dynamic_->setRigidBodyFlag(physx::PxRigidBodyFlag::eKINEMATIC, false);
}

void PhysXDynamicActorComponent::Start()
{
	// �θ��� ������ ����
	ParentActor_ = std::dynamic_pointer_cast<GameEngineActor>(GetParent());
}

void PhysXDynamicActorComponent::Update(float _DeltaTime)
{
	// PhysX Actor�� ���¿� ���缭 �θ��� Transform������ ����
	float4 tmpWorldPos = { dynamic_->getGlobalPose().p.x
	,dynamic_->getGlobalPose().p.y
	, dynamic_->getGlobalPose().p.z };

	//float4 QuatRot = float4{ dynamic_->getGlobalPose().q.x, dynamic_->getGlobalPose().q.y, dynamic_->getGlobalPose().q.z, dynamic_->getGlobalPose().q.w };
	float4 EulerRot = PhysXCommonFunc::GetQuaternionEulerAngles(dynamic_->getGlobalPose().q) * GameEngineMath::RadianToDegree;

	ParentActor_.lock()->GetTransform().SetWorldRotation(float4{ EulerRot.x, EulerRot.y, EulerRot.z });

	ParentActor_.lock()->GetTransform().SetWorldPosition(tmpWorldPos);

	if (IsSpeedLimit_ == true)
	{
		SpeedLimit();
	}
}



void PhysXDynamicActorComponent::PushImpulse(float4 _ImpulsePower)
{
	// ������ ���� ����
	dynamic_->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_X, false);
	dynamic_->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y, false);
	dynamic_->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z, false);

	dynamic_->addForce(physx::PxVec3(_ImpulsePower.x, _ImpulsePower.y, _ImpulsePower.z), physx::PxForceMode::eIMPULSE);
}

void PhysXDynamicActorComponent::PushImpulseAtLocalPos(float4 _ImpulsePower, float4 _Pos)
{
	// ������ ���� ����
	dynamic_->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_X, false);
	dynamic_->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z, false);

	physx::PxRigidBodyExt::addForceAtPos(*dynamic_, physx::PxVec3(_Pos.x, _Pos.y * 0.9f, _Pos.z),
		physx::PxVec3(_ImpulsePower.x, _ImpulsePower.y, _ImpulsePower.z), physx::PxForceMode::eIMPULSE, true);
}

void PhysXDynamicActorComponent::SetPlayerStartPos(float4 _Pos)
{
	physx::PxTransform tmpPxTransform(_Pos.x, _Pos.y, _Pos.z);

	// �θ��� Transform������ �������� PhysX Actor�� Ʈ�������� ����
	dynamic_->setGlobalPose(tmpPxTransform);
}

bool PhysXDynamicActorComponent::PlayerStandUp(float _DeltaTime)
{

	float Angle;
	physx::PxVec3 Vec3;
	dynamic_->getGlobalPose().q.toRadiansAndUnitAxis(Angle, Vec3);
	float4 YAxis(0.0f, 1.0f, 0.0f);
	physx::PxVec3 YAxisVec3(0.0f, 1.0f, 0.0f);

	float AngDiff = acosf(float4::DotProduct3D({ Vec3.x, Vec3.y, Vec3.z }, YAxis));
	//float4::VectorRotationToDegreeYAxis(float4Vec3, );

	physx::PxVec3 Normal = Vec3.cross(YAxisVec3);
	float4 FinalRot = RodriguesRotate({ Vec3.x, Vec3.y, Vec3.z }, { Normal.x, Normal.y, Normal.z }, AngDiff);
	float4 FinalPos = RodriguesRotate({ dynamic_->getGlobalPose().p.x, dynamic_->getGlobalPose().p.y, dynamic_->getGlobalPose().p.z }, 
		{ Normal.x, Normal.y, Normal.z }, AngDiff);
	physx::PxVec3 FinalPosVec3 = physx::PxVec3(FinalPos.x, FinalPos.y, FinalPos.z);
	float4 tmpQuat = FinalRot.DegreeRotationToQuaternionReturn();
	const physx::PxQuat tmpPxQuat(tmpQuat.x, tmpQuat.y, tmpQuat.z, tmpQuat.w);
	const physx::PxTransform tmpTransform(dynamic_->getGlobalPose().p, tmpPxQuat);
	dynamic_->setGlobalPose(tmpTransform);
	return true;
}

void PhysXDynamicActorComponent::SpeedLimit()
{
	physx::PxVec3 Velo = dynamic_->getLinearVelocity();
	physx::PxVec2 Velo2D(Velo.x, Velo.z);

	if (Velo2D.magnitude() > PLAYER_MAX_SPEED)
	{
		Velo2D.normalize();
		Velo2D *= PLAYER_MAX_SPEED;
		Velo.x = Velo2D.x;
		Velo.z = Velo2D.y;

		dynamic_->setLinearVelocity(Velo);
	}
}

void PhysXDynamicActorComponent::SetChangedRot(float4 _Rot)
{
	//dynamic_->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y, false);

	float4 tmpQuat = _Rot.DegreeRotationToQuaternionReturn();
	const physx::PxQuat tmpPxQuat(tmpQuat.x, tmpQuat.y, tmpQuat.z, tmpQuat.w);
	const physx::PxTransform tmpTansform(dynamic_->getGlobalPose().p, tmpPxQuat);

	dynamic_->setGlobalPose(tmpTansform);
}


