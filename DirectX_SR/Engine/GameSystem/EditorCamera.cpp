#include "pch.h"
#include "EditorCamera.h"
#include "Transform.h"
#include "Camera.h"
#include "ManagerDef.h"
#include "Light.h"

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
		gameObject->AddComponent(new Camera(D3D9DEVICE->GetDevice()));
		D3DCOLORVALUE c;
		c.a = 1;
		c.r = 1;
		c.g = 1;
		c.b = 1;
		gameObject->AddComponent(new Light(Light::Type::DIRECTIONAL, D3D9DEVICE->GetDevice(), c, 1000));
		GetCursorPos(&_ptPrevMousePos);
	}

	void EditorCamera::Update(float fElapsedTime) noexcept
	{
		D3DXVECTOR3 foward = transform->GetForward();
		D3DXVECTOR3	right = transform->GetRight();

		D3DXVec3Normalize(&foward, &foward);
		D3DXVec3Normalize(&right, &right);

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
			GetCursorPos(&_ptPrevMousePos);
		}

		else if (INPUT->GetKeyStay(VK_RBUTTON))
		{
			POINT pt;
			GetCursorPos(&pt);

			int dx = pt.x - _ptPrevMousePos.x;
			int dy = pt.y - _ptPrevMousePos.y;

			transform->Rotate(dy * fElapsedTime * _velocity, dx * fElapsedTime * _velocity, 0);

			_ptPrevMousePos = pt;
		}
	}
}