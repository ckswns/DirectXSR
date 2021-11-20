#include "pch.h"
#include "Camera.h"
#include "Transform.h"
#include "GameObject.h"
#include "Assertion.h"
#include "D3D9Device.h"
#include "../Base/CEMath.h"
#include "SkyBox.h"

namespace ce
{
	Camera* Camera::mainCamera = nullptr;

	Camera::Camera(LPDIRECT3DDEVICE9 pDevice, Type type, ClearOption clearOption, Texture* skyboxTex) noexcept :
		Component(COMPONENT_ID::CAMERA),
		_clearOption(clearOption),
		_pDevice(pDevice)
	{
		_skybox = new SkyBox(_pDevice);
		_skybox->SetTexture(skyboxTex);
	}

	void Camera::Init(void) noexcept
	{
		if (mainCamera == nullptr)
			mainCamera = this;
		else
			CE_ASSERT("ckswns", "현재 다중카메라 미지원하므로 코드 수정바랍니다");

		if (_pDevice == nullptr)
			CE_ASSERT("ckswns", "Device객체는 nullptr일 수 없습니다.");

		Transform* transform = _owner->GetTransform();
		POINT winSize = D3D9Device::Instance()->GetWindowSize();

		const D3DXVECTOR3& world = transform->GetWorldPosition();
		D3DXVECTOR3 look = transform->GetForward();
		D3DXVec3Normalize(&look, &look);
		look = world + look;
		D3DXVECTOR3 up = transform->GetUp();

		D3DXMatrixLookAtLH(&_matView, &world, &look, &up);

		_pDevice->SetTransform(D3DTS_VIEW, &_matView);

		D3DXMatrixPerspectiveFovLH(&_matProj, CE_MATH::PI_4, winSize.x / float(winSize.y), 0.1f, 1000.0f);

		_pDevice->SetTransform(D3DTS_PROJECTION, &_matProj);

		_skybox->SetTransform(transform);
		_owner->SetLayer(GameObjectLayer::SKYBOX);
	}

	void Camera::LateUpdate(float fElapsedTime) noexcept
	{
		if (mainCamera != this)
			return;

		Transform* transform = GetTransform();
		const D3DXVECTOR3& pos = transform->GetWorldPosition();

		D3DXVECTOR3 world = pos;
		D3DXVECTOR3 look = transform->GetForward();
		D3DXVec3Normalize(&look, &look);
		look = world + look;
		D3DXVECTOR3 up = transform->GetUp();

		D3DXMatrixLookAtLH(&_matView, &world, &look, &up);

		_pDevice->SetTransform(D3DTS_VIEW, &_matView);
	}

	void Camera::Release(void) noexcept
	{
		if(mainCamera == this)
			mainCamera = nullptr;

		if (_skybox)
		{
			_skybox->Release();
			delete _skybox;
			_skybox = nullptr;
		}
	}

	void Camera::Render(void) noexcept
	{
		if(_skybox && _clearOption == ClearOption::SKYBOX)
			_skybox->Render();
	}

	void Camera::SetSkyBoxTexture(Texture* tex) noexcept
	{
		if (_skybox == nullptr)
			return;
		_skybox->SetTexture(tex);
	}

	Transform* Camera::GetTransform(void) noexcept
	{
		return _owner->GetTransform();
	}

	Ray Camera::ScreenPointToRay(D3DXVECTOR3 point) noexcept
	{
		Ray ray;
		D3DVIEWPORT9		ViewPort;
		ZeroMemory(&ViewPort, sizeof(D3DVIEWPORT9));

		D3D9DEVICE->GetDevice()->GetViewport(&ViewPort);

		// 윈도우 좌표에 상태에 있는 마우스를 투영 좌표로 변환
		point.x = point.x / (ViewPort.Width * 0.5f) - 1.f;
		point.y = point.y / -(ViewPort.Height * 0.5f) + 1.f;
		point.z = 0.f;

		// 투영 좌표를 뷰 스페이스 좌표로 변환
		D3DXMATRIX		matProj;
		D3D9DEVICE->GetDevice()->GetTransform(D3DTS_PROJECTION, &matProj);
		D3DXMatrixInverse(&matProj, NULL, &matProj);
		D3DXVec3TransformCoord(&point, &point, &matProj);

		// 뷰스페이스 좌표를 월드 좌표로 변환
		D3DXVECTOR3		vRayPos, vRayDir;

		vRayPos = D3DXVECTOR3(0.f, 0.f, 0.f);
		vRayDir = point - vRayPos;

		D3DXMATRIX		matView;
		D3D9DEVICE->GetDevice()->GetTransform(D3DTS_VIEW, &matView);
		D3DXMatrixInverse(&matView, NULL, &matView);

		D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matView);
		D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matView);

		ray._origin = vRayPos;
		ray._dir = vRayDir;
		ray._length = 1000;

		return ray;
	}
}