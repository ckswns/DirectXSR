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

	gameObject->AddComponent(new Camera(D3D9DEVICE->GetDevice(), Camera::Type::PERSPECTIVE, Camera::ClearOption::SKYBOX, ASSETMANAGER->GetTextureData("Asset\\SkyBox\\Night1.dds")));
	
	_pTrans->SetLocalPosition(0, _fTPVHeight, _fTPVDist);

	D3DXVECTOR3 vLook(0, 0, 1);
	D3DXVECTOR3 vDir = _pTargetTrans->GetWorldPosition() - _pTrans->GetWorldPosition();
	D3DXVec3Normalize(&vDir, &vDir);
	_fAngle = D3DXVec3Dot(&vLook, &vDir);

	_pTrans->SetLocalEulerAngle(_fAngle, 0, 0);
}

void TargetCamera::Update(float fElapsedTime) noexcept
{
	
}

void TargetCamera::FixedUpdate(float fElapsedTime) noexcept
{
	if (!_bFPV)
	{
		if (_bDoLerp == false)
		{
			D3DXVECTOR3 vDir = _pTargetTrans->GetWorldPosition() - _pTrans->GetWorldPosition();
			vDir.y += _fTPVHeight;
			vDir.z += _fTPVDist;

			float length = D3DXVec3Length(&vDir);

			if (length > 1.f)
			{
				_srcPos = transform->GetWorldPosition();
				_destPos = _pTargetTrans->GetWorldPosition();
				_destPos.y += _fTPVHeight;
				_destPos.z += _fTPVDist;
				_bDoLerp = true;
				_currentLerpTime = 0;
			}
			else
			{
				D3DXVECTOR3 targetPos = _pTargetTrans->GetWorldPosition();
				targetPos.y += _fTPVHeight;
				targetPos.z += _fTPVDist;
				transform->SetWorldPosition(targetPos);
			}
		}
		else
		{
			D3DXVECTOR3 targetPos = _pTargetTrans->GetWorldPosition();
			targetPos.y += _fTPVHeight;
			targetPos.z += _fTPVDist;

			_currentLerpTime += fElapsedTime;
			if (_currentLerpTime > 1)
			{
				_currentLerpTime = 1;
				_bDoLerp = false;
			}
			transform->SetWorldPosition(
				CETween::Lerp(_srcPos.x, targetPos.x, _currentLerpTime, CETween::EaseType::easeOutBack),
				CETween::Lerp(_srcPos.y, targetPos.y, _currentLerpTime, CETween::EaseType::easeOutBack),
				CETween::Lerp(_srcPos.z, targetPos.z, _currentLerpTime, CETween::EaseType::easeOutBack)
				);
		}
	}
	else
	{
		if (_fDelta <= 1)
		{
			_fDelta += fElapsedTime;
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
