#include "pch.h"
#include "Scene.h"
#include "GameObject.h"
#include "TypeDefine.h"
#include "Assertion.h"
#ifndef _ALGORITH_
#include <algorithm>
#endif
#include "RectTransform.h"
#include "GameController.h"
#include "ManagerDef.h"
#include "Camera.h"
#include "Transform.h"
#include "Vector3.h"


using namespace ce::UI;

namespace ce
{
	void Scene::OnChangeGameObjectLayerXXX(std::pair<GameObjectLayer, GameObject*> obj) noexcept
	{
		_vLayerChangedObj.emplace_back(obj);
	}

	void Scene::InsertPrevSceneGameObj(Scene* prevScene) noexcept
	{
		for (int i = 0; i < static_cast<int>(GameObjectLayer::END); i++)
		{
			for (auto iter = prevScene->_vGameObjs[i].begin(); iter != prevScene->_vGameObjs[i].end();)
			{
				_vGameObjs[i].emplace_back(*iter);
				iter = prevScene->_vGameObjs[i].erase(iter);
				continue;
			}
		}
	}

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

				if ((*iter)->GetWillDestroy())
				{
					(*iter)->ReleaseXXX();

					delete (*iter);
					iter = _vGameObjs[i].erase(iter);
					continue;
				}

				iter++;
			}
		}

		CheckUIPicking();

		if (_vGameObjWaitForInsert.empty() == false)
		{
			for (auto iter = _vGameObjWaitForInsert.begin(); iter != _vGameObjWaitForInsert.end();)
			{
				GameObject* obj = (*iter);
				int layer = static_cast<int>(obj->_eLayer);
				_vGameObjs[layer].emplace_back(obj);
				iter = _vGameObjWaitForInsert.erase(iter);
			}
		}

		if (_vLayerChangedObj.empty() == false)
		{
			for (int i = 0; i < _vLayerChangedObj.size(); i++)
			{
				int layer = static_cast<int>(_vLayerChangedObj[i].first);
				auto iter = std::find(_vGameObjs[layer].begin(), _vGameObjs[layer].end(), _vLayerChangedObj[i].second);

				if (iter != _vGameObjs[layer].end())
				{
					_vGameObjs[layer].erase(iter);
					int newLayer = static_cast<int>(_vLayerChangedObj[i].second->GetLayer());
					_vGameObjs[newLayer].emplace_back(_vLayerChangedObj[i].second);
				}
				else
				{
					layer = static_cast<int>(_vLayerChangedObj[i].second->_eLayer);
					auto iter2 = std::find(_vGameObjs[layer].begin(), _vGameObjs[layer].end(), _vLayerChangedObj[i].second);

					if (iter2 == _vGameObjs[layer].end())
					{
						CE_ASSERT("ckswns", "레이어 이동중에 게임오브젝트가 유실되었을 가능성이 있습니다\n개발자에게 문의하세요");
					}
				}
			}

			_vLayerChangedObj.clear();
		}
	}

	void Scene::RenderXXX(float fElapsedTime) noexcept
	{
		//SortObjByCamera(GameObjectLayer::OBJECT);
		SortObjByCamera(GameObjectLayer::ALPHA);

		for (int i = 0; i < static_cast<int>(GameObjectLayer::UI); i++)
		{
			for (size_t j = 0; j < _vGameObjs[i].size(); j++)
			{
				if (_vGameObjs[i][j] == nullptr)
					continue;

				if (_vGameObjs[i][j]->GetActive() == false)
					continue;

				_vGameObjs[i][j]->RenderXXX();
			}
		}
	}

	void Scene::UIRenderXXX(float fElapsedTime) noexcept
	{
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
		}
	}

	void Scene::UnloadXXX(void) noexcept
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

				if ((*iter)->GetDontDestroy())
				{
					iter++;
					continue;
				}

				(*iter)->ReleaseXXX();

				delete ((*iter));
				iter = _vGameObjs[i].erase(iter);
			}
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

				delete ((*iter));
				iter = _vGameObjs[i].erase(iter);
			}
		}
	}

	void Scene::SortObjByCamera(GameObjectLayer layer) noexcept
	{
		D3DXVECTOR3 position;
		int index = static_cast<int>(layer);

		if (Camera::GetMainCamera() != nullptr)
			position = Camera::GetMainCamera()->GetTransform()->GetWorldPosition();
		else
			position = D3DXVECTOR3(0, 0, 0);

		std::sort(_vGameObjs[index].begin(), _vGameObjs[index].end(), [&](GameObject* lhs, GameObject* rhs) {
			Vector3 a = (position - lhs->GetTransform()->GetWorldPosition());
			Vector3 b = (position - rhs->GetTransform()->GetWorldPosition());

			return (a.SqrLength() > b.SqrLength());
			});
	}

	void Scene::CheckUIPicking(void) noexcept
	{
		bool picked = false;
		int layer = static_cast<int>(GameObjectLayer::UI);
		
		POINT cursor;
		MOUSE_STATE mouseState = MOUSE_STATE::UP;

		GetCursorPos(&cursor);
		ScreenToClient(GameController::GetHandle(), &cursor);

		if (INPUT->GetKeyUp(VK_LBUTTON))
			mouseState = MOUSE_STATE::UP;
		if (INPUT->GetKeyStay(VK_LBUTTON))
			mouseState = MOUSE_STATE::HELD_DOWN;
		if (INPUT->GetKeyDown(VK_LBUTTON))
			mouseState = MOUSE_STATE::DOWN;

		std::sort(_vGameObjs[layer].begin(), _vGameObjs[layer].end(),
			[](const GameObject* lhs, const GameObject* rhs)
			{
				return (lhs->GetSortOrder() > rhs->GetSortOrder()) ? true : false;
			});

		for (auto iter = _vGameObjs[layer].begin(); iter != _vGameObjs[layer].end();)
		{
			if ((*iter)->GetActive() == false)
			{
				iter++;
				continue;
			}

			RectTransform* rectTransform = static_cast<RectTransform*>((*iter)->GetComponent(COMPONENT_ID::RECT_TRANSFORM));

			if (rectTransform->GetInteractive() == false)
			{
				iter++;
				continue;
			}

			if (picked == false)
			{
				RECT rt = rectTransform->GetPickingRect();

				if (PtInRect(&rt, cursor))
				{
					picked = true;

					switch (mouseState)
					{
					case MOUSE_STATE::DOWN:
						(*iter)->OnMouseDownXXX();
						rectTransform->SetPrevPickingState(PICKING_STATE::DOWN);
						break;
					case MOUSE_STATE::HELD_DOWN:
						if (rectTransform->GetPrevPickingState() == PICKING_STATE::DOWN || rectTransform->GetPrevPickingState() == PICKING_STATE::HELDDOWN)
						{
							(*iter)->OnMouseHeldDownXXX();
							rectTransform->SetPrevPickingState(PICKING_STATE::HELDDOWN);
						}
						else
						{
							(*iter)->OnMouseOverXXX();
							rectTransform->SetPrevPickingState(PICKING_STATE::OVER);
						}
						break;
					case MOUSE_STATE::UP:
						if (rectTransform->GetPrevPickingState() == PICKING_STATE::DOWN || rectTransform->GetPrevPickingState() == PICKING_STATE::HELDDOWN)
						{
							(*iter)->OnMouseUpXXX();
							rectTransform->SetPrevPickingState(PICKING_STATE::UP);
						}
						else
						{
							(*iter)->OnMouseOverXXX();
							rectTransform->SetPrevPickingState(PICKING_STATE::OVER);
						}
						break;
					default:
						(*iter)->OnMouseOverXXX();
						rectTransform->SetPrevPickingState(PICKING_STATE::OVER);
						break;
					}
				}

				else
				{
					if (rectTransform->GetPrevPickingState() == PICKING_STATE::UP ||
						rectTransform->GetPrevPickingState() == PICKING_STATE::DOWN ||
						rectTransform->GetPrevPickingState() == PICKING_STATE::OVER ||
						rectTransform->GetPrevPickingState() == PICKING_STATE::HELDDOWN)
					{
						(*iter)->OnMouseLeaveXXX();
					}
					rectTransform->SetPrevPickingState(PICKING_STATE::LEAVE);
				}

				iter++;
				continue;
			}

			{
				if (rectTransform->GetPrevPickingState() == PICKING_STATE::UP ||
					rectTransform->GetPrevPickingState() == PICKING_STATE::DOWN ||
					rectTransform->GetPrevPickingState() == PICKING_STATE::OVER ||
					rectTransform->GetPrevPickingState() == PICKING_STATE::HELDDOWN)
				{
					(*iter)->OnMouseLeaveXXX();
				}

				rectTransform->SetPrevPickingState(PICKING_STATE::LEAVE);

				iter++;
			}
		}
	}

	GameObject* Scene::InsertGameObject(GameObject* obj) noexcept
	{
		if (obj->_eLayer == GameObjectLayer::END)
			obj->_eLayer = GameObjectLayer::OBJECT;

		_vGameObjWaitForInsert.push_back(obj);

		return obj;
	}
}