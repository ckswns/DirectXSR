#pragma once
#ifndef MapTool_Struct_h__
#define MapTool_Struct_h__

typedef struct VERTEXCOLOR
{
	D3DXVECTOR3		vPos;
	DWORD		dwColor;

}VTCOL;

const DWORD VTXCOL_FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX0;

typedef struct TagVerTexTexture
{
	D3DXVECTOR3	vPosition;
	D3DXVECTOR2	vTexUV;

}VTTEX;

const DWORD VTXTEX_FVF = D3DFVF_XYZ | D3DFVF_TEX1;

typedef struct TagVertexCubTexture
{
	D3DXVECTOR3		vPosition;
	D3DXVECTOR3		vTexUV;

}VTXCUBE;

typedef	struct TagIndex16
{
	WORD _0;
	WORD _1;
	WORD _2;

}IDX16;

typedef	struct TagIndex32
{
	DWORD _0;
	DWORD _1;
	DWORD _2;

}IDX32;

typedef	struct TagVerTexInfo
{
	DWORD				_dwVtxCntX;
	DWORD				_dwVtxCntZ;
	float				_dwVtxIntvX;
	float				_dwVtxIntvZ;
	DWORD				_dwVtxCnt;
	DWORD				_dwVtxSize;
	DWORD				_dwTriCnt;
	DWORD				_dwFVF;
	DWORD				_dwIdxSize;
	DWORD				_RoomNumber;

}VTXINFO;

#endif // MapTool_Struct_h__