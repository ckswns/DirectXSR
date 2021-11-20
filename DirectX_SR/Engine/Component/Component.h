#pragma once

#ifndef __Component_H__
#define __Component_H__

#ifndef PURE
#define PURE =0
#endif

#include "../Base/ConstValues.h"

namespace ce
{
	class GameObject;

	class Component abstract
	{
	protected:							Component() = delete;
	protected:							Component(COMPONENT_ID::ID id, bool isUniq = false, bool bDependency = false, COMPONENT_ID::ID dependencyID = 0) noexcept
											: _owner(nullptr), _identification(id), _isUniq(isUniq), _bHasDependency(bDependency), _dependencyID(dependencyID) { __noop; }
	public:		virtual 				~Component() noexcept { __noop; }

	public:		virtual void			Init(void) noexcept PURE;
	public:		virtual void			FixedUpdate(float) noexcept PURE;
	public:		virtual void			Update(float) noexcept PURE;
	public:		virtual void			LateUpdate(float) noexcept PURE;
	public:		virtual void			Render(void) noexcept PURE;
	public:		virtual void			Release(void) noexcept PURE;

	public:		virtual void			OnEnable(void) noexcept { __noop; }
	public:		virtual void			OnDisable(void) noexcept { __noop; }

	public:		virtual void			OnMouseEnter(void) noexcept { __noop; }
	public:		virtual void			OnMouseLeave(void) noexcept { __noop; }
	public:		virtual void			OnMouseOver(void) noexcept { __noop; }
	public:		virtual void			OnMouseDown(void) noexcept { __noop; }
	public:		virtual void			OnMouseUp(void) noexcept { __noop; }
	public:		virtual void			OnMouseHeldDown(void) noexcept { __noop; }

	public:		COMPONENT_ID::ID		GetID(void) const noexcept { return _identification; }
	public:		COMPONENT_ID::ID		GetDependencyID(void) const noexcept { return _dependencyID; }

	public:		bool					GetIsUniq(void) const noexcept { return _isUniq; }
	public:		bool					GetHasDependencyComponent(void) const noexcept { return _bHasDependency; }
	public:		bool					GetEnable(void) const noexcept { return _bEnable; }

	public:		virtual void			SetEnable(bool enable) noexcept { _bEnable = enable; }
	public:		void					RemoveComponent(void) noexcept;

	public:		void					SetGameObjectXXX(GameObject* obj) { _owner = obj; }
	public:		GameObject*				GetGameObject(void)	noexcept { return _owner; }

	protected:	GameObject*				_owner;

	private:	COMPONENT_ID::ID		_identification;
	private:	COMPONENT_ID::ID		_dependencyID;

	private:	bool					_isUniq;
	private:	bool					_bHasDependency;
	protected:	bool					_bEnable = true;
	};
}

#endif