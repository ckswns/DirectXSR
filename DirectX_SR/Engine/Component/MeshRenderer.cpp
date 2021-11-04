#include "pch.h"
#include "MeshRenderer.h"
#include "Mesh.h"
#include "Transform.h"
#include "Assertion.h"
#include "Texture.h"

namespace ce
{
	MeshRenderer::MeshRenderer(GameObject* owner, LPDIRECT3DDEVICE9 pDevice, Mesh* pMesh) noexcept :
		Renderer(owner, pDevice),
		_pMesh(pMesh)
	{
		if (owner == nullptr)
			CE_ASSERT("ckswns", "Renderer의 owner는 nullptr일 수 없습니다");

		_pTransform = owner->GetTransform();
	}

	void MeshRenderer::SetMesh(Mesh* pMesh) noexcept
	{
		_pMesh = pMesh;
	}

	void MeshRenderer::Render(void) noexcept
	{
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