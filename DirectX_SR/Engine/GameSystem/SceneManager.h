#pragma once
#include "SingletonBase.h"

namespace ce
{
	class Scene;

	class SceneManager : public SingletonBase<SceneManager>
	{
	private:	explicit		SceneManager(void) noexcept;
	private:	virtual			~SceneManager(void) noexcept { __noop; }

	private:	using			SCENE_MAP = std::unordered_map<std::string, Scene*>;
	private:	using			SCENE_VEC = std::vector<Scene*>;

	public:		void			FixedUpdate(float fElapedTime) noexcept;
	public:		void			Update(float fElapedTime) noexcept;
	public:		void			LateUpdate(float fElapedTime) noexcept;
	public:		void			Release(void) noexcept;
	public:		void			Render(float fElapedTime) noexcept;

	public:		bool			AddScene(Scene* pScene, std::string key) noexcept;
	public:		bool			LoadScene(std::string key) noexcept;
	public:		bool			LoadSceneAsync(std::string key) noexcept;
	public:		bool			LoadSceneAdditive(std::string key) noexcept;
	public:		bool			UnloadScene(std::string key) noexcept;

	public:		int				SceneCount(void) const noexcept { return _mapScene.size(); }
	public:		Scene*			GetActiveScene(void) noexcept { return _pActiveScene; }
	public:		std::string		GetSceneID(void) const noexcept { return _activeSceneID; }

	private:	SCENE_MAP		_mapScene;
	private:	Scene*			_pActiveScene;
	private:	Scene*			_pNextScene;
	private:	std::string		_activeSceneID;

	private:	friend			SingletonBase<SceneManager>;
	};
}
