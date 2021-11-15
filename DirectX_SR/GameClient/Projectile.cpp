#include "pch.h"
#include "Projectile.h"
#include "Transform.h"
#include "Spear.h"
#include "SpearTrail.h"
#include "AudioSource.h"
#include "BoxCollider.h"
#include "RigidBody.h"

Projectile::Projectile(D3DXVECTOR3 dir, bool isDir) noexcept
	:_fMaxDist(7.f), _fDist(0), _fSpeed(3.f), _vDir(dir), _bRot(true), _bDir(isDir)
{	__noop;	}

void Projectile::Start(void) noexcept
{
	_pTrans = gameObject->GetTransform();
	gameObject->AddComponent(new BoxCollider(D3DXVECTOR3(0.2f, 0.5f, 0.3)));
	gameObject->AddComponent(new Rigidbody());

	AudioSource* audio = static_cast<AudioSource*>(gameObject->AddComponent(new AudioSource()));
	audio->LoadAudio(ASSETMANAGER->GetAudioAsset("Asset\\Audio\\Player\\bonespear.wav"));
	//audio->SetVolume(0);
	audio->Play();

	DIR eDir = BACK;
	float angle = 0;
	float trailAng = 0;
	if (!_bDir)
	{
		_vDir -= _pTrans->GetWorldPosition();
		_vDir.y = 0;
		D3DXVec3Normalize(&_vDir, &_vDir);

		D3DXVECTOR3 vLook(0, 0, 1);
		angle = D3DXVec3Dot(&vLook, &_vDir);

		// 좌 혹은 후 
		if (CompareFloatAbsoulte(angle, 0) == 0)
			_bRot = false;
		else 
			eDir = BACK;

		angle = acosf(angle);
		trailAng = angle;

		D3DXVECTOR3 vUp(0, 1, 0);
		D3DXVECTOR3 vCross = *D3DXVec3Cross(&vCross, &_vDir, &vLook);
		float dotValue = D3DXVec3Dot(&vCross, &vUp);
		if (dotValue > 0) //left
		{
			if (!_bRot)
				eDir = LEFT;
			trailAng *= -1;
		}
		else  //right
		{
			if (!_bRot)
				eDir = RIGHT;

			angle *= -1;
		}
	}

	_pSpear = GameObject::Instantiate();
	_pSpear->AddComponent(new Spear());
	_pSpear->GetTransform()->SetParent(_pTrans);
	//방향에 따른 회전 값
	_pSpear->GetTransform()->SetLocalEulerAngle(0, 0, angle);

	_pTrails.reserve(3);

	GameObject* pTrail = GameObject::Instantiate();
	pTrail->AddComponent(new SpearTrail(0.3f,eDir));
	pTrail->GetTransform()->SetParent(_pTrans);
	pTrail->GetTransform()->SetLocalPosition(-(_vDir * 0.2f));
	pTrail->GetTransform()->SetLocalScale(0.8, 0.8f, 0);
	if (_bRot)
		pTrail->GetTransform()->SetLocalEulerAngle(0, 0, trailAng);
	_pTrails.push_back(pTrail);

	pTrail = GameObject::Instantiate();
	pTrail->AddComponent(new SpearTrail(0.3f, eDir));
	pTrail->GetTransform()->SetParent(_pTrans);
	pTrail->GetTransform()->SetLocalPosition(-_vDir * 0.4f);
	pTrail->GetTransform()->SetLocalScale(1,1, 0);
	if (_bRot)
		pTrail->GetTransform()->SetLocalEulerAngle(0, 0, trailAng);
	_pTrails.push_back(pTrail);

	pTrail = GameObject::Instantiate();
	pTrail->AddComponent(new SpearTrail(0.3f, eDir));
	pTrail->GetTransform()->SetParent(_pTrans);
	pTrail->GetTransform()->SetLocalPosition(-_vDir * 0.6f);
	pTrail->GetTransform()->SetLocalScale(1.2f,1.2f, 0);
	if (_bRot)
		pTrail->GetTransform()->SetLocalEulerAngle(0, 0, trailAng);
	_pTrails.push_back(pTrail);

	pTrail = GameObject::Instantiate();
	pTrail->AddComponent(new SpearTrail(0.3f, eDir));
	pTrail->GetTransform()->SetParent(_pTrans);
	pTrail->GetTransform()->SetLocalPosition(-_vDir * 0.8f);
	pTrail->GetTransform()->SetLocalScale(1.4f, 1.4f, 0);
	if (_bRot)
		pTrail->GetTransform()->SetLocalEulerAngle(0, 0, trailAng);
	_pTrails.push_back(pTrail);

	pTrail = GameObject::Instantiate();
	pTrail->AddComponent(new SpearTrail(0.3f, eDir));
	pTrail->GetTransform()->SetParent(_pTrans);
	pTrail->GetTransform()->SetLocalPosition(-_vDir);
	pTrail->GetTransform()->SetLocalScale(1.6f, 1.6f, 0);
	if (_bRot)
		pTrail->GetTransform()->SetLocalEulerAngle(0, 0, trailAng);
	_pTrails.push_back(pTrail);
}

void Projectile::Update(float fElapsedTime) noexcept
{
	if (_fDist >= _fMaxDist) 
	{
		gameObject->Destroy();
		_pSpear->Destroy();

		for (size_t i = 0; i < _pTrails.size(); ++i)
		{
			_pTrails[i]->Destroy();
			_pTrails[i] = nullptr;
		}
		_pTrails.clear();
	}
	else
	{
		_fDist += (fElapsedTime * _fSpeed);
		_pTrans->Translate(_vDir * fElapsedTime * _fSpeed);
	}
}

void Projectile::OnCollisionEnter(Collider* mine, Collider* other) noexcept
{
	if (other->GetGameObject()->GetTag() == GameObjectTag::MONSTER)
	{
		//데미지
	}
	else if (other->GetGameObject()->GetTag() == GameObjectTag::OBSTACLE)
	{
		//벽같은거?면 사라짐
		gameObject->Destroy();
		_pSpear->Destroy();

		for (size_t i = 0; i < _pTrails.size(); ++i)
		{
			_pTrails[i]->Destroy();
			_pTrails[i] = nullptr;
		}
		_pTrails.clear();
	}
}
