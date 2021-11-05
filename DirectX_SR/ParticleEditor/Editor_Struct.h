#pragma once
#ifndef __EDITOR_STRUCT__
#define __EDITOR_STRUCT__

typedef struct tagParticle
{
	D3DXVECTOR3	 vPosition;
	float	 fSize;
	unsigned long	 dwColor;
}PARTICLE;
const unsigned long FVF_PARTICLE = D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_DIFFUSE;

typedef struct tagParticleAttribute
{
	tagParticleAttribute()
	{
		_vPosition = Vector3::zero;
		_vVelocity = D3DXVECTOR3(0, 1, 0);
		_vAcceleration = Vector3::zero;
		_fLifeTime = 5.f;
		_fAge = 0.f;
		_dwColor = D3DXCOLOR(255, 0, 0, 255);
		_bIsAlive = true;
		_bLoop = true;
	}

	tagParticleAttribute& operator=(const tagParticleAttribute& ref)
	{
		_vPosition		=	 ref._vPosition;
		_vVelocity		=	 ref._vVelocity;
		_vAcceleration=	ref._vAcceleration;
		_fLifeTime		=	 ref._fLifeTime;
		_fAge				=	 ref._fAge;
		_dwColor		=	ref._dwColor;
		_bIsAlive		=	 ref._bIsAlive;
		_bLoop			=	ref._bLoop;

		return *this;
	}

	D3DXVECTOR3			 _vPosition;
	D3DXVECTOR3			 _vVelocity;
	D3DXVECTOR3			 _vAcceleration;
	float							 _fLifeTime;     
	float							 _fAge;        
	unsigned long				 _dwColor;           
	bool							 _bIsAlive;
	bool							 _bLoop;

}PARTICLE_ATRRI;

#endif