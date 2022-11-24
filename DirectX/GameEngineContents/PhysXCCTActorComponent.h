#pragma once
#include <PhysX/characterkinematic/PxExtended.h>
#include <PhysX/characterkinematic/PxController.h>
#include "SampleCCTJump.h"

// 설명 :
// https://gameworksdocs.nvidia.com/PhysX/4.1/documentation/physxguide/Manual/CharacterControllers.html

class PhysXCCTActorComponent : public GameEngineComponent, public PhysXCommonFunc
{
public:
	// constrcuter destructer
	PhysXCCTActorComponent();
	~PhysXCCTActorComponent();

	// delete Function
	PhysXCCTActorComponent(const PhysXCCTActorComponent& _Other) = delete;
	PhysXCCTActorComponent(PhysXCCTActorComponent&& _Other) noexcept = delete;
	PhysXCCTActorComponent& operator=(const PhysXCCTActorComponent& _Other) = delete;
	PhysXCCTActorComponent& operator=(PhysXCCTActorComponent&& _Other) noexcept = delete;

	void CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics, physx::PxControllerManager* _CtrManager);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {}

	// 이 컴포넌트를 가지고 있는 Parent에 대한 정보
	std::weak_ptr<GameEngineActor> ParentActor_;

	// Phys액터 생성에 필요한 정보
	physx::PxScene* Scene_;
	physx::PxPhysics* physics_;
	physx::PxControllerManager* CtrManager_;

	physx::PxMaterial* material_;
	physx::PxShape* shape_;
	physx::PxRigidDynamic* dynamic_;

	static physx::PxReal PhysxGravity_;

	//physx::PxController* Controller_;
	////physx::PxControllerDesc ControllerDesc_;
	//physx::PxCapsuleControllerDesc CapsuleCtrDesc_;

public:
	// PxController Description
	struct ControlledActorDesc
	{
		ControlledActorDesc();

		physx::PxControllerShapeType::Enum		mType;
		physx::PxExtendedVec3					mPosition;
		float							        mSlopeLimit;
		float							        mContactOffset;
		float							        mStepOffset;
		float							        mInvisibleWallHeight;
		float							        mMaxJumpHeight;
		float							        mRadius;
		float							        mHeight;
		float							        mProxyDensity;
		float							        mProxyScale;
		float							        mVolumeGrowth;
		physx::PxUserControllerHitReport* mReportCallback;
		physx::PxControllerBehaviorCallback* mBehaviorCallback;
	};

	// PxController로 컨트롤될 Actor 클래스
	class ControlledActor : public physx::PxDefaultAllocator
	{
	public:
		ControlledActor(physx::PxPhysics* _physics, physx::PxScene*_Scene);
		virtual	~ControlledActor() {};

		physx::PxController*		init(const ControlledActorDesc& desc, physx::PxControllerManager* manager);
		physx::PxExtendedVec3		getFootPosition()	const;
		void						reset();
		void						teleport(const physx::PxVec3& pos);
		void						jump(float force) { mJump.startJump(force); }

		PX_FORCE_INLINE	physx::PxController* getController() { return mController; }

		const SampleCCTJump::Jump& getJump() const { return mJump; }

	// protected:
		physx::PxPhysics*					physics_;
		physx::PxScene*						Scene_;
		physx::PxControllerShapeType::Enum	mType;
		SampleCCTJump::Jump					mJump;

		physx::PxExtendedVec3				mInitialPosition;
		physx::PxVec3						mDelta;
		bool								mTransferMomentum;

		physx::PxController*				mController;
		physx::PxReal						mControllerRadius;

		// move함수를 위한 객체
		physx::PxQueryFilterCallback*		mQueryFilterCallback;
	};


protected:
	ControlledActor* ControlledActor_;
	ControlledActorDesc ControlledActorDesc_;

	// CCT상호작용
	void defaultCCTInteraction(const physx::PxControllerShapeHit& hit);

private:
	// 디버그용 GUI
	void OnGUIFunc();
	std::shared_ptr<CustomableGUI> GUI;
};

