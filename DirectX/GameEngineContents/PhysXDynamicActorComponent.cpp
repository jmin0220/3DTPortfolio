#include "PreCompile.h"
#include "PhysXDynamicActorComponent.h"


PhysXDynamicActorComponent::PhysXDynamicActorComponent() 
	:IsSpeedLimit_(false)
	, StandUpProgressYAxisAngle_(0.0f)
	, IsMain_(false)
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

	dynamic_->setRigidDynamicLockFlags(
		physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_X | 
		physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y |
		physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z);

	float ScaledRadius = _GeoMetryScale.z;
	float ScaledHeight = _GeoMetryScale.y;

	// ���� ĸ�� �ݶ��̴�
	shape_ = physx::PxRigidActorExt::createExclusiveShape(*dynamic_, physx::PxCapsuleGeometry(ScaledRadius * 1.3f, ScaledHeight * 0.9f), *material_);
	//shape_ = physx::PxRigidActorExt::createExclusiveShape(*dynamic_, physx::PxBoxGeometry(ScaledHeight * 0.9f, ScaledRadius * 1.3f + ScaledHeight * 0.9f, ScaledHeight * 0.9f), *material_);
	float CapsuleHeight = (ScaledHeight * 0.9f);
	physx::PxVec3 DynamicCenter(0.0f, CapsuleHeight, 0.0f );
	//�ǹ�����
	physx::PxTransform relativePose(physx::PxQuat(physx::PxHalfPi, physx::PxVec3(0, 0, 1)));
	relativePose.p = DynamicCenter;
	physx::PxTransform relativePose2(DynamicCenter);
	shape_->setLocalPose(relativePose);
	//shape_->setSimulationFilterData(physx::PxFilterData(static_cast<physx::PxU32>(PhysXFilterGroup::PlayerDynamic), 
	//	static_cast<physx::PxU32>(PhysXFilterGroup::Ground), 
	//	static_cast<physx::PxU32>(PhysXFilterGroup::Obstacle), 0));
	//physx::PxTransform relativePose(physx::PxQuat(physx::PxHalfPi, physx::PxVec3(0, 0, 1)));
	shape_->setContactOffset(0.2f);
	physx::PxRigidBodyExt::updateMassAndInertia(*dynamic_, 0.01f);

	Instshape_ = physx::PxRigidActorExt::createExclusiveShape(*dynamic_, physx::PxCapsuleGeometry(ScaledRadius * 1.3f, ScaledHeight * 0.9f), *material_);
	// �浹���� �ݹ��� ���� ����
	//Instshape_->setSimulationFilterData(physx::PxFilterData(static_cast<physx::PxU32>(PhysXFilterGroup::Player), 0, 0, 0));
	Instshape_->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, false);
	Instshape_->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, true);

	//�ݹ��ǹ����� 
	Instshape_->setLocalPose(relativePose);
	Instshape_->setContactOffset(0.2f);
	// 
	physx::PxTransform LocalPose = dynamic_->getCMassLocalPose();

	faceshape_ = physx::PxRigidActorExt::createExclusiveShape(*dynamic_, physx::PxBoxGeometry(ScaledRadius * 0.1f, ScaledHeight * 0.4f, ScaledHeight * 0.9f), *material_);
	faceshape_->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, false);
	faceshape_->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, true);
	physx::PxTransform facerelativePose(physx::PxVec3(0.0f, CapsuleHeight * 1.3f, ScaledRadius * 1.3f));
	physx::PxTransform facerelativePose2(facerelativePose);
	faceshape_->setLocalPose(facerelativePose2);
	//faceshape_->setSimulationFilterData(physx::PxFilterData(static_cast<physx::PxU32>(PhysXFilterGroup::PlayerFace), 0, 0, 0));

	headshape_ = physx::PxRigidActorExt::createExclusiveShape(*dynamic_, physx::PxSphereGeometry(ScaledHeight * 0.9f), *material_);
	headshape_->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, false);
	headshape_->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, true);
	physx::PxTransform headrelativePose(physx::PxVec3(0.0f, CapsuleHeight * 1.5f, 0.0f));
	//physx::PxTransform facerelativePose2(headrelativePose);
	headshape_->setLocalPose(headrelativePose);
	//headshape_->setSimulationFilterData(physx::PxFilterData(static_cast<physx::PxU32>(PhysXFilterGroup::PlayerHead), 0, 0, 0));
	headshape_->setContactOffset(0.2f);

	// ����?
	dynamic_->setLinearDamping(physx::PxReal(0.5f));
	dynamic_->setMaxAngularVelocity(physx::PxReal(20.0f));
	dynamic_->setAngularDamping(physx::PxReal(2.0f));


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

void PhysXDynamicActorComponent::SetMoveDive(float _Rot)
{
	float4 DirVec = float4::DegreeToDirection2D(_Rot);
	DirVec *= 1.0f;
	dynamic_->addForce(physx::PxVec3(DirVec.y, PLAYER_JUMP_FORCE* 0.5f, DirVec.x), physx::PxForceMode::eIMPULSE);
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
	if (!(physx::PxIsFinite(dynamic_->getGlobalPose().p.x)
		|| physx::PxIsFinite(dynamic_->getGlobalPose().p.y)
		|| physx::PxIsFinite(dynamic_->getGlobalPose().p.z))
		&& true == IsMain_)
	{
		dynamic_->setGlobalPose(RecentTransform_);
	}

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
	RecentTransform_ = tmpPxTransform;
}

bool PhysXDynamicActorComponent::PlayerStandUp(float _DeltaTime, bool _IsXAixisRotReady)
{
	bool Result = false;

	physx::PxVec3 GlobalPose(dynamic_->getGlobalPose().p);
	physx::PxVec3 YAxis(0.0f, 1.0f, 0.0f);
	//float YAixsGlobalAngle = std::acosf();
	physx::PxQuat GlobalRot = dynamic_->getGlobalPose().q;
	float4 GlobalRotEuler = PhysXCommonFunc::GetQuaternionEulerAngles(GlobalRot);
	float4 AddedRotX = float4{ -1.0f, 0.0f, 0.0f }.DegreeRotationToQuaternionReturn();
	float4 AddedRotY = float4{ 0.0f, 10.0f, 0.0f }.DegreeRotationToQuaternionReturn();
	float4 AddedRotmY = float4{ 0.0f, -5.0f, 0.0f }.DegreeRotationToQuaternionReturn();
	float4 AddedRot = float4{ 0.0f, 0.0f, 0.0f }.DegreeRotationToQuaternionReturn();
	physx::PxQuat FinalRot;
	physx::PxQuat AddedRotQuat(AddedRotY.x, AddedRotY.y, AddedRotY.z, AddedRotY.w);
	FinalRot = GlobalRot * AddedRotQuat;

	//if (GlobalRotEuler.y * GameEngineMath::RadianToDegree >= 90.0f)
	//{
	//	physx::PxQuat AddedRotQuat(AddedRotY.x, AddedRotY.y, AddedRotY.z, AddedRotY.w);
	//	FinalRot = GlobalRot * AddedRotQuat;
	//}
	//else
	//{
	//	physx::PxQuat AddedRotQuat(AddedRotmY.x, AddedRotmY.y, AddedRotmY.z, AddedRotmY.w);
	//	FinalRot = GlobalRot * AddedRotQuat;
	//}

	physx::PxTransform FinalTransform(dynamic_->getGlobalPose().p, FinalRot);
	float4 EulerFinalRot = PhysXCommonFunc::GetQuaternionEulerAngles(FinalRot);
	std::string Asdf = std::to_string(EulerFinalRot.x * GameEngineMath::RadianToDegree) + ", " +
		std::to_string(EulerFinalRot.y * GameEngineMath::RadianToDegree) + ", " 
		+ std::to_string(EulerFinalRot.z * GameEngineMath::RadianToDegree)+ "\n";
	//OutputDebugString(Asdf.c_str());
 
	dynamic_->setGlobalPose(FinalTransform);
	physx::PxQuat QautPose = dynamic_->getGlobalPose().q;
	float4 EulerPose = PhysXCommonFunc::GetQuaternionEulerAngles(QautPose);
	float4 EulerPoseDegree = EulerPose * GameEngineMath::RadianToDegree;
	//physx::PxQuat newLocalRotation = dynamic_->getGlobalPose().q * Quaternion.Inverse(transform.parent.rotation)
	return Result;
		
}

bool PhysXDynamicActorComponent::StandUp2(float _DeltaTime, bool _IsXAixisRotReady)
{
	bool Result = false;
	if (_IsXAixisRotReady == false)
	{
		return PlayerStandUp(_DeltaTime, _IsXAixisRotReady);
	}

	physx::PxQuat QautPose = dynamic_->getGlobalPose().q;

	float4 EulerPose = PhysXCommonFunc::GetQuaternionEulerAngles(QautPose);
	float4 EulerPoseDegree = EulerPose * GameEngineMath::RadianToDegree;
	// dynamic�� Angle, Axis�� ���Ѵ�
	float Angle;
	physx::PxVec3 Vec3	;
	dynamic_->getGlobalPose().q.toRadiansAndUnitAxis(Angle, Vec3);
	//������ �Ǵ� Y-Axis  ����
	float4 XAxis(1.0f, 0.0f, 0.0f);
	float4 YAxis(0.0f, 1.0f, 0.0f);
	float4 ZAxis(0.0f, 0.0f, 1.0f);
	physx::PxVec3 YAxisVec3(0.0f, 1.0f, 0.0f);
	physx::PxVec3 mYAxisVec3(0.0f, -1.0f, 0.0f);
	float AngleDegree = Angle * GameEngineMath::RadianToDegree;

	physx::PxVec3 ASDASFFASGG = dynamic_->getGlobalPose().q.getBasisVector1();
	float4 XZAngle = float4{ ASDASFFASGG.x, 0.0f, ASDASFFASGG.z };
	XZAngle.Normalize3D();
	float AngDiffXZ = atanf(XZAngle.x/ XZAngle.z);

	if (ASDASFFASGG.x < 0.0f && ASDASFFASGG.z < 0.0f)
	{
		AngDiffXZ += GameEngineMath::PI;
	}


	if (ASDASFFASGG.x > 0.0f && ASDASFFASGG.z < 0.0f)
	{
		AngDiffXZ -= GameEngineMath::PI;
	}

	if (AngDiffXZ < 0.0f)
	{
		AngDiffXZ += GameEngineMath::PI * 2.0f;
	}

	//dynamic�� Axis�� Y-Axis ������ ����

	float AngDiff = acosf(float4::DotProduct3D({ Vec3.x, Vec3.y, Vec3.z }, YAxis));
	float AngDiffEuler = AngDiff * GameEngineMath::RadianToDegree;
	//if (AngDiffEuler);
	//dynamic�� Axis�� Y-Axis ������ NoramlVector
	physx::PxVec3 Normal = Vec3.cross(YAxisVec3);
	physx::PxVec3 mNormal = Vec3.cross(mYAxisVec3);
	Normal.normalize();
	StandUpProgressYAxisAngle_ += _DeltaTime;
	float ChangedAngle =  GameEngineMath::LerpLimit(StandUpStartYAxisAngle_, StandUpTargetYAxisAngle_, StandUpProgressYAxisAngle_ * 3.0f);

	//�븻���͸� �������� YAxis�� AngDiff��ŭ ȸ��
	float4 FinalRot;
	GameEngineDebug::OutPutString(std::to_string(Vec3.x) + ", " + std::to_string(Vec3.y) + ", " + std::to_string(Vec3.z) );
	//if (Vec3.y > 0)
	//{
		FinalRot = RodriguesRotate({ Vec3.x, Vec3.y, Vec3.z }, { Normal.x, Normal.y, Normal.z }, 0.08f);
	//}
	//else
	//{
	//	FinalRot = RodriguesRotate({ Vec3.x, Vec3.y, Vec3.z }, { Normal.x, Normal.y, Normal.z }, -0.08f);
	//}


	if (abs(FinalRot.y) > 0.97f)
	{
		FinalRot.x = 0.0f;
		FinalRot.z = 0.0f;
		FinalRot.y = 1.0f;
		Result = true;
		GameEngineDebug::OutPutString("WakeUp");
	}

	//if (abs(FinalRot.x) > 0.97f && ChangedAngle == 0.0f)
	//{
	//	//float AngDiffXAxis = acosf(float4::DotProduct3D({ Vec3.x, Vec3.y, Vec3.z }, XAxis));
	//	FinalRot.x = 0.0f;
	//	FinalRot.z = 0.0f;
	//	FinalRot.y = 1.0f;
	//	Result = true;
	//	GameEngineDebug::OutPutString("WakeUp");

	//}

	physx::PxVec3 FinalRotVec3(FinalRot.x, FinalRot.y, FinalRot.z);
	FinalRotVec3.normalize();
	physx::PxQuat tmpQuat(ChangedAngle, FinalRotVec3);
	//const physx::PxQuat tmpPxQuat(tmpQuat.x, tmpQuat.y, tmpQuat.z, tmpQuat.w);
	const physx::PxTransform tmpTransform(dynamic_->getGlobalPose().p, tmpQuat);
	dynamic_->setGlobalPose(tmpTransform);

	return Result;

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

//�÷��̾� ���ߴ� �Լ�
void PhysXDynamicActorComponent::FreezeDynamic()
{
	dynamic_->putToSleep();
}

void PhysXDynamicActorComponent::WakeUpDynamic()
{
	dynamic_->wakeUp();
}

void PhysXDynamicActorComponent::ResetDynamic()
{
	float4 tmpQuat = float4{0.0f,0.0f,0.0f}.DegreeRotationToQuaternionReturn();
	const physx::PxQuat tmpPxQuat(tmpQuat.x, tmpQuat.y, tmpQuat.z, tmpQuat.w);
	const physx::PxTransform tmpTansform(dynamic_->getGlobalPose().p, tmpPxQuat);

	dynamic_->setGlobalPose(tmpTansform);
	dynamic_->setRigidDynamicLockFlags(
		physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_X |
		physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y |
		physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z);
}

void PhysXDynamicActorComponent::InitializeStandUp2()
{
	physx::PxVec3 ASDASFFASGG = dynamic_->getGlobalPose().q.getBasisVector1();
	float4 XZAngle = float4{ ASDASFFASGG.x, 0.0f, ASDASFFASGG.z };
	XZAngle.Normalize3D();
	float AngDiffXZ = atanf(XZAngle.x / XZAngle.z);

	if (ASDASFFASGG.x < 0.0f && ASDASFFASGG.z < 0.0f)
	{
		AngDiffXZ += GameEngineMath::PI;
	}

	if (ASDASFFASGG.x > 0.0f && ASDASFFASGG.z < 0.0f)
	{
		AngDiffXZ -= GameEngineMath::PI;
	}

	if (AngDiffXZ < 0.0f)
	{
		AngDiffXZ += GameEngineMath::PI * 2.0f;
	}

	StandUpTargetYAxisAngle_ = AngDiffXZ;

	float Angle;
	physx::PxVec3 Vec3;
	dynamic_->getGlobalPose().q.toRadiansAndUnitAxis(Angle, Vec3);


	StandUpStartYAxisAngle_ = Angle;

	StandUpProgressYAxisAngle_ = 0.0f;
}

