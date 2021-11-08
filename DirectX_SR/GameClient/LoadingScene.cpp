#include "pch.h"
#include "LoadingScene.h"
#include "ManagerDef.h"

LoadingScene::LoadingScene(void) noexcept
{

}

bool LoadingScene::Init(void) noexcept
{
	ASSETMANAGER->LoadAssetFolder("Asset");

	return true;
}

void LoadingScene::FixedUpdate(float fElapsedTime) noexcept
{

}

void LoadingScene::Update(float fElapsedTime) noexcept
{

}

void LoadingScene::LateUpdate(float fElapsedTime) noexcept
{

}

void LoadingScene::Render(float fElapsedTime) noexcept
{

}

void LoadingScene::Release(void) noexcept
{

}
