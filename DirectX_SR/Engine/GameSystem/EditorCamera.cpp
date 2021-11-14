#include "pch.h"
#include "EditorCamera.h"
#include "Transform.h"
#include "Camera.h"
#include "ManagerDef.h"
#include "Light.h"
#include "CEMath.h"
#include "Collider.h"
namespace ce
{
	EditorCamera::EditorCamera(HWND hWnd, float velocity) noexcept :
		_ptPrevMousePos(),
		_hWnd(hWnd),
		_velocity(velocity)
	{

	}

	void EditorCamera::Start(void) noexcept
	{
#ifdef __USE_FMOD__
		gameObject->AddComponent(new Camera(D3D9DEVICE->GetDevice(), Camera::Type::PERSPECTIVE, Camera::ClearOption::SKYBOX, ASSETMANAGER->GetTextureData("Asset\\SkyBox\\Night1.dds")));
		D3DCOLORVALUE c;
		c.a = 1;
		c.r = 1;
		c.g = 1;
		c.b = 1;
		gameObject->AddComponent(new Light(Light::Type::POINT, D3D9DEVICE->GetDevice(), c, 20, 0, 0, 0.02f));
		gameObject->AddComponent(new Light(Light::Type::POINT, D3D9DEVICE->GetDevice(), c, 100, 2.f));
		GetCursorPos(&_ptPrevMousePos);
#else
		gameObject->AddComponent(new Camera(D3D9DEVICE->GetDevice()));
		D3DCOLORVALUE c;
		c.a = 1;
		c.r = 1;
		c.g = 1;
		c.b = 1;
		gameObject->AddComponent(new Light(Light::Type::POINT, D3D9DEVICE->GetDevice(), c, 20, 0, 0, 0.02f));
		gameObject->AddComponent(new Light(Light::Type::POINT, D3D9DEVICE->GetDevice(), c, 100, 2.f));
		GetCursorPos(&_ptPrevMousePos);
#endif
	}

	void EditorCamera::Update(float fElapsedTime) noexcept
	{
		D3DXVECTOR3 foward = transform->GetForward();
		D3DXVECTOR3	right = transform->GetRight();
		D3DXVECTOR3 up = transform->GetUp();

		D3DXVec3Normalize(&foward, &foward);
		D3DXVec3Normalize(&right, &right);
		D3DXVec3Normalize(&up, &up);

		if (INPUT->GetKeyStay('A') || INPUT->GetKeyStay('a'))
		{
			transform->SetWorldPosition(transform->GetWorldPosition() + (right * -10 * fElapsedTime));
		}

		if (INPUT->GetKeyStay('D') || INPUT->GetKeyStay('d'))
		{
			transform->SetWorldPosition(transform->GetWorldPosition() + (right * 10 * fElapsedTime));
		}

		if (INPUT->GetKeyStay('W') || INPUT->GetKeyStay('w'))
		{
			transform->SetWorldPosition(transform->GetWorldPosition() + (foward * 10 * fElapsedTime));
		}

		if (INPUT->GetKeyStay('S') || INPUT->GetKeyStay('s'))
		{
			transform->SetWorldPosition(transform->GetWorldPosition() - (foward * 10 * fElapsedTime));
		}

		if (INPUT->GetKeyDown(VK_TAB))
		{
			if (_bWireFrame == false)
				D3D9DEVICE->GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
			else
				D3D9DEVICE->GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

			_bWireFrame = !_bWireFrame;
		}

		if (INPUT->GetKeyDown(VK_RBUTTON))
		{
			_bMBRightDown = true;
			_bMBMiddleDown = false;
			GetCursorPos(&_ptPrevMousePos);
		}

		else if (INPUT->GetKeyDown(VK_MBUTTON))
		{
			_bMBMiddleDown = true;
			_bMBRightDown = false;
			GetCursorPos(&_ptPrevMousePos);
		}

		if (INPUT->GetKeyStay(VK_RBUTTON) && _bMBRightDown)
		{
			POINT pt;
			GetCursorPos(&pt);

			int dx = pt.x - _ptPrevMousePos.x;
			int dy = pt.y - _ptPrevMousePos.y;

			transform->Rotate(dy * fElapsedTime * _velocity, dx * fElapsedTime * _velocity, 0);

			_ptPrevMousePos = pt;
		}
		else
		{
			_bMBRightDown = false;
		}

		//if (INPUT->GetKeyStay(VK_MBUTTON) && _bMBMiddleDown)
		//{
		//	POINT pt;
		//	POINT prev = _ptPrevMousePos;
		//	POINT diff;

		//	GetCursorPos(&pt);

		//	_ptPrevMousePos = pt;

		//	//ScreenToClient(_hWnd, &pt);
		//	//ScreenToClient(_hWnd, &prev);

		//	diff.x = pt.x - prev.x;
		//	diff.y = pt.y - prev.y;

		//	transform->SetWorldPosition(transform->GetWorldPosition() + (right * -diff.x * fElapsedTime));
		//	transform->SetWorldPosition(transform->GetWorldPosition() + (up * diff.y *  fElapsedTime));
		//}
		//else
		//{
		//	_bMBMiddleDown = false;
		//}
	}

	//void EditorCamera::OnCollisionEnter(Collider* mine, Collider* other) noexcept
	//{
	//	other->GetGameObject()->Destroy();
	//}

}