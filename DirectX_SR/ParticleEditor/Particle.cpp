#include "pch.h"
#include "Particle.h"

Particle::Particle() noexcept
{
	_eLayer = GameObjectLayer::EFFECT;
}
Particle::~Particle() noexcept
{
}

bool Particle::Init(void) noexcept 
{
	_pGraphicDev = D3D9DEVICE->GetDevice();

	_fSize = 1.f;
	_dwVbSize = 2048;


	if (FAILED(_pGraphicDev->CreateVertexBuffer(_dwVbSize * sizeof(PARTICLE),
		D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
		FVF_PARTICLE,
		D3DPOOL_DEFAULT,
		&_pVB, 0)))
	{
		MessageBoxW(NULL, L"Failed", L"VertexBuffer Error", MB_OK);
		return false;
	}

	_dwVbOffset = 0;
	_dwVbBathSize = 512;

	for (int i = 0; i < 10; i++)
		AddParticle();

	if (FAILED(D3DXCreateTextureFromFile(_pGraphicDev, L"D:/SR/GitHunSR/DirectXSR/DirectX_SR/ParticleEditor/res/SS.tga", &_pTexture)))
	{
		MessageBoxW(NULL, L"Failed", L"Texture Error", MB_OK);
		return false;
	}

	return true;

}
void Particle::Update(float fElapsedTime) noexcept
{
	std::list<PARTICLE_ATRRI*>::iterator iter;
	for (iter = _pParticles.begin(); iter != _pParticles.end(); iter++)
	{
		if ((*iter)->_bIsAlive)
		{
			(*iter)->_vPosition += (*iter)->_vVelocity * fElapsedTime;
			(*iter)->_fAge += fElapsedTime;

			if ((*iter)->_fAge > (*iter)->_fLifeTime)
			{
				if((*iter)->_bLoop)
					ResetParticle((*iter));
				else
					(*iter)->_bIsAlive = false;
			}
		}
	}


}
void Particle::Render(void) noexcept
{
	if (_pParticles.empty()) return;

	_pGraphicDev->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	_pGraphicDev->SetRenderState(D3DRS_POINTSCALEENABLE, true);
	_pGraphicDev->SetRenderState(D3DRS_POINTSIZE, _fSize);
	_pGraphicDev->SetRenderState(D3DRS_POINTSIZE_MIN, 0.0f);

	_pGraphicDev->SetRenderState(D3DRS_POINTSCALE_A, 0.0f);
	_pGraphicDev->SetRenderState(D3DRS_POINTSCALE_B, 0.0f);
	_pGraphicDev->SetRenderState(D3DRS_POINTSCALE_C, 1.0f);

	_pGraphicDev->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	_pGraphicDev->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);

	_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	_pGraphicDev->SetTexture(0, _pTexture);

	_pGraphicDev->SetFVF(FVF_PARTICLE);
	_pGraphicDev->SetStreamSource(0, _pVB, 0, sizeof(PARTICLE));

	if (_dwVbOffset >= _dwVbSize)
		_dwVbOffset = 0;

	PARTICLE* v = 0;

	_pVB->Lock(_dwVbOffset * sizeof(PARTICLE),
		_dwVbBathSize * sizeof(PARTICLE),
		(void**)&v,
		_dwVbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

	DWORD numParticlesInBatch = 0;

	std::list<PARTICLE_ATRRI*>::iterator iter;
	for (iter = _pParticles.begin(); iter != _pParticles.end(); ++iter)
	{
		if ((*iter)->_bIsAlive)
		{
			v->vPosition = (*iter)->_vPosition;
			v->fSize = _fSize;
			v->dwColor = (D3DCOLOR)((*iter)->_dwColor);
		
			v++;
			numParticlesInBatch++;

			if (numParticlesInBatch == _dwVbBathSize)
			{
				_pVB->Unlock();

				_pGraphicDev->DrawPrimitive(D3DPT_POINTLIST, _dwVbOffset, _dwVbBathSize);

				_dwVbOffset += _dwVbBathSize;
				if (_dwVbOffset >= _dwVbSize)
					_dwVbOffset = 0;

				_pVB->Lock(_dwVbOffset * sizeof(PARTICLE),
					_dwVbBathSize * sizeof(PARTICLE),
					(void**)&v,
					_dwVbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

				numParticlesInBatch = 0;
			}
		}
	}
	_pVB->Unlock();

	if (numParticlesInBatch)
	{
		_pGraphicDev->DrawPrimitive(D3DPT_POINTLIST, _dwVbOffset, numParticlesInBatch);
	}
	_dwVbOffset += _dwVbBathSize;

	_pGraphicDev->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	_pGraphicDev->SetRenderState(D3DRS_POINTSCALEENABLE, false);
	_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}
void Particle::Release(void) noexcept
{
	if (_pParticles.empty())
	{
		std::list<PARTICLE_ATRRI*>::iterator iter;
		for (iter = _pParticles.begin(); iter != _pParticles.end(); iter++)
			delete (*iter);

		_pParticles.clear();
	}
}

void Particle::Reset()
{
	std::list<PARTICLE_ATRRI*>::iterator iter;
	for (iter = _pParticles.begin(); iter != _pParticles.end(); iter++)
		ResetParticle((*iter));
}
void Particle::ResetParticle(PARTICLE_ATRRI* attribute)
{
	*attribute = _tOrign;
}
void Particle::AddParticle() 
{
	PARTICLE_ATRRI* attribute = new PARTICLE_ATRRI;
	ResetParticle(attribute);

	_pParticles.push_back(attribute);
}