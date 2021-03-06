#pragma once
#include "Component.h"

#ifndef PURE
#define PURE = 0
#endif

namespace ce
{
	class Collider;
	class GameObject;
	class Transform;

	class Behaviour : public Component
	{
	public:		explicit					Behaviour(void) noexcept : Component(CONST_VALUES::COMPONENT_ID::BEHAVIOUR), gameObject(nullptr) { __noop; }
	public:		virtual						~Behaviour(void) noexcept { __noop; }

	private:	virtual void				Init(void) noexcept override final;
	private:	virtual void				Render(void) noexcept override final;
	private:	virtual void				Release(void) noexcept override final { OnDestroy(); }

	public:		virtual void				OnEnable(void) noexcept override { __noop; }
	public:		virtual void				OnDisable(void) noexcept override { __noop; }

	public:		virtual void				Awake(void) noexcept { __noop; }
	public:		virtual void				Start(void) noexcept PURE;
	public:		virtual void				FixedUpdate(float fElapsedTime) noexcept { __noop; }
	public:		virtual void				LateUpdate(float fElapsedTime) noexcept { __noop; }
	public:		virtual void				OnDestroy(void) noexcept { __noop; }

	public:		virtual void				OnAnimationEvent(std::string str) noexcept { __noop; }

	public:		virtual void				OnCollisionEnter(Collider* mine, Collider* other) noexcept { __noop; }
	public:		virtual void				OnCollisionStay(Collider* mine, Collider* other) noexcept { __noop; }
	public:		virtual void				OnCollisionExit(Collider* mine, Collider* other) noexcept { __noop; }

	public:		virtual void				DbgRender(void) noexcept { __noop; } // call debug mode only

	public:		Transform*					GetTransform(void) noexcept { return transform; }
	public:		GameObject*					GetGameObject(void) noexcept { return gameObject; }

	protected:	Transform*					transform;
	protected:	GameObject*					gameObject;
	};
}
