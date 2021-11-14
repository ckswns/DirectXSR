#include "pch.h"
#include "BoxCollider.h"
#include "Transform.h"
#ifdef _DEBUG
#include "Cube.h"
#include "ManagerDef.h"
#endif
#include "SphereCollider.h"


namespace ce
{
	BoxCollider::BoxCollider(const D3DXVECTOR3& size, const D3DXVECTOR3& center, std::string tag) noexcept :
		Collider(Collider::Type::BOX, tag),
		_center(center),
		_size(size)
	{
	}

	void BoxCollider::Open(void) noexcept
	{
#ifdef _DEBUG
		D3DXCreateBox(D3D9DEVICE->GetDevice(), _size.x, _size.y, _size.z, &_dbgBox, nullptr);

		_material.Diffuse.r = 0;
		_material.Diffuse.g = 1;
		_material.Diffuse.b = 0;
		_material.Diffuse.a = 1;
#endif
	}

	void BoxCollider::Close(void) noexcept
	{
#ifdef _DEBUG
		if (_dbgBox)
		{
			_dbgBox->Release();
			//delete _dbgBox;
			_dbgBox = nullptr;
		}
#endif
	}

	bool BoxCollider::CheckCollision(Collider* rhs) const noexcept
	{
		if (rhs->GetType() == Collider::Type::BOX)
		{
			BoxCollider* box = static_cast<BoxCollider*>(rhs);

			D3DXVECTOR3 lhsMin = GetMin();
			D3DXVECTOR3 lhsMax = GetMax();

			D3DXVECTOR3 rhsMin = box->GetMin();
			D3DXVECTOR3 rhsMax = box->GetMax();

			if (lhsMax.x < rhsMin.x || lhsMin.x > rhsMax.x) return false;
			if (lhsMax.y < rhsMin.y || lhsMin.y > rhsMax.y) return false;
			if (lhsMax.z < rhsMin.z || lhsMin.z > rhsMax.z) return false;

			return true;
		}
		else if (rhs->GetType() == Collider::Type::SPHERE)
		{
			float radius = static_cast<SphereCollider*>(rhs)->GetRadius();

			const D3DXVECTOR3& max = GetMax();
			const D3DXVECTOR3& min = GetMin();
			const D3DXVECTOR3& world = rhs->GetTransform()->GetWorldPosition();

			if (max.x < (world.x - radius) || min.x >(world.x + radius)) return false;
			if (max.y < (world.y - radius) || min.y >(world.y + radius)) return false;
			if (max.z < (world.z - radius) || min.z >(world.z + radius)) return false;

			return true;
		}
		else
		{
			return false;
		}

		return false;
	}

	bool BoxCollider::CheckHitRaycast(const Ray& ray, RaycastHit& hit) const noexcept
	{
		D3DXVECTOR3 min = GetMin();
		D3DXVECTOR3 max = GetMax();

		float t1 = (min.x - ray._origin.x) / ray._dir.x;
		float t2 = (max.x - ray._origin.x) / ray._dir.x;
		float t3 = (min.y - ray._origin.y) / ray._dir.y;
		float t4 = (max.y - ray._origin.y) / ray._dir.y;
		float t5 = (min.z - ray._origin.z) / ray._dir.z;
		float t6 = (max.z - ray._origin.z) / ray._dir.z;

		float tmin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
		float tmax = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::max(t5, t6));

		// if tmax < 0, ray (line) is intersecting AABB, but whole AABB is behing us
		if (tmax < 0) {
			return false;
		}

		// if tmin > tmax, ray doesn't intersect AABB
		if (tmin > tmax) {
			return false;
		}

		if (tmin < 0.f) {
			hit.collider = const_cast<BoxCollider*>(this);
			hit.transform = _transform;
			hit.point = ray._origin + tmax * ray._dir;
			return true;
		}

		hit.collider = const_cast<BoxCollider*>(this);
		hit.transform = _transform;
		hit.point = ray._origin + tmin * ray._dir;
		return true;
	}

	void BoxCollider::Render(void) noexcept
	{
#ifdef _DEBUG
		if (_dbgBox && _showDbg)
		{
			DWORD state = 0;
			auto device = D3D9DEVICE->GetDevice();
			device->GetRenderState(D3DRS_FILLMODE, &state);
			device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
			device->SetTransform(D3DTS_WORLD, &_transform->GetWorldMatrix());
			device->SetMaterial(&_material);
			_dbgBox->DrawSubset(0);
			device->SetRenderState(D3DRS_FILLMODE, state);
		}
#endif
	}

	D3DXVECTOR3 BoxCollider::GetMin(void) const noexcept
	{
		D3DXVECTOR3 pos = _transform->GetWorldPosition();
		D3DXVECTOR3 min;

		min.x = (pos.x + _center.x) - (_size.x / 2.f);
		min.y = (pos.y + _center.y) - (_size.y / 2.f);
		min.z = (pos.z + _center.z) - (_size.z / 2.f);
		return min;
	}

	D3DXVECTOR3 BoxCollider::GetMax(void) const noexcept
	{
		D3DXVECTOR3 pos = _transform->GetWorldPosition();
		D3DXVECTOR3 max;

		max.x = (pos.x + _center.x) + (_size.x / 2.f);
		max.y = (pos.y + _center.y) + (_size.y / 2.f);
		max.z = (pos.z + _center.z) + (_size.z / 2.f);
		return max;
	}
}