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

	public:		explicit			Collider(Collider::Type type, std::string tag) noexcept : 
										Component(COMPONENT_ID::COLLIDER), _type(type), _tag(tag) { __noop; }
	public:		virtual				~Collider(void) noexcept { __noop; }

	public:		using				TList = std::vector<Collider*>;
	public:		using				CPTR = const Collider* const;

	public:		void				Init(void) noexcept override final;
	public:		void				Release(void) noexcept override final;

	public:		void				FixedUpdate(float) noexcept override final { __noop; }
	public:		void				Update(float) noexcept override final;
	public:		void				LateUpdate(float) noexcept override final;

	public:		void				SetTag(std::string tag) noexcept { _tag = tag; }
	public:		const std::string&	GetTag(void) const noexcept { return _tag; }

	public:		virtual void		Open(void) noexcept PURE;
	public:		virtual	void		Close(void) noexcept PURE;

	public:		virtual bool		CheckCollision(Collider* rhs) const noexcept PURE;
	public:		virtual bool		CheckHitRaycast(const Ray& ray, RaycastHit& hit) const noexcept PURE;

	public:		Collider::Type		GetType(void) const noexcept { return _type; }
	public:		Transform*			GetTransform(void) noexcept { return _transform; }

	public:		GameObject*			GetGameObject(void) noexcept { return _owner; }
	public:		void				SetRaycastTarget(bool rhs) noexcept { _enableRaycast = rhs; }

	public:		virtual void		SetEnable(bool enable) noexcept override;

	private:	bool				_bEnbaleChanged = false;
	private:	bool				_bDirtEnable = false;
	private:	bool				_bInserted = false;
	protected:	bool				_enableRaycast = true;
	protected:	Collider::Type		_type;

	protected:	Transform*			_transform;
	protected:	std::string			_tag;
#ifdef _DEBUG
	protected:	static bool			_showDbg;
	protected:	D3DMATERIAL9		_material;
#endif
	};
}
