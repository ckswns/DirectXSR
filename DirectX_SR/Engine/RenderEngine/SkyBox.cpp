#include "pch.h"
#include "SkyBox.h"
#include "Transform.h"
#include "Texture.h"
#include "Cube.h"

namespace ce
{
	SkyBox::SkyBox(LPDIRECT3DDEVICE9 device) noexcept :
		_pDevice(device)
	{
		_cube = new Cube(1000);
		_cube->Open(device);
	}

	void SkyBox::SetTexture(Texture* texture) noexcept
	{
		_texture = texture;
	}

	void SkyBox::Render(void) noexcept
	{
		_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		_pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
		
		D3DXMATRIX mat;
		D3DXVECTOR3 pos = _transform->GetWorldPosition();
		D3DXMatrixTranslation(&mat, pos.x, pos.y, pos.z);

		_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
		_pDevice->SetRenderState(D3DRS_LIGHTING, false);

		_pDevice->SetTransform(D3DTS_WORLD, &mat);
		if (_texture)
			_pDevice->SetTexture(0, _texture->GetTexturePTR());
		else
			_pDevice->SetTexture(0, nullptr);
		_cube->Render(_pDevice);

		_pDevice->SetRenderState(D3DRS_LIGHTING, true);
		_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
		_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

		_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
		_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
		_pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);
	}

	void SkyBox::Release(void) noexcept
	{
		if (_cube)
		{
			delete _cube;
			_cube = nullptr;
		}
	}
}