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
	DWORD										_dwVbSize;		//���ؽ� ���� ������ 
	DWORD										_dwVbOffset;	//�����ܰ���� ������
	DWORD										_dwVbBathSize;	//�ϳ��� �ܰ迡 ���ǵ� ��ƼŬ�� ��

	PARTICLE_ATRRI						_tOrign;

	float zero = 0.f;
	float one = 1.f;

};

