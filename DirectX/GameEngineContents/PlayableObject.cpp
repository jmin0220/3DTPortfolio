#include "PreCompile.h"
#include "PlayableObject.h"

#include <GameEngineContents/GlobalValues.h>

PlayableObject::PlayableObject()
	: IsMoveRightOn(false)
	, IsMoveLeftOn(false)
	, IsMoveForwardOn(false)
	, IsMoveBackwardOn(false)
	, MovementAccx({2000.0f, 0.0f, 0.0f}) //움직일때의 가속도
	, MovementAccz({0.0f, 0.0f, 2000.0f}) //움직일때의 가속도
	, MovementVelocity({0.0f, 0.0f, 0.0f})//움직일때의 속도
	, MaxSpeed(100.0f) // 움직이는 최대 속도
{
	if (GameEngineInput::GetInst()->IsKey("MoveRight") == false)
	{
		GameEngineInput::GetInst()->CreateKey("MoveRight", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("MoveLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("MoveForward", VK_UP);
		GameEngineInput::GetInst()->CreateKey("MoveBackward", VK_DOWN);
	}
}

PlayableObject::~PlayableObject()
{
}

void PlayableObject::InputUpdate()
{
	IsMoveRightOn = GameEngineInput::GetInst()->IsPress("MoveRight");
	IsMoveLeftOn = GameEngineInput::GetInst()->IsPress("MoveLeft");
	IsMoveForwardOn = GameEngineInput::GetInst()->IsPress("MoveForward");
	IsMoveBackwardOn = GameEngineInput::GetInst()->IsPress("MoveBackward");
}


float4 PlayableObject::CalculateMoveVel(float _DeltaTime, float InclineRate)
{
	{
		if (IsMoveRightOn == true)
		{
			if (IsMoveLeftOn == false)
			{
				MovementVelocity += MovementAccx * InclineRate * _DeltaTime;
				if (MovementVelocity.x > MaxSpeed)
				{
					MovementVelocity.x = MaxSpeed;
				}
			}
		}

		else
		{
			if (IsMoveLeftOn == false && MovementVelocity.x > 0)
			{
				MovementVelocity -= MovementAccx * InclineRate * _DeltaTime;
				if (MovementVelocity.x < 0)
				{
					MovementVelocity.x = 0;
				}
			}
		}

		if (IsMoveLeftOn == true)
		{
			if (IsMoveRightOn == false)
			{
				MovementVelocity -= MovementAccx * InclineRate * _DeltaTime;
				if (MovementVelocity.x < -MaxSpeed)
				{
					MovementVelocity.x = -MaxSpeed;
				}
			}
		}
		else
		{
			if (IsMoveRightOn == false && MovementVelocity.x < 0)
			{
				MovementVelocity += MovementAccx * InclineRate * _DeltaTime;
				if (MovementVelocity.x > 0)
				{
					MovementVelocity.x = 0;
				}
			}
		}
	}

	{
		if (IsMoveForwardOn == true)
		{
			if (IsMoveBackwardOn == false)
			{
				MovementVelocity -= MovementAccz * InclineRate * _DeltaTime;
				if (MovementVelocity.z < -MaxSpeed)
				{
					MovementVelocity.z = -MaxSpeed;
				}
			}
		}

		else
		{
			if (IsMoveBackwardOn == false && MovementVelocity.z < 0)
			{
				MovementVelocity += MovementAccz * InclineRate * _DeltaTime;
				if (MovementVelocity.z > 0)
				{
					MovementVelocity.z = 0;
				}
			}
		}

		if (IsMoveBackwardOn == true)
		{
			if (IsMoveForwardOn == false)
			{
				MovementVelocity += MovementAccz * InclineRate * _DeltaTime;
				if (MovementVelocity.z > MaxSpeed)
				{
					MovementVelocity.z = MaxSpeed;
				}
			}
		}
		else
		{
			if (IsMoveForwardOn == false && MovementVelocity.z > 0)
			{
				MovementVelocity -= MovementAccz * InclineRate * _DeltaTime;
				if (MovementVelocity.z < 0)
				{
					MovementVelocity.z = 0;
				}
			}
		}
	}
	return MovementVelocity;
}