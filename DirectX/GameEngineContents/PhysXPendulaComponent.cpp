#include "PreCompile.h"
#include "PhysXPendulaComponent.h"

PhysXPendulaComponent::PhysXPendulaComponent() 
{
}

PhysXPendulaComponent::~PhysXPendulaComponent() 
{
}


void PhysXPendulaComponent::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics, physx::PxVec3 _GeoMetryScale, float4 _GeoMetryRot)
{
	float4 tmpQuat = _GeoMetryRot.DegreeRotationToQuaternionReturn();

	// 부모 액터로부터 위치 생성
	physx::PxTransform localTm(physx::PxVec3(ParentActor_.lock()->GetTransform().GetWorldPosition().x
		, ParentActor_.lock()->GetTransform().GetWorldPosition().y
		, ParentActor_.lock()->GetTransform().GetWorldPosition().z),
		physx::PxQuat(tmpQuat.x, tmpQuat.y, tmpQuat.z, tmpQuat.w));

	// 마찰, 탄성계수
	material_ = _physics->createMaterial(0.5f, 0.5f, 0.6f);

	// TODO::배율을 적용할 경우 이쪽 코드를 사용
	//float4 tmpMagnification = { SIZE_MAGNIFICATION_RATIO };
	//physx::PxVec3 tmpGeoMetryScale(_GeoMetryScale.x * tmpMagnification.x * 0.5f, 
	//							   _GeoMetryScale.y * tmpMagnification.y * 0.5f, 
	//							   _GeoMetryScale.z * tmpMagnification.z * 0.5f);

	physx::PxVec3 tmpGeoMetryScale(_GeoMetryScale.x * 0.5f,
		_GeoMetryScale.y * 0.5f,
		_GeoMetryScale.z * 0.5f);

	// 충돌체의 형태
	// 충돌체의 크기는 절반의 크기를 설정하므로 실제 Renderer의 스케일은 충돌체의 2배로 설정되어야 함
	// TODO::부모 액터의 RenderUnit으로부터 Mesh의 Scale 과 WorldScale의 연산의 결과를 지오메트리의 Scale로 세팅해야함.
	shape_ = _physics->createShape(physx::PxBoxGeometry(tmpGeoMetryScale), *material_);

	// 충돌체의 종류
	//dynamic_ = _physics->createRigidDynamic(localTm);
	//dynamic_->attachShape(*shape_);
	//// 중력이 적용되지 않도록
	//// TODO::RigidStatic으로 변경해야
	//dynamic_->setActorFlag(physx::PxActorFlag::eDISABLE_GRAVITY, true);

	//// RigidDynamic의 밀도를 설정
	//physx::PxRigidBodyExt::updateMassAndInertia(*dynamic_, 10.0f);

	//// Scene에 액터 추가
	//_Scene->addActor(*dynamic_);

	// 충돌체의 종류
	rigidStatic_ = _physics->createRigidStatic(localTm);
	rigidStatic_->attachShape(*shape_);

	// Scene에 액터 추가
	_Scene->addActor(*rigidStatic_);

	// TODO::Pendula 코드 일단 긁어옴
	//physx::PxSceneWriteLock scopedLock(*scene_);
	////Create some giant pendula
	//{
	//	physx::PxTransform shapeTransforms[3] = { physx::PxTransform(physx::PxIdentity),physx::PxTransform(physx::PxIdentity),physx::PxTransform(physx::PxIdentity) };
	//	physx::PxMaterial* shapeMaterials[3] = { NULL,NULL,NULL };
	//	physx::PxGeometry* shapeGeometries[3] = { NULL,NULL,NULL };
	//	physx::PxShape* shapes[3] = { NULL,NULL,NULL };

	//	gNumRevoluteJoints = 0;

	//		//Get the transform to position the next pendulum ball.
	//		const physx::PxTransform& ballStartTransform = gPendulaBallStartTransforms[i];

	//		//Pendulum made of two shapes : a sphere for the ball and a cylinder for the shaft.
	//		//In the absence of a special material for pendula just use the tarmac material. 
	//		physx::PxSphereGeometry geomBall(gPendulumBallRadius);
	//		shapeGeometries[0] = &geomBall;
	//		shapeTransforms[0] = PxTransform(PxIdentity);
	//		shapeMaterials[0] = mStandardMaterials[SURFACE_TYPE_TARMAC];
	//		physx::PxConvexMeshGeometry geomShaft(createCylinderConvexMesh(gPendulumShaftLength, gPendulumShaftWidth, 8, getPhysics(), getCooking()));
	//		shapeGeometries[1] = &geomShaft;
	//		shapeTransforms[1] = PxTransform(PxVec3(0, 0.5f * gPendulumShaftLength, 0), PxQuat(PxHalfPi, PxVec3(0, 0, 1))),
	//			shapeMaterials[1] = mStandardMaterials[SURFACE_TYPE_TARMAC];

	//		//Ready to add the pendulum as a dynamic object.
	//		physx::PxRigidDynamic* actor = addDynamicObstacle(ballStartTransform, gPendulumBallMass, 2, shapeTransforms, shapeGeometries, shapeMaterials);

	//		//As an optimization we don't want pendulum to intersect with static geometry because the position and 
	//		//limits on joint rotation will ensure that this is already impossible.
	//		actor->getShapes(shapes, 2);
	//		physx::PxFilterData simFilterData = shapes[0]->getSimulationFilterData();
	//		simFilterData.word1 &= ~COLLISION_FLAG_GROUND;
	//		shapes[0]->setSimulationFilterData(simFilterData);
	//		shapes[1]->setSimulationFilterData(simFilterData);
	//		//As a further optimization lets set the pendulum shapes to be non-drivable surfaces.
	//		physx::PxFilterData qryFilterData;
	//		SampleVehicleSetupNonDrivableShapeQueryFilterData(&qryFilterData);
	//		shapes[0]->setQueryFilterData(qryFilterData);
	//		shapes[1]->setQueryFilterData(qryFilterData);

	//		//Add static geometry to give the appearance that something is physically supporting the pendulum.
	//		//This supporting geometry is just a vertical bar and two horizontal bars.
	//		const physx::PxF32 groundClearance = 3.0f;
	//		physx::PxConvexMeshGeometry geomHorizontalBar(createCylinderConvexMesh(gPendulumSuspensionStructureWidth, gPendulumShaftWidth, 8, getPhysics(), getCooking()));
	//		physx::PxConvexMeshGeometry geomVerticalBar(createCylinderConvexMesh(gPendulumShaftLength + groundClearance, gPendulumShaftWidth, 8, getPhysics(), getCooking()));
	//		shapeGeometries[0] = &geomHorizontalBar;
	//		shapeMaterials[0] = mStandardMaterials[SURFACE_TYPE_TARMAC];
	//		shapeTransforms[0] = PxTransform(PxVec3(0, gPendulumShaftLength, 0), PxQuat(PxIdentity));
	//		shapeGeometries[1] = &geomVerticalBar;
	//		shapeMaterials[1] = mStandardMaterials[SURFACE_TYPE_TARMAC];
	//		shapeTransforms[1] = PxTransform(PxVec3(0.5f * gPendulumSuspensionStructureWidth, 0.5f * (gPendulumShaftLength - groundClearance), 0), PxQuat(PxHalfPi, PxVec3(0, 0, 1)));
	//		shapeGeometries[2] = &geomVerticalBar;
	//		shapeMaterials[2] = mStandardMaterials[SURFACE_TYPE_TARMAC];
	//		shapeTransforms[2] = PxTransform(PxVec3(-0.5f * gPendulumSuspensionStructureWidth, 0.5f * (gPendulumShaftLength - groundClearance), 0), PxQuat(PxHalfPi, PxVec3(0, 0, 1)));

	//		//Ready to add the support geometry as a static object.
	//		physx::PxRigidStatic* staticActor = addStaticObstacle(ballStartTransform, 3, shapeTransforms, shapeGeometries, shapeMaterials);

	//		//As an optimization lets disable collision with the dynamic pendulum because the joint limits will make 
	//		//collision impossible.
	//		staticActor->getShapes(shapes, 3);
	//		simFilterData = shapes[0]->getSimulationFilterData();
	//		simFilterData.word1 &= ~COLLISION_FLAG_OBSTACLE;
	//		shapes[0]->setSimulationFilterData(simFilterData);
	//		shapes[1]->setSimulationFilterData(simFilterData);
	//		shapes[2]->setSimulationFilterData(simFilterData);

	//		//Now finally add the joint that will create the pendulum behaviour : rotation around a single axis.
	//		const physx::PxVec3 pendulumPos = ballStartTransform.p + PxVec3(0, gPendulumShaftLength, 0);
	//		physx::PxQuat pendulumRotation = PxQuat(PxHalfPi, PxVec3(0, 1, 0));
	//		physx::PxRevoluteJoint* joint = physx::PxRevoluteJointCreate
	//		(*physics_,
	//			NULL, PxTransform(pendulumPos, ballStartTransform.q * pendulumRotation),
	//			actor, PxTransform(PxVec3(0, gPendulumShaftLength, 0), pendulumRotation));
	//		joint->setDriveVelocity(gRevoluteJointDriveSpeeds[i]);
	//		joint->setRevoluteJointFlag(physx::PxRevoluteJointFlag::eDRIVE_ENABLED, true);
	//		gRevoluteJoints[gNumRevoluteJoints] = joint;
	//		gNumRevoluteJoints++;

	//	//Work out the maximum angle of rotation allowed before the pendulum hits the support geometry.
	//	//We're going to monitor the pendulum's progress at each update and reverse the pendulum drive speed
	//	//if the limit is exceed.
	//	const physx::PxF32 sinTheta = (gPendulumSuspensionStructureWidth * 0.5f - gPendulumBallRadius) / gPendulumShaftLength;
	//	gRevoluteJointMaxTheta = PxAsin(sinTheta);
	//}
}

void PhysXPendulaComponent::Start()
{
	// 부모의 정보의 저장
	ParentActor_ = std::dynamic_pointer_cast<GameEngineActor>(GetParent());
}

void PhysXPendulaComponent::Update(float _DeltaTime)
{
	// TODO::static은 변경되지 않으니 Update할 필요가 없을지도
	// PhysX Actor의 상태에 맞춰서 부모의 Transform정보를 갱신
	float4 tmpWorldPos = { rigidStatic_->getGlobalPose().p.x
	, rigidStatic_->getGlobalPose().p.y
	, rigidStatic_->getGlobalPose().p.z };

	float4 tmpWorldRot = { rigidStatic_->getGlobalPose().q.x
	, rigidStatic_->getGlobalPose().q.y
	, rigidStatic_->getGlobalPose().q.z };

	ParentActor_.lock()->GetTransform().SetWorldPosition(tmpWorldPos);
	ParentActor_.lock()->GetTransform().SetWorldRotation(tmpWorldRot);
}
