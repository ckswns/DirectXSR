#include "pch.h"
#include "Skeleton.h"
#include "Transform.h"
#include "Texture.h"
#include "Quad.h"
#include "MeshRenderer.h"

Skeleton::Skeleton(Transform* ownerTrans) noexcept
	: _pOwnerTrans(ownerTrans), _fSpeed(5.f), _fMaxDist(10.f)
{	 
}

void Skeleton::Start(void) noexcept
{
	_pTrans = static_cast<Transform*>(GetGameObject()->GetTransform());
	_pTexture = new Texture();
	_pTexture->Init(D3D9DEVICE->GetDevice(), "Asset/Player/Skeleton.png");

	Quad* quad = new Quad(0, 0);
	MeshRenderer* mr = new MeshRenderer(D3D9DEVICE->GetDevice(), quad);

	//�ؽ�ó ����
	//mr->GetMaterialPTR()->SetTextures(_pTexture);
//	GetGameObject()->AddComponent(mr);

	//���õ� ��ü ��ġ 
	//���̷��� ���� �ִϸ��̼�
}

void Skeleton::FixedUpdate(float fElapsedTime) noexcept
{
	//�÷��̾�� �Ÿ�Ȯ��
	D3DXVECTOR3 vDir = _pOwnerTrans->GetWorldPosition() - _pTrans->GetWorldPosition();
	if (D3DXVec3Length(&vDir) >= 10.f)
	{
		//���� �־��� ��� �ֺ����� �����̵� 
		float fX = CE_MATH::Random(-3,3) + _pOwnerTrans->GetWorldPosition().x;
		float fZ = CE_MATH::Random(-3,3) + _pOwnerTrans->GetWorldPosition().z;

		_pTrans->SetWorldPosition(fX, _pOwnerTrans->GetWorldPosition().y, fZ);
	}

	//���ƴٴ�
	//���� �߰� �� ����(���϶����� ����)

}
