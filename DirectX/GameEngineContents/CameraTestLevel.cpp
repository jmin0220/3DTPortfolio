#include "PreCompile.h"
#include "CameraTestLevel.h"
#include <GameEngineCore/CoreMinimal.h>

#include "TestActor_WaterPlane.h"
#include "TestActor_Character.h"

CameraTestLevel::CameraTestLevel() 
{
}

CameraTestLevel::~CameraTestLevel() 
{
}

void CameraTestLevel::Start()
{
	if (false == GetMainCameraActor()->IsFreeCameraMode())
	{
		GetMainCameraActor()->FreeCameraModeOnOff();
		GetMainCameraActor()->GetTransform().SetWorldMove({ 0, 200, -3000 });
	}




}

void CameraTestLevel::Update(float _DeltaTime)
{

}

void CameraTestLevel::End()
{
}

void CameraTestLevel::LevelStartEvent()
{
	// 로드 겹치면 에러 발생
	// 캐릭터 텍스쳐 로드
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources/Mesh/Character");

		std::vector<GameEngineFile> Files = Dir.GetAllFile(".png");

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineTexture::Load(Files[i].GetFullPath());
		}
	}

	// 메쉬 로드
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources/Mesh/Character");

		GameEngineFBXMesh* Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath("Character.FBX"));
		std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
	}

	
	GEngine::CollisionDebugOff();

	Floor_ = CreateActor<TestActor_WaterPlane>();

	Player_ = CreateActor<TestActor_Character>();
	Player_->GetTransform().SetWorldPosition({ 0, 300, 0 });
}

void CameraTestLevel::LevelEndEvent()
{
	Player_->Death();
	Floor_->Death();
}

