#include "pch.h"
#include "Projectile.h"
#include "Transform.h"
#include "Spear.h"
#include "SpearTrail.h"

Projectile::Projectile(D3DXVECTOR3 dir) noexcept
	:_fMaxDist(7.f), _fDist(0), _fSpeed(3.f), _vDir(dir)
{	__noop;	}

void Projectile::Start(void) noexcept
{
	_pTrans = GetGameObject()->GetTransform();
	_vDir -= _pTrans->GetWorldPosition();
	_vDir.y = 0;
	D3DXVec3Normalize(&_vDir, &_vDir);

	D3DXVECTOR3 vLook(0, 0, 1);
	float angle = D3DXVec3Dot(&vLook, &_vDir);
	angle = acosf(angle);

	D3DXVECTOR3 vUp(0, 1, 0);
	D3DXVECTOR3 vCross = *D3DXVec3Cross(&vCross, &_vDir, &vLook);
	float dotValue = D3DXVec3Dot(&vCross, &vUp);
	if (dotValue < 0) angle *= -1;

	GameObject* pSpear = GameObject::Instantiate();
	pSpear->AddComponent(new Spear());
	pSpear->GetTransform()->SetParent(GetGameObject()->GetTransform());
	//방향에 따른 회전 값
	pSpear->GetTransform()->SetLocalEulerAngle(0, 0, angle);

	GameObject* pTrail = GameObject::Instantiate();
	pTrail->AddComponent(new SpearTrail(0.3f));
	pTrail->GetTransform()->SetParent(_pTrans);
	pTrail->GetTransform()->SetLocalPosition(-(_vDir * 0.1f));
	pTrail->GetTransform()->SetLocalEulerAngle(0, 0, angle);

	pTrail = GameObject::Instantiate();
	pTrail->AddComponent(new SpearTrail(0.3f));
	pTrail->GetTransform()->SetParent(_pTrans);
	pTrail->GetTransform()->SetLocalPosition(-_vDir * 0.5f);
	pTrail->GetTransform()->SetLocalScale(1.2f,1.2f,1.2f);
	pTrail->GetTransform()->SetLocalEulerAngle(0, 0,angle);
}

void Projectile::Update(float fElapsedTime) noexcept
{
	if (_fDist >= _fMaxDist)
		gameObject->Destroy(gameObject);
	else
	{
		_fDist += (fElapsedTime * _fSpeed);
		_pTrans->Translate(_vDir * fElapsedTime * _fSpeed);
	}
}
