#pragma once

#include "GameObject.h"
class Particle : public GameObject
{
public:		explicit 							Particle() noexcept;
public:		virtual								~Particle() noexcept;

public:		virtual bool						Init(void) noexcept override;
public:		virtual void						Update(float fElapsedTime) noexcept override;
public:		virtual void						Render(void) noexcept override;
public:		virtual void						Release(void) noexcept override;

	  void Reset();
	  void ResetParticle(PARTICLE_ATRRI* attribute);
	  void AddParticle();

private:

	float											_fEmitRate;
	float											_fSize;
	int												_iMaxParticles;

	std::list<PARTICLE_ATRRI*>			_pParticles;
	LPDIRECT3DDEVICE9					_pGraphicDev;
	LPDIRECT3DTEXTURE9				_pTexture;

	IDirect3DVertexBuffer9*				_pVB;
	DWORD										_dwVbSize;		//���ؽ� ���� ������ 
	DWORD										_dwVbOffset;	//�����ܰ���� ������
	DWORD										_dwVbBathSize;	//�ϳ��� �ܰ迡 ���ǵ� ��ƼŬ�� ��

	PARTICLE_ATRRI						_tOrign;

};

