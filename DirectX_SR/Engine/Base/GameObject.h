#pragma once

#ifndef PURE
#define PURE =0
#endif
#ifndef _QUEUE_
#include <queue>
#endif
#include "TypeDefine.h"
#include "ConstValues.h"
#include "MemoryPool.h"

namespace ce
{
	class Transform;
	class Component;
	class SceneManager;
	class Scene;
	class Behaviour;
	class Collider;

	class GameObject final //: public MemoryPool<GameObject>
	{
	public:		using								TList = std::vector<GameObject*>;
	public:		using								QUEUE = std::queue<GameObject*>;

	public:		explicit 							GameObject() noexcept;
	public:											~GameObject() noexcept;

	private:	void								OnEnable(void) noexcept;
	private:	void								OnDisable(void) noexcept;

	private:	void								FixedUpdateXXX(float fElapsedTime) noexcept;
	private:	void								UpdateXXX(float fElapsedTime) noexcept;
	private:	void								LateUpdateXXX(float fElapsedTime) noexcept;
	private:	void								RenderXXX(void) noexcept;
	private:	void								ReleaseXXX(void) noexcept;

	public:		void								OnMouseEnterXXX(void) noexcept;
	public:		void								OnMouseLeaveXXX(void) noexcept;
	public:		void								OnMouseOverXXX(void) noexcept;
	public:		void								OnMouseDownXXX(void) noexcept;
	public:		void								OnMouseUpXXX(void) noexcept;
	public:		void								OnMouseHeldDownXXX(void) noexcept;

	public:		void								OnCollisionEnterXXX(Collider* mine, Collider* other) noexcept;
	public:		void								OnCollisionStayXXX(Collider* mine, Collider* other) noexcept;
	public:		void								OnCollisionExitXXX(Collider* mine, Collider* other) noexcept;

	public:		void								SetDontDestroy(bool b) noexcept { _bDontDestroy = b; }
	public:		bool								GetDontDestroy(void) const noexcept { return _bDontDestroy; }

	public:		GameObjectLayer						GetLayer(void) const noexcept { return _eLayer; }

	public:		void								SetLayer(GameObjectLayer _layer) noexcept;
	public:		virtual int32						GetSortOrder(void) const noexcept { return _nSortOrder; }
	public:		void								SetSortOrder(int order) noexcept { _nSortOrder = order; }

	public:		std::string							GetName(void) const noexcept { return _strName; }
	public:		const GameObjectTag&				GetTag(void) const noexcept { return _eTag; }

	public:		void								SetName(std::string name) noexcept { _strName = name; }
	public:		void								SetTag(GameObjectTag tag) noexcept { _eTag = tag; }

	public:		Transform* const					GetTransform(void) noexcept;

	public:		Component* const					GetComponent(COMPONENT_ID::ID typeID) noexcept;
	public:		const std::vector<Component*>&		GetComponents(void) noexcept { return _pComponents; }

	public:		Component* const					AddComponent(Component* value) noexcept;
	public:		bool								HasComponent(Component* value) const noexcept;
	public:		bool								HasComponent(COMPONENT_ID::ID typeID) const noexcept;

	public:		void								RemoveComponent(Component* value) noexcept;

	public:		bool								GetActive(void) const noexcept { return _bWorldActive; }
	public:		void								SetActive(bool active) noexcept;

	private:	bool								GetWillDestroy(void) const noexcept { return _bWillDestroy; }
	public:		void								Destroy(void) noexcept;

	private:	void								SetWorldActive(bool active) noexcept;
	private:	bool								GetLocalActive(void) const noexcept { return _bLocalActive; }

	private:	bool								GetActiveChanged(void) noexcept { return _bActiveChanged; }
	private:	void								SetActiveChanged(bool active) noexcept { _bActiveChanged = active; }

	public:		void								OnAnimationEvent(int frame, std::string eventName);

	public:		static GameObject*					Instantiate() noexcept;
	public:		static void							Destroy(GameObject* obj) noexcept;

	public:		static GameObject*					FindObjectByName(std::string name) noexcept;
	public:		static GameObject*					FindObjectByTag(GameObjectTag tag) noexcept;
	public:		static std::vector<GameObject*>		FindObjectsByName(std::string name) noexcept;
	public:		static std::vector<GameObject*>		FindObjectsByTag(GameObjectTag tag) noexcept;

	public:		static GameObject*					FindObjectByName(GameObjectLayer layer, std::string name) noexcept;
	public:		static GameObject*					FindObjectByTag(GameObjectLayer layer, GameObjectTag tag) noexcept;
	public:		static std::vector<GameObject*>		FindObjectsByName(GameObjectLayer layer, std::string name) noexcept;
	public:		static std::vector<GameObject*>		FindObjectsByTag(GameObjectLayer layer, GameObjectTag tag) noexcept;

	protected:	GameObjectLayer						_eLayer;
	protected:	GameObjectTag						_eTag;

	protected:	bool								_bWorldActive = true;
	protected:	bool								_bLocalActive = true;
	protected:	bool								_bActiveChanged = false;

	protected:	bool								_bDontDestroy = false;
	protected:	bool								_bWillDestroy = false;

	protected:	int32								_nSortOrder;

	protected:	std::string							_strName;

	private:	Transform*							_pTransform;
	private:	std::vector<Component*>				_pComponents;

	private:	COMPONENT_ID::ID					_hasComponentID;

	private:	friend								SceneManager;
	private:	friend								Scene;
	};
}
