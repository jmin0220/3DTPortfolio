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
	Max,
	CheckPoint,
	Trigger
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
	PlayButton,
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


enum class MapSelect
{
	Splash_CoY_DoorDash,
	Splash_JumpClub,
	Splash_Hexagone,	// ��������� ������ �� �ִ� ��������

	Splash_AirTime,		// ���⼭ ���� ������ �������� �̹����� ������ �� ����
	Splash_BasketFall,
	Splash_BiggestFan,
	Splash_BigShots,
	Splash_BlastBall,
	Splash_BlockParty,
	Splash_BlueJay,
	Splash_BounceParty,
	Splash_BubbleTrouble,
	Splash_Buttonbashers,
	Splash_ChompChomp,
	Splash_CosmicHighway,
	Splash_CoY_HitParade,
	Splash_CoY_SkiFall,
	Splash_CoY_WallGuys,
	Splash_DoorRush,
	Splash_EggGrab,
	Splash_EggSiege,
	Splash_FallBall,
	Splash_FallMountain,
	Splash_FloorIsLava,
	Splash_FranticFactory,
	Splash_FreezyPeak,
	Splash_FruitBowl,
	Splash_FruitChute,
	Splash_FullTilt,
	Splash_Gauntlet,
	Splash_HexARing,
	Splash_HexaTerrestrial,
	Splash_Hoarders,
	Splash_HoopsieDaisy,
	Splash_HoopsLegends,
	Splash_HoverboardHeroes,
	Splash_HyperdriveHeroes,
	Splash_Invisibeans,
	Splash_InvisibeansHalloween,
	Splash_Jinxed,
	Splash_JumpShowdown,
	Splash_KnightFever,
	Splash_LeadingLight,
	Splash_LilyLeapers,
	Splash_LostTemple,
	Splash_MatchFall,
	Splash_PartyPromenade,
	Splash_PegwinPoolParty,
	Splash_PenguinPursuit,
	Splash_PipeDream,
	Splash_PixelPerfect,
	Splash_PowerTrip,
	Splash_RockandRoll,
	Splash_RollOff,
	Splash_RollOn,
	Splash_RollOut,
	Splash_Rotatonator,
	Splash_RoyalRumble,
	Splash_SeeSaw,
	Splash_ShortCircuit,
	Splash_ShortCircuit2,
	Splash_Skifall,
	Splash_SkylineStumble,
	Splash_Slimescraper,
	Splash_SnowballSurvival,
	Splash_SnowyScrap,
	Splash_SpaceRace,
	Splash_Starchart,
	Splash_StompinGround,
	Splash_TailTag,
	Splash_TeamTailTag,
	Splash_TheSwiveller,
	Splash_Thinice,
	Splash_TipToe,
	Splash_TipToeFinale,
	Splash_TrackAttack,
	Splash_TreetopTumble,
	Splash_TundraRun,
	Splash_VolleyFall,
	Splash_WallGuys,
	Splash_Whirligig,

	NONE
};