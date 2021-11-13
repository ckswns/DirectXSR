#include "pch.h"
#include "TargetCamera.h"
#include "Transform.h"
#include "Camera.h"
#include "Light.h"

TargetCamera::TargetCamera(Transform* target) noexcept
	:_pTargetTrans(target), _fDist(-5), _fHeight(5)
{
}

void TargetCamera::Start(void) noexcept
{
	_pTrans = gameObject->GetTransform();

	gameObject->AddComponent(new Camera(D3D9DEVICE->GetDevice()));
	
	_pTrans->SetLocalPosition(0, _fHeight, _fDist);

	D3DXVECTOR3 vLook(0, 0, 1);
	D3DXVECTOR3 vDir = _pTargetTrans->GetWorldPosition() - _pTrans->GetWorldPosition();
	D3DXVec3Normalize(&vDir, &vDir);
	float angle = D3DXVec3Dot(&vLook, &vDir);

	_pTrans->SetLocalEulerAngle(angle, 0, 0);

	D3DCOLORVALUE c;
	c.a = 1;
	c.r = 1;
	c.g = 1;
	c.b = 1;
	gameObject->AddComponent(new Light(Light::Type::POINT, D3D9DEVICE->GetDevice(), c, 10));

}

void TargetCamera::Update(float fElapsedTime) noexcept
{
	D3DXVECTOR3 vDir = _pTargetTrans->GetWorldPosition() - _pTrans->GetWorldPosition();
	vDir.y += _fHeight;
	vDir.z += _fDist;

	if (D3DXVec3Length(&vDir) > 0.1f)
	{
		D3DXVec3Normalize(&vDir, &vDir);
		_pTrans->Translate(vDir * fElapsedTime * 6);
	}
}
