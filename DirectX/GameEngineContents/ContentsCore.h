#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineCore.h>
#include "GlobalValues.h"

// 설명 : 프로그램 자체를 시작하게 한다.
class ContentsCore : public GameEngineCore
{
	friend class GameManagerGUI;
	// 레벨 리소스 관리
public:
	static std::shared_ptr<ContentsCore> GetInst()
	{
		return Inst_;
	}

	void LoadLevelResource(LEVELS _LEVEL);
	void ReleaseCurLevelResource();

	// 리소스 로딩 현황 알려줌 Return : 0 ~ 1
	float GetLoadingProgress()
	{
		if (LoadingSize_ < 1)
		{
			return 0;
		}

		return LoadingProgress_ / LoadingSize_;
	}

private:
	static std::shared_ptr<ContentsCore> Inst_;

	// ~레벨 리소스 관리

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

	// 이 프로그램이 어느 상황에서건 계속 Update하면서 체크할일이 있다면 여기서 한다.
	// 서버가 붙지 않으면 그럴일은 없다. 게임이 무슨 레벨이건 뭐건 무슨키를 누르면 종료한다.
	// 타이틀을 넘기거나 이런
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

	// 레벨별 리소스
private:
	void ResLoadLobby(GameEngineDirectory& _Dir);
	void ResLoadLoading(GameEngineDirectory& _Dir);
	void ResLoadStage01(GameEngineDirectory& _Dir);
	void ResStage02(GameEngineDirectory& _Dir);
	void ResStage04(GameEngineDirectory& _Dir);

	// 테스트 및 임시
	void ResLoadTmpTest(GameEngineDirectory& _Dir);
	void ResLoadCameraTest(GameEngineDirectory& _Dir);
	void ResLoadPhysXTest(GameEngineDirectory& _Dir);
	void ResLoadPhysicsTest(GameEngineDirectory& _Dir);
	void ResLoadMapEditor(GameEngineDirectory& _Dir);
	void ResScaleTest(GameEngineDirectory& _Dir);

	void LevelAllResourceLoad(GameEngineDirectory& _LevelDir);

	float LoadingSize_;
	float LoadingProgress_;
};

