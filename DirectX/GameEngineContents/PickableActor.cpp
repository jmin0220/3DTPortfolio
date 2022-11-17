#include "PreCompile.h"
#include "PickableActor.h"
#include <GameEngineCore/CoreMinimal.h>

#include "ActorPicker.h"

std::shared_ptr<GameEngineCollision> PickableActor::CurPicking_Collision;

PickableActor::PickableActor()
{

}

PickableActor::~PickableActor() 
{
}

void PickableActor::Start()
{

}

void PickableActor::Update(float _DeltaTime)
{
	CheckPickingRay();

	CheckSelected();
}


// ActorPicker�� �� �浹�߾�� �˷���
void PickableActor::CheckPickingRay()
{
	if (nullptr == Collision_Picking_)
	{
		MsgBoxAssert("�� �����Ϳ� ���Ϳ� ��ŷ�� �ݸ����� �������� �ʾҽ��ϴ�");
	}

	// �浹������ PickedActors��Ʈ�� �߰�
	bool Pickable = Collision_Picking_->IsCollision(CollisionType::CT_OBB, CollisionGroup::Ray, CollisionType::CT_OBB,
		[=](std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
		{


			ActorPicker::PickedActors.insert(std::dynamic_pointer_cast<PickableActor>(shared_from_this()));

			return CollisionReturn::ContinueCheck;
		});

	// �浹�������� PickedActors��Ʈ ���� ����
	if (false == Pickable)
	{
		ActorPicker::PickedActors.erase(std::dynamic_pointer_cast<PickableActor>(shared_from_this()));
	}
}

void PickableActor::CheckSelected()
{
	// ���õ� ���ʹ� Axis�ݸ����� Ȱ��ȭ�ϰ� ��ŷ �ݸ����� ��Ȱ��ȭ
	if (shared_from_this() == std::dynamic_pointer_cast<GameEngineUpdateObject>(ActorPicker::SelectedActor))
	{
		Collision_Picking_->Off();
	}
	else
	{
		Collision_Picking_->On();
	}
}

void PickableActor::SetStaticMesh(const std::string& _FBX, const std::string& _Texture)
{
	IsAxis_ = false;

	FBXRenderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	FBXRenderer_->SetFBXMesh(_FBX, "Texture");

	// �޽� ������ ũ�� �ް� ������ ���� ����ũ��
	float4 FBXScale = FBXRenderer_->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	//float4 Ratio(SIZE_MAGNIFICATION_RATIO * 0.25f);

	// ��ŷ�� �ݸ���
	float4 CollisionScale = FBXScale * 25;
	Collision_Picking_ = CreateComponent<GameEngineCollision>();
	Collision_Picking_->GetTransform().SetLocalScale(CollisionScale);
	Collision_Picking_->SetDebugSetting(CollisionType::CT_OBB, float4(0.5f, 0.0f, 0.0f, 0.25f));
	Collision_Picking_->ChangeOrder(CollisionGroup::Picking);

	// ������
	FBXRenderer_->GetTransform().SetLocalScale(FBXScale);

	// �ǹ�
	FBXRenderer_->GetTransform().SetLocalMove(float4(CollisionScale.x * -0.5f, CollisionScale.y * -0.5f, 0.0f));
	if (0 != _Texture.compare(""))
	{
		std::vector<std::vector<GameEngineRenderUnit>>& UnitSet = FBXRenderer_->GetAllRenderUnit();
		for (std::vector<GameEngineRenderUnit>& Units : UnitSet)
		{
			for (GameEngineRenderUnit& Unit : Units)
			{
				if (Unit.ShaderResources.IsTexture("DiffuseTexture"))
				{
					Unit.ShaderResources.SetTexture("DiffuseTexture", _Texture);
				}
			}
		}
	}
}

void PickableActor::SetCollisionOnly(const float4& _Scale)
{
	// ó�� �������� ��
	if (nullptr == CollisionRenderer_)
	{
		IsAxis_ = false;

		CollisionRenderer_ = CreateComponent<GameEngineTextureRenderer>();
		CollisionRenderer_->SetMesh("Box");
		CollisionRenderer_->SetPipeLine("Color");
		ResultColor_ = float4(0.0f, 1.0f, 0.0f, 0.5f);
		CollisionRenderer_->GetRenderUnit().ShaderResources.SetConstantBufferLink("ResultColor", ResultColor_);

		// ��ŷ�� �ݸ���
		Collision_Picking_ = CreateComponent<GameEngineCollision>();
		Collision_Picking_->GetTransform().SetLocalScale(_Scale);
		Collision_Picking_->SetDebugSetting(CollisionType::CT_OBB, float4(0.5f, 0.0f, 0.0f, 0.25f));
		Collision_Picking_->ChangeOrder(CollisionGroup::Picking);

		// ������
		CollisionRenderer_->GetTransform().SetLocalScale(_Scale);
	}
	// ����� �����ϰ� ���� ��
	else
	{
		CollisionRenderer_->GetTransform().SetLocalScale(_Scale);
		Collision_Picking_->GetTransform().SetLocalScale(_Scale);
	}

}

void PickableActor::SetAxisMove(float4 _Color, float4 _Scale, float4 _MoveDir)
{
	IsAxis_ = true;
	MoveDir_ = _MoveDir;

	Collision_Picking_ = CreateComponent<GameEngineCollision>();
	Collision_Picking_->GetTransform().SetLocalScale(_Scale);
	Collision_Picking_->SetDebugSetting(CollisionType::CT_OBB, _Color);
	Collision_Picking_->ChangeOrder(CollisionGroup::Picking);

}


void PickableActor::SetAxisRot(float4 _Color, float4 _Scale)
{
	IsAxis_ = true;
	//MoveDir_ = _MoveDir;

	Collision_Picking_ = CreateComponent<GameEngineCollision>();
	Collision_Picking_->GetTransform().SetLocalScale(_Scale);
	Collision_Picking_->SetDebugSetting(CollisionType::CT_OBB, _Color);
	Collision_Picking_->ChangeOrder(CollisionGroup::Picking);
}
