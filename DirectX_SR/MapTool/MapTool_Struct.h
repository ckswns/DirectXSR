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

typedef struct TagCUSTOMVTX
{
	D3DXVECTOR3 vPosition;
	D3DXVECTOR2 vAplhaUV;
	D3DXVECTOR2	vTextureUV;

}CUSVTX;

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEX2)

typedef struct TagLINE3D
{
	D3DXVECTOR3	VPos;
	D3DCOLOR	Col;

}L3D;
#define D3DFVF_LINE3D (D3DFVF_XYZ | D3DFVF_DIFFUSE)

typedef struct TagTexture
{
	IDirect3DTexture9* pTexture;
	IDirect3DTexture9* pAlphamap;
	TagTexture()
	{
		pTexture = nullptr;
		pAlphamap = nullptr;
	}
}tTex;

#endif // MapTool_Struct_h__