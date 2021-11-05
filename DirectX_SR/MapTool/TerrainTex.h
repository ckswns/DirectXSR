#ifndef TerrainTex_h__
#define TerrainTex_h__

#include "Behaviour.h"

class CTerrain final : public Behaviour
{
public: explicit CTerrain(LPDIRECT3DDEVICE9& pGraphicDev, const DWORD& dwCntX, const DWORD& dwCntZ, const float& dwIntv, const float& dwIntvX, const DWORD& dwRoomNumber);
public: virtual ~CTerrain(void);

public:	virtual void Start(void) noexcept override;
public: virtual void Update(float) noexcept;

private: DWORD						m_dwVtxCntX;
private: DWORD						m_dwVtxCntZ;
private: DWORD						m_dwVtxIntvX;
private: DWORD						m_dwVtxIntvZ;

private: DWORD						m_dwVtxCnt;
private: DWORD						m_dwVtxSize;
private: DWORD						m_dwTriCnt;
private: DWORD						m_dwFVF;

private: D3DFORMAT					m_IdxFmt;
private: DWORD						m_dwIdxSize;

private: DWORD						m_RoomNumber;

//private: D3DFORMAT					m_IdxFmt;
private: VTXINFO					m_VtxInfo;

private: LPDIRECT3DVERTEXBUFFER9	m_pVB;
private: LPDIRECT3DINDEXBUFFER9		m_pIB;
	   
private: LPDIRECT3DDEVICE9			m_pGraphicDev;
private: LPDIRECT3DTEXTURE9			m_pTexture;
};

#endif // TerrainTex_h__
