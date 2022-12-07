#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� : //�κ� ������ �÷��̾�
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

	void SetCharacterAnimation();//�迹�� : ���� �ߺ��������� �������� �غ��ϰԲ� �ۺ��� �÷���

	void ChangeAnimationIdle();
	void ChangeAnimationFall();
	void ChangeAnimationWin();
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

	void LevelStartEvent() override;

	// ĳ���� ��Ų & �ִϸ��̼� �ʱ�ȭ
private:

	void SetCharacterTexture();

	struct SkinData
	{
		float4 BodyColor;
	};

	SkinData SkinData_;


private:
	std::shared_ptr<GameEngineFBXAnimationRenderer> FBXRenderer_;
	//std::shared_ptr<GameEngineFBXMesh> Mesh;
};

