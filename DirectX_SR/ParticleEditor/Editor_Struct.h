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
	D3DXVECTOR3		vPosition;
	unsigned long			dwColor;   	 
	D3DXVECTOR2		vTexUV;
}VTXCOLTEX;
const unsigned long FVF_VTXCOLTEX = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1;

typedef struct tagParticleAttribute
{
	tagParticleAttribute()
	{	
		_bIsAlive			= true;

		_fLifeTime			= 2.f;
		_fAge					= 0.f;
		_fSize				= 0.2f;

		_vPosition			= Vector3::zero;
		_vVelocity			= D3DXVECTOR3(0, 1, 0);
		_vAcceleration	= Vector3::zero;
		_dwColor			= D3DXCOLOR(1.f, 1.f, 1.f,1.f);
	
	}

	tagParticleAttribute& operator=(const tagParticleAttribute& ref)
	{
		_bIsAlive			= ref._bIsAlive;
		_fLifeTime			= ref._fLifeTime;
		_fAge					= 0.f;
		_fSize				= ref._fSize;
		_vPosition			= ref._vPosition;
		_vVelocity			= ref._vVelocity;
		_vAcceleration	= ref._vAcceleration;
		_dwColor			= ref._dwColor;

		return *this;
	}

	bool							 _bIsAlive;
	unsigned long				 _dwColor;
	float							 _fLifeTime;
	float							 _fAge;
	float							 _fSize;
	D3DXVECTOR3			 _vPosition;
	D3DXVECTOR3			 _vVelocity;
	D3DXVECTOR3			 _vAcceleration;
        


}PARTICLE_ATRRI;

typedef struct tagShapeOption
{
	tagShapeOption()
	{
		_fRadius = 1.f;
		_fAngle	 = 0.f;
	}
	float _fRadius;
	float _fAngle;
}SHAPEOPTION;
#endif