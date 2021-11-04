#pragma once

#include "INoncopyable.h"
#include "TypeDefine.h"

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
	private:	using				GameObjVec = std::vector<GameObject*>;

	public:		virtual bool		Init(void) noexcept { return true; }
	public:		virtual	void		FixedUpdate(float fElapsedTime) noexcept { __noop; }
	public:		virtual	void		Update(float fElapsedTime) noexcept { __noop; }
	public:		virtual	void		LateUpdate(float fElapsedTime) noexcept { __noop; }
	public:		virtual void		Render(float fElapsedTime) noexcept { __noop; }
	public:		virtual void		Release(void) noexcept { __noop; }

	private:	void				FixedUpdateXXX(float fElapsedTime) noexcept;
	private:	void				UpdateXXX(float fElapsedTime) noexcept;
	private:	void				LateUpdateXXX(float fElapsedTime) noexcept;
	private:	void				RenderXXX(float fElapsedTime) noexcept;
	private:	void				ReleaseXXX(void) noexcept;

	public:		const GameObjVec&	GetSceneGameObjectXXXXXXXXXXXX(GameObjectLayer layer) const noexcept { return _vGameObjs[static_cast<int>(layer)]; }
	public:		GameObject*			InsertGameObject(GameObject* obj) noexcept;

	private:	GameObjVec			_vGameObjs[static_cast<int>(GameObjectLayer::END)];
	private:	

	private:	friend				SceneManager;
	};
}
