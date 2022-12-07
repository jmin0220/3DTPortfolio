#pragma once

// Ό³Έν :
class HoopsScythe
{
public:
	// constrcuter destructer
	HoopsScythe();
	~HoopsScythe();

	// delete Function
	HoopsScythe(const HoopsScythe& _Other) = delete;
	HoopsScythe(HoopsScythe&& _Other) noexcept = delete;
	HoopsScythe& operator=(const HoopsScythe& _Other) = delete;
	HoopsScythe& operator=(HoopsScythe&& _Other) noexcept = delete;

protected:

private:

};

