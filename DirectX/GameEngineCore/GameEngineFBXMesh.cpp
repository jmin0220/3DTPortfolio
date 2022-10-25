#include "PreCompile.h"
#include "GameEngineFBXMesh.h"

GameEngineFBXMesh::GameEngineFBXMesh() 
{
}

GameEngineFBXMesh::~GameEngineFBXMesh() 
{
}



GameEngineFBXMesh* GameEngineFBXMesh::Load(const std::string& _Path, const std::string& _Name)
{
	GameEngineFBXMesh* NewRes = CreateResName(_Name);
	NewRes->LoadMesh(_Path, _Name);
	return NewRes;
}

void GameEngineFBXMesh::LoadMesh(const std::string& _Path, const std::string& _Name)
{
	if (false == CreateFBXSystemInitialize(_Path))
	{
		MsgBoxAssert("시스템 로드에 실패했습니다.");
	}

	FBXConvertScene();
}

void GameEngineFBXMesh::MeshLoad()
{
	// MeshNodeCheck();
}

//
//void GameEngineFBXMesh::MeshNodeCheck()
//{
//	int geometryCount = Scene->GetGeometryCount();
//	for (int i = 0; i < geometryCount; i++)
//	{
//		// 노드중에서 기하구조를 가진녀석들을 뽑아내는것이고.
//		fbxsdk::FbxGeometry* geoMetry = Scene->GetGeometry(i);
//		fbxsdk::FbxNode* geoMetryNode = geoMetry->GetNode();
//
//		// 뽑아낸 애들중에서 그 타입이
//		if (geoMetry->GetAttributeType() == fbxsdk::FbxNodeAttribute::eMesh)
//		{
//			MeshInfos.push_back(FbxExMeshInfo());
//			FbxExMeshInfo& Info = MeshInfos[MeshInfos.size() - 1];
//
//			if (geoMetry->GetName()[0] != '\0')
//			{
//				Info.Name = GameEngineString::AnsiToUTF8Return(geoMetry->GetName());
//			}
//			else
//			{
//				Info.Name = nullptr != geoMetryNode ? GameEngineString::AnsiToUTF8Return(geoMetryNode->GetName()) : "None";
//			}
//
//			Info.Mesh = reinterpret_cast<fbxsdk::FbxMesh*>(geoMetry);
//			Info.bTriangulated = Info.Mesh->IsTriangleMesh();
//			Info.MaterialNum = geoMetryNode ? geoMetryNode->GetMaterialCount() : 0;
//			Info.FaceNum = Info.Mesh->GetPolygonCount();
//			Info.VertexNum = Info.Mesh->GetControlPointsCount();
//			Info.UniqueId = Info.Mesh->GetUniqueID();
//
//
//			// 나중에 정리할수 있을것 같다.
//			Info.LODGroup = "";
//			if (nullptr != geoMetryNode)
//			{
//				fbxsdk::FbxNode* ParentNode = RecursiveFindParentLodGroup(geoMetryNode->GetParent());
//				if (ParentNode != nullptr && ParentNode->GetNodeAttribute()
//					&& ParentNode->GetNodeAttribute()->GetAttributeType() == fbxsdk::FbxNodeAttribute::eLODGroup)
//				{
//					Info.LODGroup = GameEngineString::AnsiToUTF8Return(ParentNode->GetName());
//					Info.bIsLodGroup = true;
//					for (int LODIndex = 0; LODIndex < ParentNode->GetChildCount(); LODIndex++)
//					{
//						fbxsdk::FbxNode* MeshNode = FindLODGroupNode(ParentNode, LODIndex, geoMetryNode);
//						if (geoMetryNode == MeshNode)
//						{
//							Info.LodLevel = LODIndex;
//							break;
//						}
//					}
//				}
//			}
//
//			if (Info.Mesh->GetDeformerCount(FbxDeformer::eSkin) > 0)
//			{
//				Info.bIsSkelMesh = true;
//				Info.MorphNum = Info.Mesh->GetShapeCount();
//				fbxsdk::FbxSkin* Skin = (fbxsdk::FbxSkin*)Info.Mesh->GetDeformer(0, FbxDeformer::eSkin);
//				int ClusterCount = Skin->GetClusterCount();
//				fbxsdk::FbxNode* Link = NULL;
//				for (int ClusterId = 0; ClusterId < ClusterCount; ++ClusterId)
//				{
//					fbxsdk::FbxCluster* Cluster = Skin->GetCluster(ClusterId);
//					// 서로 연결된 
//					Link = Cluster->GetLink();
//					while (Link && Link->GetParent() && Link->GetParent()->GetSkeleton())
//					{
//						Link = Link->GetParent();
//					}
//
//					if (Link != NULL)
//					{
//						break;
//					}
//				}
//
//				Info.SkeletonRoot = nullptr != Link ? GameEngineString::UTF8ToAnsiReturn(Link->GetName()) : "None";
//				Info.SkeletonElemNum = nullptr != Link ? Link->GetChildCount(true) : 0;
//
//				//if (nullptr != Link)
//				//{
//				//	fbxsdk::FbxTimeSpan AnimTimeSpan(fbxsdk::FBXSDK_TIME_INFINITE, fbxsdk::FBXSDK_TIME_MINUS_INFINITE);
//				//	Link->GetAnimationInterval(AnimTimeSpan);
//				//	GlobalTimeSpan.UnionAssignment(AnimTimeSpan);
//				//}
//			}
//			else
//			{
//				Info.bIsSkelMesh = false;
//				Info.SkeletonRoot = "";
//			}
//		}
//	}
//}