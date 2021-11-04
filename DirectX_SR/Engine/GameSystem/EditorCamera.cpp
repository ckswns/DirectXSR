#include "pch.h"
#include "EditorCamera.h"
#include "Transform.h"
#include "Camera.h"
#include "ManagerDef.h"
#include "Light.h"

namespace ce
{
	EditorCamera::EditorCamera(HWND hWnd) noexcept :
		_ptPrevMousePos(),
		_hWnd(hWnd)
	{
		_eLayer = GameObjectLayer::OBJECT;
	}

	bool EditorCamera::Init(void) noexcept
	{
		AddComponent(new Camera(this, D3D9DEVICE->GetDevice()));
		D3DCOLORVALUE c;
		c.a = 1;
		c.r = 1;
		c.g = 1;
		c.b = 1;
		AddComponent(new Light(this, Light::Type::SPOT, D3D9DEVICE->GetDevice(), c, 1000, 0.01f, D3DX_PI / 16, D3DX_PI / 8, 12.0f));
		GetCursorPos(&_ptPrevMousePos);
		_pTransform = GetTransform();
		return true;
	}

	void EditorCamera::Update(float fElapsedTime) noexcept
	{
		D3DXVECTOR3 foward = _pTransform->GetForward();
		D3DXVECTOR3	right = _pTransform->GetRight();

		D3DXVec3Normalize(&foward, &foward);
		D3DXVec3Normalize(&right, &right);

		if (INPUT->GetKeyStay('A') || INPUT->GetKeyStay('a'))
		{
			_pTransform->SetWorldPosition(_pTransform->GetWorldPosition() + (right * -10 * fElapsedTime));
		}

		if (INPUT->GetKeyStay('D') || INPUT->GetKeyStay('d'))
		{
			_pTransform->SetWorldPosition(_pTransform->GetWorldPosition() + (right * 10 * fElapsedTime));
		}

		if (INPUT->GetKeyStay('W') || INPUT->GetKeyStay('w'))
		{
			_pTransform->SetWorldPosition(_pTransform->GetWorldPosition() + (foward * 10 * fElapsedTime));
		}

		if (INPUT->GetKeyStay('S') || INPUT->GetKeyStay('s'))
		{
			_pTransform->SetWorldPosition(_pTransform->GetWorldPosition() - (foward * 10 * fElapsedTime));
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
			GetCursorPos(&_ptPrevMousePos);
		}

		else if (INPUT->GetKeyStay(VK_RBUTTON))
		{
			POINT pt;
			GetCursorPos(&pt);

			int dx = pt.x - _ptPrevMousePos.x;
			int dy = pt.y - _ptPrevMousePos.y;

			_pTransform->Rotate(dy * fElapsedTime * 0.5f, dx * fElapsedTime * 0.5f, 0);

			_ptPrevMousePos = pt;
		}
	}

	void EditorCamera::Render(void) noexcept
	{

	}

	void EditorCamera::Release(void) noexcept
	{

	}
}