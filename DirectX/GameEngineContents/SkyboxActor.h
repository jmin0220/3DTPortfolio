#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 :
class SkyboxActor : public GameEngineActor
{
public:
	void SetSkyTexture(const std::string_view& _TextureName)
	{
		// 텍스쳐 씌워주기
		std::vector<std::vector<GameEngineRenderUnit>>& UnitSet = StaticRenderer_->GetAllRenderUnit();
		for (std::vector<GameEngineRenderUnit>& Units : UnitSet)
		{
			for (GameEngineRenderUnit& Unit : Units)
			{
				if (true == Unit.ShaderResources.IsTexture("DiffuseTexture"))
				{
					Unit.ShaderResources.SetTexture("DiffuseTexture", _TextureName.data());
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
	SkyboxActor();
	~SkyboxActor();

	// delete Function
	SkyboxActor(const SkyboxActor& _Other) = delete;
	SkyboxActor(SkyboxActor&& _Other) noexcept = delete;
	SkyboxActor& operator=(const SkyboxActor& _Other) = delete;
	SkyboxActor& operator=(SkyboxActor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {}

private:
	std::shared_ptr<GameEngineFBXStaticRenderer> StaticRenderer_;
};

