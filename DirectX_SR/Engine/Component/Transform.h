#pragma once

#include "Component.h"
#include <vector>

#ifndef IN
#define IN
#endif

namespace ce
{
	class Transform final : public Component
	{
	public:		explicit						Transform() = delete;
	public:		explicit						Transform(GameObject* const owner) noexcept;
	public:		virtual							~Transform(void) noexcept { __noop; }

	public:		virtual void					Init(void) noexcept override final { __noop; }
	public:		virtual void					Update(float) noexcept override final;
	public:		virtual void					Render(void) noexcept override final { __noop; }
	public:		virtual void					Release(void) noexcept override final;

	public:		Transform*						GetParent(void) noexcept;
	public:		const Transform*				GetParent(void) const noexcept;

	public:		std::vector<const Transform*>	GetParents(void) const noexcept;

	public:		const std::vector<Transform*>&	GetChilds(void) const noexcept;

	public:		void							SetParent(IN Transform* parent) noexcept;

	public:		D3DXVECTOR3						GetForward(void) const noexcept;
	public:		D3DXVECTOR3						GetUp(void) const noexcept;
	public:		D3DXVECTOR3						GetRight(void) const noexcept;

	public:		void							Translate(const D3DXVECTOR3& position, bool isLocal = true);
	public:		void							Translate(float x, float y, float z, bool isLocal = true);

	public:		void							Rotate(const D3DXVECTOR3& euler, bool isLocal = true);
	public:		void							Rotate(float x, float y, float z, bool isLocal = true);

	public:		const D3DXVECTOR3&				GetWorldPosition(void) const noexcept { return _worldPosition; }
	public:		void							SetWorldPosition(const D3DXVECTOR3& worldPosition) noexcept;
	public:		void							SetWorldPosition(float x, float y, float z) noexcept;

	public:		const D3DXVECTOR3&				GetLocalPosition(void) const noexcept { return _localPosition; }
	public:		void							SetLocalPosition(const D3DXVECTOR3& localPosition) noexcept;
	public:		void							SetLocalPosition(float x, float y, float z) noexcept;

	public:		const D3DXVECTOR3&				GetWorldEulerAngle(void) const noexcept { return _worldEulerAngle; }
	public:		void							SetWorldEulerAngle(const D3DXVECTOR3& eulerAngle) noexcept;
	public:		void							SetWorldEulerAngle(float x, float y, float z) noexcept;

	public:		const D3DXVECTOR3&				GetLocalEulerAngle(void) const noexcept { return _localEulerAngle; }
	public:		void							SetLocalEulerAngle(const D3DXVECTOR3& eulerAngle) noexcept;
	public:		void							SetLocalEulerAngle(float x, float y, float z) noexcept;

	public:		D3DXVECTOR3						GetLossyScale(void) const noexcept;
	private:	void							CalculateLossyScale(OUT D3DXVECTOR3& lossy) noexcept;
	public:		const D3DXVECTOR3&				GetLocalScale(void) const noexcept { return _localScale; }
	public:		void							SetLocalScale(const D3DXVECTOR3& localScale) noexcept;
	public:		void							SetLocalScale(float x, float y, float z) noexcept;

	public:		const D3DXMATRIX&				GetWorldMatrix(void) const noexcept { return _matWorld; }

	private:	bool							RemoveChild(const Transform* child) noexcept;
	private:	void							SetChild(IN const Transform* child) noexcept;
	private:	void							FindParentRecur(const Transform* transform, OUT std::vector<const Transform*>& vecParents) const noexcept;

	public:		void							OnParentPosChanged(void) noexcept;
	public:		void							ForcedReCalMat(void) noexcept;

	private:	D3DXVECTOR3						_worldPosition;
	private:	D3DXVECTOR3						_localPosition;
	private:	D3DXMATRIX						_matPosition;

	private:	D3DXVECTOR3						_localEulerAngle;
	private:	D3DXVECTOR3						_worldEulerAngle;
	private:	D3DXMATRIX						_matRotation;

	private:	D3DXQUATERNION					_quatRotation;

	private:	D3DXVECTOR3						_localScale;
	private:	D3DXMATRIX						_matScale;

	private:	D3DXMATRIX						_matWorld;

	private:	bool							_bDirtyPosition;
	private:	bool							_bDirtyRotation;
	private:	bool							_bDirtyScale;
	private:	bool							_bChangedPosition;
	private:	bool							_bChangedRotation;
	private:	bool							_bChangedScale;
	private:	bool							_bChanged;

	private:	Transform*						_pParent;

	private:	std::vector<Transform*>			_vecChild;
	};
}
