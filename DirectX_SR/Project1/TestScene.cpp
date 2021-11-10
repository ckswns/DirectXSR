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
#include "SpriteRenderer.h"

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
	_texture2->Init(D3D9DEVICE->GetDevice(), "flag.png");

	GameObject* obj;

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			obj = GameObject::Instantiate();
			obj->AddComponent(new SpriteRenderer(D3D9DEVICE->GetDevice(), _texture2));
			obj->GetTransform()->SetLocalPosition(i * 10, j * 20, 0);
		}
	}

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
