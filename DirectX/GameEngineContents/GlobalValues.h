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

enum class Axis
{
	X,
	Y,
	Z
};

enum class UICOLLISION //김예나 작성
{
	Mouse,
	Button,
};