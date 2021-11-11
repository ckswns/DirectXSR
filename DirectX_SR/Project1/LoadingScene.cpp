#include "pch.h"
#include "LoadingScene.h"
#include "ManagerDef.h"

bool LoadingScene::Init(void) noexcept
{
	ASSETMANAGER->LoadAssetFolder("Asset");
	
	return true;
}

void LoadingScene::FixedUpdate(float fElapsedTime) noexcept
{
	if (ASSETMANAGER->GetLoadingProgress() == 1)
		SCENEMANAGER->LoadScene("test");
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
