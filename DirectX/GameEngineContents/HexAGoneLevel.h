#pragma once
#include "StageParentLevel.h"
// 설명 :
class HexTile;
class InGameSetUI;
class HexAGoneLevel	:	public StageParentLevel
{
public:
	// constrcuter destructer
	HexAGoneLevel();
	~HexAGoneLevel();

	// delete Function
	HexAGoneLevel(const HexAGoneLevel& _Other) = delete;
	HexAGoneLevel(HexAGoneLevel&& _Other) noexcept = delete;
	HexAGoneLevel& operator=(const HexAGoneLevel& _Other) = delete;
	HexAGoneLevel& operator=(HexAGoneLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;
private:
	std::shared_ptr<GameEngineActor> BackGroundObj_;;
	std::shared_ptr<GameEngineActor> Tiles_;
	//std::shared_ptr<GameEngineActor> Player_;

	std::shared_ptr<InGameSetUI> UIs_;

	std::vector<std::shared_ptr<GameEngineActor>> TilesVec_;
	int Row_;  //행
	int Col_;  //열 
	int Num_;
	float4 TileScale_;
};

