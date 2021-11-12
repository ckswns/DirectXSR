#pragma once
#include "Component.h"

#ifdef __USE_FMOD__

namespace ce
{
	class GameObject;
	class Transform;

	class AudioListener : public Component
	{
	public:		explicit				AudioListener(void) noexcept;
	public:		virtual					~AudioListener(void) noexcept { __noop; }
		
	public:		void					Init(void) noexcept override;
	public:		void					FixedUpdate(float) noexcept override { __noop; }
	public:		void					Update(float) noexcept override { __noop; }
	public:		void					LateUpdate(float) noexcept override;
	public:		void					Render(void) noexcept override { __noop; }
	public:		void					Release(void) noexcept override;
			 
	private:	Transform*				_pTransform;
	private:	FMOD::System*			_pSystem;
			 
	private:	static AudioListener*	_pListener;
	};
}

#endif