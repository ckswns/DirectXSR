#include "pch.h"
#include "GameController.h"
#include "ManagerDef.h"
#include "Assertion.h"

namespace ce
{
	GameController::GameController() noexcept
	{
	}

	bool GameController::Init(HWND hWnd, const Scene::KEY_VALUE_LIST& scenes, uint32 winX, uint32 winY) noexcept
	{
		if (D3D9DEVICE->Init(hWnd, winX, winY, D3DCOLOR_ARGB(255, 50, 50, 50)) == false)
		{
			CE_ASSERT("ckswns", "D3D9Device�� �ʱ�ȭ�� �����Ͽ����ϴ�.");
			return false;
		}

		if (TIMEMANAGER->Init() == false)
		{
			CE_ASSERT("ckswns", "TimeManager�� �ʱ�ȭ�� �����Ͽ����ϴ�.");
			return false;
		}
#ifdef __USE_FMOD__
		if (FMODMANAGER->Init() == false)
		{
			CE_ASSERT("ckswns", "SOUNDMANAGER�� �ʱ�ȭ�� �����Ͽ����ϴ�");
			return false;
		}
#endif

		if (scenes.empty())
		{
			CE_ASSERT("ckswns", "������ �� ����� ��� ���� �� �����ϴ�");
			return false;
		}

		for (int i = 0; i < scenes.size(); i++)
		{
			SCENEMANAGER->AddScene(scenes[i].second, scenes[i].first);
		}

		SCENEMANAGER->LoadScene(scenes[0].first);

		return true;
	}

	void GameController::Update(void) noexcept
	{
		TIMEMANAGER->Update();

		if (TIMEMANAGER->FrameLock())
			return;

		float deltaTime = TIMEMANAGER->GetDeltaTime();

		SCENEMANAGER->FixedUpdate(deltaTime);
		SCENEMANAGER->Update(deltaTime);
		SCENEMANAGER->LateUpdate(deltaTime);
#ifdef __USE_FMOD__
		FMODMANAGER->Update();
#endif
	}

	void GameController::Render(void) noexcept
	{
		if (TIMEMANAGER->FrameLock())
			return;

		float deltaTime = TIMEMANAGER->GetDeltaTime();

		D3D9DEVICE->Begin();

		SCENEMANAGER->Render(deltaTime);

		D3D9DEVICE->End();
	}

	void GameController::Release(void) noexcept
	{
		D3D9DEVICE->Release();
		SCENEMANAGER->Release();
#ifdef __USE_FMOD__
		FMODMANAGER->Release();
#endif
		ASSETMANAGER->Release();

		D3D9DEVICE->ReleaseSingleton();
		SCENEMANAGER->ReleaseSingleton();
#ifdef __USE_FMOD__
		FMODMANAGER->ReleaseSingleton();
#endif
		ASSETMANAGER->ReleaseSingleton();
		INIMANAGER->ReleaseSingleton();
		INPUT->ReleaseSingleton();
		TIMEMANAGER->ReleaseSingleton();
	}
}