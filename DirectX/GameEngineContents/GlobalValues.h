#pragma once
#include <GameEngineBase/GameEngineMath.h>

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
	PlayerCheck,
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
	Player = (1 << 0),		// 플레이어
	Ground = (1 << 1),		// 바닥
	Obstacle = (1 << 2),	// 충돌체(HitCallback을 호출할 용도)
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


enum class UICOLLISION //김예나 작성
{
	Mouse,
	Button,
	PlayButton,
	Sound
};

//static GameEngineSoundPlayer BgmPlayer_;
static float Volume_ = 1.0f;

enum class LEVELS
{
	MAP_EDITOR,
	LOBBY,
	LOADING,
	MIDSCORE,

	// 예시
	//PLAY_STAGE_???,
	//PLAY_STAGE_???,
	//PLAY_STAGE_???,
	//PLAY_STAGE_???,
	//GAMEOVER
	STAGE01_DOORDASH,
	STAGE02_JUMPCLUB,
	STAGE03_BIGSHOTS,
	STAGE04_HEX_A_GONE,
	STAGE05_HOOPS_LEGENDS,
	WINNNER,


	// 테스트용
	LOBBY_TEST,
	PHYSICS_TEST,
	PHYSX_TEST,
	CAMERA_TEST,
	SCALE_TEST,
	STAGE1_TEST,
	PLAYER_TEST,

	NONE
};


enum class StageNum
{
	STAGE1,
	STAGE2,
	STAGE3,
	STAGE4,
	STAGE5,
};


// 중복 플래그 없음
enum ServerFlag
{
	S_None					= 0,
	S_GameStartChangeReady			= (1 << 1),
	S_GameStartChangeOver			= (1 << 2),	
	S_LoadingChangeReady		= (1 << 3),
	S_LoadingChangeOver	= (1 << 4),	

	S_StageIdleChangeReady			= (1 << 5),
	S_StageIdleChangeOver			= (1 << 6),
	S_StagePreviewChangeReady		= (1 << 7),	
	S_StagePreviewChangeOver		= (1 << 8),	

	S_StageReadyChangeReady			= (1 << 9),
	S_StageReadyChangeOver		= (1 << 10),

	S_StageRaceChangeReady			= (1 << 11),
	S_StageRaceChangeOver			= (1 << 12),
	S_StageEndChangeReady			= (1 << 13),
	S_StageEndChangeOver			= (1 << 14), 
	
};

// 게임플레이에 관련된 상태 아님
// 유저가 다음 화면으로 넘어갈지에 대한 상태
// 중복 플래그 없음
// 하나만 켜지는거로
enum PlayerFlag
{
	P_None					= 0,
	P_GameStartChangeReady			= (1 << 1),
	P_GameStartChangeOver			= (1 << 2),	
	P_LoadingChangeReady		= (1 << 3),
	P_LoadingChangeOver	= (1 << 4),	

	P_StageIdleChangeReady			= (1 << 5),
	P_StageIdleChangeOver			= (1 << 6),
	P_StagePreviewChangeReady		= (1 << 7),	
	P_StagePreviewChangeOver		= (1 << 8),	

	P_StageReadyChangeReady			= (1 << 9),
	P_StageReadyChangeOver		= (1 << 10),	

	P_StageRaceChangeReady			= (1 << 11),
	P_StageRaceChangeOver			= (1 << 12),	
	P_StageEndChangeReady			= (1 << 13),
	P_StageEndChangeOver			= (1 << 14),
};

enum class MapSelect
{
	Splash_CoY_DoorDash,
	Splash_JumpClub,
	Splash_Hexagone,	
	Splash_HoopsLegends,  // 여기까지가 선택할 수 있는 스테이지

	Splash_AirTime,		// 여기서 부턴 선택은 못하지만 이미지는 보여줄 수 있음
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

enum class PlayerColor
{
	PINK,
	RED,
	GREEN,
	BLUE,
	BLACK,
	WHITE,
	// ...

	MAX,
};

struct SkinData
{
	float4 BodyColor;
};