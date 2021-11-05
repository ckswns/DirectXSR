#include "pch.h"
#include "TestScene.h"
#include "CubeObject.h"
#include "EditorCamera.h"
#include "DirectionLight.h"
#include "Transform.h"
#include "Texture.h"
TestScene::TestScene(void) noexcept
{
}

TestScene::~TestScene(void) noexcept
{
}

bool TestScene::Init(void) noexcept
{
	GameObject* obj;
	Texture* tex = new Texture();
	tex->Init(D3D9DEVICE->GetDevice(), "cubeTest.dds");

	//for (int i = 0; i < 10; i++)
	//{
	//	for (int j = 0; j < 10; j++)
	//	{
			obj = GameObject::Instantiate();
			obj->GetTransform()->SetLocalScale(1, 1, 1);
			obj->AddComponent(new CubeObject(tex));
	//	}
	//}
	obj = GameObject::Instantiate();
	obj->AddComponent(new EditorCamera(g_hWnd));
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

}
