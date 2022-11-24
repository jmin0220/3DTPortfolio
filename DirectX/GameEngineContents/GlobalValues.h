#pragma once

struct MeshPixelData
{
	float4 MulColor;
	float4 PlusColor;
	float4 Slice;

	MeshPixelData()
		: MulColor(float4::WHITE)
		, PlusColor(float4::ZERO)
		, Slice(float4::ZERO)
	{

	}
};

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

enum class PhysXFilterGroup
{
	Player = (1 << 0),		// �÷��̾�
	Ground = (1 << 1),		// �ٴ�
	Obstacle = (1 << 2),	// �浹ü(HitCallback�� ȣ���� �뵵)
};

enum class AxisMode
{
	Move,
	Rotate
};

enum class HexTileState
{
	Move,
	Shake
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
	STAGE01_DOORDASH,
	STAGE02_JUMPCLUB,
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