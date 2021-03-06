#pragma once

#include "INoncopyable.h"
#include "TypeDefine.h"
#ifndef _QUEUE_
#include <queue>
#endif
#ifndef PURE
#define PURE =0
#endif
#include "GameObject.h"

namespace ce
{
	class SceneManager;

	class Scene : public INoncopyable
	{
	public:		explicit					Scene(void) noexcept { __noop; }
	public:		virtual						~Scene(void) noexcept { __noop; }

	public:		using						KEY_VALUE_LIST = std::vector<std::pair<std::string, Scene*>>;
	public:		using						LAYER_VALUE_LIST = std::vector<std::pair<GameObjectLayer, GameObject*>>;

	public:		virtual bool				Init(void) noexcept { return true; }
	public:		virtual	void				FixedUpdate(float fElapsedTime) noexcept { __noop; }
	public:		virtual	void				Update(float fElapsedTime) noexcept { __noop; }
	public:		virtual	void				LateUpdate(float fElapsedTime) noexcept { __noop; }
	public:		virtual void				Render(float fElapsedTime) noexcept { __noop; }
	public:		virtual void				Release(void) noexcept { __noop; }

	public:		void						OnChangeGameObjectLayerXXX(std::pair<GameObjectLayer, GameObject*> obj) noexcept;

	private:	void						InsertPrevSceneGameObj(Scene* prevScene) noexcept;

	private:	void						FixedUpdateXXX(float fElapsedTime) noexcept;
	private:	void						UpdateXXX(float fElapsedTime) noexcept;
	private:	void						LateUpdateXXX(float fElapsedTime) noexcept;
	private:	void						RenderXXX(float fElapsedTime) noexcept;
	private:	void						UIRenderXXX(float fElapsedTime) noexcept;
	private:	void						UnloadXXX(void) noexcept;
	private:	void						ReleaseXXX(void) noexcept;

	private:	void						SortObjByCamera(GameObjectLayer layer) noexcept;

	private:	void						CheckUIPicking(void) noexcept;

	public:		const GameObject::TList&	GetSceneGameObjectXXXXXXXXXXXX(GameObjectLayer layer) const noexcept { return _vGameObjs[static_cast<int>(layer)]; }
	public:		const GameObject::TList&	GetSceneWaitInsertGameObjectXXXXXXXXXXXX(void) const noexcept { return _vGameObjWaitForInsert; }
	public:		GameObject*					InsertGameObject(GameObject* obj) noexcept;

	private:	GameObject::TList			_vGameObjs[static_cast<int>(GameObjectLayer::END)];
	private:	GameObject::TList			_vGameObjWaitForInsert;
	private:	LAYER_VALUE_LIST			_vLayerChangedObj;

	private:	friend						SceneManager;
	};
}
