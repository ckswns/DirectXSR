#include "pch.h"
#include "MapTool_Cam.h"

MapTool_Cam::MapTool_Cam(LPDIRECT3DDEVICE9& pGraphicDev)
	: m_pGraphicDev(pGraphicDev), _ptPrevMousePos()
{
	_eLayer = GameObjectLayer::OBJECT;
}

MapTool_Cam::~MapTool_Cam(void)
{

}

bool MapTool_Cam::Init(void) noexcept
{
	AddComponent(new Camera(this, m_pGraphicDev));

	GetCursorPos(&_ptPrevMousePos);
	m_pTransform = GetTransform();

	//m_pTransform->SetWorldPosition(0.f, 10.f, -1.f);

	return TRUE;
}

void MapTool_Cam::Update(float fElapsedTime) noexcept
{
	D3DXVECTOR3		vLook = m_pTransform->GetForward();
	D3DXVECTOR3		vRight = m_pTransform->GetRight();

	D3DXVec3Normalize(&vLook, &vLook);
	D3DXVec3Normalize(&vRight, &vRight);

	if (INPUT->GetKeyStay('A') || INPUT->GetKeyStay('a'))
	{
		m_pTransform->SetWorldPosition(m_pTransform->GetWorldPosition() + (vRight * -10 * fElapsedTime));
	}

	if (INPUT->GetKeyStay('D') || INPUT->GetKeyStay('d'))
	{
		m_pTransform->SetWorldPosition(m_pTransform->GetWorldPosition() + (vRight * 10 * fElapsedTime));
	}

	if (INPUT->GetKeyStay('W') || INPUT->GetKeyStay('w'))
	{
		m_pTransform->SetWorldPosition(m_pTransform->GetWorldPosition() + (vLook * 10 * fElapsedTime));
	}

	if (INPUT->GetKeyStay('S') || INPUT->GetKeyStay('s'))
	{
		m_pTransform->SetWorldPosition(m_pTransform->GetWorldPosition() + (vLook * -10 * fElapsedTime));
	}

	if (INPUT->GetKeyDown(VK_TAB))
	{
		if (m_bWireFrame == false)
			D3D9DEVICE->GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		else
			D3D9DEVICE->GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

		m_bWireFrame = !m_bWireFrame;
	}

	if (INPUT->GetKeyDown(VK_RBUTTON))
	{
		GetCursorPos(&_ptPrevMousePos);
	}
	else if (INPUT->GetKeyStay(VK_RBUTTON))
	{
		POINT pt;
		GetCursorPos(&pt);

		int dx = pt.x - _ptPrevMousePos.x;
		int dy = pt.y - _ptPrevMousePos.y;

		m_pTransform->Rotate(dy * fElapsedTime * 5.f, dx * fElapsedTime * 5.f, 0);

		_ptPrevMousePos = pt;
	}
	

}

void MapTool_Cam::Render(void) noexcept
{
}

void MapTool_Cam::Release(void) noexcept
{
}
