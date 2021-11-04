#include "pch.h"
#include "Scene.h"
#include "GameObject.h"
#include "TypeDefine.h"
#include "Assertion.h"
#ifndef _ALGORITH_
#include <algorithm>
#endif

namespace ce
{
	void Scene::FixedUpdateXXX(float fElapsedTime) noexcept
	{
		for (int i = 0; i < static_cast<int>(GameObjectLayer::END); i++)
		{
			for (auto iter = _vGameObjs[i].begin(); iter != _vGameObjs[i].end();)
			{
				if ((*iter) == nullptr)
				{
					iter = _vGameObjs[i].erase(iter);
					continue;
				}

				if ((*iter)->GetActiveChanged())
				{
					if ((*iter)->GetActive())
						(*iter)->OnEnable();
					else
						(*iter)->OnDisable();

					(*iter)->SetActiveChanged(false);
				}

				if ((*iter)->GetActive() == false)
				{
					iter++;
					continue;
				}

				(*iter)->FixedUpdateXXX(fElapsedTime);
				(*iter)->FixedUpdate(fElapsedTime);

				if ((*iter)->GetWillDestroy())
				{
					(*iter)->ReleaseXXX();
					(*iter)->Release();
					
					delete (*iter);

					iter = _vGameObjs[i].erase(iter);
					continue;
				}

				iter++;
			}
		}
	}

	void Scene::UpdateXXX(float fElapsedTime) noexcept
	{
		for (int i = 0; i < static_cast<int>(GameObjectLayer::END); i++)
		{
			for (auto iter = _vGameObjs[i].begin(); iter != _vGameObjs[i].end();)
			{
				if ((*iter) == nullptr)
				{
					iter = _vGameObjs[i].erase(iter);
					continue;
				}

				if ((*iter)->GetActive() == false)
				{
					iter++;
					continue;
				}

				(*iter)->UpdateXXX(fElapsedTime);
				(*iter)->Update(fElapsedTime);

				if ((*iter)->GetWillDestroy())
				{
					(*iter)->ReleaseXXX();
					(*iter)->Release();
					delete (*iter);
					iter = _vGameObjs[i].erase(iter);
					continue;
				}

				iter++;
			}
		}
	}

	void Scene::LateUpdateXXX(float fElapsedTime) noexcept
	{
		for (int i = 0; i < static_cast<int>(GameObjectLayer::END); i++)
		{
			for (auto iter = _vGameObjs[i].begin(); iter != _vGameObjs[i].end();)
			{
				if ((*iter) == nullptr)
				{
					iter = _vGameObjs[i].erase(iter);
					continue;
				}

				if ((*iter)->GetActive() == false)
				{
					iter++;
					continue;
				}

				(*iter)->LateUpdateXXX(fElapsedTime);
				(*iter)->LateUpdate(fElapsedTime);

				if ((*iter)->GetWillDestroy())
				{
					(*iter)->ReleaseXXX();
					(*iter)->Release();
					delete (*iter);
					iter = _vGameObjs[i].erase(iter);
					continue;
				}

				iter++;
			}
		}
	}

	void Scene::RenderXXX(float fElapsedTime) noexcept
	{
		for (int i = 0; i < static_cast<int>(GameObjectLayer::UI); i++)
		{
			for (size_t j = 0; j < _vGameObjs[i].size(); j++)
			{
				if (_vGameObjs[i][j] == nullptr)
					continue;

				if (_vGameObjs[i][j]->GetActive() == false)
					continue;

				_vGameObjs[i][j]->RenderXXX();
				_vGameObjs[i][j]->Render();
			}
		}

		std::sort(_vGameObjs[static_cast<int>(GameObjectLayer::UI)].begin(), _vGameObjs[static_cast<int>(GameObjectLayer::UI)].end(),
			[](GameObject* lhs, GameObject* rhs)
			{
				return lhs->GetSortOrder() < rhs->GetSortOrder();
			});

		int i = static_cast<int>(GameObjectLayer::UI);

		for (size_t j = 0; j < _vGameObjs[i].size(); j++)
		{
			if (_vGameObjs[i][j] == nullptr)
				continue;

			if (_vGameObjs[i][j]->GetActive() == false)
				continue;

			_vGameObjs[i][j]->RenderXXX();
			_vGameObjs[i][j]->Render();
		}
	}

	void Scene::ReleaseXXX(void) noexcept
	{
		for (int i = 0; i < static_cast<int>(GameObjectLayer::END); i++)
		{
			for (auto iter = _vGameObjs[i].begin(); iter != _vGameObjs[i].end();)
			{
				if ((*iter) == nullptr)
				{
					iter = _vGameObjs[i].erase(iter);
					continue;
				}

				(*iter)->ReleaseXXX();
				(*iter)->Release();
				delete ((*iter));
				iter = _vGameObjs[i].erase(iter);
			}
		}
	}

	GameObject* Scene::InsertGameObject(GameObject* obj) noexcept
	{
		if (obj->_bIsInit == false)
			obj->Init();

		if (obj->_eLayer == GameObjectLayer::END)
			CE_ASSERT("ckswns", "GameObject의 레이어는 END일 수 없습니다");

		_vGameObjs[static_cast<int>(obj->_eLayer)].push_back(obj);

		return obj;
	}
}