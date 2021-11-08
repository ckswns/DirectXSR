#include "pch.h"
#include "SphereCollider.h"
#include "Transform.h"
#include "Vector3.h"

namespace ce
{
	SphereCollider::SphereCollider(void) noexcept :
		Collider(Collider::Type::SPHERE)
	{

	}

	bool SphereCollider::CheckCollision(Collider* rhs) noexcept
	{
		if (_type == Type::SPHERE)
		{
			if (rhs->GetType() == Type::SPHERE)
			{
				SphereCollider* sphere = static_cast<SphereCollider*>(rhs);
				float diameter = _radius + sphere->_radius;

				Vector3 world = _owner->GetTransform()->GetWorldPosition();
				Vector3 rhsWorld = rhs->GetTransform()->GetWorldPosition();

				if ((world - rhsWorld).SqrLength() <= diameter * diameter)
					return true;
				else
					return false;
			}
		}
		else if (_type == Type::BOX)
		{

		}
		else
		{
			CE_ASSERT("ckswns", "Collider의 Type이 설정되지않았습니다.")
		}

		return false;
	}

	bool SphereCollider::CheckHitRaycast(const Ray& ray, RaycastHit& hit) noexcept
	{
		Vector3 q = GetTransform()->GetWorldPosition() - ray._origin;
		float c = q.SqrLength();
		Vector3 dir = ray._dir;
		
		float v = Vector3::Dot(q, dir);

		float d = _radius * _radius - (c - (v * v));

		if (d < 0.0f)
			return false;

		hit.collider = this;
		hit.transform = GetTransform();
		hit.distance = v - ::sqrt(d);
		hit.point = ray._origin + (ray._dir * hit.distance);

		return true;
	}

	void SphereCollider::Init(void) noexcept
	{

	}

	void SphereCollider::Update(float) noexcept
	{

	}

	void SphereCollider::Render(void) noexcept
	{

	}

	void SphereCollider::Release(void) noexcept
	{

	}

}