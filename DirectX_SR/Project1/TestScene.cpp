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

TestScene::TestScene(void) noexcept
{
}

TestScene::~TestScene(void) noexcept
{
}

bool TestScene::Init(void) noexcept
{
	GameObject* obj;

	obj = GameObject::Instantiate();
	obj->AddComponent(new CubeObject());
	AudioSource* as = static_cast<AudioSource*>(obj->AddComponent(new AudioSource()));
	as->LoadAudio(ASSETMANAGER->GetAudioAsset("Asset\\Audio\\DiabloInit.wav"));
	as->SetLoop(true);
	as->SetSoundWorld(true);

	obj = GameObject::Instantiate();
	obj->AddComponent(new EditorCamera(g_hWnd));
	obj->AddComponent(new AudioListener());
	obj->AddComponent(new SphereCollider(2));
	obj->AddComponent(new Rigidbody());

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
