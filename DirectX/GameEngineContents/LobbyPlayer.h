#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 : //로비에 서있을 플레이어
class GameEngineFBXAnimationRenderer;
class LobbyPlayer : public GameEngineActor
{
public:
	// constrcuter destructer
	LobbyPlayer();
	~LobbyPlayer();

	// delete Function
	LobbyPlayer(const LobbyPlayer& _Other) = delete;
	LobbyPlayer(LobbyPlayer&& _Other) noexcept = delete;
	LobbyPlayer& operator=(const LobbyPlayer& _Other) = delete;
	LobbyPlayer& operator=(LobbyPlayer&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

	void LevelStartEvent() override;
private:
	std::shared_ptr<GameEngineFBXAnimationRenderer> FBXRenderer_;
	std::shared_ptr<GameEngineFBXAnimationRenderer> Chair_;
	//std::shared_ptr<GameEngineFBXMesh> Mesh;
};

