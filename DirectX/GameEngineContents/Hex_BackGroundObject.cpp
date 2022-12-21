#include "PreCompile.h"
#include "Hex_BackGroundObject.h"

Hex_BackGroundObject::Hex_BackGroundObject() 
{
}

Hex_BackGroundObject::~Hex_BackGroundObject() 
{
}

void Hex_BackGroundObject::Start()
{
	{
		std::shared_ptr<GameEngineFBXStaticRenderer> Renderer = CreateComponent<GameEngineFBXStaticRenderer>();
		Renderer->SetFBXMesh("HexAGoneMap.FBX", "CustomDefferedColor");
		//Renderer->GetTransform().SetWorldScale({ 50.0f,50.0f, 50.0f });
	}
}

void Hex_BackGroundObject::Update(float _DeltaTime)
{
}

