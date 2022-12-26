#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 : //로비에 서있을 플레이어
class GameEngineFBXAnimationRenderer;
class LobbyPlayer : public GameEngineActor
{
public:
	// 서버
	//static void SetPlayerColor();
	void SetPlayerColor(float4 _Color);

public:
	// constrcuter destructer
	LobbyPlayer();
	~LobbyPlayer();

	// delete Function
	LobbyPlayer(const LobbyPlayer& _Other) = delete;
	LobbyPlayer(LobbyPlayer&& _Other) noexcept = delete;
	LobbyPlayer& operator=(const LobbyPlayer& _Other) = delete;
	LobbyPlayer& operator=(LobbyPlayer&& _Other) noexcept = delete;

	void SetCharacterAnimation();//김예나 : 상태 중복오류떠서 레벨마다 준비하게끔 퍼블릭에 올려봄

	void ChangeAnimationIdle();
	void ChangeAnimationFall();
	void ChangeAnimationWin();
	void ChangeAnimationTumbel();
	void ChangeAnimationJogging();
	void ChangeAnimationGasp();
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

	void LevelStartEvent() override;

	// 캐릭터 스킨 & 애니메이션 초기화
private:

	void SetCharacterTexture();

	SkinData SkinData_;


private:
	std::shared_ptr<GameEngineFBXAnimationRenderer> FBXRenderer_;
	//std::shared_ptr<GameEngineFBXMesh> Mesh;
};

