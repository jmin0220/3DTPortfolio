#include "PreCompile.h"
#include "PhysXTestPlayer.h"

PhysXTestPlayer::PhysXTestPlayer() 
{
}

PhysXTestPlayer::~PhysXTestPlayer() 
{
}

void PhysXTestPlayer::Start()
{
	// ĳ���� �޽� �ε� �׽�Ʈ��
	FbxRenderer_ = CreateComponent<GameEngineFBXRenderer>();

}

void PhysXTestPlayer::Update(float _DeltaTime)
{
}

void PhysXTestPlayer::LevelStartEvent()
{
	// �޽� �ε�
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources/Mesh/Character");

		GameEngineFBXMesh* Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("Character.FBX"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();

		FbxRenderer_->SetFBXMesh("Character.FBX", "Texture");
		FbxRenderer_->GetTransform().SetWorldScale({ 100, 100, 100 });
	}
}

