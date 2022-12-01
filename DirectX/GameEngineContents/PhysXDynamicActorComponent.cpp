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
	material_ = _physics->createMaterial(0.0f, 0.0f, 0.0f);

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
	//shape_ = physx::PxRigidActorExt::createExclusiveShape(*dynamic_, physx::PxSphereGeometry(ScaledRadius * 1.3f), *material_);

	//shape_->setSimulationFilterData(physx::PxFilterData(static_cast<physx::PxU32>(PhysXFilterGroup::Player)
	//	, static_cast<physx::PxU32>(PhysXFilterGroup::Ground), 0, 0));
	physx::PxTransform relativePose(physx::PxQuat(physx::PxHalfPi, physx::PxVec3(0, 0, 1)));
	shape_->setLocalPose(relativePose);

	physx::PxRigidBodyExt::updateMassAndInertia(*dynamic_, 0.01f);
	
	physx::PxShape* Instshape_;
	Instshape_ = physx::PxRigidActorExt::createExclusiveShape(*dynamic_, physx::PxCapsuleGeometry(ScaledRadius * 1.3f, ScaledHeight * 0.9f), *material_);
	// �浹���� �ݹ��� ���� ����
	Instshape_->setSimulationFilterData(physx::PxFilterData(static_cast<physx::PxU32>(PhysXFilterGroup::Player)
		, static_cast<physx::PxU32>(PhysXFilterGroup::Ground), 0, 0));
	Instshape_->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, false);
	Instshape_->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, true);

	//physx::PxTransform relativePose(physx::PxVec3(0.0f, +ScaledHeight * 0.9f + ScaledRadius * 1.3f, 0.0f), physx::PxQuat(physx::PxHalfPi, physx::PxVec3(0, 0, 1)));
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

	//float4 tmpWorldRot = { dynamic_->getGlobalPose().q.x
	//,dynamic_->getGlobalPose().q.y
	//, dynamic_->getGlobalPose().q.z };
	float4 QuatRot = float4{ dynamic_->getGlobalPose().q.x, dynamic_->getGlobalPose().q.y, dynamic_->getGlobalPose().q.z, dynamic_->getGlobalPose().q.w };
	float4 EulerRot = float4::QuaternionToEulerAngles(QuatRot);
	float angle;
	physx::PxVec3 Vec3;
	dynamic_->getGlobalPose().q.toRadiansAndUnitAxis(angle, Vec3);
	float4 AAE = AnglexAxistoEuler(float4{Vec3.x, Vec3.y, Vec3.z}, angle);
	float4 tmpWorldRot = { ToEulerAngles(dynamic_->getGlobalPose().q) };
	tmpWorldRot = tmpWorldRot * GameEngineMath::RadianToDegree;



	ParentActor_.lock()->GetTransform().SetLocalRotation(EulerRot * GameEngineMath::RadianToDegree);
	ParentActor_.lock()->GetTransform().SetWorldPosition(tmpWorldPos);


	if (IsSpeedLimit_ == true)
	{
		SpeedLimit();
	}

}

float4 PhysXDynamicActorComponent::AnglexAxistoEuler(float4 Vec3, float angle)
{
	double s = std::sin(angle);
	double c = std::cos(angle);
	double t = 1 - c;
	//  if axis is not already normalised then uncomment this
	// double magnitude = Math.sqrt(x*x + y*y + z*z);
	// if (magnitude==0) throw error;
	// x /= magnitude;
	// y /= magnitude;
	// z /= magnitude;
	if ((Vec3.x * Vec3.y * t + Vec3.z * s) > 0.998) { // north pole singularity detected
		float heading = 2 * atan2(Vec3.x * std::sin(angle / 2), std::cos(angle / 2));
		float attitude = GameEngineMath::PI / 2;
		float bank = 0;

		//return float4{attitude, heading, bank };
		return float4{ heading ,attitude ,bank };
		//return float4{heading , attitude, bank };
	}
	if ((Vec3.x * Vec3.y * t + Vec3.z * s) < -0.998) { // south pole singularity detected
		float heading = -2 * atan2(Vec3.x * std::sin(angle / 2), std::cos(angle / 2));
		float attitude = -GameEngineMath::PI / 2;
		float bank = 0;
		//return float4{ attitude, heading, bank };
		return float4{ heading ,attitude ,bank };
		//return float4{ heading , attitude, bank };
	}
	float heading = std::atan2(Vec3.y * s - Vec3.x * Vec3.z * t, 1 - (Vec3.y * Vec3.y + Vec3.z * Vec3.z) * t);
	float attitude = std::asin(Vec3.x * Vec3.y * t + Vec3.z * s);
	float bank = std::atan2(Vec3.x * s - Vec3.y * Vec3.z * t, 1 - (Vec3.x * Vec3.x + Vec3.z * Vec3.z) * t);

	//return float4{ attitude, heading, bank };
	return float4{ heading ,attitude ,bank };
	//return float4{heading , attitude, bank };
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

bool PhysXDynamicActorComponent::PlayerStandUp()
{
	return false;
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
	//if (std::abs(Velo.x) > PLAYER_MAX_SPEED)
	//{
	//	int k = (Velo.x > 0) ? 1 : ((Velo.x < 0) ? -1 : 0);
	//	Velo.x = PLAYER_MAX_SPEED * k;
	//}

	//if (std::abs(Velo.z) > PLAYER_MAX_SPEED)
	//{
	//	int k = (Velo.z > 0) ? 1 : ((Velo.z < 0) ? -1 : 0);
	//	Velo.z = PLAYER_MAX_SPEED * k;
	//}
	////Velo.normalize();
	//dynamic_->setLinearVelocity(Velo);
}


