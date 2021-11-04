#pragma once
#include "Component.h"

#ifdef __USE_FMOD__

namespace ce
{
	class GameObject;
	class Transform;

	class AudioListener : public Component
	{
	public:	 explicit				AudioListener(GameObject* owner) noexcept;
	public:	 virtual				~AudioListener(void) noexcept { __noop; }
			 
	public:	 void					FixedUpdate(float) noexcept override;
	public:	 void					Update(float) noexcept override;
	public:	 void					LateUpdate(float) noexcept override;
	public:	 void					Render(float) noexcept override;
	public:	 void					Release(void) noexcept override;
			 
	private: Transform*				_pTransform;
	private: FMOD::System*			_pSystem;
			 
	private: static AudioListener*	_pListener;
	};
}

#endif