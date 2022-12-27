#include "PreCompile.h"
#include "VirtualPhysXLevel.h"
#include "MovingBar.h"

int MovingBar::Num = 0;

MovingBar::MovingBar() :
	MyNum(0),
	Switch_(false),
	Speed_(30.0f),
	ServerActivated_(false)
{
	MyNum = Num;
	Num++;
}

MovingBar::~MovingBar() 
{
}

void MovingBar::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics)
{
	float4 Scale = GetTransform().GetWorldScale();


	float4 MeshBoundScale = Renderer_->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	MeshBoundScale *= Scale;
	PhysXBoxGeometry_->CreatePhysXActors(_Scene, _physics, physx::PxVec3(MeshBoundScale.x- 1.0f , MeshBoundScale.y- 5.0f, MeshBoundScale.z -1.5f));
	PhysXBoxGeometry_->SetObjectObstacle();
	PhysXBoxGeometry_->SetPositionSetFromParentFlag(true);
}

void MovingBar::Move(float _DeltaTime)
{
	//좌표들을 나중에 벽에 닿았을때 return 받는 값으로 변경할수있으면 변경
	switch (MyNum)
	{
	case 0:
	{
		if (false == Switch_)
		{
			GetTransform().SetWorldLeftMove(Speed_, _DeltaTime);

			if (GetTransform().GetWorldPosition().x <= -66.801f)  // 왼쪽벽에 닿았으면
			{
				Switch_ = true;
			}
		}
		else
		{
			GetTransform().SetWorldRightMove(Speed_, _DeltaTime);

			if (GetTransform().GetWorldPosition().x >= -3.335f)  // 오른쪽 벽에 닿았으면
			{
				Switch_ = false;
			}
		}
		break;
	}
	case 1:
	{
		if (false == Switch_)
		{
			GetTransform().SetWorldRightMove(Speed_, _DeltaTime);

			if (GetTransform().GetWorldPosition().x >= 66.527f)  // 오른쪽 벽에 닿았으면
			{
				Switch_ = true;
			}
		}
		else
		{
			GetTransform().SetWorldLeftMove(Speed_, _DeltaTime);

			if (GetTransform().GetWorldPosition().x <= 3.077f)  // 왼쪽 벽에 닿았으면
			{
				Switch_ = false;
			}
		}
		break;
	}
	case 2:
	{
		if (false == Switch_)
		{
			GetTransform().SetWorldLeftMove(Speed_, _DeltaTime);

			if (GetTransform().GetWorldPosition().x <= -66.801f)  // 왼쪽벽에 닿았으면
			{
				Switch_ = true;
			}
		}
		else
		{
			GetTransform().SetWorldRightMove(Speed_, _DeltaTime);

			if (GetTransform().GetWorldPosition().x >= -3.335f)  // 오른쪽 벽에 닿았으면
			{
				Switch_ = false;
			}
		}
		break;
	}
	case 3:
	{
		if (false == Switch_)
		{
			GetTransform().SetWorldRightMove(Speed_, _DeltaTime);

			if (GetTransform().GetWorldPosition().x >= 66.527f)  // 오른쪽 벽에 닿았으면
			{
				Switch_ = true;
			}
		}
		else
		{
			GetTransform().SetWorldLeftMove(Speed_, _DeltaTime);

			if (GetTransform().GetWorldPosition().x <= 3.077f)  // 왼쪽 벽에 닿았으면
			{
				Switch_ = false;
			}
		}
		break;
	}
	case 4:
	{
		if (false == Switch_)
		{
			GetTransform().SetWorldLeftMove(Speed_, _DeltaTime);

			if (GetTransform().GetWorldPosition().x <= -79.591f)  // 왼쪽벽에 닿았으면
			{
				Switch_ = true;
			}
		}
		else
		{
			GetTransform().SetWorldRightMove(Speed_, _DeltaTime);

			if (GetTransform().GetWorldPosition().x >= -14.666f)  // 오른쪽 벽에 닿았으면
			{
				Switch_ = false;
			}
		}
		break;
	}
	case 5:
	{
		if (false == Switch_)
		{
			GetTransform().SetWorldRightMove(Speed_, _DeltaTime);

			if (GetTransform().GetWorldPosition().x >= 79.200)  // 오른쪽 벽에 닿았으면
			{
				Switch_ = true;
			}
		}
		else
		{
			GetTransform().SetWorldLeftMove(Speed_, _DeltaTime);

			if (GetTransform().GetWorldPosition().x <= 14.355)  // 왼쪽 벽에 닿았으면
			{
				Switch_ = false;
			}
		}
		break;
	}
	case 6:
	{
		if (false == Switch_)
		{
			GetTransform().SetWorldRightMove(Speed_, _DeltaTime);

			if (GetTransform().GetWorldPosition().x >= 35.320)  // 오른쪽 벽에 닿았으면
			{
				Switch_ = true;
			}
		}
		else
		{
			GetTransform().SetWorldLeftMove(Speed_, _DeltaTime);

			if (GetTransform().GetWorldPosition().x <= -35.467)  // 왼쪽 벽에 닿았으면
			{
				Switch_ = false;
			}
		}
		break;
	}
	default:
		break;
	}
}

void MovingBar::Start()
{
	PhysXBoxGeometry_ = CreateComponent<PhysXBoxGeometryComponent>();

	// 2. 메쉬세팅 Static renderer
	Renderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	Renderer_->SetFBXMesh("MovingBar.FBX", "CustomDefferedColor");

}

void MovingBar::Update(float _DeltaTime)
{
	if (true == GameServer::GetInst()->CheckServerSignal(ServerFlag::S_StageIdleChangeOver))
	{
		ServerActivated_ = true;
	}

	if (false == ServerActivated_)
	{
		return;
	}

	Move(_DeltaTime);
}

void MovingBar::LevelStartEvent()
{
	CreatePhysXActors(static_cast<VirtualPhysXLevel*>(GetLevel())->GetScene(),
		static_cast<VirtualPhysXLevel*>(GetLevel())->GetPhysics());
}
