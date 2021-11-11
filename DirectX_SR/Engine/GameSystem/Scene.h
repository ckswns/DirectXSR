#pragma once

#include "INoncopyable.h"
#include "TypeDefine.h"
#ifndef _QUEUE_
#include <queue>
#endif
#ifndef PURE
#define PURE =0
#endif

namespace ce
{
	class SceneManager;
	class GameObject;

	class Scene : public INoncopyable
	{
	public:		explicit			Scene(void) noexcept { __noop; }
	public:		virtual				~Scene(void) noexcept { __noop; }

	public:		using				KEY_VALUE_LIST = std::vector<std::pair<std::string, Scene*>>;
	public:		using				LAYER_VALUE_LIST = std::vector<std::pair<GameObjectLayer, GameObject*>>;
	public:		using				TList = std::vector<GameObject*>;
	public:		using				QUEUE = std::queue<GameObject*>;

	public:		virtual bool		Init(void) noexcept { return true; }
	public:		virtual	void		FixedUpdate(float fElapsedTime) noexcept { __noop; }
	public:		virtual	void		Update(float fElapsedTime) noexcept { __noop; }
	public:		virtual	void		LateUpdate(float fElapsedTime) noexcept { __noop; }
	public:		virtual void		Render(float fElapsedTime) noexcept { __noop; }
	public:		virtual void		Release(void) noexcept { __noop; }

	public:		void				OnChangeGameObjectLayerXXX(std::pair<GameObjectLayer, GameObject*> obj) noexcept;

	private:	void				FixedUpdateXXX(float fElapsedTime) noexcept;
	private:	void				UpdateXXX(float fElapsedTime) noexcept;
	private:	void				LateUpdateXXX(float fElapsedTime) noexcept;
	private:	void				RenderXXX(float fElapsedTime) noexcept;
	private:	void				UIRenderXXX(float fElapsedTime) noexcept;
	private:	void				ReleaseXXX(void) noexcept;

	private:	void				CheckUIPicking(void) noexcept;

	public:		const TList&		GetSceneGameObjectXXXXXXXXXXXX(GameObjectLayer layer) const noexcept { return _vGameObjs[static_cast<int>(layer)]; }
	public:		GameObject*			InsertGameObject(GameObject* obj) noexcept;

	private:	TList				_vGameObjs[static_cast<int>(GameObjectLayer::END)];
	private:	QUEUE				_qGameObjWaitForInsert;
	private:	LAYER_VALUE_LIST	_vLayerChangedObj;

	private:	friend				SceneManager;
	};
}
