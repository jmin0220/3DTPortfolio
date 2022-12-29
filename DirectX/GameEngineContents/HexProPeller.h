#pragma once

// ���� :
class HexProPeller :	public GameEngineActor
{
public:
	// constrcuter destructer
	HexProPeller();
	~HexProPeller();

	// delete Function
	HexProPeller(const HexProPeller& _Other) = delete;
	HexProPeller(HexProPeller&& _Other) noexcept = delete;
	HexProPeller& operator=(const HexProPeller& _Other) = delete;
	HexProPeller& operator=(HexProPeller&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:
	std::shared_ptr<GameEngineFBXStaticRenderer> Renderer_;

	float Speed_;

	static int Num;
	int JumboNum;

	// ����
	bool ServerActivated_;
public:
	void SetMesh(std::string _Name)
	{
		Renderer_->SetFBXMesh(_Name, "CustomDefferedColor");

		std::vector<std::vector< std::shared_ptr<GameEngineRenderUnit>>>& UnitSet = Renderer_->GetAllRenderUnit();
		for (std::vector< std::shared_ptr<GameEngineRenderUnit>>& Units : UnitSet)
		{
			for (std::shared_ptr<GameEngineRenderUnit> Unit : Units)
			{
				Unit->GetRenderer()->RenderOptionInst.IsNormal = 0;
			}
		}
	}

	void AddNum()
	{
		Num++;
	}

	int GetNum()
	{
		return Num;
	}
	void SetJumboNum(int Num)
	{
		JumboNum = Num;
	}
};

