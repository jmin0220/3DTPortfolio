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

	// �θ� ���ͷκ��� ��ġ ����
	physx::PxTransform localTm(physx::PxVec3(ParentActor_.lock()->GetTransform().GetWorldPosition().x
		, ParentActor_.lock()->GetTransform().GetWorldPosition().y
		, ParentActor_.lock()->GetTransform().GetWorldPosition().z),
		physx::PxQuat(tmpQuat.x, tmpQuat.y, tmpQuat.z, tmpQuat.w));

	// ����, ź�����
	material_ = _physics->createMaterial(0.5f, 0.5f, 0.6f);

	// TODO::������ ������ ��� ���� �ڵ带 ���
	//float4 tmpMagnification = { SIZE_MAGNIFICATION_RATIO };
	//physx::PxVec3 tmpGeoMetryScale(_GeoMetryScale.x * tmpMagnification.x * 0.5f, 
	//							   _GeoMetryScale.y * tmpMagnification.y * 0.5f, 
	//							   _GeoMetryScale.z * tmpMagnification.z * 0.5f);

	physx::PxVec3 tmpGeoMetryScale(_GeoMetryScale.x * 0.5f,
		_GeoMetryScale.y * 0.5f,
		_GeoMetryScale.z * 0.5f);

	// �浹ü�� ����
	// �浹ü�� ũ��� ������ ũ�⸦ �����ϹǷ� ���� Renderer�� �������� �浹ü�� 2��� �����Ǿ�� ��
	// TODO::�θ� ������ RenderUnit���κ��� Mesh�� Scale �� WorldScale�� ������ ����� ������Ʈ���� Scale�� �����ؾ���.
	shape_ = _physics->createShape(physx::PxBoxGeometry(tmpGeoMetryScale), *material_);

	// �浹ü�� ����
	//dynamic_ = _physics->createRigidDynamic(localTm);
	//dynamic_->attachShape(*shape_);
	//// �߷��� ������� �ʵ���
	//// TODO::RigidStatic���� �����ؾ�
	//dynamic_->setActorFlag(physx::PxActorFlag::eDISABLE_GRAVITY, true);

	//// RigidDynamic�� �е��� ����
	//physx::PxRigidBodyExt::updateMassAndInertia(*dynamic_, 10.0f);

	//// Scene�� ���� �߰�
	//_Scene->addActor(*dynamic_);

	// �浹ü�� ����
	rigidStatic_ = _physics->createRigidStatic(localTm);
	rigidStatic_->attachShape(*shape_);

	// Scene�� ���� �߰�
	_Scene->addActor(*rigidStatic_);

	// TODO::Pendula �ڵ� �ϴ� �ܾ��
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
	// �θ��� ������ ����
	ParentActor_ = std::dynamic_pointer_cast<GameEngineActor>(GetParent());
}

void PhysXPendulaComponent::Update(float _DeltaTime)
{
	// TODO::static�� ������� ������ Update�� �ʿ䰡 ��������
	// PhysX Actor�� ���¿� ���缭 �θ��� Transform������ ����
	float4 tmpWorldPos = { rigidStatic_->getGlobalPose().p.x
	, rigidStatic_->getGlobalPose().p.y
	, rigidStatic_->getGlobalPose().p.z };

	float4 tmpWorldRot = { rigidStatic_->getGlobalPose().q.x
	, rigidStatic_->getGlobalPose().q.y
	, rigidStatic_->getGlobalPose().q.z };

	ParentActor_.lock()->GetTransform().SetWorldPosition(tmpWorldPos);
	ParentActor_.lock()->GetTransform().SetWorldRotation(tmpWorldRot);
}
