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
#include "AudioListener.h"
#include "AudioSource.h"
#include "SphereCollider.h"
#include "RigidBody.h"
#include "Camera.h"
#include "BillboardTest.h"

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
			obj->AddComponent(new SpriteRenderer(D3D9DEVICE->GetDevice(), ASSETMANAGER->GetTextureData("Asset\\test.jpg")));
			obj->AddComponent(new BillboardTest());
			obj->GetTransform()->SetWorldPosition(i * 5, j * 5, 0);
		}
	}

	obj = GameObject::Instantiate();
	obj->AddComponent(new EditorCamera(g_hWnd));
	//obj->AddComponent(new AudioListener());
	//obj->AddComponent(new SphereCollider(2));
	//obj->AddComponent(new Rigidbody());

	return true;
}

void TestScene::FixedUpdate(float fElapsedTime) noexcept
{

}

void TestScene::Update(float fElapsedTime) noexcept
{
	if (INPUT->GetKeyDown(VK_LBUTTON))
	{
		if (Camera::GetMainCamera() == nullptr)
			CE_ASSERT("ckswns", "main camera does not exits");
		Ray ray = Camera::GetMainCamera()->ScreenPointToRay(INPUT->GetMousePosition());
		RaycastHit hit;

		if (Physics::Raycast(ray, hit, GameObjectLayer::OBJECT))
		{
			if(hit.collider->GetGameObject() != Camera::GetMainCamera()->GetGameObject())
				hit.collider->GetGameObject()->Destroy();
		}
	}
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
