#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 : 인게임에서 넘어가는데 그대로 쓰면 터져서 UI용 하나 더 만듬
class GameEngineFBXStaticRenderer;
class UISkyBoxActor : public GameEngineActor
{
public:
	void SetSkyTexture(const std::string_view& _TextureName)
	{
		// 텍스쳐 씌워주기
		//std::vector<std::vector<GameEngineRenderUnit>>& UnitSet = StaticRenderer_->GetAllRenderUnit();
		std::vector<std::vector< std::shared_ptr<GameEngineRenderUnit>>>& UnitSet = StaticRenderer_->GetAllRenderUnit();
		for (std::vector< std::shared_ptr<GameEngineRenderUnit>>& Units : UnitSet)
		{
			for (std::shared_ptr<GameEngineRenderUnit>& Unit : Units)
			{
				if (true == Unit->ShaderResources.IsTexture("DiffuseTexture"))
				{
					Unit->ShaderResources.SetTexture("DiffuseTexture", _TextureName.data());
				}
			}
		}
	}

	void SetSkyPivot(float4 _Value)
	{
		StaticRenderer_->GetTransform().SetLocalPosition(_Value);
	}

public:
	// constrcuter destructer
	UISkyBoxActor();
	~UISkyBoxActor();

	// delete Function
	UISkyBoxActor(const UISkyBoxActor& _Other) = delete;
	UISkyBoxActor(UISkyBoxActor&& _Other) noexcept = delete;
	UISkyBoxActor& operator=(const UISkyBoxActor& _Other) = delete;
	UISkyBoxActor& operator=(UISkyBoxActor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {}

private:
	std::shared_ptr<GameEngineFBXStaticRenderer> StaticRenderer_;
};

