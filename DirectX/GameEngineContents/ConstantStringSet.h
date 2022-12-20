#pragma once

// ������ ����
#define SIZE_MAGNIFICATION_RATIO 1.0f, 1.0f, 1.0f
#define PLAYER_SIZE_MAGNIFICATION_RATIO 3.0f, 3.0f, 3.0f

// �߷� -98.1f * 0.8f
//#define PHYSX_GRAVITY -78.48f
#define PHYSX_GRAVITY -50.48f

// �÷��̾� �ִ�ӷ�
#define PLAYER_MAX_SPEED 25.0f

//�÷��̾� ������
#define PLAYER_JUMP_FORCE 10.0f

//�÷��̾� eventCol ������
#define PLAYER_COL_SCALE 3.0f, 5.0f, 3.0f

//�������� �ٴ��� Staticfriction (�����������)
#define FLOOR_STATICFRICTION 0.7f

//�������� �ٴ��� Dynammicfriction (��������)
#define FLOOR_DYNAMICFRICTION 1.5f

//�������� �ٴ��� Resistution (�ݹ߰��)
#define FLOOR_RESISTUTION 0.0f

// �ִϸ��̼� �����ӽð�
#define ANIMATION_FRAME_TIME 0.016666666666666666666666666666666666666666667f

// ���丮
#define DIR_RESOURCES "Resources"
#define DIR_PHYSXMESH "PhysxMesh"
#define DIR_GAMES "Texture2D\\Games"
#define DIR_LEVELS "Levels"
#define DIR_TESTLEVELS "Levels\\TestLevels"
#define DIR_JSONTEST "JsonTest"
#define DIR_LEVEL_LOBBY "Levels\\LobbyLevel"
#define DIR_LEVEL_MIDSCORE "Levels\\MidScoreLevel"
#define DIR_LEVEL_STAGE01 "Levels\\StageLevel\\Stage01"
#define DIR_LEVEL_STAGE02 "Levels\\StageLevel\\Stage02"
#define DIR_LEVEL_STAGE03 "Levels\\StageLevel\\Stage03"
#define DIR_LEVEL_STAGE04 "Levels\\StageLevel\\Stage04"
#define DIR_LEVEL_STAGE05 "Levels\\StageLevel\\Stage05"
#define DIR_LEVEL_WINNER "Levels\\WinnerLevel"
#define DIR_CHARACTER "CHARACTER"

// �׽�Ʈ���� �и�
#define DIR_TESTLEVEL_CAMERA "Levels\\TestLevels\\CameraTestLevel"
#define DIR_TESTLEVEL_PHYSX "Levels\\TestLevels\\PhysXTestLevel"
#define DIR_TESTLEVEL_PHISICS "Levels\\TestLevels\\PhysicsTestLevel"
#define DIR_TESTLEVEL_MAPEDITOR "Levels\\TestLevels\\MapEditorLevel"
#define DIR_TESTLEVEL_SCALETEST "Levels\\TestLevels\\ScaleTestLevel"
#define DIR_TESTLEVEL_LOBBY "Levels\\TestLevels\\LobbyTestLevel"
#define DIR_TESTLEVEL_PLAYERTEST "Levels\\TestLevels\\PlayerTestLevel"

// ��Ʈ
#define FONT_NOTO_SANS_CJK_SC "Noto Sans CJK SC"
#define FONT_TITAN_ONE "Titan One"

// Ȯ����
#define EXT_PNG ".png"
#define EXT_FBX ".fbx"
#define EXT_MP3 ".mp3"


// FBX
#define FBX_NAME_CHARACTER "Character.FBX"
#define FBX_NAME_CHARACTER_IDLE "Character_Idle_A.FBX"
#define FBX_NAME_CHARACTER_WALK "Character_Walk_A.FBX"
#define FBX_NAME_CHARACTER_RUN "Character_Run_A.FBX"
#define FBX_NAME_CHARACTER_VICTORY "Character_Victory_Gasp.FBX"

#define FBX_NAME_RAINBOW "Rainbow.FBX"
#define FBX_NAME_HEXAGONWALL "HexagonWall.FBX"
#define FBX_NAME_HEXAGONFLOOR "HexagonFloor.FBX"
#define FBX_NAME_TESTMAP "TestMap.FBX"

//JSON
#define JSON_NAME_DOORDASH "\\DoorDash.Json"
#define JSON_NAME_HEXAGONE "\\HexAGone.json"
#define JSON_NAME_HOOPSLEGENDS "\\HoopsMap.json"



// Level
#define LEVEL_NAME_TITLE "TitleLevel"
#define LEVEL_NAME_LOBBY "LobbyLevel"
#define LEVEL_NAME_WINNER "WinnerLevel"
#define LEVEL_NAME_LOADING "Loading"
#define LEVEL_NAME_MIDSCORE "MidScoreLevel"
#define LEVEL_NAME_MAP_EDITER "MapEditorLevel"
#define LEVEL_NAME_PHYSICS_TEST "PhysicsTestLevel"
#define LEVEL_NAME_PHYSX_HELLOWORLD "LJM_PhysXHelloWorld"
#define LEVEL_NAME_PHYSX_PLAYER_TEST "LJM_PhysXPlayerTest"
#define LEVEL_NAME_PHYSX_BOX_GEOMETRY_TEST "LJM_PhysXBoxGeometryTest"
#define LEVEL_NAME_CAMERA_TEST "CameraTestLevel"
#define LEVEL_NAME_SHADER_TUTORIAL "ShaderTutorialLevel"
#define LEVEL_NAME_DOORDASH "DoorDashLevel"
#define LEVEL_NAME_JUMPCLUB "JumpClubLevel"
#define LEVEL_NAME_BIGSHOTS "BigShotsLevel"
#define LEVEL_NAME_HEXAGONE "HexAGoneLevel"
#define LEVEL_NAME_HOOPSLEGENDS "HoopsLegendsLevel"

//Axis Mode
#define AXIS_MOVE "Axis_Move"
#define AXIS_ROTATE "Axis_Rotate"
#define LEVEL_NAME_PHYSX_BOX_GEOMETRY_TEST "LJM_PhysXBoxGeometryTest"
#define LEVEL_NAME_CAMERA_TEST "CameraTestLevel"
#define LEVEL_NAME_CAMERA_TEST "CameraTestLevel"
#define LEVEL_NAME_SCALE_TEST "ScaleTestLevel"
#define LEVEL_NAME_PLAYER_TEST "PlayerTestLevel"

// Input Key
#define KEY_W "W"
#define KEY_A "A"
#define KEY_S "S"
#define KEY_D "D"
#define KEY_MOUSELEFT "VK_LBUTTON"
#define KEY_MOUSERIGHT "VK_RBUTTON"
#define KEY_SPACEBAR "SpaceBar"
#define KEY_ENTER "VK_RETURN"


////////////////
//  ����
////////////////

// ȣ��Ʈ �ּ�
//#define IP_HOST "10.0.4.83" 
#define IP_HOST "172.30.1.37" 
//#define IP_HOST "127.0.0.1" 
