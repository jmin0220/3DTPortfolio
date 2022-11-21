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
	HexTiles,
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

enum class LEVELS
{
	MAP_EDITOR,
	LOBBY,
	LOADING,

	// ����
	//PLAY_STAGE_???,
	//PLAY_STAGE_???,
	//PLAY_STAGE_???,
	//PLAY_STAGE_???,
	//GAMEOVER
	STAGE04_HEX_A_GONE,


	// �׽�Ʈ��
	LOBBY_TEST,
	PHYSICS_TEST,
	PHYSX_TEST,
	CAMERA_TEST,
	SCALE_TEST,
	STAGE1_TEST,
	PLAYER_TEST,
};