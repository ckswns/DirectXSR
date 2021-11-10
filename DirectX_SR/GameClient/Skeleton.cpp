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

	//텍스처 셋팅
	//mr->GetMaterialPTR()->SetTextures(_pTexture);
//	GetGameObject()->AddComponent(mr);

	//선택된 시체 위치 
	//스켈레톤 생성 애니메이션
}

void Skeleton::FixedUpdate(float fElapsedTime) noexcept
{
	//플레이어와 거리확인
	D3DXVECTOR3 vDir = _pOwnerTrans->GetWorldPosition() - _pTrans->GetWorldPosition();
	if (D3DXVec3Length(&vDir) >= 10.f)
	{
		//많이 멀어진 경우 주변으로 순간이동 
		float fX = CE_MATH::Random(-3,3) + _pOwnerTrans->GetWorldPosition().x;
		float fZ = CE_MATH::Random(-3,3) + _pOwnerTrans->GetWorldPosition().z;

		_pTrans->SetWorldPosition(fX, _pOwnerTrans->GetWorldPosition().y, fZ);
	}

	//돌아다님
	//몬스터 발견 시 공격(죽일때까지 공격)

}
