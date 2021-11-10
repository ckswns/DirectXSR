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
		//마우스 피킹 
		//바닥인 경우 이동
		_pMoveCommand->Execute(_pPlayer, MousePicking());
		//아닌 경우 커맨드 
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

	// 윈도우 좌표에 상태에 있는 마우스를 투영 좌표로 변환
	vMousePos.x = ptMouse.x / (ViewPort.Width * 0.5f) - 1.f;
	vMousePos.y = ptMouse.y / -(ViewPort.Height * 0.5f) + 1.f;
	vMousePos.z = 0.f;

	// 투영 좌표를 뷰 스페이스 좌표로 변환
	D3DXMATRIX		matProj;
	D3D9DEVICE->GetDevice()->GetTransform(D3DTS_PROJECTION, &matProj);
	D3DXMatrixInverse(&matProj, NULL, &matProj);
	D3DXVec3TransformCoord(&vMousePos, &vMousePos, &matProj);

	// 뷰스페이스 좌표를 월드 좌표로 변환
	D3DXVECTOR3		vRayPos, vRayDir;

	vRayPos = D3DXVECTOR3(0.f, 0.f, 0.f);
	vRayDir = vMousePos - vRayPos;

	D3DXMATRIX		matView;
	D3D9DEVICE->GetDevice()->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matView, NULL, &matView);

	D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matView);
	D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matView);

	// 월드 영역의 좌표를 로컬 스페이스 좌표로 변환
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

			// 오른쪽 위
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

			// 왼쪽 아래
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
