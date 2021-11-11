#include "pch.h"
#include "InputHandler.h"
#include "AttackCommand.h"
#include "MoveCommand.h"
#include "Terrain.h"

InputHandler::InputHandler(GameObject* player, Terrain* terrain) noexcept
	:_pPlayer(player), _pTerrain(terrain)
{
}

void InputHandler::Start(void) noexcept
{

	_pLBCommand = new AttackCommand();
	_pRBCommand = new AttackCommand();
	_pMoveCommand = new MoveCommand();
}

void InputHandler::Update(float fElapsedTime) noexcept
{
	if (INPUT->GetKeyStay(KEY_LBUTTON))
	{
		//���콺 ��ŷ 
		//�ٴ��� ��� �̵�
		_pMoveCommand->Execute(_pPlayer, MousePicking());
		//�ƴ� ��� Ŀ�ǵ� 
//		_pLBCommand->Execute(_pPlayer, MousePicking());
	}
	else if (INPUT->GetKeyStay(KEY_RBUTTON))
	{
	//	_pMoveCommand->Execute(_pPlayer, MousePicking());
	}


}

D3DXVECTOR3 InputHandler::MousePicking()
{
	POINT		ptMouse{};

	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	D3DXVECTOR3		vMousePos;

	D3DVIEWPORT9		ViewPort;
	ZeroMemory(&ViewPort, sizeof(D3DVIEWPORT9));

	D3D9DEVICE->GetDevice()->GetViewport(&ViewPort);

	// ������ ��ǥ�� ���¿� �ִ� ���콺�� ���� ��ǥ�� ��ȯ
	vMousePos.x = ptMouse.x / (ViewPort.Width * 0.5f) - 1.f;
	vMousePos.y = ptMouse.y / -(ViewPort.Height * 0.5f) + 1.f;
	vMousePos.z = 0.f;

	// ���� ��ǥ�� �� �����̽� ��ǥ�� ��ȯ
	D3DXMATRIX		matProj;
	D3D9DEVICE->GetDevice()->GetTransform(D3DTS_PROJECTION, &matProj);
	D3DXMatrixInverse(&matProj, NULL, &matProj);
	D3DXVec3TransformCoord(&vMousePos, &vMousePos, &matProj);

	// �佺���̽� ��ǥ�� ���� ��ǥ�� ��ȯ
	D3DXVECTOR3		vRayPos, vRayDir;

	vRayPos = D3DXVECTOR3(0.f, 0.f, 0.f);
	vRayDir = vMousePos - vRayPos;

	D3DXMATRIX		matView;
	D3D9DEVICE->GetDevice()->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matView, NULL, &matView);

	D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matView);
	D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matView);

	// ���� ������ ��ǥ�� ���� �����̽� ��ǥ�� ��ȯ
	/*D3DXMATRIX		matWorld;
	pTerrainTransCom->Get_WorldMatrix(&matWorld);
	D3DXMatrixInverse(&matWorld, NULL, &matWorld);

	D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matWorld);
	D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matWorld);*/

	unsigned long		dwCntX = _pTerrain->Get_VtxCntX();
	unsigned long		dwCntZ = _pTerrain->Get_VtxCntZ();
	const	 D3DXVECTOR3* pTerrainVtxPos = _pTerrain->Get_VtxPos();

	unsigned long 	dwVtxIdx[3];
	float	fU, fV, fDist;

	for (unsigned long i = 0; i < dwCntZ - 1; ++i)
	{
		for (unsigned long j = 0; j < dwCntX - 1; ++j)
		{
			unsigned long	dwIndex = i * dwCntX + j;

			// ������ ��
			dwVtxIdx[0] = dwIndex + dwCntX;
			dwVtxIdx[1] = dwIndex + dwCntX + 1;
			dwVtxIdx[2] = dwIndex + 1;

			if (D3DXIntersectTri(&pTerrainVtxPos[dwVtxIdx[1]],
				&pTerrainVtxPos[dwVtxIdx[0]],
				&pTerrainVtxPos[dwVtxIdx[2]],
				&vRayPos, &vRayDir,
				&fU, &fV, &fDist))
			{
				return D3DXVECTOR3(pTerrainVtxPos[dwVtxIdx[1]].x + (pTerrainVtxPos[dwVtxIdx[0]].x - pTerrainVtxPos[dwVtxIdx[1]].x) * fU,
					0.f,
					pTerrainVtxPos[dwVtxIdx[1]].z + (pTerrainVtxPos[dwVtxIdx[2]].z - pTerrainVtxPos[dwVtxIdx[1]].z) * fV);
			}

			// ���� �Ʒ�
			dwVtxIdx[0] = dwIndex + dwCntX;
			dwVtxIdx[1] = dwIndex + 1;
			dwVtxIdx[2] = dwIndex;

			if (D3DXIntersectTri(&pTerrainVtxPos[dwVtxIdx[2]],
				&pTerrainVtxPos[dwVtxIdx[1]],
				&pTerrainVtxPos[dwVtxIdx[0]],
				&vRayPos, &vRayDir,
				&fU, &fV, &fDist))
			{
				return D3DXVECTOR3(pTerrainVtxPos[dwVtxIdx[2]].x + (pTerrainVtxPos[dwVtxIdx[1]].x - pTerrainVtxPos[dwVtxIdx[2]].x) * fU,
					0.f,
					pTerrainVtxPos[dwVtxIdx[2]].z + (pTerrainVtxPos[dwVtxIdx[0]].z - pTerrainVtxPos[dwVtxIdx[1]].z) * fV);
			}
		}
	}

	return D3DXVECTOR3(0.f, 0.f, 0.f);
}
