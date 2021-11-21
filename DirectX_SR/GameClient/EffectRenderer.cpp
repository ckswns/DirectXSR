#include "pch.h"
#include "EffectRenderer.h"
#include "Transform.h"
#include "Quad.h"

EffectRenderer::EffectRenderer(void) noexcept :
	SpriteRenderer(D3D9DEVICE->GetDevice(), nullptr)
{
}

void EffectRenderer::Render(void) noexcept
{
	_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	_pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

	DWORD flag = 0, cull = 0;
	_pDevice->GetRenderState(D3DRS_LIGHTING, &flag);
	_pDevice->GetRenderState(D3DRS_CULLMODE, &cull);
	_pDevice->SetRenderState(D3DRS_LIGHTING, false);

	_pDevice->SetRenderState(D3DRS_CULLMODE, _cullOption);
	_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	//_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	//_pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	//_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	//_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);

	_pDevice->SetTextureStageState(0, D3DTSS_CONSTANT, _material.GetColor());
	//_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CONSTANT);
	//_pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	//_pDevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);


	_pDevice->SetTransform(D3DTS_WORLD, &_transform->GetWorldMatrix());

	_material.Render(_pDevice);
	_quad->Render(_pDevice);

	_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	//_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	_pDevice->SetRenderState(D3DRS_LIGHTING, flag);
	_pDevice->SetRenderState(D3DRS_CULLMODE, cull);
}
