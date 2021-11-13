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

		D3DXMATRIX matView;

		D3DXMatrixLookAtLH(&matView, &world, &look, &up);

		_pDevice->SetTransform(D3DTS_VIEW, &matView);

		D3DXMatrixPerspectiveFovLH(&_matProj, CE_MATH::PI_4, winSize.x / float(winSize.y), 0.1f, 1000.0f);

		_pDevice->SetTransform(D3DTS_PROJECTION, &_matProj);

		_skybox->SetTransform(transform);
	}

	void Camera::LateUpdate(float fElapsedTime) noexcept
	{
		Transform* transform = GetTransform();
		const D3DXVECTOR3& pos = transform->GetWorldPosition();

		D3DXVECTOR3 world = pos;
		D3DXVECTOR3 look = transform->GetForward();
		D3DXVec3Normalize(&look, &look);
		look = world + look;
		D3DXVECTOR3 up = transform->GetUp();

		D3DXMATRIX matView;

		D3DXMatrixLookAtLH(&matView, &world, &look, &up);

		_pDevice->SetTransform(D3DTS_VIEW, &matView);
	}

	void Camera::Release(void) noexcept
	{
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
}