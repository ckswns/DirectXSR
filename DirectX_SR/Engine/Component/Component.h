#pragma once

#ifndef __Component_H__
#define __Component_H__

#ifndef PURE
#define PURE =0
#endif

#include "../Base/ConstValues.h"
#include "../Base/GameObject.h"

namespace ce
{
	class Component abstract
	{
	protected:							Component() = delete;
	protected:							Component(GameObject* object, COMPONENT_ID::ID id, bool isUniq = false, bool bDependency = false, COMPONENT_ID::ID dependencyID = 0) noexcept
											: _pOwner(object), _identification(id), _isUniq(isUniq), _bHasDependency(bDependency), _dependencyID(dependencyID) { __noop; }
	public:		virtual 				~Component() noexcept { __noop; }

	public:		virtual void			FixedUpdate(float) noexcept PURE;
	public:		virtual void			Update(float) noexcept PURE;
	public:		virtual void			LateUpdate(float) noexcept PURE;
	public:		virtual void			Render(void) noexcept PURE;
	public:		virtual void			Release(void) noexcept PURE;

	public:		COMPONENT_ID::ID		GetType(void) const noexcept { return _identification; }
	public:		COMPONENT_ID::ID		GetDependencyID(void) const noexcept { return _dependencyID; }

	public:		bool					GetIsUniq(void) const noexcept { return _isUniq; }
	public:		bool					GetHasDependencyComponent(void) const noexcept { return _bHasDependency; }
	public:		bool					GetEnable(void) const noexcept { return _bEnable; }

	public:		void					SetEnable(bool enable) noexcept { _bEnable = enable; }
	public:		void					RemoveComponent(void) noexcept { _pOwner->RemoveComponent(this); }

	public:		GameObject*				GetGameObject(void)	noexcept { return _pOwner; }

	protected:	GameObject*				_pOwner;

	private:	COMPONENT_ID::ID		_identification;
	private:	COMPONENT_ID::ID		_dependencyID;

	private:	bool					_isUniq;
	private:	bool					_bHasDependency;
	private:	bool					_bEnable = true;
	};
}

#endif