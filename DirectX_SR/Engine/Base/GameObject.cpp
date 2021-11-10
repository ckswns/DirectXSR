#include "pch.h"
#include "GameObject.h"
#include "Transform.h"
#include "Component.h"
#include "Assertion.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Behaviour.h"

namespace ce
{
    GameObject::GameObject() noexcept
		: _eLayer(GameObjectLayer::END)
		, _eTag(GameObjectTag::DEFAULT)
		, _strName("")
		, _nSortOrder(0)
		, _pTransform(nullptr)
		, _hasComponentID(0)
	{
		_pTransform = new Transform(this);
		_pComponents.emplace_back(_pTransform);
		_hasComponentID = COMPONENT_ID::TRANSFORM;
	}

	GameObject::~GameObject() noexcept
	{
		for (size_t i = 0; i < _pComponents.size(); i++)
		{
			if (_pComponents[i] != nullptr)
			{
				_pComponents[i]->Release();
				delete _pComponents[i];
				_pComponents[i] = nullptr;
			}
		}
	}

	void GameObject::OnEnable(void) noexcept
	{
		for (int i = 0; i < _pComponents.size(); i++)
		{
			_pComponents[i]->OnEnable();
		}
	}

	void GameObject::OnDisable(void) noexcept
	{
		for (int i = 0; i < _pComponents.size(); i++)
		{
			_pComponents[i]->OnDisable();
		}
	}

    void GameObject::FixedUpdateXXX(float fElapsedTime) noexcept
    {
		for (size_t i = 0; i < _pComponents.size(); i++)
		{
			_pComponents[i]->FixedUpdate(fElapsedTime);
		}
    }

    void GameObject::UpdateXXX(float fElapsedTime) noexcept
    {
		for (size_t i = 0; i < _pComponents.size(); i++)
		{
			_pComponents[i]->Update(fElapsedTime);
		}
    }

    void GameObject::LateUpdateXXX(float fElapsedTime) noexcept
    {
		for (size_t i = 0; i < _pComponents.size(); i++)
		{
			_pComponents[i]->LateUpdate(fElapsedTime);
		}
    }

    void GameObject::RenderXXX(void) noexcept
    {
		for (size_t i = 0; i < _pComponents.size(); i++)
		{
			_pComponents[i]->Render();
		}
    }

    void GameObject::ReleaseXXX(void) noexcept
    {
		for (size_t i = 0; i < _pComponents.size(); i++)
		{
			_pComponents[i]->Release();
			delete _pComponents[i];
			_pComponents[i] = nullptr;
		}
    }

	void GameObject::SetLayer(GameObjectLayer _layer) noexcept
	{
		if (_eLayer == _layer)
			return;
		GameObjectLayer old = _eLayer;
		_eLayer = _layer;

		SceneManager::Instance()->GetActiveScene()->OnChangeGameObjectLayerXXX(std::make_pair(old, this));
	}

    Transform* const GameObject::GetTransform(void) noexcept
    {
        return _pTransform;
    }

    Component* const GameObject::GetComponent(COMPONENT_ID::ID typeID) noexcept
    {
		if ((_hasComponentID & typeID) == false)
			return nullptr;

		auto iter = std::find_if(_pComponents.begin(), _pComponents.end(),
			[&typeID](Component* value) { return value->GetID() & typeID; });

		if (iter == _pComponents.end())
			return nullptr;

		return *iter;
    }

    Component* const GameObject::AddComponent(Component* value) noexcept
    {
		if (value->GetIsUniq())
		{
			if (_hasComponentID & value->GetID())
			{
				CE_ASSERT("ckswns", "해당 컴퍼넌트는 중복 삽입이 불가능합니다.");
				return nullptr;
			}
		}

		if (value->GetHasDependencyComponent())
		{
			if (!(_hasComponentID & value->GetDependencyID()))
			{
				CE_ASSERT("ckswns", "해당 컴퍼넌트의 필수 컴퍼넌트가 이 게임오브젝트에 존재하지 않습니다.");
				return nullptr;
			}
		}

		value->SetGameObjectXXX(this);
		value->Init();

		//if (value->GetID() == CONST_VALUES::COMPONENT_ID::COLLIDER2D)
		//{
		//	GAMEOBJECTMANAGER->InsertPhysicsObjectXXXX(static_cast<Collider2D*>(value));
		//}

		_pComponents.emplace_back(value);
		_hasComponentID |= value->GetID();

		return value;
    }

    bool GameObject::HasComponent(Component* value) const noexcept
    {
		return _hasComponentID & value->GetID() ? true : false;
    }

    bool GameObject::HasComponent(COMPONENT_ID::ID typeID) const noexcept
    {
		return _hasComponentID & typeID ? true : false;
    }

    void GameObject::RemoveComponent(Component* value) noexcept
    {
		if ((_hasComponentID & value->GetID()) == false)
			return;

		if (value->GetID() & COMPONENT_ID::TRANSFORM)
			return;

		auto iter = std::find(_pComponents.begin(), _pComponents.end(), value);

		if (iter == _pComponents.end())
			return;

		_hasComponentID ^= (*iter)->GetID();

		delete* iter;
		*iter = nullptr;

		_pComponents.erase(iter);
    }

    void GameObject::SetActive(bool active) noexcept
    {
		if (_bLocalActive == active)
			return;

		Transform* transform = GetTransform();
		Transform* parent = transform->GetParent();

		if (parent == nullptr)
		{
			_bWorldActive = _bLocalActive = active;
			_bActiveChanged = true;
		}
		else
		{
			_bLocalActive = active;

			if (parent->GetGameObject()->GetActive() == false)
				_bWorldActive = false;

			else
			{
				if (_bWorldActive != active)
					_bActiveChanged = true;

				_bWorldActive = active;
			}
		}

		auto childs = transform->GetChilds();

		for (auto iter = childs.begin(); iter != childs.end(); iter++)
		{
			(*iter)->GetGameObject()->SetWorldActive(active);
		}
    }

  //  void GameObject::Destroy(void) noexcept
  //  {
		//if (_bDontDestroy == false)
		//	_bWillDestroy = true;
  //  }

    void GameObject::SetWorldActive(bool active) noexcept
    {
		if (_bLocalActive == false)
			_bWorldActive = false;
		else
		{
			if (_bWorldActive != active)
				_bActiveChanged = true;

			_bWorldActive = active;
		}

		auto childs = GetTransform()->GetChilds();

		for (auto iter = childs.begin(); iter != childs.end(); iter++)
		{
			(*iter)->GetGameObject()->SetWorldActive(_bWorldActive);
		}
    }

	void GameObject::OnAnimationEvent(int frame, std::string eventName)
	{
	}

	GameObject* GameObject::Instantiate() noexcept
	{
		if (SceneManager::Instance()->GetActiveScene() != nullptr)
			return SceneManager::Instance()->GetActiveScene()->InsertGameObject(new GameObject());
		else
			return nullptr;
	}

	void GameObject::Destroy(GameObject* obj) noexcept
	{

	}

	GameObject* GameObject::FindObjectByName(std::string name) noexcept
	{
		if (SceneManager::Instance()->GetActiveScene() == nullptr)
		{
			CE_ASSERT("ckswns", "ActiveScene이 nullptr입니다");
			return nullptr;
		}
		
		const std::vector<GameObject*>& vObjects_Background = SceneManager::Instance()->GetActiveScene()->GetSceneGameObjectXXXXXXXXXXXX(GameObjectLayer::BACKGROUND);

		for (int i = 0; i < vObjects_Background.size(); i++)
		{
			if (vObjects_Background[i]->GetName() == name)
				return vObjects_Background[i];
		}

		const std::vector<GameObject*>& vObjects_Object = SceneManager::Instance()->GetActiveScene()->GetSceneGameObjectXXXXXXXXXXXX(GameObjectLayer::OBJECT);

		for (int i = 0; i < vObjects_Object.size(); i++)
		{
			if (vObjects_Object[i]->GetName() == name)
				return vObjects_Object[i];
		}

		const std::vector<GameObject*>& vObjects_UI = SceneManager::Instance()->GetActiveScene()->GetSceneGameObjectXXXXXXXXXXXX(GameObjectLayer::UI);

		for (int i = 0; i < vObjects_UI.size(); i++)
		{
			if (vObjects_UI[i]->GetName() == name)
				return vObjects_UI[i];
		}

		const std::vector<GameObject*>& vObjects_EFFECT = SceneManager::Instance()->GetActiveScene()->GetSceneGameObjectXXXXXXXXXXXX(GameObjectLayer::EFFECT);

		for (int i = 0; i < vObjects_EFFECT.size(); i++)
		{
			if (vObjects_EFFECT[i]->GetName() == name)
				return vObjects_EFFECT[i];
		}

		return nullptr;
	}

	GameObject* GameObject::FindObjectByTag(GameObjectTag tag) noexcept
	{
		const std::vector<GameObject*>& vObjects_Background = SceneManager::Instance()->GetActiveScene()->GetSceneGameObjectXXXXXXXXXXXX(GameObjectLayer::BACKGROUND);

		for (int i = 0; i < vObjects_Background.size(); i++)
		{
			if (vObjects_Background[i]->GetTag() == tag)
				return vObjects_Background[i];
		}

		const std::vector<GameObject*>& vObjects_Object = SceneManager::Instance()->GetActiveScene()->GetSceneGameObjectXXXXXXXXXXXX(GameObjectLayer::OBJECT);

		for (int i = 0; i < vObjects_Object.size(); i++)
		{
			if (vObjects_Object[i]->GetTag() == tag)
				return vObjects_Object[i];
		}

		const std::vector<GameObject*>& vObjects_UI = SceneManager::Instance()->GetActiveScene()->GetSceneGameObjectXXXXXXXXXXXX(GameObjectLayer::UI);

		for (int i = 0; i < vObjects_UI.size(); i++)
		{
			if (vObjects_UI[i]->GetTag() == tag)
				return vObjects_UI[i];
		}

		const std::vector<GameObject*>& vObjects_EFFECT = SceneManager::Instance()->GetActiveScene()->GetSceneGameObjectXXXXXXXXXXXX(GameObjectLayer::EFFECT);

		for (int i = 0; i < vObjects_EFFECT.size(); i++)
		{
			if (vObjects_EFFECT[i]->GetTag() == tag)
				return vObjects_EFFECT[i];
		}

		return nullptr;
	}

	std::vector<GameObject*> GameObject::FindObjectsByName(std::string name) noexcept
	{
		std::vector<GameObject*> result;

		if (SceneManager::Instance()->GetActiveScene() == nullptr)
		{
			CE_ASSERT("ckswns", "ActiveScene이 nullptr입니다");
			return result;
		}

		const std::vector<GameObject*>& vObjects_Background = SceneManager::Instance()->GetActiveScene()->GetSceneGameObjectXXXXXXXXXXXX(GameObjectLayer::BACKGROUND);

		for (int i = 0; i < vObjects_Background.size(); i++)
		{
			if (vObjects_Background[i]->GetName() == name)
				result.emplace_back(vObjects_Background[i]);
		}

		const std::vector<GameObject*>& vObjects_Object = SceneManager::Instance()->GetActiveScene()->GetSceneGameObjectXXXXXXXXXXXX(GameObjectLayer::OBJECT);

		for (int i = 0; i < vObjects_Object.size(); i++)
		{
			if (vObjects_Object[i]->GetName() == name)
				result.emplace_back(vObjects_Object[i]);
		}

		const std::vector<GameObject*>& vObjects_UI = SceneManager::Instance()->GetActiveScene()->GetSceneGameObjectXXXXXXXXXXXX(GameObjectLayer::UI);

		for (int i = 0; i < vObjects_UI.size(); i++)
		{
			if (vObjects_UI[i]->GetName() == name)
				result.emplace_back(vObjects_UI[i]);
		}

		const std::vector<GameObject*>& vObjects_EFFECT = SceneManager::Instance()->GetActiveScene()->GetSceneGameObjectXXXXXXXXXXXX(GameObjectLayer::EFFECT);

		for (int i = 0; i < vObjects_EFFECT.size(); i++)
		{
			if (vObjects_EFFECT[i]->GetName() == name)
				result.emplace_back(vObjects_EFFECT[i]);
		}

		return result;
	}

	std::vector<GameObject*> GameObject::FindObjectsByTag(GameObjectTag tag) noexcept
	{
		std::vector<GameObject*> result;

		if (SceneManager::Instance()->GetActiveScene() == nullptr)
		{
			CE_ASSERT("ckswns", "ActiveScene이 nullptr입니다");
			return result;
		}

		const std::vector<GameObject*>& vObjects_Background = SceneManager::Instance()->GetActiveScene()->GetSceneGameObjectXXXXXXXXXXXX(GameObjectLayer::BACKGROUND);

		for (int i = 0; i < vObjects_Background.size(); i++)
		{
			if (vObjects_Background[i]->GetTag() == tag)
				result.emplace_back(vObjects_Background[i]);
		}

		const std::vector<GameObject*>& vObjects_Object = SceneManager::Instance()->GetActiveScene()->GetSceneGameObjectXXXXXXXXXXXX(GameObjectLayer::OBJECT);

		for (int i = 0; i < vObjects_Object.size(); i++)
		{
			if (vObjects_Object[i]->GetTag() == tag)
				result.emplace_back(vObjects_Object[i]);
		}

		const std::vector<GameObject*>& vObjects_UI = SceneManager::Instance()->GetActiveScene()->GetSceneGameObjectXXXXXXXXXXXX(GameObjectLayer::UI);

		for (int i = 0; i < vObjects_UI.size(); i++)
		{
			if (vObjects_UI[i]->GetTag() == tag)
				result.emplace_back(vObjects_UI[i]);
		}

		const std::vector<GameObject*>& vObjects_EFFECT = SceneManager::Instance()->GetActiveScene()->GetSceneGameObjectXXXXXXXXXXXX(GameObjectLayer::EFFECT);

		for (int i = 0; i < vObjects_EFFECT.size(); i++)
		{
			if (vObjects_EFFECT[i]->GetTag() == tag)
				result.emplace_back(vObjects_EFFECT[i]);
		}

		return result;
	}

	GameObject* GameObject::FindObjectByName(GameObjectLayer layer, std::string name) noexcept
	{
		if (SceneManager::Instance()->GetActiveScene() == nullptr)
		{
			CE_ASSERT("ckswns", "ActiveScene이 nullptr입니다");
			return nullptr;
		}

		const std::vector<GameObject*>& vObjects = SceneManager::Instance()->GetActiveScene()->GetSceneGameObjectXXXXXXXXXXXX(layer);

		for (int i = 0; i < vObjects.size(); i++)
		{
			if (vObjects[i]->GetName() == name)
				return vObjects[i];
		}

		return nullptr;
	}

	GameObject* GameObject::FindObjectByTag(GameObjectLayer layer, GameObjectTag tag) noexcept
	{
		if (SceneManager::Instance()->GetActiveScene() == nullptr)
		{
			CE_ASSERT("ckswns", "ActiveScene이 nullptr입니다");
			return nullptr;
		}

		const std::vector<GameObject*>& vObjects = SceneManager::Instance()->GetActiveScene()->GetSceneGameObjectXXXXXXXXXXXX(layer);

		for (int i = 0; i < vObjects.size(); i++)
		{
			if (vObjects[i]->GetTag() == tag)
				return vObjects[i];
		}

		return nullptr;
	}

	std::vector<GameObject*> GameObject::FindObjectsByName(GameObjectLayer layer, std::string name) noexcept
	{
		std::vector<GameObject*> result;

		if (SceneManager::Instance()->GetActiveScene() == nullptr)
		{
			CE_ASSERT("ckswns", "ActiveScene이 nullptr입니다");
			return result;
		}

		const std::vector<GameObject*>& vObjects = SceneManager::Instance()->GetActiveScene()->GetSceneGameObjectXXXXXXXXXXXX(layer);

		for (int i = 0; i < vObjects.size(); i++)
		{
			if (vObjects[i]->GetName() == name)
				result.emplace_back(vObjects[i]);
		}

		return result;
	}

	std::vector<GameObject*> GameObject::FindObjectsByTag(GameObjectLayer layer, GameObjectTag tag) noexcept
	{
		std::vector<GameObject*> result;

		if (SceneManager::Instance()->GetActiveScene() == nullptr)
		{
			CE_ASSERT("ckswns", "ActiveScene이 nullptr입니다");
			return result;
		}

		const std::vector<GameObject*>& vObjects = SceneManager::Instance()->GetActiveScene()->GetSceneGameObjectXXXXXXXXXXXX(layer);

		for (int i = 0; i < vObjects.size(); i++)
		{
			if (vObjects[i]->GetTag() == tag)
				result.emplace_back(vObjects[i]);
		}

		return result;
	}
}