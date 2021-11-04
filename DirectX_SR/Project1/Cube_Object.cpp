#include "pch.h"
#include "Cube_Object.h"
#include "MeshRenderer.h"
#include "Mesh.h"
#include "Cube.h"
#include "Transform.h"

bool Cube_Object::Init(void) noexcept
{
	_eLayer = GameObjectLayer::OBJECT;

	Mesh* cube = new Cube();
	cube->Open(D3D9DEVICE->GetDevice());

	MeshRenderer* meshRenderer = new MeshRenderer(this, D3D9DEVICE->GetDevice(), cube);
	Texture* tex;
	tex = new Texture();
	tex->Init(D3D9DEVICE->GetDevice(), "test.jpg");
	meshRenderer->GetMaterialPTR()->SetTexture(tex);

	D3DCOLORVALUE v;
	v.a = 1;
	v.r = 1;
	v.g = 1;
	v.b = 1;

	meshRenderer->GetMaterialPTR()->SetColor(v);
	AddComponent(meshRenderer);

	return true;
}

void Cube_Object::Update(float fElapsedTime) noexcept
{

}

void Cube_Object::Render(void) noexcept
{

}

void Cube_Object::Release(void) noexcept
{

}
