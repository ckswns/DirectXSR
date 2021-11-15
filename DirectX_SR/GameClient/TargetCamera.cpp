#include "pch.h"
#include "TargetCamera.h"
#include "Transform.h"
#include "Camera.h"
#include "Light.h"
#include "CETween.h"

TargetCamera::TargetCamera(Transform* target) noexcept
	:_pTrans(nullptr), _pTargetTrans(target), _bFPV(false),
	_fTPVDist(-5), _fTPVHeight(5), _fFPVDist(1), _fFPVHeight(0.5f)
{
}

void TargetCamera::Start(void) noexcept
{
	_pTrans = gameObject->GetTransform();

	gameObject->AddComponent(new Camera(D3D9DEVICE->GetDevice()));
	
	_pTrans->SetLocalPosition(0, _fTPVHeight, _fTPVDist);

	D3DXVECTOR3 vLook(0, 0, 1);
	D3DXVECTOR3 vDir = _pTargetTrans->GetWorldPosition() - _pTrans->GetWorldPosition();
	D3DXVec3Normalize(&vDir, &vDir);
	_fAngle = D3DXVec3Dot(&vLook, &vDir);

	_pTrans->SetLocalEulerAngle(_fAngle, 0, 0);

	D3DCOLORVALUE c;
	c.a = 1;
	c.r = 1;
	c.g = 1;
	c.b = 1;
	gameObject->AddComponent(new Light(Light::Type::POINT, D3D9DEVICE->GetDevice(), c, 10));

}

void TargetCamera::Update(float fElapsedTime) noexcept
{
	if (!_bFPV) 
	{
		D3DXVECTOR3 vDir = _pTargetTrans->GetWorldPosition() - _pTrans->GetWorldPosition();
		vDir.y += _fTPVHeight;
		vDir.z += _fTPVDist;

		if (D3DXVec3Length(&vDir) > 0.1f)
		{
			D3DXVec3Normalize(&vDir, &vDir);
			_pTrans->Translate(vDir * fElapsedTime * 6);
		}
	}
	else
	{
		_fDelta +=	fElapsedTime;
		if (_fDelta <= 1)
		{
			float ang = CETween::Lerp(_fAngle, 0, _fDelta, CETween::EaseType::easeInBack);
			_pTrans->SetLocalEulerAngle(ang, 0, 0);
		}

		D3DXVECTOR3 vPos = _pTargetTrans->GetWorldPosition();
		vPos.x -= _pTargetTrans->GetWorldMatrix()._31;
		vPos.y += _fFPVHeight;
		vPos.z -= _pTargetTrans->GetWorldMatrix()._33 * _fFPVDist;

		D3DXVECTOR3 vDir = vPos - _pTrans->GetWorldPosition();

		if (D3DXVec3Length(&vDir) > 0.1f)
		{
			D3DXVec3Normalize(&vDir, &vDir);
			_pTrans->Translate(vDir * fElapsedTime * 6);
		}
	}
}

void TargetCamera::ChangeView()
{
	//3인칭으로 변경
	if (_bFPV)
	{
		_bFPV = false;
		_pTrans->SetLocalEulerAngle(_fAngle, 0, 0);
	}
	else //1인칭으로 변경
	{
		_bFPV = true;
		_fDelta = 0;

		//D3DXVECTOR3 vPos = _pTargetTrans->GetWorldPosition();
		//vPos.y += _fFPVHeight;
		//vPos.z -= _fFPVDist;
		//_pTrans->SetWorldPosition(vPos);
	}
}
