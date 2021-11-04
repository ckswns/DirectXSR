#include "pch.h"
#include "CubeObject.h"
#include "MeshRenderer.h"
#include "Mesh.h"
#include "Cube.h"
#include "Transform.h"
#include "D3D9Device.h"

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

	bool CubeObject::Init(void) noexcept
	{
		_eLayer = GameObjectLayer::OBJECT;

		Mesh* cube = new Cube();
		cube->Open(D3D9Device::Instance()->GetDevice());

		MeshRenderer* meshRenderer = new MeshRenderer(this, D3D9Device::Instance()->GetDevice(), cube);
		meshRenderer->GetMaterialPTR()->SetTexture(_texture);

		meshRenderer->GetMaterialPTR()->SetColor(_color);
		AddComponent(meshRenderer);

		return true;
	}

	void CubeObject::Update(float fElapsedTime) noexcept
	{
	}

	void CubeObject::Render(void) noexcept
	{
	}

	void CubeObject::Release(void) noexcept
	{
	}
}