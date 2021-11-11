#pragma once
#include "Mesh.h"

class FloorTerrain : public Mesh
{
public: explicit FloorTerrain(DWORD wwidth, DWORD whegiht, float flength = 1.f);
public: virtual ~FloorTerrain(void);

public: bool							Open(LPDIRECT3DDEVICE9 pDevice) noexcept override;
public: void							Render(LPDIRECT3DDEVICE9 pDevice) noexcept override;
public: void							Close(void) noexcept override;

public:  bool							LoadTextures();
public:  BOOL							CreateAlphaMaps();
public:  BOOL							IntersectTriangle(const D3DXVECTOR3& orig,
															const D3DXVECTOR3& dir, D3DXVECTOR3& v0,
															D3DXVECTOR3& v1, D3DXVECTOR3& v2,
															FLOAT* t, FLOAT* u, FLOAT* v);
public:  void							PickingProcess(RECT& rtRect, CPoint ptMouse/*float fCurPosX, float fCurPosY*/);
public:  D3DXVECTOR3					PickingOnTerrain(CPoint point);

public:  bool							DrawAlphamaps(int nIndex);
public:  void							DrawPickCircle(int Count, float size, D3DCOLOR Col);
public:  void							AlphaTextureRender();
public:  void							MiniAlphaTextureRender();
public:  bool							TerrainInit(DWORD wWidth, DWORD wHeight, float fLength);
public:  void							TerrainRender();

public:  //----------------------------------------------------------------------------------//
public:  inline	DWORD					GetTotalIndices()  const { return _dwTotalIndices; }
public:  inline	DWORD					GetTotalVertices() const { return _dwTotalVertices; }

public:  inline	int						GetCurSelIndex()   const { return _nCurSelIndex; }
public:  inline	int*					GetDrawIndex() { return _pDrawIndex; }
public:  inline	float					GetBrushSize()	   const { return _fBrushSize; }
public:  inline	float					GetSmoothSize()	   const { return _fSmoothSize; }
public:  inline	BOOL					GetPickOK()		   const { return _blPickOK; }
public:  inline	BOOL					GetClicked()       const { return _blClicked; }

public: tTex							Get_FloorTerrainTex(int Index) { return _Tex[Index]; }

public: DWORD							Get_Width()		const { return _wWidth; }
public: DWORD							Get_Height()		const { return _wHeight; }

public: std::vector<std::string>		Get_FilePath() { return _vecFilepath; }

public:	 inline D3DXVECTOR3				Get_PickingPos()   const { return _vGetPos; }

public:  inline	void					SetCurSelIndex(int nIndex) { _nCurSelIndex = nIndex; }
public:  inline	void					SetBrushSize(float fSize) { _fBrushSize = fSize; }
public:  inline	void					SetSmoothSize(float fSize) { _fSmoothSize = fSize; }
public:  inline	void					SetPickOK(bool blPick) { _blPickOK = blPick; }
public:  inline	void					SetClicked(bool blClick) { _blClicked = blClick; }

public: void							SetBaseTex(IDirect3DTexture9* pBaseTexture) { _pBaseTexture = pBaseTexture; }
public: void							SetAlphaTex(IDirect3DTexture9* pTexture, IDirect3DTexture9* pTextureAlpha, int i);

public:  inline	void					SetDrawIndex(int* pIndex)
	  {
		  for (int i = 0; i < 4; ++i)
			  _pDrawIndex[i] = pIndex[i];
	  }

	  //----------------------------------------------------------------------------------//
	   // 상속 받은 멤버변수
	   //uint64					_nVtxCnt;
	   //uint64					_nVtxSize;
	   //uint64					_nTriCnt;
	   //uint64					_nFVF;
	   //uint64					_nIdxSize;

	   //bool					_bOpen = false;
	   //float					_scaleFactor = 1;

	   //D3DFORMAT				_idxFmt;

	   //LPDIRECT3DVERTEXBUFFER9	_pVB;
	   //LPDIRECT3DINDEXBUFFER9		_pIB;

private: LPDIRECT3DDEVICE9			_pGraphicDev;

private: LPDIRECT3DTEXTURE9			_pBaseTexture;
private: tTex						_Tex[MAXTEXNUM];

private: CUSVTX*					_pVertices;

private: DWORD						_wWidth;			//맵의 가로사이즈
private: DWORD						_wHeight;			//맵의 세로사이즈
private: DWORD						_wWidthVertices;	//맵의 가로텍스
private: DWORD						_wHeightVertices;	//맵의 세로버텍스
private: DWORD						_dwTotalVertices;	//맵의 총버티스

private: DWORD						_dwTotalIndices;	//맵의 총인디스
private: float						_fLength;			//맵의 한타일의 길이
private: DWORD						_dwPolygonsCount;	//그려야할 폴리곤 카운트

private: int						_nCurSelIndex;
private: int						_pDrawIndex[4];

private: float						_fBrushSize;
private: float						_fSmoothSize;

private: BOOL						_blPickOK;							// pick 성공 여부
private: D3DXVECTOR3				_vGetPos;							// pick 위치
private: float						_fGetU;
private: float						_fGetV;
private: BOOL						_blClicked;
private: int						_nTexPosX;
private: int						_nTexPosY;

private: std::vector<std::string>	_vecFilepath;

private: uint64						_TexAlphaSize;
private: uint64						_MiniAlphaSize;
};

