#ifndef TerrainTex_h__
#define TerrainTex_h__

#include "Behaviour.h"
#include "Texture.h"

class MapTab;

class CTerrain final : public Behaviour
{

public: explicit CTerrain(LPDIRECT3DDEVICE9 pGraphicDev, const DWORD& dwCntX, const DWORD& dwCntZ
						, const DWORD& dwRoomNumber, const int& dwMoveX = 0, const int& dwMoveZ = 0);
public: virtual ~CTerrain(void);
	  
public:	virtual void Start(void) noexcept override;
public: virtual void Update(float) noexcept;
public: virtual void DbgRender(void) noexcept override;

public: void						Set_Textureinfo(Texture* pTexture, std::string& strfilepath);
public: inline void					Set_MoveCheck() { _bMoveCheck = true; }

public: inline const int&			Get_VtxCntX() const { return m_dwVtxCntX; }
public: inline const int&			Get_VtxCntZ() const { return m_dwVtxCntZ; }

public: inline const int&			Get_RoomNumber() const { return m_RoomNumber; }

public: inline const int&			Get_CurrtMovePosX() const { return _iCurrMovePositionX; }
public: inline const int&			Get_CurrtMovePosZ() const { return _iCurrMovePositionZ; }

public: inline std::string			Get_Filepath() { return _strFilePath; }

public: inline D3DXVECTOR3*			Get_VtxPos(void) { return _pVtxPos; }

private: void						Buffer_Init(const int& iMoveX = 0,const int& iMoveZ = 0);

private: DWORD						m_dwVtxCntX;
private: DWORD						m_dwVtxCntZ;

private: DWORD						m_dwVtxCnt;
private: DWORD						m_dwVtxSize;
private: DWORD						m_dwTriCnt;
private: DWORD						m_dwFVF;

private: D3DFORMAT					m_IdxFmt;
private: DWORD						m_dwIdxSize;

private: DWORD						m_RoomNumber;

//private: D3DFORMAT				m_IdxFmt;
private: VTXINFO					m_VtxInfo;

private: LPDIRECT3DVERTEXBUFFER9	m_pVB;
private: LPDIRECT3DINDEXBUFFER9		m_pIB;
	   
private: LPDIRECT3DDEVICE9			m_pGraphicDev;
private: Texture*					m_pTexture;
private: std::string				_strFilePath;

private: MapTab*					_pMaptab;
private: bool						_bMoveCheck = false;
private: int						_iCurrMovePositionX;
private: int						_iCurrMovePositionZ;

private: D3DXVECTOR3*				_pVtxPos;
};

#endif // TerrainTex_h__
