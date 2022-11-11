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


enum class UICOLLISION //김예나 작성
{
	Mouse,
	Button,
};

enum class LEVELS
{
	MAP_EDITOR,
	LOBBY,
	LOADING,

	// 예시
	//PLAY_STAGE_???,
	//PLAY_STAGE_???,
	//PLAY_STAGE_???,
	//PLAY_STAGE_???,
	//GAMEOVER


	// 테스트용
	TMP_TEST,
	PHYSICS_TEST,
	PHYSX_TEST,
	CAMERA_TEST,
	SCALE_TEST
};