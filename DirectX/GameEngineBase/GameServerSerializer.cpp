#include "PreCompile.h"
#include "GameServerSerializer.h"

GameServerSerializer::GameServerSerializer(const char* _Data, unsigned int _Size)
{
	Data.resize(_Size);

	memcpy_s(&Data[0], _Size, _Data, _Size);
}

GameServerSerializer::~GameServerSerializer() 
{
}

