#include "pch.h"
#include "CubeObject.h"
#include "MeshRenderer.h"
#include "Mesh.h"
#include "Cube.h"
#include "Transform.h"
#include "D3D9Device.h"
#include "BoxCollider.h"
#include "GameObject.h"

namespace ce
{
	CubeObject::CubeObject(D3DCOLORVALUE color, float scaleFactor) noexcept :
		_scaleFactor(scaleFactor),
		_color(color)
	{
	}

	CubeObject::CubeObject(Texture* texure, D3DCOLORVALUE color, float scaleFactor) noexcept :
		_texture(texure),
		_scaleFactor(scaleFactor),
		_color(color)
	{
	}

	CubeObject::~CubeObject(void) noexcept
	{
	}

	void CubeObject::Start(void) noexcept
	{
		Mesh* cube = new Cube();
		cube->Open(D3D9Device::Instance()->GetDevice());

		MeshRenderer* meshRenderer = new MeshRenderer(D3D9Device::Instance()->GetDevice(), cube);
		meshRenderer->GetMaterialPTR()->SetMainTexture(_texture);

		meshRenderer->GetMaterialPTR()->SetColor(_color);
		gameObject->AddComponent(meshRenderer);
	}

	void CubeObject::Update(float fElapsedTime) noexcept
	{
	}
}