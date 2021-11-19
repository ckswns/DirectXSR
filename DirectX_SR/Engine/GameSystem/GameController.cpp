#include "pch.h"
#include "GameController.h"
#include "ManagerDef.h"
#include "Assertion.h"
#include "MemoryPool.h"
#include "GameObject.h"
#include "PhysicsManager.h"

namespace ce
{
	HWND GameController::_hWnd = nullptr;

	GameController::GameController() noexcept
	{
		
	}

	bool GameController::Init(HWND hWnd, const Scene::KEY_VALUE_LIST& scenes, uint32 winX, uint32 winY, const char* fontFilePath, const char* fontFaceName) noexcept
	{
		_hWnd = hWnd;

		INPUT->Init(_hWnd);

		if (D3D9DEVICE->Init(hWnd, winX, winY, D3DCOLOR_ARGB(255, 50, 50, 50), fontFilePath, fontFaceName) == false)
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

	void GameController::GetWndMsg(UINT message, WPARAM wParam, LPARAM lParam) noexcept
	{

	}

	void GameController::Update(void) noexcept
	{
		TIMEMANAGER->Update();

		if(_hWnd)
			SetWindowTextA(_hWnd, std::to_string(TIMEMANAGER->GetFPSCount()).c_str());

		if (TIMEMANAGER->FrameLock())
			return;

		float deltaTime = TIMEMANAGER->GetDeltaTime();

		SCENEMANAGER->FixedUpdate(deltaTime);
		PhysicsManager::Instance()->Update();
		SCENEMANAGER->Update(deltaTime);
		SCENEMANAGER->LateUpdate(deltaTime);
#ifdef __USE_FMOD__
		FMODMANAGER->Update();
#endif
		INPUT->Update();
	}

	void GameController::Render(void) noexcept
	{
		if (TIMEMANAGER->FrameLock())
			return;

		float deltaTime = TIMEMANAGER->GetDeltaTime();

		D3D9DEVICE->Begin();

		SCENEMANAGER->Render(deltaTime);

		D3D9DEVICE->UIBegin();
		SCENEMANAGER->UIRender(deltaTime);
		D3D9DEVICE->UIEnd();

		D3D9DEVICE->End();
	}

	void GameController::Release(void) noexcept
	{
		SCENEMANAGER->Release();
		ASSETMANAGER->Release();
		D3D9DEVICE->Release();
#ifdef __USE_FMOD__
		FMODMANAGER->Release();
#endif

		MemoryPool<GameObject>::Release();

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