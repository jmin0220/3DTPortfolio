#pragma once


// Ό³Έν :
class PhysXTestPlayer;
class LJM_PhysXPlayerTest : public GameEngineLevel
{
public:
	// constrcuter destructer
	LJM_PhysXPlayerTest();
	~LJM_PhysXPlayerTest();

	// delete Function
	LJM_PhysXPlayerTest(const LJM_PhysXPlayerTest& _Other) = delete;
	LJM_PhysXPlayerTest(LJM_PhysXPlayerTest&& _Other) noexcept = delete;
	LJM_PhysXPlayerTest& operator=(const LJM_PhysXPlayerTest& _Other) = delete;
	LJM_PhysXPlayerTest& operator=(LJM_PhysXPlayerTest&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	PhysXTestPlayer* Player_;
};

