#pragma once
#include "GameObject.h"

#include "Camera.h"
#include "Transform.h"

class MapTool_Cam : public GameObject
{
public: MapTool_Cam(LPDIRECT3DDEVICE9& pGraphicDev);
public: ~MapTool_Cam(void);

public:	bool Init(void) noexcept override;
public:	void Update(float fElapsedTime) noexcept override;
public:	void Render(void) noexcept override;
public:	void Release(void) noexcept override;

private: LPDIRECT3DDEVICE9	m_pGraphicDev = nullptr;
private: Transform*			m_pTransform = nullptr;
private: POINT				_ptPrevMousePos;
private: bool				m_bWireFrame = false;
};

