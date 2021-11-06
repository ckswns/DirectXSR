#pragma once

#include "Component.h"
#include "Transform.h"
class BillBordParticle :public Component
{
private:							BillBordParticle() = delete;
public:							BillBordParticle(LPDIRECT3DDEVICE9 pDev) noexcept;
public:		virtual 			~BillBordParticle() noexcept { __noop; }

public:		virtual void						Init(void) noexcept override;
public:		virtual void						Update(float fElapsedTime) noexcept override;
public:		virtual void						Render(void) noexcept override;
public:		virtual void						Release(void) noexcept override;

private:		void								InitBuffer();
private:		void								 ResetParticle(PARTICLE_ATRRI* attribute);
private:		void								 AddParticle();
private:		void								 Reset();

public:		void								 Play();
public:		void								 Stop();

public:		void								SetLoop(bool loop) { _bLoop = loop; }
public:		void								SetDuration(float duration) { _fDuration = duration; }
public:		void								SetSpeed(float speed) { _fSpeed = speed; }
public:		void								SetGravity(float gravity) { _fGravity = gravity; _vGravity = Vector3(0, -(9.8f * gravity), 0); }
public:		void								SetEmitRate(float emitRate) { _fEmitRate = emitRate; }
public:		void								SetMaxParticles(float maxParticles) { _iMaxParticles = maxParticles; }

public:		void								SetLifeTime(float lifeTime) { _tOrign._fLifeTime = lifeTime; }
public:		void								SetSize(float size) { _tOrign._fSize = size; }
public:		void								SetColor(D3DXCOLOR color) { _tOrign._dwColor = color; }

private:	bool											_bPlay;
private:  bool											_bLoop;
private:  float											_fDuration;			//파티클 전체 시간 
private: float											_fTime;
private:  float											_fSpeed;
private:  float											_fGravity;
private:	float											_fEmitRate;			//초당 새로 추가될 파티클 수 
private:  float											_fEmitTime;
private:	int												_iMaxParticles;  //파티클 최대 수
private:	Vector3										_vGravity;

private:	Transform* _pTrans;
private:	std::list<PARTICLE_ATRRI*>			_pParticles;
private:	LPDIRECT3DDEVICE9					_pGraphicDev;
private:	LPDIRECT3DTEXTURE9				_pTexture;

private:	IDirect3DVertexBuffer9* _pVB;
private:	DWORD										_dwVbSize;		//버텍스 버퍼 최대 사이즈 
private:	DWORD										_dwVbOffset;	//다음단계로의 오프셋
private:	DWORD										_dwVbBathSize;	//하나의 단계에 정의된 파티클의 수

private:	IDirect3DIndexBuffer9* _pIB;
private:	DWORD										_dwIbSize;		//버텍스 버퍼 사이즈 
private:	DWORD										_dwIbOffset;	//다음단계로의 오프셋
private:	DWORD										_dwIbBathSize;	//하나의 단계에 정의된 파티클의 수

private:	PARTICLE_ATRRI						_tOrign;

private:	float zero = 0.f;
private:	float one = 1.f;

};