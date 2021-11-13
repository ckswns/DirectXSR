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
	D3DXVec3Normalize(&_vDir, &_vDir);

	//D3DXVECTOR3 spear(0, 0, -1);
	//float angle = D3DXVec3Dot(&spear, &_vDir);

	GameObject* pSpear = GameObject::Instantiate();
	pSpear->AddComponent(new Spear());
	pSpear->GetTransform()->SetParent(GetGameObject()->GetTransform());
	//방향에 따른 회전 값
	pSpear->GetTransform()->SetLocalEulerAngle(0, 0,-80);

	GameObject* pTrail = GameObject::Instantiate();
	pTrail->AddComponent(new SpearTrail(0.3f));
	pTrail->GetTransform()->SetParent(_pTrans);
	pTrail->GetTransform()->SetLocalPosition(-(_vDir * 0.5f));
	pTrail->GetTransform()->SetLocalEulerAngle(0, 0, -80);

	pTrail = GameObject::Instantiate();
	pTrail->AddComponent(new SpearTrail(0.3f));
	pTrail->GetTransform()->SetParent(_pTrans);
	pTrail->GetTransform()->SetLocalPosition(-_vDir);
	pTrail->GetTransform()->SetLocalScale(1.5f,1.5f,1.5f);
	pTrail->GetTransform()->SetLocalEulerAngle(0, 0,-80);
}

void Projectile::Update(float fElapsedTime) noexcept
{
	if (_fDist >= _fMaxDist)
		gameObject->Destroy(GetGameObject());
	else
	{
		_fDist += (fElapsedTime * _fSpeed);
		_pTrans->Translate(_vDir * fElapsedTime * _fSpeed);
	}
}
