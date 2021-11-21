#pragma once
#include "Component.h"

namespace ce
{
	class Animation;
	class Animator : public Component
	{	
	private:	using			MAP_ANI = std::unordered_map<std::string, Animation*>;

	public:		explicit		Animator(bool playOnAwake = false) noexcept;
	public:		virtual			~Animator(void) noexcept { __noop; }

	public:		void			Init(void) noexcept override;
	public:		void			FixedUpdate(float) noexcept override { __noop; }
	public:		void			Update(float) noexcept override;
	public:		void			LateUpdate(float) noexcept override { __noop; }
	public:		void			Render(void) noexcept override;
	public:		void			Release(void) noexcept override;

	public:		bool			InsertAnimation(std::string key, Animation* ani) noexcept;
	public:		bool			SetAnimation(std::string key) noexcept;

	public:		bool			Play(std::string key = "") noexcept;
	public:		void			Stop(void) noexcept;
	public:		void			Resume(void) noexcept;
	public:		void			Pause(void) noexcept;

	public:		bool			GetCurrentAnimationEnd(void) noexcept;
	public:		std::string		GetCurrentAnimationName(void) const noexcept;
	public:		int				GetCurrentFrame(void) const noexcept;

	public:		void			SetFrame(int frame) noexcept;

	public:		Animation*		GetAnimationByKey(std::string key) noexcept;

	private:	bool			_bPlayOnAwake;
	private:	std::string		_currentAniName;
	private:	Animation*		_currentAni;
	private:	MAP_ANI			_mapAnim;
	};
}
