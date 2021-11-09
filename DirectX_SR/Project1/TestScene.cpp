#include "pch.h"
#include "TestScene.h"
#include "CubeObject.h"
#include "EditorCamera.h"
#include "DirectionLight.h"
#include "Transform.h"
#include "Texture.h"
#include "Terrain.h"
#include "MeshRenderer.h"
#include "Quad.h"

TestScene::TestScene(void) noexcept
{
}

TestScene::~TestScene(void) noexcept
{
}

bool TestScene::Init(void) noexcept
{
	_texture = new ce::Texture();
	_texture->Init(D3D9DEVICE->GetDevice(), "Npc1_1.png");
	
	_texture2 = new ce::Texture();
	_texture2->Init(D3D9DEVICE->GetDevice(), "test.jpg");

	Mesh* terrain = new Terrain(40, 40);
	terrain->Open(D3D9DEVICE->GetDevice());

	GameObject* obj;
	obj = GameObject::Instantiate();
	MeshRenderer* mr = new MeshRenderer(D3D9DEVICE->GetDevice(), terrain);
	obj->AddComponent(mr);
	mr->GetMaterialPTR()->SetTexture(_texture);

	obj = GameObject::Instantiate();
	obj->AddComponent(new CubeObject());
	obj->GetTransform()->SetLocalPosition(-1, 0, 0);
	static_cast<MeshRenderer*>(obj->GetComponent(COMPONENT_ID::RENDERER))->GetMaterialPTR()->SetTexture(_texture);

	obj = GameObject::Instantiate();
	obj->AddComponent(new CubeObject());
	obj->GetTransform()->SetLocalPosition(1, 0, 0);
	static_cast<MeshRenderer*>(obj->GetComponent(COMPONENT_ID::RENDERER))->GetMaterialPTR()->SetTexture(_texture2);

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

	_texture2->Release();
	delete _texture2;
}
