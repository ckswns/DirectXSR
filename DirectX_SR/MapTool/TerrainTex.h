#ifndef TerrainTex_h__
#define TerrainTex_h__

#include "Behaviour.h"
#include "Texture.h"
#include "Mesh.h"

class MapTab;

class CTerrain final : public Behaviour
{
public: explicit CTerrain(LPDIRECT3DDEVICE9 pGraphicDev, const DWORD& dwCntX, const DWORD& dwCntZ
						, const DWORD& dwRoomNumber, const D3DXVECTOR3 vworldpos = D3DXVECTOR3(0,0,0));
public: virtual ~CTerrain(void);
	  
public:	virtual void Start(void) noexcept override;
public: virtual void Update(float) noexcept;
public: virtual void DbgRender(void) noexcept override;

public: void						Set_Textureinfo(Texture* pTexture, std::string strfilepath);
public: void						MoveCheck(bool bCheck);

public: inline const int&			Get_VtxCntX() const { return m_dwVtxCntX; }
public: inline const int&			Get_VtxCntZ() const { return m_dwVtxCntZ; }

public: inline const int&			Get_RoomNumber() const { return m_RoomNumber; }

public: inline std::string			Get_Filepath() { return _strFilePath; }

public: const D3DXVECTOR3*			Get_VtxPos(void) { return _pVtxPos; }

private: void						BufferInit(const int& iMoveX = 0,const int& iMoveZ = 0);

public: const D3DXVECTOR3			Getworldvec() const { return _vworldpos; }

private: DWORD						m_dwVtxCntX;
private: DWORD						m_dwVtxCntZ;

private: DWORD						m_dwVtxCnt;
private: DWORD						m_dwVtxSize;
private: DWORD						m_dwTriCnt;
private: DWORD						m_dwFVF;

private: D3DFORMAT					m_IdxFmt;
private: DWORD						m_dwIdxSize;

private: DWORD						m_RoomNumber;

private: LPDIRECT3DVERTEXBUFFER9	m_pVB;
private: LPDIRECT3DINDEXBUFFER9		m_pIB;
	   
private: LPDIRECT3DDEVICE9			m_pGraphicDev;
private: Texture*					m_pTexture = nullptr;
private: std::string				_strFilePath;

private: MapTab*					_pMaptab = nullptr;
private: bool						_bMoveCheck = false;

private: D3DXVECTOR3*				_pVtxPos = nullptr;
private: D3DXVECTOR3				_vworldpos;
};

#endif // TerrainTex_h__
