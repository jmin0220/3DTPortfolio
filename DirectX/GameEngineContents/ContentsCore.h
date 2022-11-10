#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineCore.h>
#include "GlobalValues.h"

// ���� : ���α׷� ��ü�� �����ϰ� �Ѵ�.
class ContentsCore : public GameEngineCore
{
	// ���� ���ҽ� ����
public:
	static std::shared_ptr<ContentsCore> GetInst()
	{
		return Inst_;
	}

	void LoadLevelResource(LEVELS _LEVEL);
	void ReleaseCurLevelResource();

private:
	static std::shared_ptr<ContentsCore> Inst_;

	// ~���� ���ҽ� ����

public:
	// constrcuter destructer
	ContentsCore(); 
	~ContentsCore(); 
	
	// delete Function
	ContentsCore(const ContentsCore& _Other) = delete;
	ContentsCore(ContentsCore&& _Other) noexcept = delete;
	ContentsCore& operator=(const ContentsCore& _Other) = delete;
	ContentsCore& operator=(ContentsCore&& _Other) noexcept = delete;

	// float4 StartWindowSize() override { return float4{ 1920.0f, 1080.0f } * 0.6f; } ;

	float4 StartWindowSize() override { return float4{ 1600, 900.0f }; };
	float4 StartWindowPosition() override { return { 0,0 }; };


	std::string GetWindowTitle() override
	{
		return "FallGuys";
	}

protected:
	void Start() override;

	// �� ���α׷��� ��� ��Ȳ������ ��� Update�ϸ鼭 üũ������ �ִٸ� ���⼭ �Ѵ�.
	// ������ ���� ������ �׷����� ����. ������ ���� �����̰� ���� ����Ű�� ������ �����Ѵ�.
	// Ÿ��Ʋ�� �ѱ�ų� �̷�
	void Update(float _DeltaTime) override;

	void End() override;

private:
	void CreateKeys();
	void CreateLevels();
	void CreateShaders();
	void LoadShaders();
	void LoadCommonResources();

	// ������ ���ҽ�
private:
	void ResLoadLobby(GameEngineDirectory& _Dir);
	void ResLoadLoading(GameEngineDirectory& _Dir);


	// �׽�Ʈ �� �ӽ�
	void ResLoadTmpTest(GameEngineDirectory& _Dir);
	void ResLoadCameraTest(GameEngineDirectory& _Dir);
	void ResLoadPhysXTest(GameEngineDirectory& _Dir);
	void ResLoadPhysicsTest(GameEngineDirectory& _Dir);
	void ResLoadMapEditor(GameEngineDirectory& _Dir);

	void LevelAllResourceLoad(GameEngineDirectory& _LevelDir);
};

