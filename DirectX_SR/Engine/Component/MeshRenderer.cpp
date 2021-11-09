#include "pch.h"
#include "MeshRenderer.h"
#include "Mesh.h"
#include "Transform.h"
#include "Assertion.h"
#include "Texture.h"

namespace ce
{
	MeshRenderer::MeshRenderer(LPDIRECT3DDEVICE9 pDevice, Mesh* pMesh) noexcept :
		Renderer(pDevice),
		_pMesh(pMesh)
	{

	}

	void MeshRenderer::SetMesh(Mesh* pMesh) noexcept
	{
		_pMesh = pMesh;
	}

	void MeshRenderer::Init(void) noexcept
	{
		_pTransform = _owner->GetTransform();
	}

	void MeshRenderer::Render(void) noexcept
	{
		//_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		//_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		//_pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

		_pDevice->SetTransform(D3DTS_WORLD, &_pTransform->GetWorldMatrix());

		_material.Render(_pDevice);
		_pMesh->Render(_pDevice);
	}

	void MeshRenderer::Release(void) noexcept
	{
		if (_pMesh != nullptr)
		{
			_pMesh->Close();
			delete _pMesh;
			_pMesh = nullptr;
		}
	}
}