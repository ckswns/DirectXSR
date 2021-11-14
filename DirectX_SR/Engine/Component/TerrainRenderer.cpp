#include "pch.h"
#include "TerrainRenderer.h"
#include "Terrain.h"
#include "Transform.h"

namespace ce
{
	TerrainRenderer::TerrainRenderer(LPDIRECT3DDEVICE9 pDevice, Terrain* terrain) noexcept :
		Renderer(pDevice),
		_pTerrain(terrain)
	{

	}

	void TerrainRenderer::SetTerrain(Terrain* pTerrain) noexcept
	{
		_pTerrain = pTerrain;
	}

	void TerrainRenderer::Init(void) noexcept
	{
		_pTransform = _owner->GetTransform();
		_owner->SetLayer(GameObjectLayer::BACKGROUND);
	}

	void TerrainRenderer::Render(void) noexcept
	{
		_pDevice->SetTransform(D3DTS_WORLD, &_pTransform->GetWorldMatrix());

		_pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

		//알파 블렌딩
		_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		_pDevice->SetMaterial(&_material.GetNativeMaterial());
		D3DXMATRIXA16 matTemp;

		//_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
		_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);

		_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		_pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

		//_pDevice->SetIndices(_pTerrain->GetIndexBuffer());
		//_pDevice->SetFVF(_pTerrain->GetFVF());

		_pDevice->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);
		_pDevice->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);

		//텍스쳐 맵핑모드 
		_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
		_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

		D3DXMatrixScaling(&matTemp, (float)_pTerrain->Get_VtxCntX(), (float)_pTerrain->Get_VtxCntZ(), 1.0f);

		_pDevice->SetTransform(D3DTS_TEXTURE0, &matTemp);

		if(_material.GetTextureLength() > 0)
			_pDevice->SetTexture(0, _material.GetMainTexture()->GetTexturePTR());

		//_pDevice->SetStreamSource(0, _pTerrain->GetVtxBuffer(), 0, _pTerrain->GetVtxSize());
		//_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, _pTerrain->GetVtxCnt(), 0, _pTerrain->GetTriCnt());

		_pTerrain->Render(_pDevice);

		_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
		_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);

		_pDevice->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);

		// Texture: take the color from the texture, take the alpha from the previous stage
	//	_pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_SELECTARG1); 
		_pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE);
		_pDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);

		_pDevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
		_pDevice->SetTextureStageState(1, D3DTSS_ALPHAARG1, D3DTA_CURRENT);

		//_pDevice->SetIndices(_pTerrain->GetIndexBuffer());
		//_pDevice->SetFVF(_pTerrain->GetFVF());

		_pDevice->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		_pDevice->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		_pDevice->SetSamplerState(1, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

		// 0번 인덱스 알파 텍스쳐는 전체에 한번만 그려져야 하므로
		// 타일화 셋팅 하지 않음
		_pDevice->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
		_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
		_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

		_pDevice->SetTextureStageState(1, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);
		_pDevice->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 0);
		_pDevice->SetSamplerState(1, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
		_pDevice->SetSamplerState(1, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

		_pDevice->SetTransform(D3DTS_TEXTURE0, &matTemp);
		_pDevice->SetTransform(D3DTS_TEXTURE1, &matTemp);


		for (int i = 0; i < _alphaMaterial.GetTextureLength(); ++i)
		{
			if (_material.GetTextureLength() <= i + 1)
				break;
			_pDevice->SetTexture(0, _alphaMaterial.GetTexture(i)->GetTexturePTR());
			_pDevice->SetTexture(1, _material.GetTexture(i + 1)->GetTexturePTR());

			_pDevice->SetStreamSource(0, _pTerrain->GetVtxBuffer(), 0, _pTerrain->GetVtxSize());
			_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, _pTerrain->GetVtxCnt(), 0, _pTerrain->GetTriCnt());
		}

		_pDevice->SetTextureStageState(1, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);

		// 멀티텍스쳐 0,1번 셋팅을 사용을 중지 한다.
		//_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_DISABLE);
		//_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
		_pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
		_pDevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);

		_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		_pDevice->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
		// 알파 사용을 중지 한다. 
		_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	}

	void TerrainRenderer::Release(void) noexcept
	{
		if (_pTerrain)
		{
			_pTerrain->Close();
			delete _pTerrain;
		}
	}
}