#pragma once

enum class CollisionGroup
{
	Axis,
	Picking,
	Ray,
	Player,
	Map,
	PhysicsGround,
	PhysicsWall,
	PhysicsPlayer,
	Max
};

enum class AxisMode
{
	Move,
	Rotate
};


enum class UICOLLISION //�迹�� �ۼ�
{
	Mouse,
	Button,
};