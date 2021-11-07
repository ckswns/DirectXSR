#pragma once

#include "Component.h"
#include "Transform.h"
class BillBordParticle :public Component
{
private:											BillBordParticle() = delete;
public:											BillBordParticle(LPDIRECT3DDEVICE9 pDev) noexcept;
public:		virtual 							~BillBordParticle() noexcept { __noop; }

public:		virtual void						Init(void) noexcept override;
public:		virtual void						Update(float fElapsedTime) noexcept override;
public:		virtual void						Render(void) noexcept override;
public:		virtual void						Release(void) noexcept override;

private:		void								InitBuffer();
private:		void								ResetParticle(PARTICLE_ATRRI* attribute);
private:		void								AddParticle();
private:		void								Reset();

public:		void								Play();
public:		void								Stop();

public:		void								SetPlayOnAWake(bool b) { _bAwake = b; }
public:		void								SetLoop(bool loop) { _bLoop = loop; }
public:		void								SetDuration(float duration) { _fDuration = duration; }
public:		void								SetSpeed(float speed) { _fSpeed = speed; }
public:		void								SetGravity(float gravity) { _fGravity = gravity;}
public:		void								SetEmitRate(float emitRate) { _fEmitRate = emitRate; }
public:		void								SetMaxParticles(float maxParticles) { _iMaxParticles = maxParticles; }

public:		void								SetLifeTime(float lifeTime) { _tOrign._fLifeTime = lifeTime; }
public:		void								SetSize(float size) { _tOrign._fSize = size; }
public:		void								SetColor(D3DXCOLOR color) { _tOrign._dwColor = color; }

public:		void								SetShape(int shape) { _iShape = shape; }
public:		void								SetBoxSize(Vector3 size) { _vBox = size; }
public:		void								SetRadius(float r) { _fRadius = r; }
public:		void								SetAngle(float ang) { _fAngle = ang; }

public:		const bool								IsPlayOnAWake() { return _bAwake; }
public:		const bool								IsLoop() { return _bLoop; }
public:		const float								GetDuration() { return _fDuration; }
public:		const float								GetSpeed() { return _fSpeed; }
public:		const float								GetGravity() { return _fGravity; }
public:		const float								GetEmitRate() { return _fEmitRate; }
public:		const float								GetMaxParticles() { return _iMaxParticles; }												
public:		const PARTICLE_ATRRI*			GetOrign() { return &_tOrign; }
													
public:		const int									GetShape() { return _iShape; }
public:		const D3DXVECTOR3		GetBoxSize() { return _vBox; }
public:		const float								GetRadius() { return _fRadius; }
public:		const float								GetAngle() { return _fAngle; }

private:	 bool											_bAwake;
private:	 bool											_bPlay;
private:	 bool											_bLoop;
private:	 float											_fDuration;			//��ƼŬ ��ü �ð� 
private:	 float											_fTime;
private:	 float											_fSpeed;
private:	 float											_fGravity;
private:	 float											_fEmitRate;			//�ʴ� ���� �߰��� ��ƼŬ �� 
private:	 float											_fEmitTime;
private:	 int											_iMaxParticles;  //��ƼŬ �ִ� ��

private:	 int											_iShape;
private:	 D3DXVECTOR3							_vBox;
private:	float											_fRadius;
private:	float											_fAngle;
private: float											_fHeight;

private:	Transform*									_pTrans;
private:	std::list<PARTICLE_ATRRI*>			_pParticles;
private:	LPDIRECT3DDEVICE9					_pGraphicDev;
private:	LPDIRECT3DTEXTURE9				_pTexture;
			
private:	IDirect3DVertexBuffer9*				_pVB;
private:	DWORD										_dwVbSize;		//���ؽ� ���� �ִ� ������ 
private:	DWORD										_dwVbOffset;	//�����ܰ���� ������
private:	DWORD										_dwVbBathSize;	//�ϳ��� �ܰ迡 ���ǵ� ��ƼŬ�� ��
			
private:	IDirect3DIndexBuffer9*				_pIB;
private:	DWORD										_dwIbSize;		//���ؽ� ���� ������ 
private:	DWORD										_dwIbOffset;	//�����ܰ���� ������
private:	DWORD										_dwIbBathSize;	//�ϳ��� �ܰ迡 ���ǵ� ��ƼŬ�� ��
			
private:	PARTICLE_ATRRI						_tOrign;
			
private:	float zero = 0.f;
private:	float one = 1.f;

};