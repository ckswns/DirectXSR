#pragma once

#include "Component.h"
#include "Transform.h"
class Particle : public Component
{
private:							Particle() = delete;
public:							Particle(LPDIRECT3DDEVICE9 pDev) noexcept;
public:		virtual 			~Particle() noexcept { __noop; }

public:		virtual void						Init(void) noexcept override;
public:		virtual void						Update(float fElapsedTime) noexcept override;
public:		virtual void						Render(void) noexcept override;
public:		virtual void						Release(void) noexcept override;

	  void Reset();
	  void ResetParticle(PARTICLE_ATRRI* attribute);
	  void AddParticle();

private:
	bool _bLoop;
	float											_fEmitRate;
	float											_fSize;
	int												_iMaxParticles;

	Transform*									_pTrans;
	std::list<PARTICLE_ATRRI*>			_pParticles;
	LPDIRECT3DDEVICE9					_pGraphicDev;
	LPDIRECT3DTEXTURE9				_pTexture;

	IDirect3DVertexBuffer9*				_pVB;
	DWORD										_dwVbSize;		//버텍스 버퍼 사이즈 
	DWORD										_dwVbOffset;	//다음단계로의 오프셋
	DWORD										_dwVbBathSize;	//하나의 단계에 정의된 파티클의 수

	PARTICLE_ATRRI						_tOrign;

	float zero = 0.f;
	float one = 1.f;

};

