#include "PreCompile.h"
#include "GameEngineFBXRenderer.h"

GameEngineFBXRenderer::GameEngineFBXRenderer() 
{
}

GameEngineFBXRenderer::~GameEngineFBXRenderer() 
{
}

void GameEngineFBXRenderer::SetFBXMesh(const std::string& _Name, std::string _Material)
{
	std::shared_ptr<GameEngineFBXMesh> FindFBXMesh = GameEngineFBXMesh::Find(_Name);
	// 너 몇개 가지고 있어.
	for (size_t UnitCount = 0; UnitCount < FindFBXMesh->GetRenderUnitCount(); UnitCount++)
	{
		size_t SubSet = FindFBXMesh->GetSubSetCount(UnitCount);



		SetFBXMesh(_Name, _Material, UnitCount);
	}
}

void GameEngineFBXRenderer::SetFBXMesh(const std::string& _Name, std::string _Material, size_t MeshIndex)
{
	std::shared_ptr<GameEngineFBXMesh> FindFBXMesh = GameEngineFBXMesh::Find(_Name);

	for (size_t SubSetCount = 0; SubSetCount < FindFBXMesh->GetSubSetCount(MeshIndex); SubSetCount++)
	{
		size_t SubSet = FindFBXMesh->GetSubSetCount(MeshIndex);

		SetFBXMesh(_Name, _Material, MeshIndex, SubSetCount);
	}
}

// SetFbxMesh를 해서 만들어진 랜더 유니트를 사용하게 하기 위해서 리턴해준다.
std::shared_ptr<GameEngineRenderUnit> GameEngineFBXRenderer::SetFBXMesh(const std::string& _Name,
	std::string _Material,
	size_t Index, 
	size_t _SubSetIndex /*= 0*/)
{
	std::shared_ptr<GameEngineFBXMesh> FindFBXMesh = GameEngineFBXMesh::Find(_Name);

	if (nullptr == FindFBXMesh)
	{
		MsgBoxAssert("존재하지 않는 FBXMesh를 세팅했습니다.");
		return nullptr;
	}

	if (nullptr == FBXMesh && nullptr != FindFBXMesh)
	{
		FBXMesh = FindFBXMesh;
	}
	else if (nullptr != FBXMesh && FBXMesh != FindFBXMesh)
	{
		// 지금까지 만든거 다 날립니다.
	}

	if (Unit.empty())
	{
		Unit.resize(FBXMesh->GetRenderUnitCount());
		for (size_t i = 0; i < Unit.size(); i++)
		{
			size_t Count = FBXMesh->GetSubSetCount(i);

			Unit[i].resize(Count);
			for (size_t j = 0; j < Count; j++)
			{
				Unit[i][j] = CreateRenderUnit();
			}
		}
	}
	
	std::shared_ptr<GameEngineRenderUnit> RenderUnit = Unit[Index][_SubSetIndex];
	RenderUnit->SetMaterial(_Material);
	RenderUnit->PushCamera();

	std::shared_ptr <GameEngineMesh> FbxMesh = FBXMesh->GetGameEngineMesh(Index, _SubSetIndex);
	RenderUnit->SetMesh(FbxMesh);

	if (RenderUnit->ShaderResources.IsTexture("DiffuseTexture"))
	{
		const FbxExMaterialSettingData& MatData = FBXMesh->GetMaterialSettingData(Index, _SubSetIndex);

		if (nullptr != GameEngineTexture::Find(MatData.DifTextureName))
		{
			RenderUnit->ShaderResources.SetTexture("DiffuseTexture", MatData.DifTextureName);
		}
	}


	if (RenderUnit->ShaderResources.IsTexture("NormalTexture"))
	{
		const FbxExMaterialSettingData& MatData = FBXMesh->GetMaterialSettingData(Index, _SubSetIndex);

		if (nullptr != GameEngineTexture::Find(MatData.NorTextureName))
		{
			RenderUnit->ShaderResources.SetTexture("NormalTexture", MatData.NorTextureName);
		}

		RenderOptionInst.IsNormal = 1;
	}


	return RenderUnit;
}

void GameEngineFBXRenderer::Render(float _DeltaTime) 
{
	for (size_t UnitIndex = 0; UnitIndex < Unit.size(); UnitIndex++)
	{
		for (size_t SubSetIndex = 0; SubSetIndex < Unit[UnitIndex].size(); SubSetIndex++)
		{
			if (nullptr == Unit[UnitIndex][SubSetIndex]->GetMaterial())
			{
				continue;
			}

			//if (nullptr == Unit[UnitIndex][SubSetIndex].GetMaterial()->GetPixelShader()->GetIsDeffered())
			//{
			//	continue;
			//}

			Unit[UnitIndex][SubSetIndex]->Render(_DeltaTime);
		}
	}
}
