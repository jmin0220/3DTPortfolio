#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineCore.h>
#include "GlobalValues.h"
#include "GameServerGUI.h"


// ���� : ���α׷� ��ü�� �����ϰ� �Ѵ�.
class ContentsCore : public GameEngineCore
{
	friend class GameManagerGUI;
	// ���� ���ҽ� ����
public:
	static std::shared_ptr<ContentsCore> GetInst()
	{
		return Inst_;
	}

	void LoadLevelResource(LEVELS _LEVEL);
	void ReleaseCurLevelResource();
	LEVELS StringLevelToLEVELS(std::string_view _StringLevel);
	std::string_view StringLevelToStringSetLevel(std::string_view _StringLevel);

	// ���ҽ� �ε� ��Ȳ �˷��� Return : 0 ~ 1
	void InitLoadingProgress()
	{
		LoadingSize_ = 0;
		LoadingProgress_ = 0;
	}

	float GetLoadingProgress()
	{
		if (LoadingSize_ < 1)
		{
			return 0;
		}

		return LoadingProgress_ / LoadingSize_;
	}

	// *��Ƽ ������ �ε�*
	// �ε� �������� ���ҽ� �ε� �ϰڴ�
	void ChangeLevelByLoading(std::string_view _Level);

	// �׳� ���� �������� �ε��� �ϰڴ�
	void ChangeLevelByThread(std::string_view _Level);

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
	float4 StartWindowPosition() override { return { 0, 0 }; };


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

	static std::vector<GameEngineLevel*> TestLevels_;
	static std::vector<GameEngineLevel*> GameLevels_;

	// ������ ���ҽ�
private:
	void ResLoadLobby(GameEngineDirectory& _Dir);
	void ResLoadLoading(GameEngineDirectory& _Dir);
	void ResLoadStage01(GameEngineDirectory& _Dir);
	void ResLoadStage02(GameEngineDirectory& _Dir);
	void ResLoadStage03(GameEngineDirectory& _Dir);
	void ResLoadStage04(GameEngineDirectory& _Dir);
	void ResLoadStage05(GameEngineDirectory& _Dir);
	void ResLoadWinner(GameEngineDirectory& _Dir);

	// �׽�Ʈ �� �ӽ�
	void ResLoadTmpTest(GameEngineDirectory& _Dir);
	void ResLoadCameraTest(GameEngineDirectory& _Dir);
	void ResLoadPhysXTest(GameEngineDirectory& _Dir);
	void ResLoadPhysicsTest(GameEngineDirectory& _Dir);
	void ResLoadMapEditor(GameEngineDirectory& _Dir);
	void ResScaleTest(GameEngineDirectory& _Dir);

	void LevelAllResourceLoad(GameEngineDirectory& _LevelDir);

	float LoadingSize_;
	float LoadingProgress_;


	////////////////////////////////
	///		����
	////////////////////////////////
public:
	void ServerGUIOn()
	{
		ServerGUI_->On();
	}

private:
	static std::shared_ptr<GameServerGUI> ServerGUI_;
};

