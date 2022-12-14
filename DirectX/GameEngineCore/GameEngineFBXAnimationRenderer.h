#pragma once
#include "GameEngineFBXRenderer.h"
#include "GameEngineFBXAnimation.h"
#include "GameEngineRenderingEvent.h"
#include <map>

class FbxExAniData;
class GameEngineFBXMesh;
class GameEngineFBXAnimation;
class GameEngineFBXAnimationRenderer;
class FBXRendererAnimation : public std::enable_shared_from_this<FBXRendererAnimation>
{
public:
	GameEngineFBXAnimationRenderer* ParentRenderer;
	// SetFBX 본을 가지고 있는 매쉬
	std::shared_ptr<GameEngineFBXMesh> Mesh;
	// 애니메이션을 가지고 있는 FBX
	std::shared_ptr<GameEngineFBXAnimation> Aniamtion;
	FbxExAniData* FBXAnimationData;

	UINT Start;
	UINT End;

	GameEngineRenderingEvent Info;

	bool bOnceStart;
	bool bOnceEnd;
	std::function<void(const GameEngineRenderingEvent&)> FrameEvent;
	std::function<void(const GameEngineRenderingEvent&)> EndEvent;
	std::function<void(const GameEngineRenderingEvent&)> StartEvent;
	std::function<void(const GameEngineRenderingEvent&, float)> TimeEvent;

	// Event

	void Init(const std::string_view& _Name, int _Index);
	void Reset();
	void Update(float _DeltaTime);

	//******BlendAnimation추가본*******(선생님 코드엔 없음)
	float CurBlendTime;
	float BlendTime;
	void BlendUpdate(float _DeltaTime);
	//******BlendAnimation추가본*******(선생님 코드엔 없음)

public:
	FBXRendererAnimation() 
		: Start(0)
		, End(0)
		, bOnceStart(false)
		, bOnceEnd(false)
		//******BlendAnimation추가본*******(선생님 코드엔 없음)
		, CurBlendTime(0.0f)
		, BlendTime(0.0f)
		//******BlendAnimation추가본*******(선생님 코드엔 없음)
	{
		int a = 0;
	}

	~FBXRendererAnimation()
	{
		int a = 0;
	}
};

struct AnimationBoneData
{
public:
	int Index = -1;
	float4 Scale;
	float4 RotQuaternion;
	float4 Pos;
	float4 RotEuler;
};


// 설명 :
class GameEngineFBXAnimationRenderer : public GameEngineFBXRenderer
{
	friend FBXRendererAnimation;

public:
	// constrcuter destructer
	GameEngineFBXAnimationRenderer();
	~GameEngineFBXAnimationRenderer();

	// delete Function
	GameEngineFBXAnimationRenderer(const GameEngineFBXAnimationRenderer& _Other) = delete;
	GameEngineFBXAnimationRenderer(GameEngineFBXAnimationRenderer&& _Other) noexcept = delete;
	GameEngineFBXAnimationRenderer& operator=(const GameEngineFBXAnimationRenderer& _Other) = delete;
	GameEngineFBXAnimationRenderer& operator=(GameEngineFBXAnimationRenderer&& _Other) noexcept = delete;

	void SetFBXMesh(const std::string& _Name, std::string _Material) override;
	std::shared_ptr<GameEngineRenderUnit> SetFBXMesh(const std::string& _Name, std::string _Material, size_t _MeshIndex, size_t _SubSetIndex = 0) override;

	void CreateFBXAnimation(const std::string& _AnimationName, const GameEngineRenderingEvent& _Desc, int _Index = 0);


	void ChangeAnimation(const std::string& _AnimationName);

	void Update(float _DeltaTime) override;

	void PauseSwtich();


	//******BlendAnimation추가본*******(선생님 코드엔 없음)
	void OffIsBlending()
	{
		IsBlending = false;
	}
	//******BlendAnimation추가본*******(선생님 코드엔 없음)

	// 애니메이션 바인드
	// 시작 프레임에 들어온다.
	void AnimationBindStart(const std::string& _AnimationName, std::function<void(const GameEngineRenderingEvent&)> _Function)
	{
		std::string Name = GameEngineString::ToUpperReturn(_AnimationName);

		if (Animations.end() == Animations.find(Name))
		{
			MsgBoxAssert("존재하지 않는 애니메이션으로 체인지 하려고 했습니다.");
			return;
		}

		Animations[Name]->StartEvent = _Function;
	}
	// 끝나는 프레임에 들어온다
	void AnimationBindEnd(const std::string& _AnimationName, std::function<void(const GameEngineRenderingEvent&)> _Function)
	{
		std::string Name = GameEngineString::ToUpperReturn(_AnimationName);

		if (Animations.end() == Animations.find(Name))
		{
			MsgBoxAssert("존재하지 않는 애니메이션으로 체인지 하려고 했습니다.");
			return;
		}

		Animations[Name]->EndEvent = _Function;
	}
	// 프레임이 바뀔때마다 들어온다
	void AnimationBindFrame(const std::string& _AnimationName, std::function<void(const GameEngineRenderingEvent&)> _Function)
	{
		std::string Name = GameEngineString::ToUpperReturn(_AnimationName);

		if (Animations.end() == Animations.find(Name))
		{
			MsgBoxAssert("존재하지 않는 애니메이션으로 체인지 하려고 했습니다.");
			return;
		}

		Animations[Name]->FrameEvent = _Function;
	}
	// Update
	void AnimationBindTime(const std::string& _AnimationName, std::function<void(const GameEngineRenderingEvent&, float)> _Function)
	{
		std::string Name = GameEngineString::ToUpperReturn(_AnimationName);

		if (Animations.end() == Animations.find(Name))
		{
			MsgBoxAssert("존재하지 않는 애니메이션으로 체인지 하려고 했습니다.");
			return;
		}

		Animations[Name]->TimeEvent = _Function;
	}
	
	//******bOnceEnd 강제 조정을 위한 추가 코드*******(선생님 코드엔 없음)
	inline std::shared_ptr<FBXRendererAnimation> GetCurAni()
	{
		return CurAnimation;
	}
	//******bOnceEnd 강제 조정을 위한 추가 코드*******(선생님 코드엔 없음)

protected:

private:
	bool Pause;

	std::map<std::string, std::shared_ptr<FBXRendererAnimation>> Animations;
	std::shared_ptr<FBXRendererAnimation> CurAnimation;

	std::map<size_t, std::vector<float4x4>> AnimationBoneMatrixs;
	// std::map<size_t, std::vector<float4x4>> PrevAnimationBoneMatrixs;

	std::map<size_t, std::vector<AnimationBoneData>> AnimationBoneDatas;

	//******BlendAnimation추가본*******(선생님 코드엔 없음)
	// 이전 애니메이션 정보 -> 애니메이션 블렌딩의 시작점
	std::map<size_t, std::vector<AnimationBoneData>> tmpAnimationBoneDatas;
	bool IsBlending;
	//******BlendAnimation추가본*******(선생님 코드엔 없음)
};

