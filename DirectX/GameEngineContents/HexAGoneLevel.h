#pragma once

// Ό³Έν :
class HexAGoneLevel
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

private:

};

