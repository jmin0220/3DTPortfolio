#include "PreCompile.h"
#include "PhysXCCTActorComponent.h"

static physx::PxPhysics* physics_ = nullptr;
static physx::PxScene* scene_ = nullptr;

PhysXCCTActorComponent::PhysXCCTActorComponent() 
{
}

PhysXCCTActorComponent::~PhysXCCTActorComponent() 
{
	//Controller_->release();
}

void PhysXCCTActorComponent::Start()
{
	// 부모의 정보의 저장
	ParentActor_ = static_cast<GameEngineActor*>(GetParent());
}

void PhysXCCTActorComponent::Update(float _DeltaTime)
{
	if (ControlledActor_ == nullptr)
	{
		return;
	}

	// PhysX Actor의 상태에 맞춰서 부모의 Transform정보를 갱신
	float4 tmpWorldPos = { static_cast<float>(ControlledActor_->getFootPosition().x)
	, static_cast<float>(ControlledActor_->getFootPosition().y)
	, static_cast<float>(ControlledActor_->getFootPosition().z) };

	//float4 tmpWorldRot = { ControlledActor_->getFootPosition().
	//,dynamic_->getGlobalPose().q.y
	//, dynamic_->getGlobalPose().q.z };

	ParentActor_->GetTransform().SetWorldPosition(tmpWorldPos);
	//ParentActor_->GetTransform().SetWorldRotation(tmpWorldRot);
}

void PhysXCCTActorComponent::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics, physx::PxControllerManager* _Manager)
{
	Scene_ = _Scene;
	physics_ = _physics;
	CtrManager_ = _Manager;

	// 부모 액터로부터 위치 생성
	physx::PxTransform localTm(ParentActor_->GetTransform().GetWorldPosition().x
		, ParentActor_->GetTransform().GetWorldPosition().y
		, ParentActor_->GetTransform().GetWorldPosition().z);


	// 초기 포지션
	physx::PxExtendedVec3 mControllerInitialPosition(
		ParentActor_->GetTransform().GetWorldPosition().x,
		ParentActor_->GetTransform().GetWorldPosition().y, 
		ParentActor_->GetTransform().GetWorldPosition().z);
	
	ControlledActorDesc_.mType = physx::PxControllerShapeType::eCAPSULE;
	ControlledActorDesc_.mPosition = mControllerInitialPosition;
	ControlledActorDesc_.mSlopeLimit = 0.0f;
	ControlledActorDesc_.mContactOffset = 0.01f;
	ControlledActorDesc_.mStepOffset = 0.05f;
	ControlledActorDesc_.mInvisibleWallHeight = 0.0f;
	ControlledActorDesc_.mMaxJumpHeight = 0.0f;
	ControlledActorDesc_.mRadius = 1.0f;
	ControlledActorDesc_.mHeight = 10.0f;
	ControlledActorDesc_.mReportCallback = nullptr;
	ControlledActorDesc_.mBehaviorCallback = nullptr;
	//CapsuleCtrDesc_.radius = 1.0f;
	//CapsuleCtrDesc_.height = 10.0f;

	//// 경사로를 오를때 판정
	//CapsuleCtrDesc_.climbingMode = physx::PxCapsuleClimbingMode::eEASY;

	//Controller_ = CtrManager_->createController(CapsuleCtrDesc_);


	ControlledActor_ = new ControlledActor(physics_, Scene_);
	ControlledActor_->init(ControlledActorDesc_, CtrManager_);
	// Scene에 액터 추가
	// _Scene->addActor(*dynamic_);
}


// PxControllerDesc 초기치 
PhysXCCTActorComponent::ControlledActorDesc::ControlledActorDesc() :
	mType(physx::PxControllerShapeType::eFORCE_DWORD),
	mPosition(physx::PxExtendedVec3(0, 0, 0)),
	mSlopeLimit(0.0f),
	mContactOffset(0.0f),
	mStepOffset(0.0f),
	mInvisibleWallHeight(0.0f),
	mMaxJumpHeight(0.0f),
	mRadius(0.0f),
	mHeight(0.0f),
	mProxyDensity(10.0f),
	//	mProxyScale			(0.8f)
	mProxyScale(0.9f),
	mVolumeGrowth(1.5f),
	mReportCallback(NULL),
	mBehaviorCallback(NULL)
{
}

PhysXCCTActorComponent::ControlledActor::ControlledActor(physx::PxPhysics* _physics, physx::PxScene* _Scene) :
	physics_(_physics),
	Scene_(_Scene),
	mType(physx::PxControllerShapeType::eFORCE_DWORD),
	mController(NULL),
	mControllerRadius(0.0f)
{

}

physx::PxController* PhysXCCTActorComponent::ControlledActor::init(const ControlledActorDesc& desc, physx::PxControllerManager* manager)
{
	// DESC 초기화 시작
	const float radius = desc.mRadius;
	float height = desc.mHeight;

	physx::PxControllerDesc* cDesc;
	physx::PxCapsuleControllerDesc capsuleDesc;

	// 캡슐 형태로 초기화
	PX_ASSERT(desc.mType == PxControllerShapeType::eCAPSULE);
	capsuleDesc.height = height;
	capsuleDesc.radius = radius;
	capsuleDesc.climbingMode = physx::PxCapsuleClimbingMode::eCONSTRAINED;
	cDesc = &capsuleDesc;

	cDesc->density = desc.mProxyDensity;
	cDesc->scaleCoeff = desc.mProxyScale;
	// TODO::되는지 잘 모름
	cDesc->material = physics_->createMaterial(0.5f, 0.5f, 0.6f);
	cDesc->position = desc.mPosition;
	cDesc->slopeLimit = desc.mSlopeLimit;
	cDesc->contactOffset = desc.mContactOffset;
	cDesc->stepOffset = desc.mStepOffset;
	cDesc->invisibleWallHeight = desc.mInvisibleWallHeight;
	cDesc->maxJumpHeight = desc.mMaxJumpHeight;
	cDesc->reportCallback = desc.mReportCallback;
	cDesc->behaviorCallback = desc.mBehaviorCallback;
	cDesc->volumeGrowth = desc.mVolumeGrowth;

	mType = desc.mType;
	mInitialPosition = desc.mPosition;
	mControllerRadius = radius;
	// DESC 초기화 끝

	// 
	physx::PxController* ctrl = static_cast<physx::PxCapsuleController*>(manager->createController(*cDesc));
	PX_ASSERT(ctrl);

	// remove controller shape from scene query for standup overlap test
	physx::PxRigidDynamic* actor = ctrl->getActor();
	if (actor)
	{
		if (actor->getNbShapes())
		{
			physx::PxShape* ctrlShape;
			actor->getShapes(&ctrlShape, 1);
			ctrlShape->setFlag(physx::PxShapeFlag::eSCENE_QUERY_SHAPE, false);
		}
	}

	mController = ctrl;
	return ctrl;
}

// the position of the bottom of the CCT's shape.
physx::PxExtendedVec3 PhysXCCTActorComponent::ControlledActor::getFootPosition() const
{
	return mController->getFootPosition();
}

void PhysXCCTActorComponent::ControlledActor::reset()
{
	//physx::PxSceneWriteLock scopedLock(mOwner.getActiveScene());
	physx::PxSceneWriteLock scopedLock(*Scene_);
	mController->setPosition(mInitialPosition);
}

void PhysXCCTActorComponent::ControlledActor::teleport(const physx::PxVec3& pos)
{
	//physx::PxSceneWriteLock scopedLock(mOwner.getActiveScene());
	physx::PxSceneWriteLock scopedLock(*Scene_);
	mController->setPosition(physx::PxExtendedVec3(pos.x, pos.y, pos.z));
	mTransferMomentum = false;
	mDelta = physx::PxVec3(0);
}


// PT: I'm forced to duplicate this code here for now, since otherwise "eACCELERATION" is banned

PX_INLINE void addForceAtPosInternal(physx::PxRigidBody& body, const physx::PxVec3& force, const physx::PxVec3& pos, physx::PxForceMode::Enum mode, bool wakeup)
{
	/*	if(mode == PxForceMode::eACCELERATION || mode == PxForceMode::eVELOCITY_CHANGE)
		{
			Ps::getFoundation().error(PxErrorCode::eINVALID_PARAMETER, __FILE__, __LINE__,
				"PxRigidBodyExt::addForce methods do not support eACCELERATION or eVELOCITY_CHANGE modes");
			return;
		}*/

	const physx::PxTransform globalPose = body.getGlobalPose();
	const physx::PxVec3 centerOfMass = globalPose.transform(body.getCMassLocalPose().p);

	const physx::PxVec3 torque = (pos - centerOfMass).cross(force);
	body.addForce(force, mode, wakeup);
	body.addTorque(torque, mode, wakeup);
}

static void addForceAtLocalPos(physx::PxRigidBody& body, const physx::PxVec3& force, const physx::PxVec3& pos, physx::PxForceMode::Enum mode, bool wakeup = true)
{
	//transform pos to world space
	const physx::PxVec3 globalForcePos = body.getGlobalPose().transform(pos);

	::addForceAtPosInternal(body, force, globalForcePos, mode, wakeup);
}

void PhysXCCTActorComponent::defaultCCTInteraction(const physx::PxControllerShapeHit& hit)
{
	physx::PxRigidDynamic* actor = hit.shape->getActor()->is<physx::PxRigidDynamic>();
	if (actor)
	{
		if (actor->getRigidBodyFlags() & physx::PxRigidBodyFlag::eKINEMATIC)
			return;

		if (0)
		{
			const physx::PxVec3 p = actor->getGlobalPose().p + hit.dir * 10.0f;

			physx::PxShape* shape;
			actor->getShapes(&shape, 1);
			physx::PxRaycastHit newHit;
			physx::PxU32 n = physx::PxShapeExt::raycast(*shape, *shape->getActor(), p, -hit.dir, 20.0f, physx::PxHitFlag::ePOSITION, 1, &newHit);
			if (n)
			{
				// We only allow horizontal pushes. Vertical pushes when we stand on dynamic objects creates
				// useless stress on the solver. It would be possible to enable/disable vertical pushes on
				// particular objects, if the gameplay requires it.
				const physx::PxVec3 upVector = hit.controller->getUpDirection();
				const physx::PxF32 dp = hit.dir.dot(upVector);
				//		shdfnd::printFormatted("%f\n", fabsf(dp));
				if (fabsf(dp) < 1e-3f)
					//		if(hit.dir.y==0.0f)
				{
					const physx::PxTransform globalPose = actor->getGlobalPose();
					const physx::PxVec3 localPos = globalPose.transformInv(newHit.position);
					::addForceAtLocalPos(*actor, hit.dir * hit.length * 1000.0f, localPos, physx::PxForceMode::eACCELERATION);
				}
			}
		}

		// We only allow horizontal pushes. Vertical pushes when we stand on dynamic objects creates
		// useless stress on the solver. It would be possible to enable/disable vertical pushes on
		// particular objects, if the gameplay requires it.
		const physx::PxVec3 upVector = hit.controller->getUpDirection();
		const physx::PxF32 dp = hit.dir.dot(upVector);
		//		shdfnd::printFormatted("%f\n", fabsf(dp));
		if (fabsf(dp) < 1e-3f)
			//		if(hit.dir.y==0.0f)
		{
			const physx::PxTransform globalPose = actor->getGlobalPose();
			const physx::PxVec3 localPos = globalPose.transformInv(toVec3(hit.worldPos));
			::addForceAtLocalPos(*actor, hit.dir * hit.length * 1000.0f, localPos, physx::PxForceMode::eACCELERATION);
		}
	}
}