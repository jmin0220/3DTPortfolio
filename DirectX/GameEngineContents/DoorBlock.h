#pragma once
#include "VirtualPhysXActor.h"
#include "PhysXBoxGeometryComponent.h"

// ���� :
class DoorBlock	:	public VirtualPhysXActor
{
public:
	// constrcuter destructer
	DoorBlock();
	~DoorBlock();

	// delete Function
	DoorBlock(const DoorBlock& _Other) = delete;
	DoorBlock(DoorBlock&& _Other) noexcept = delete;
	DoorBlock& operator=(const DoorBlock& _Other) = delete;
	DoorBlock& operator=(DoorBlock&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void LevelStartEvent() override;

	void OffEvent();
	void OnEvent();

	void CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics) override;

private:
	float Speed_;
	bool Switch_;

	float YPos;
	float Pos;

	float UpTimer_;
	float DownTimer_;
	float WaitTimer_;

	//�ð������
	float UpTime_;
	float DownTime_;

	//�� ������ ����  �� ������ �ٸ� �ӵ��� ���¸� �ο��ϱ�����
	static int Num;
	int MyNum;

	void Init();
	void DoorMove(float _DeltaTime);
	
	std::shared_ptr<PhysXBoxGeometryComponent> PhysXBoxGeometry_;
	std::shared_ptr<GameEngineFBXStaticRenderer> Renderer_;

};

