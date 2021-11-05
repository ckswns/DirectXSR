#pragma once
#ifndef __EDITOR_STRUCT__
#define __EDITOR_STRUCT__

typedef struct tagParticle
{
	D3DXVECTOR3	 vPosition;
	float					 fSize;
	unsigned long			 dwColor;
}PARTICLE;
const unsigned long FVF_PARTICLE = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_PSIZE;

typedef struct tagVertexTexture
{
	D3DXVECTOR3	 vPosition;
	D3DCOLOR	 dwColor;
	D3DXVECTOR2		vTexUV;
}VTXCOLTEX;
const unsigned long FVF_VTXCOLTEX = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE3(0);

typedef struct tagParticleAttribute
{
	tagParticleAttribute()
	{
		_vPosition = Vector3::zero;
		_vVelocity = D3DXVECTOR3(0, 1, 0);
		_vAcceleration = Vector3::zero;
		_fLifeTime = 2.f;
		_fAge = 0.f;
		_fSize = 0.2f;
		_dwColor = D3DXCOLOR(1.f, 0, 0,1.f);
		_bIsAlive = true;
	}

	tagParticleAttribute& operator=(const tagParticleAttribute& ref)
	{
		_vPosition		=	 ref._vPosition;
		_vVelocity		=	 ref._vVelocity;
		_vAcceleration=	ref._vAcceleration;
		_fLifeTime		=	 ref._fLifeTime;
		_fAge = 0.f;
		_fSize = ref._fSize;
		_dwColor		=	ref._dwColor;
		_bIsAlive		=	 ref._bIsAlive;

		return *this;
	}

	D3DXVECTOR3			 _vPosition;
	D3DXVECTOR3			 _vVelocity;
	D3DXVECTOR3			 _vAcceleration;
	float							 _fLifeTime;     
	float							 _fAge;        
	float							 _fSize;
	D3DXCOLOR			 _dwColor;           
	bool							 _bIsAlive;

}PARTICLE_ATRRI;

#endif