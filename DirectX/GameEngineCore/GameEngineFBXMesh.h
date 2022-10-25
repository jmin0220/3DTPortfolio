#pragma once
#include "GameEngineRes.h"
#include <GameEngineCore/GameEngineFBX.h>


struct FbxExMeshInfo
{
	std::string Name;
	fbxsdk::FbxMesh* Mesh;
	bool bTriangulated;

	unsigned __int64 UniqueId;
	int FaceNum;
	int VertexNum;
	int MaterialNum;

	// 애니메이션과 연결되는 매쉬인가?
	bool bIsSkelMesh;
	std::string SkeletonRoot;
	int SkeletonElemNum;

	bool bIsLodGroup;
	std::string LODGroup;
	int LodLevel;
	int MorphNum;

	FbxExMeshInfo()
	{
		Name = "";
		UniqueId = 0;
		FaceNum = 0;
		VertexNum = 0;
		bTriangulated = false;
		MaterialNum = 0;
		bIsSkelMesh = false;
		SkeletonRoot = "";
		SkeletonElemNum = 0;
		bIsLodGroup = false;
		LODGroup = "";
		LodLevel = -1;
		MorphNum = 0;
	}
};


// 설명 :
class GameEngineFBXMesh : public GameEngineFBX, public GameEngineRes<GameEngineFBXMesh>
{
public:
	// constrcuter destructer
	GameEngineFBXMesh();
	~GameEngineFBXMesh();

	// delete Function
	GameEngineFBXMesh(const GameEngineFBXMesh& _Other) = delete;
	GameEngineFBXMesh(GameEngineFBXMesh&& _Other) noexcept = delete;
	GameEngineFBXMesh& operator=(const GameEngineFBXMesh& _Other) = delete;
	GameEngineFBXMesh& operator=(GameEngineFBXMesh&& _Other) noexcept = delete;

	static GameEngineFBXMesh* Load(const std::string& _Path)
	{
		return Load(_Path, GameEnginePath::GetFileName(_Path));
	}

	static GameEngineFBXMesh* Load(const std::string& _Path, const std::string& _Name);


protected:
	std::vector<FbxExMeshInfo> MeshInfos;

private:
	void LoadMesh(const std::string& _Path, const std::string& _Name);

	void MeshLoad();
	// void MeshNodeCheck();
};

