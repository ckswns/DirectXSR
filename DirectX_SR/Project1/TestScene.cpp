#include "pch.h"
#include "TestScene.h"
#include "CubeObject.h"
#include "EditorCamera.h"
#include "DirectionLight.h"
#include "Transform.h"

TestScene::TestScene(void) noexcept
{
}

TestScene::~TestScene(void) noexcept
{
}

bool TestScene::Init(void) noexcept
{
	GameObject* obj;

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			obj = GameObject::Instantiate();
			obj->GetTransform()->SetLocalScale(i, j, 1);
			obj->AddComponent(new CubeObject());
		}
	}
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
