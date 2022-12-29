#include "PreCompile.h"
#include "DoorBlock.h"
#include "VirtualPhysXLevel.h"

int DoorBlock::Num = 0;

DoorBlock::DoorBlock() :
	Switch_(false),
	Speed_(0.0f),
	UpTimer_(0.0f),
	DownTimer_(0.0f),
	ServerActivated_(false)
{
	MyNum = Num;
	Num++;
}

DoorBlock::~DoorBlock() 
{
}

void DoorBlock::Start()
{

	PhysXBoxGeometry_ = CreateComponent<PhysXBoxGeometryComponent>();

	// 2. 메쉬세팅 Static renderer
	Renderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	Renderer_->SetFBXMesh("DoorBlock.FBX", "CustomDefferedColor");

	std::vector<std::vector< std::shared_ptr<GameEngineRenderUnit>>>& UnitSet = Renderer_->GetAllRenderUnit();
	for (std::vector< std::shared_ptr<GameEngineRenderUnit>>& Units : UnitSet)
	{
		for (std::shared_ptr<GameEngineRenderUnit> Unit : Units)
		{
			Unit->GetRenderer()->RenderOptionInst.IsNormal = 0;
		}
	}

	Init();
}

void DoorBlock::Update(float _DeltaTime)
{
	if (true == GameServer::RaceStart_)
	{
		ServerActivated_ = true;
	}

	if (false == ServerActivated_)
	{
		return;
	}

	DoorMove(_DeltaTime);
	
}

void DoorBlock::LevelStartEvent()
{

	YPos = GetTransform().GetWorldPosition().y + 11.0f;
	Pos = GetTransform().GetWorldPosition().y;

	CreatePhysXActors(static_cast<VirtualPhysXLevel*>(GetLevel())->GetScene(),
		static_cast<VirtualPhysXLevel*>(GetLevel())->GetPhysics());
}

void DoorBlock::OffEvent()
{
}

void DoorBlock::OnEvent()
{
}

void DoorBlock::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics)
{
	PhysXBoxGeometry_->SetAggregateObj(true);

	float4 Scale = GetTransform().GetWorldScale();


	float4 MeshBoundScale = Renderer_->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	MeshBoundScale *= Scale;
	PhysXBoxGeometry_->CreatePhysXActors(_Scene, _physics, physx::PxVec3(MeshBoundScale.x - 4.0f , MeshBoundScale.y, MeshBoundScale.z));
	PhysXBoxGeometry_->SetObjectObstacle();
	PhysXBoxGeometry_->SetPositionSetFromParentFlag(true);
}

void DoorBlock::Init()
{
	switch (MyNum)
	{
	case 0:
		DownTime_ = 1.0f;
		UpTime_ = 1.5f;
		Speed_ = 5.0f;


		WaitTimer_ = UpTime_;
		DownTimer_ = DownTime_;
		UpTimer_ = UpTime_;
		break;
	case 1:
		DownTime_ = 1.0f;
		UpTime_ = 4.0f;
		Speed_ = 5.0f;

		WaitTimer_ = UpTime_;
		DownTimer_ = DownTime_;
		UpTimer_ = UpTime_;
		break;
	case 2:
		DownTime_ = 1.0f;
		UpTime_ = 8.0f;
		Speed_ = 5.0f;

		WaitTimer_ = UpTime_;
		DownTimer_ = DownTime_;
		UpTimer_ = UpTime_;
		break;
	case 3:
		DownTime_ = 1.0f;
		UpTime_ = 1.0f;
		Speed_ = 8.0f;

		WaitTimer_ = 0;
		DownTimer_ = DownTime_;
		UpTimer_ = UpTime_;
		break;
	case 4:
		DownTime_ = 1.0f;
		UpTime_ = 1.0f;
		Speed_ = 8.0f;

		WaitTimer_ = 2.4f;
		DownTimer_ = DownTime_;
		UpTimer_ = UpTime_;
		break;
	case 5:
		DownTime_ = 1.0f;
		UpTime_ = 1.0f;
		Speed_ = 8.0f;

		WaitTimer_ = 0.0f;
		DownTimer_ = DownTime_;
		UpTimer_ = UpTime_;
		break;
	case 6:
		DownTime_ = 1.0f;
		UpTime_ = 1.0f;
		Speed_ = 8.0f;

		WaitTimer_ = 2.4f;
		DownTimer_ = DownTime_;
		UpTimer_ = UpTime_;
		break;
	case 7:
		DownTime_ = 1.0f;
		UpTime_ = 1.0f;
		Speed_ = 8.0f;

		WaitTimer_ = 2.4f;
		DownTimer_ = DownTime_;
		UpTimer_ = UpTime_;
		break;
	case 8:
		DownTime_ = 1.0f;
		UpTime_ = 1.0f;
		Speed_ = 8.0f;

		WaitTimer_ = 0;
		DownTimer_ = DownTime_;
		UpTimer_ = UpTime_;
		break;
	case 9:
		DownTime_ = 1.0f;
		UpTime_ = 1.0f;
		Speed_ = 8.0f;

		WaitTimer_ = 2.4f;
		DownTimer_ = DownTime_;
		UpTimer_ = UpTime_;
		break;
	case 10:
		DownTime_ = 1.0f;
		UpTime_ = 1.0f;
		Speed_ = 8.0f;

		WaitTimer_ = 0;
		DownTimer_ = DownTime_;
		UpTimer_ = UpTime_;
		break;
	case 11:
		DownTime_ = 6.0f;
		UpTime_ = 1.5f;
		Speed_ = 10.0f;

		WaitTimer_ = UpTime_;
		DownTimer_ = DownTime_;
		UpTimer_ = UpTime_;
		break;
	case 12:
		DownTime_ = 1.0f;
		UpTime_ = 1.0f;
		Speed_ = 10.0f;

		WaitTimer_ = UpTime_;
		DownTimer_ = DownTime_;
		UpTimer_ = UpTime_;
		break;
	case 13:
		DownTime_ = 1.0f;
		UpTime_ = 1.0f;
		Speed_ = 10.0f;

		WaitTimer_ = UpTime_;
		DownTimer_ = DownTime_;
		UpTimer_ = UpTime_;
		break;
	case 14:
		DownTime_ = 6.0f;
		UpTime_ = 1.5f;
		Speed_ = 10.0f;

		WaitTimer_ = UpTime_;
		DownTimer_ = DownTime_;
		UpTimer_ = UpTime_;
		break;
	case 15:
		DownTime_ = 6.0f;
		UpTime_ = 1.5f;
		Speed_ = 10.0f;

		WaitTimer_ = UpTime_;
		DownTimer_ = DownTime_;
		UpTimer_ = UpTime_;
		break;
	case 16:
		DownTime_ = 1.0f;
		UpTime_ = 1.0f;
		Speed_ = 10.0f;

		WaitTimer_ = UpTime_;
		DownTimer_ = DownTime_;
		UpTimer_ = UpTime_;
		break;
	case 17:
		DownTime_ = 1.0f;
		UpTime_ = 1.0f;
		Speed_ = 10.0f;

		WaitTimer_ = UpTime_;
		DownTimer_ = DownTime_;
		UpTimer_ = UpTime_;
		break;
	case 18:
		DownTime_ = 6.0f;
		UpTime_ = 1.5f;
		Speed_ = 10.0f;

		WaitTimer_ = UpTime_;
		DownTimer_ = DownTime_;
		UpTimer_ = UpTime_;
		break;
	case 19:
		DownTime_ = 0.8f;
		UpTime_ = 0.8f;
		Speed_ = 20.0f;

		WaitTimer_ = 0;
		DownTimer_ = DownTime_;
		UpTimer_ = UpTime_;
		break;
	case 20:
		DownTime_ = 0.8f;
		UpTime_ = 0.8f;
		Speed_ = 20.0f;

		WaitTimer_ = 1.5f;
		DownTimer_ = DownTime_;
		UpTimer_ = UpTime_;
		break;
	case 21:
		DownTime_ = 0.8f;
		UpTime_ = 0.8f;
		Speed_ = 20.0f;

		WaitTimer_ = 0;
		DownTimer_ = DownTime_;
		UpTimer_ = UpTime_;
		break;
	case 22:
		DownTime_ = 0.8f;
		UpTime_ = 0.8f;
		Speed_ = 20.0f;

		WaitTimer_ = 1.5f;
		DownTimer_ = DownTime_;
		UpTimer_ = UpTime_;
		break;
	case 23:
		DownTime_ = 0.8f;
		UpTime_ = 0.8f;
		Speed_ = 20.0f;

		WaitTimer_ = 0;
		DownTimer_ = DownTime_;
		UpTimer_ = UpTime_;
		break;
	case 24:
		DownTime_ = 1.0f;
		UpTime_ = 1.0f;
		Speed_ = 5.0f;

		WaitTimer_ = 4.3f;
		DownTimer_ = DownTime_;
		UpTimer_ = UpTime_;
		break;
	case 25:
		DownTime_ = 1.0f;
		UpTime_ = 1.0f;
		Speed_ = 5.0f;

		WaitTimer_ = UpTime_;
		DownTimer_ = DownTime_;
		UpTimer_ = UpTime_;
		break;
	case 26:
		DownTime_ = 1.0f;
		UpTime_ = 1.0f;
		Speed_ = 5.0f;

		WaitTimer_ = 4.3f;
		DownTimer_ = DownTime_;
		UpTimer_ = UpTime_;
		break;
	default:
		break;
	}
}

void DoorBlock::DoorMove(float _DeltaTime)
{
	WaitTimer_ -= _DeltaTime;

	if (WaitTimer_ <= 0)
	{
		switch (MyNum)
		{
		case 0:
			if (Switch_ == false)
			{
				if (GetTransform().GetWorldPosition().y >= YPos)
				{
					DownTimer_ -= _DeltaTime;
					if (DownTimer_ <= 0)
					{
						Switch_ = true;
						DownTimer_ = DownTime_;
					}
					break;
				}

				GetTransform().SetWorldUpMove(Speed_, _DeltaTime);
			}
			else if (Switch_ == true)
			{
				if (GetTransform().GetWorldPosition().y <= Pos)
				{
					UpTimer_ -= _DeltaTime;
					if (UpTimer_ <= 0)
					{
						Switch_ = false;
						UpTimer_ = UpTime_;
					}
					break;
				}
				GetTransform().SetWorldDownMove(Speed_, _DeltaTime);
			}

			break;
		case 1:
			if (Switch_ == false)
			{
				if (GetTransform().GetWorldPosition().y >= YPos)
				{
					DownTimer_ -= _DeltaTime;
					if (DownTimer_ <= 0)
					{
						Switch_ = true;
						DownTimer_ = DownTime_;
					}
					break;
				}

				GetTransform().SetWorldUpMove(Speed_, _DeltaTime);
			}
			else if (Switch_ == true)
			{
				if (GetTransform().GetWorldPosition().y <= Pos)
				{
					UpTimer_ -= _DeltaTime;
					if (UpTimer_ <= 0)
					{
						Switch_ = false;
						UpTimer_ = UpTime_;
					}
					break;
				}
				GetTransform().SetWorldDownMove(Speed_, _DeltaTime);
			}

			break;
		case 2:
			if (Switch_ == false)
			{
				if (GetTransform().GetWorldPosition().y >= YPos)
				{
					DownTimer_ -= _DeltaTime;
					if (DownTimer_ <= 0)
					{
						Switch_ = true;
						DownTimer_ = DownTime_;
					}
					break;
				}

				GetTransform().SetWorldUpMove(Speed_, _DeltaTime);
			}
			else if (Switch_ == true)
			{
				if (GetTransform().GetWorldPosition().y <= Pos)
				{
					UpTimer_ -= _DeltaTime;
					if (UpTimer_ <= 0)
					{
						Switch_ = false;
						UpTimer_ = UpTime_;
					}
					break;
				}
				GetTransform().SetWorldDownMove(Speed_, _DeltaTime);
			}

			break;
		case 3:
			if (Switch_ == false)
			{
				if (GetTransform().GetWorldPosition().y >= YPos)
				{
					DownTimer_ -= _DeltaTime;
					if (DownTimer_ <= 0)
					{
						Switch_ = true;
						DownTimer_ = DownTime_;
					}
					break;
				}

				GetTransform().SetWorldUpMove(Speed_, _DeltaTime);
			}
			else if (Switch_ == true)
			{
				if (GetTransform().GetWorldPosition().y <= Pos)
				{
					UpTimer_ -= _DeltaTime;
					if (UpTimer_ <= 0)
					{
						Switch_ = false;
						UpTimer_ = UpTime_;
					}
					break;
				}
				GetTransform().SetWorldDownMove(Speed_, _DeltaTime);
			}

			break;
		case 4:
			if (Switch_ == false)
			{
				if (GetTransform().GetWorldPosition().y >= YPos)
				{
					DownTimer_ -= _DeltaTime;
					if (DownTimer_ <= 0)
					{
						Switch_ = true;
						DownTimer_ = DownTime_;
					}
					break;
				}

				GetTransform().SetWorldUpMove(Speed_, _DeltaTime);
			}
			else if (Switch_ == true)
			{
				if (GetTransform().GetWorldPosition().y <= Pos)
				{
					UpTimer_ -= _DeltaTime;
					if (UpTimer_ <= 0)
					{
						Switch_ = false;
						UpTimer_ = UpTime_;
					}
					break;
				}
				GetTransform().SetWorldDownMove(Speed_, _DeltaTime);
			}

			break;
		case 5:
			if (Switch_ == false)
			{
				if (GetTransform().GetWorldPosition().y >= YPos)
				{
					DownTimer_ -= _DeltaTime;
					if (DownTimer_ <= 0)
					{
						Switch_ = true;
						DownTimer_ = DownTime_;
					}
					break;
				}

				GetTransform().SetWorldUpMove(Speed_, _DeltaTime);
			}
			else if (Switch_ == true)
			{
				if (GetTransform().GetWorldPosition().y <= Pos)
				{
					UpTimer_ -= _DeltaTime;
					if (UpTimer_ <= 0)
					{
						Switch_ = false;
						UpTimer_ = UpTime_;
					}
					break;
				}
				GetTransform().SetWorldDownMove(Speed_, _DeltaTime);
			}
			break;
		case 6:
			if (Switch_ == false)
			{
				if (GetTransform().GetWorldPosition().y >= YPos)
				{
					DownTimer_ -= _DeltaTime;
					if (DownTimer_ <= 0)
					{
						Switch_ = true;
						DownTimer_ = DownTime_;
					}
					break;
				}

				GetTransform().SetWorldUpMove(Speed_, _DeltaTime);
			}
			else if (Switch_ == true)
			{
				if (GetTransform().GetWorldPosition().y <= Pos)
				{
					UpTimer_ -= _DeltaTime;
					if (UpTimer_ <= 0)
					{
						Switch_ = false;
						UpTimer_ = UpTime_;
					}
					break;
				}
				GetTransform().SetWorldDownMove(Speed_, _DeltaTime);
			}

			break;
		case 7:
			if (Switch_ == false)
			{
				if (GetTransform().GetWorldPosition().y >= YPos)
				{
					DownTimer_ -= _DeltaTime;
					if (DownTimer_ <= 0)
					{
						Switch_ = true;
						DownTimer_ = DownTime_;
					}
					break;
				}

				GetTransform().SetWorldUpMove(Speed_, _DeltaTime);
			}
			else if (Switch_ == true)
			{
				if (GetTransform().GetWorldPosition().y <= Pos)
				{
					UpTimer_ -= _DeltaTime;
					if (UpTimer_ <= 0)
					{
						Switch_ = false;
						UpTimer_ = UpTime_;
					}
					break;
				}
				GetTransform().SetWorldDownMove(Speed_, _DeltaTime);
			}

			break;
		case 8:
			if (Switch_ == false)
			{
				if (GetTransform().GetWorldPosition().y >= YPos)
				{
					DownTimer_ -= _DeltaTime;
					if (DownTimer_ <= 0)
					{
						Switch_ = true;
						DownTimer_ = DownTime_;
					}
					break;
				}

				GetTransform().SetWorldUpMove(Speed_, _DeltaTime);
			}
			else if (Switch_ == true)
			{
				if (GetTransform().GetWorldPosition().y <= Pos)
				{
					UpTimer_ -= _DeltaTime;
					if (UpTimer_ <= 0)
					{
						Switch_ = false;
						UpTimer_ = UpTime_;
					}
					break;
				}
				GetTransform().SetWorldDownMove(Speed_, _DeltaTime);
			}

			break;
		case 9:
			if (Switch_ == false)
			{
				if (GetTransform().GetWorldPosition().y >= YPos)
				{
					DownTimer_ -= _DeltaTime;
					if (DownTimer_ <= 0)
					{
						Switch_ = true;
						DownTimer_ = DownTime_;
					}
					break;
				}

				GetTransform().SetWorldUpMove(Speed_, _DeltaTime);
			}
			else if (Switch_ == true)
			{
				if (GetTransform().GetWorldPosition().y <= Pos)
				{
					UpTimer_ -= _DeltaTime;
					if (UpTimer_ <= 0)
					{
						Switch_ = false;
						UpTimer_ = UpTime_;
					}
					break;
				}
				GetTransform().SetWorldDownMove(Speed_, _DeltaTime);
			}

			break;
		case 10:
			if (Switch_ == false)
			{
				if (GetTransform().GetWorldPosition().y >= YPos)
				{
					DownTimer_ -= _DeltaTime;
					if (DownTimer_ <= 0)
					{
						Switch_ = true;
						DownTimer_ = DownTime_;
					}
					break;
				}

				GetTransform().SetWorldUpMove(Speed_, _DeltaTime);
			}
			else if (Switch_ == true)
			{
				if (GetTransform().GetWorldPosition().y <= Pos)
				{
					UpTimer_ -= _DeltaTime;
					if (UpTimer_ <= 0)
					{
						Switch_ = false;
						UpTimer_ = UpTime_;
					}
					break;
				}
				GetTransform().SetWorldDownMove(Speed_, _DeltaTime);
			}
			break;
		case 11:
			if (Switch_ == false)
			{
				if (GetTransform().GetWorldPosition().y >= YPos)
				{
					DownTimer_ -= _DeltaTime;
					if (DownTimer_ <= 0)
					{
						Switch_ = true;
						DownTimer_ = DownTime_;
					}
					break;
				}

				GetTransform().SetWorldUpMove(Speed_, _DeltaTime);
			}
			else if (Switch_ == true)
			{
				if (GetTransform().GetWorldPosition().y <= Pos)
				{
					UpTimer_ -= _DeltaTime;
					if (UpTimer_ <= 0)
					{
						Switch_ = false;
						UpTimer_ = UpTime_;
					}
					break;
				}
				GetTransform().SetWorldDownMove(Speed_, _DeltaTime);
			}
			break;
		case 12:
			if (Switch_ == false)
			{
				if (GetTransform().GetWorldPosition().y >= YPos)
				{
					DownTimer_ -= _DeltaTime;
					if (DownTimer_ <= 0)
					{
						Switch_ = true;
						DownTimer_ = DownTime_;
					}
					break;
				}

				GetTransform().SetWorldUpMove(Speed_, _DeltaTime);
			}
			else if (Switch_ == true)
			{
				if (GetTransform().GetWorldPosition().y <= Pos)
				{
					UpTimer_ -= _DeltaTime;
					if (UpTimer_ <= 0)
					{
						Switch_ = false;
						UpTimer_ = UpTime_;
					}
					break;
				}
				GetTransform().SetWorldDownMove(Speed_, _DeltaTime);
			}

			break;
		case 13:
			if (Switch_ == false)
			{
				if (GetTransform().GetWorldPosition().y >= YPos)
				{
					DownTimer_ -= _DeltaTime;
					if (DownTimer_ <= 0)
					{
						Switch_ = true;
						DownTimer_ = DownTime_;
					}
					break;
				}

				GetTransform().SetWorldUpMove(Speed_, _DeltaTime);
			}
			else if (Switch_ == true)
			{
				if (GetTransform().GetWorldPosition().y <= Pos)
				{
					UpTimer_ -= _DeltaTime;
					if (UpTimer_ <= 0)
					{
						Switch_ = false;
						UpTimer_ = UpTime_;
					}
					break;
				}
				GetTransform().SetWorldDownMove(Speed_, _DeltaTime);
			}

			break;
		case 14:
			if (Switch_ == false)
			{
				if (GetTransform().GetWorldPosition().y >= YPos)
				{
					DownTimer_ -= _DeltaTime;
					if (DownTimer_ <= 0)
					{
						Switch_ = true;
						DownTimer_ = DownTime_;
					}
					break;
				}

				GetTransform().SetWorldUpMove(Speed_, _DeltaTime);
			}
			else if (Switch_ == true)
			{
				if (GetTransform().GetWorldPosition().y <= Pos)
				{
					UpTimer_ -= _DeltaTime;
					if (UpTimer_ <= 0)
					{
						Switch_ = false;
						UpTimer_ = UpTime_;
					}
					break;
				}
				GetTransform().SetWorldDownMove(Speed_, _DeltaTime);
			}

			break;
		case 15:
			if (Switch_ == false)
			{
				if (GetTransform().GetWorldPosition().y >= YPos)
				{
					DownTimer_ -= _DeltaTime;
					if (DownTimer_ <= 0)
					{
						Switch_ = true;
						DownTimer_ = DownTime_;
					}
					break;
				}

				GetTransform().SetWorldUpMove(Speed_, _DeltaTime);
			}
			else if (Switch_ == true)
			{
				if (GetTransform().GetWorldPosition().y <= Pos)
				{
					UpTimer_ -= _DeltaTime;
					if (UpTimer_ <= 0)
					{
						Switch_ = false;
						UpTimer_ = UpTime_;
					}
					break;
				}
				GetTransform().SetWorldDownMove(Speed_, _DeltaTime);
			}

			break;
		case 16:
			if (Switch_ == false)
			{
				if (GetTransform().GetWorldPosition().y >= YPos)
				{
					DownTimer_ -= _DeltaTime;
					if (DownTimer_ <= 0)
					{
						Switch_ = true;
						DownTimer_ = DownTime_;
					}
					break;
				}

				GetTransform().SetWorldUpMove(Speed_, _DeltaTime);
			}
			else if (Switch_ == true)
			{
				if (GetTransform().GetWorldPosition().y <= Pos)
				{
					UpTimer_ -= _DeltaTime;
					if (UpTimer_ <= 0)
					{
						Switch_ = false;
						UpTimer_ = UpTime_;
					}
					break;
				}
				GetTransform().SetWorldDownMove(Speed_, _DeltaTime);
			}

			break;
		case 17:
			if (Switch_ == false)
			{
				if (GetTransform().GetWorldPosition().y >= YPos)
				{
					DownTimer_ -= _DeltaTime;
					if (DownTimer_ <= 0)
					{
						Switch_ = true;
						DownTimer_ = DownTime_;
					}
					break;
				}

				GetTransform().SetWorldUpMove(Speed_, _DeltaTime);
			}
			else if (Switch_ == true)
			{
				if (GetTransform().GetWorldPosition().y <= Pos)
				{
					UpTimer_ -= _DeltaTime;
					if (UpTimer_ <= 0)
					{
						Switch_ = false;
						UpTimer_ = UpTime_;
					}
					break;
				}
				GetTransform().SetWorldDownMove(Speed_, _DeltaTime);
			}

			break;
		case 18:
			if (Switch_ == false)
			{
				if (GetTransform().GetWorldPosition().y >= YPos)
				{
					DownTimer_ -= _DeltaTime;
					if (DownTimer_ <= 0)
					{
						Switch_ = true;
						DownTimer_ = DownTime_;
					}
					break;
				}

				GetTransform().SetWorldUpMove(Speed_, _DeltaTime);
			}
			else if (Switch_ == true)
			{
				if (GetTransform().GetWorldPosition().y <= Pos)
				{
					UpTimer_ -= _DeltaTime;
					if (UpTimer_ <= 0)
					{
						Switch_ = false;
						UpTimer_ = UpTime_;
					}
					break;
				}
				GetTransform().SetWorldDownMove(Speed_, _DeltaTime);
			}

			break;
		case 19:
			if (Switch_ == false)
			{
				if (GetTransform().GetWorldPosition().y >= YPos)
				{
					DownTimer_ -= _DeltaTime;
					if (DownTimer_ <= 0)
					{
						Switch_ = true;
						DownTimer_ = DownTime_;
					}
					break;
				}

				GetTransform().SetWorldUpMove(Speed_, _DeltaTime);
			}
			else if (Switch_ == true)
			{
				if (GetTransform().GetWorldPosition().y <= Pos)
				{
					UpTimer_ -= _DeltaTime;
					if (UpTimer_ <= 0)
					{
						Switch_ = false;
						UpTimer_ = UpTime_;
					}
					break;
				}
				GetTransform().SetWorldDownMove(Speed_, _DeltaTime);
			}

			break;
		case 20:
			if (Switch_ == false)
			{
				if (GetTransform().GetWorldPosition().y >= YPos)
				{
					DownTimer_ -= _DeltaTime;
					if (DownTimer_ <= 0)
					{
						Switch_ = true;
						DownTimer_ = DownTime_;
					}
					break;
				}

				GetTransform().SetWorldUpMove(Speed_, _DeltaTime);
			}
			else if (Switch_ == true)
			{
				if (GetTransform().GetWorldPosition().y <= Pos)
				{
					UpTimer_ -= _DeltaTime;
					if (UpTimer_ <= 0)
					{
						Switch_ = false;
						UpTimer_ = UpTime_;
					}
					break;
				}
				GetTransform().SetWorldDownMove(Speed_, _DeltaTime);
			}

			break;
		case 21:
			if (Switch_ == false)
			{
				if (GetTransform().GetWorldPosition().y >= YPos)
				{
					DownTimer_ -= _DeltaTime;
					if (DownTimer_ <= 0)
					{
						Switch_ = true;
						DownTimer_ = DownTime_;
					}
					break;
				}

				GetTransform().SetWorldUpMove(Speed_, _DeltaTime);
			}
			else if (Switch_ == true)
			{
				if (GetTransform().GetWorldPosition().y <= Pos)
				{
					UpTimer_ -= _DeltaTime;
					if (UpTimer_ <= 0)
					{
						Switch_ = false;
						UpTimer_ = UpTime_;
					}
					break;
				}
				GetTransform().SetWorldDownMove(Speed_, _DeltaTime);
			}

			break;
		case 22:
			if (Switch_ == false)
			{
				if (GetTransform().GetWorldPosition().y >= YPos)
				{
					DownTimer_ -= _DeltaTime;
					if (DownTimer_ <= 0)
					{
						Switch_ = true;
						DownTimer_ = DownTime_;
					}
					break;
				}

				GetTransform().SetWorldUpMove(Speed_, _DeltaTime);
			}
			else if (Switch_ == true)
			{
				if (GetTransform().GetWorldPosition().y <= Pos)
				{
					UpTimer_ -= _DeltaTime;
					if (UpTimer_ <= 0)
					{
						Switch_ = false;
						UpTimer_ = UpTime_;
					}
					break;
				}
				GetTransform().SetWorldDownMove(Speed_, _DeltaTime);
			}

			break;
		case 23:
			if (Switch_ == false)
			{
				if (GetTransform().GetWorldPosition().y >= YPos)
				{
					DownTimer_ -= _DeltaTime;
					if (DownTimer_ <= 0)
					{
						Switch_ = true;
						DownTimer_ = DownTime_;
					}
					break;
				}

				GetTransform().SetWorldUpMove(Speed_, _DeltaTime);
			}
			else if (Switch_ == true)
			{
				if (GetTransform().GetWorldPosition().y <= Pos)
				{
					UpTimer_ -= _DeltaTime;
					if (UpTimer_ <= 0)
					{
						Switch_ = false;
						UpTimer_ = UpTime_;
					}
					break;
				}
				GetTransform().SetWorldDownMove(Speed_, _DeltaTime);
			}

			break;
		case 24:
			if (Switch_ == false)
			{
				if (GetTransform().GetWorldPosition().y >= YPos)
				{
					DownTimer_ -= _DeltaTime;
					if (DownTimer_ <= 0)
					{
						Switch_ = true;
						DownTimer_ = DownTime_;
					}
					break;
				}

				GetTransform().SetWorldUpMove(Speed_, _DeltaTime);
			}
			else if (Switch_ == true)
			{
				if (GetTransform().GetWorldPosition().y <= Pos)
				{
					UpTimer_ -= _DeltaTime;
					if (UpTimer_ <= 0)
					{
						Switch_ = false;
						UpTimer_ = UpTime_;
					}
					break;
				}
				GetTransform().SetWorldDownMove(Speed_, _DeltaTime);
			}

			break;
		case 25:
			if (Switch_ == false)
			{
				if (GetTransform().GetWorldPosition().y >= YPos)
				{
					DownTimer_ -= _DeltaTime;
					if (DownTimer_ <= 0)
					{
						Switch_ = true;
						DownTimer_ = DownTime_;
					}
					break;
				}

				GetTransform().SetWorldUpMove(Speed_, _DeltaTime);
			}
			else if (Switch_ == true)
			{
				if (GetTransform().GetWorldPosition().y <= Pos)
				{
					UpTimer_ -= _DeltaTime;
					if (UpTimer_ <= 0)
					{
						Switch_ = false;
						UpTimer_ = UpTime_;
					}
					break;
				}
				GetTransform().SetWorldDownMove(Speed_, _DeltaTime);
			}

			break;
		case 26:
			if (Switch_ == false)
			{
				if (GetTransform().GetWorldPosition().y >= YPos)
				{
					DownTimer_ -= _DeltaTime;
					if (DownTimer_ <= 0)
					{
						Switch_ = true;
						DownTimer_ = DownTime_;
					}
					break;
				}

				GetTransform().SetWorldUpMove(Speed_, _DeltaTime);
			}
			else if (Switch_ == true)
			{
				if (GetTransform().GetWorldPosition().y <= Pos)
				{
					UpTimer_ -= _DeltaTime;
					if (UpTimer_ <= 0)
					{
						Switch_ = false;
						UpTimer_ = UpTime_;
					}
					break;
				}
				GetTransform().SetWorldDownMove(Speed_, _DeltaTime);
			}

			break;
		default:
			break;
		}
	}
}
