// ObjectTab.cpp: 구현 파일
//

#include "pch.h"
#include "MapTool.h"
#include "ObjectTab.h"
#include "afxdialogex.h"


// ObjectTab 대화 상자

IMPLEMENT_DYNAMIC(ObjectTab, CDialog)

ObjectTab::ObjectTab(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_ObjectTab, pParent)
{

}

ObjectTab::~ObjectTab()
{
}

void ObjectTab::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

//D3DXVECTOR3 ObjectTab::Picking_OnTerrain(HWND hWnd, D3DXVECTOR3* pBufferpos)
//{
//	POINT		ptMouse{};
//
//	GetCursorPos(&ptMouse);
//	ScreenToClient(hWnd, &ptMouse);
//
//	D3DXVECTOR3		vMousePos;
//
//	D3DVIEWPORT9		ViewPort;
//	ZeroMemory(&ViewPort, sizeof(D3DVIEWPORT9));
//
//	m_pGraphicDev->GetViewport(&ViewPort);
//
//	// 윈도우 좌표에 상태에 있는 마우스를 투영 좌표로 변환
//	vMousePos.x = ptMouse.x / (ViewPort.Width * 0.5f) - 1.f;
//	vMousePos.y = ptMouse.y / -(ViewPort.Height * 0.5f) + 1.f;
//	vMousePos.z = 0.f;
//
//	// 투영 좌표를 뷰 스페이스 좌표로 변환
//	_matrix		matProj;
//	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);
//	D3DXMatrixInverse(&matProj, NULL, &matProj);
//	D3DXVec3TransformCoord(&vMousePos, &vMousePos, &matProj);
//
//	// 뷰스페이스 좌표를 월드 좌표로 변환
//	_vec3		vRayPos, vRayDir;
//
//	vRayPos = _vec3(0.f, 0.f, 0.f);
//	vRayDir = vMousePos - vRayPos;
//
//	_matrix		matView;
//	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
//	D3DXMatrixInverse(&matView, NULL, &matView);
//
//	D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matView);
//	D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matView);
//
//	// 월드 영역의 좌표를 로컬 스페이스 좌표로 변환
//	_matrix		matWorld;
//	pTerrainTransCom->Get_WorldMatrix(&matWorld);
//	D3DXMatrixInverse(&matWorld, NULL, &matWorld);
//
//	D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matWorld);
//	D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matWorld);
//
//	_ulong		dwCntX = pTerrainBufferCom->Get_VtxCntX();
//	_ulong		dwCntZ = pTerrainBufferCom->Get_VtxCntZ();
//	const	_vec3* pTerrainVtxPos = pTerrainBufferCom->Get_VtxPos();
//
//	_ulong	dwVtxIdx[3];
//	_float	fU, fV, fDist;
//
//	for (_ulong i = 0; i < dwCntZ - 1; ++i)
//	{
//		for (_ulong j = 0; j < dwCntX - 1; ++j)
//		{
//			_ulong	dwIndex = i * dwCntX + j;
//
//			// 오른쪽 위
//			dwVtxIdx[0] = dwIndex + dwCntX;
//			dwVtxIdx[1] = dwIndex + dwCntX + 1;
//			dwVtxIdx[2] = dwIndex + 1;
//
//			if (D3DXIntersectTri(&pTerrainVtxPos[dwVtxIdx[1]],
//				&pTerrainVtxPos[dwVtxIdx[0]],
//				&pTerrainVtxPos[dwVtxIdx[2]],
//				&vRayPos, &vRayDir,
//				&fU, &fV, &fDist))
//			{
//				return _vec3(pTerrainVtxPos[dwVtxIdx[1]].x + (pTerrainVtxPos[dwVtxIdx[0]].x - pTerrainVtxPos[dwVtxIdx[1]].x) * fU,
//					0.f,
//					pTerrainVtxPos[dwVtxIdx[1]].z + (pTerrainVtxPos[dwVtxIdx[2]].z - pTerrainVtxPos[dwVtxIdx[1]].z) * fV);
//			}
//
//			// 왼쪽 아래
//			dwVtxIdx[0] = dwIndex + dwCntX;
//			dwVtxIdx[1] = dwIndex + 1;
//			dwVtxIdx[2] = dwIndex;
//
//			if (D3DXIntersectTri(&pTerrainVtxPos[dwVtxIdx[2]],
//				&pTerrainVtxPos[dwVtxIdx[1]],
//				&pTerrainVtxPos[dwVtxIdx[0]],
//				&vRayPos, &vRayDir,
//				&fU, &fV, &fDist))
//			{
//				return _vec3(pTerrainVtxPos[dwVtxIdx[2]].x + (pTerrainVtxPos[dwVtxIdx[1]].x - pTerrainVtxPos[dwVtxIdx[2]].x) * fU,
//					0.f,
//					pTerrainVtxPos[dwVtxIdx[2]].z + (pTerrainVtxPos[dwVtxIdx[0]].z - pTerrainVtxPos[dwVtxIdx[1]].z) * fV);
//			}
//		}
//	}
//
//	return D3DXVECTOR3(0.f, 0.f, 0.f);
//}


BEGIN_MESSAGE_MAP(ObjectTab, CDialog)
END_MESSAGE_MAP()


// ObjectTab 메시지 처리기
