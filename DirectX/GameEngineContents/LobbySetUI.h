#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 : 로비에 나올 모든 UI세트
class CrownCount;
class NamePlate;
class NoneButton;
class NoneMoney;
class PlayButton;
class SelectShowButton;
class TopMenu;
class LobbySetUI : public GameEngineActor
{
public:
	// constrcuter destructer
	LobbySetUI();
	~LobbySetUI();

	// delete Function
	LobbySetUI(const LobbySetUI& _Other) = delete;
	LobbySetUI(LobbySetUI&& _Other) noexcept = delete;
	LobbySetUI& operator=(const LobbySetUI& _Other) = delete;
	LobbySetUI& operator=(LobbySetUI&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

	void LevelStartEvent() override;
	void LevelEndEvent() override;
private:
	std::shared_ptr<CrownCount> CrownCount_;
	std::shared_ptr<NamePlate> NamePlate_;
	std::shared_ptr<NoneButton> NoneButton_;
	std::shared_ptr<NoneMoney> NoneMoney_;
	std::shared_ptr<PlayButton> PlayButton_;
	std::shared_ptr<SelectShowButton> SelectShowButton_;
	std::shared_ptr<TopMenu> TopMenu_;
};

