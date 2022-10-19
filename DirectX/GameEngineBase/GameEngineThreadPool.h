#pragma once
#include <functional>

// 설명 :
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

	// 함수를 넘기면 쓰레드가 알아서 처리한다.
	void EnQueue(std::function<void()> _Job);

protected:

private:

};

