#include "pch.h"
#include "TestScene.h"
#include "CubeObject.h"
#include "EditorCamera.h"
#include "DirectionLight.h"
#include "Transform.h"
#include "Texture.h"
#include "Terrain.h"
#include "MeshRenderer.h"

TestScene::TestScene(void) noexcept
{
}

TestScene::~TestScene(void) noexcept
{
}

bool TestScene::Init(void) noexcept
{
	_texture = new ce::Texture();
	std::string str = "test.jpg";
	_texture->Init(D3D9DEVICE->GetDevice(), str.c_str());
	
	Terrain* terrain = new Terrain(5, 5);
	terrain->Open(D3D9DEVICE->GetDevice());

	GameObject* obj;
	obj = GameObject::Instantiate();
	MeshRenderer* mr = new MeshRenderer(D3D9DEVICE->GetDevice(), terrain);
	mr->GetMaterialPTR()->SetTexture(_texture);

	obj->AddComponent(mr);

	obj = GameObject::Instantiate();
	obj->AddComponent(new CubeObject());

	obj = GameObject::Instantiate();
	obj->AddComponent(new EditorCamera(g_hWnd));
	obj->GetTransform()->SetLocalPosition(0, 1, 0);
	obj->GetTransform()->SetLocalEulerAngle(0, 0, 0);
	//GameObject::Instantiate(new DirectionLight());

	return true;
}

void TestScene::FixedUpdate(float fElapsedTime) noexcept
{

}

void TestScene::Update(float fElapsedTime) noexcept
{

}

void TestScene::LateUpdate(float fElapsedTime) noexcept
{

}

void TestScene::Render(float fElapsedTime) noexcept
{

}

void TestScene::Release(void) noexcept
{
	_texture->Release();
	delete _texture;
}
