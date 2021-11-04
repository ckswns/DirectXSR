#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Assertion.h"

namespace ce
{
	SceneManager::SceneManager(void) noexcept :
		_pActiveScene(nullptr),
		_activeSceneID("")
	{

	}

	bool SceneManager::LoadScene(std::string id) noexcept
	{
		Scene* scene = nullptr;
		auto iter = _mapScene.find(id);

		if (iter == _mapScene.end())
			return false;

		scene = iter->second;

		if (_pActiveScene == nullptr)
		{
			_pActiveScene = scene;
			_pActiveScene->Init();
		}
		else
		{
			_pNextScene = scene;
			_pNextScene->Init();
		}

		return true;
	}

	bool SceneManager::LoadSceneAsync(std::string id) noexcept
	{
		return false;
	}

	bool SceneManager::LoadSceneAdditive(std::string key) noexcept
	{
		return false;
	}

	bool SceneManager::UnloadScene(std::string id) noexcept
	{
		return false;
	}

	void SceneManager::FixedUpdate(float fElapedTime) noexcept
	{
		if (_pNextScene)
		{
			_pActiveScene->Release();
			_pActiveScene = _pNextScene;
			_pNextScene = nullptr;
		}

		if (_pActiveScene)
		{
			_pActiveScene->FixedUpdateXXX(fElapedTime);
			_pActiveScene->FixedUpdate(fElapedTime);
		}
	}

	void SceneManager::Update(float fElapedTime) noexcept
	{
		if (_pActiveScene)
		{
			_pActiveScene->UpdateXXX(fElapedTime);
			_pActiveScene->Update(fElapedTime);
		}
	}

	void SceneManager::LateUpdate(float fElapedTime) noexcept
	{
		if (_pActiveScene)
		{
			_pActiveScene->LateUpdateXXX(fElapedTime);
			_pActiveScene->LateUpdate(fElapedTime);
		}
	}

	void SceneManager::Render(float fElapedTime) noexcept
	{
		if (_pActiveScene)
		{
			_pActiveScene->RenderXXX(fElapedTime);
			_pActiveScene->Render(fElapedTime);
		}
	}

	void SceneManager::Release(void) noexcept
	{
		for (auto iter = _mapScene.begin(); iter != _mapScene.end(); iter++)
		{
			iter->second->ReleaseXXX();
			iter->second->Release();
			delete iter->second;
			iter->second = nullptr;
		}

		_mapScene.clear();
	}

	bool SceneManager::AddScene(Scene* pScene, std::string key) noexcept
	{
		if (_mapScene.find(key) != _mapScene.end())
		{
			CE_ASSERT("ckswns", "중복키가 존재하여 씬삽입에 실패하였습니다");
			return false;
		}

		if (pScene == nullptr)
		{
			CE_ASSERT("ckswns", "삽입을 시도한 씬이 nullptr입니다");
			return false;
		}

		_mapScene.insert(std::make_pair(key, pScene));

		return true;
	}
}