#pragma once
#include <PhysX/characterkinematic/PxExtended.h>
#include <PhysX/characterkinematic/PxController.h>
#include "SampleCCTJump.h"

// ���� :
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

	// �� ������Ʈ�� ������ �ִ� Parent�� ���� ����
	std::weak_ptr<GameEngineActor> ParentActor_;

	// Phys���� ������ �ʿ��� ����
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

	// PxController�� ��Ʈ�ѵ� Actor Ŭ����
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

		// move�Լ��� ���� ��ü
		physx::PxQueryFilterCallback*		mQueryFilterCallback;
	};


protected:
	ControlledActor* ControlledActor_;
	ControlledActorDesc ControlledActorDesc_;

	// CCT��ȣ�ۿ�
	void defaultCCTInteraction(const physx::PxControllerShapeHit& hit);

private:
	// ����׿� GUI
	void OnGUIFunc();
	std::shared_ptr<CustomableGUI> GUI;
};

