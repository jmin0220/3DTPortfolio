#pragma once
#include <functional>

// ���� :
class GameEngineThreadPool
{
public:
	// constrcuter destructer
	GameEngineThreadPool();
	~GameEngineThreadPool();

	// delete Function
	GameEngineThreadPool(const GameEngineThreadPool& _Other) = delete;
	GameEngineThreadPool(GameEngineThreadPool&& _Other) noexcept = delete;
	GameEngineThreadPool& operator=(const GameEngineThreadPool& _Other) = delete;
	GameEngineThreadPool& operator=(GameEngineThreadPool&& _Other) noexcept = delete;

	// �Լ��� �ѱ�� �����尡 �˾Ƽ� ó���Ѵ�.
	void EnQueue(std::function<void()> _Job);

protected:

private:

};

