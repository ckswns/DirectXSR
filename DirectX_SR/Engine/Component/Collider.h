#pragma once
#include "Component.h"
#include "Ray.h"

namespace ce
{
	class Transform;

	class Collider : public Component
	{
	public:		enum class			Type
									{
										SPHERE,
										BOX,
										TERRAIN,
										END
									};

	public:		explicit			Collider(Collider::Type type) noexcept : Component(COMPONENT_ID::COLLIDER) { _type = type; }
	public:		virtual				~Collider(void) noexcept { __noop; }

	public:		using				TList = std::vector<Collider*>;

	public:		void				Init(void) noexcept override final;
	public:		void				Release(void) noexcept override final;

	public:		virtual void		Open(void) noexcept PURE;
	public:		virtual	void		Close(void) noexcept PURE;

	public:		virtual bool		CheckCollision(Collider* rhs) noexcept PURE;
	public:		virtual bool		CheckHitRaycast(const Ray& ray, RaycastHit& hit) noexcept PURE;

	public:		Collider::Type		GetType(void) const noexcept { return _type; }
	public:		Transform*			GetTransform(void) noexcept { return _transform; }

	public:		GameObject*			GetGameObject(void) noexcept { return _owner; }
	public:		void				SetRaycastTarget(bool rhs) noexcept { _enableRaycast = rhs; }

	protected:	bool				_enableRaycast = true;
	protected:	Collider::Type		_type;

	protected:	Transform*			_transform;
	};
}
