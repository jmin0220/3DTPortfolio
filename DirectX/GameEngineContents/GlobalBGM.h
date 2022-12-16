#pragma once

// ���� : �� �ϳ��� ���(�̱���..?�Ƹ���..)
class GlobalBGM
{
public:


protected:

private:
	GlobalBGM();
	~GlobalBGM();

	// delete Function
	GlobalBGM(const GlobalBGM& _Other) = delete;
	GlobalBGM(GlobalBGM&& _Other) noexcept = delete;
	GlobalBGM& operator=(const GlobalBGM& _Other) = delete;
	GlobalBGM& operator=(GlobalBGM&& _Other) noexcept = delete;


	static GlobalBGM* Inst_;
	GameEngineSoundPlayer BGM_;
	
public:
	static GlobalBGM* GetInst()
	{
		if (nullptr == Inst_)
		{
			Inst_ = new GlobalBGM();
		}
		return Inst_;
	}

	static void Destroy()
	{
		if (nullptr != Inst_)
		{
			delete Inst_;
			Inst_ = nullptr;
		}
	}

	GameEngineSoundPlayer GetBGM()
	{
		return BGM_;
	}

	void  SetBGM(GameEngineSoundPlayer _BGM)
	{
		BGM_ = _BGM;
	}
};

