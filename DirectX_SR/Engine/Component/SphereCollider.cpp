#include "pch.h"
#include "SphereCollider.h"
#include "Transform.h"
#include "Vector3.h"
#include "BoxCollider.h"
#ifdef _DEBUG
#include "ManagerDef.h"
#endif

namespace ce
{
	SphereCollider::SphereCollider(float radius, std::string tag) noexcept :
		Collider(Collider::Type::SPHERE, tag),
		_radius(radius)
	{

	}

	void SphereCollider::Open(void) noexcept
	{
#ifdef _DEBUG
		D3DXCreateSphere(D3D9DEVICE->GetDevice(), _radius, 10, 10, &_dbgMesh, NULL);
		_material.Diffuse.r = 0;
		_material.Diffuse.g = 1;
		_material.Diffuse.b = 0;
		_material.Diffuse.a = 1;
#endif
	}

	void SphereCollider::Close(void) noexcept
	{
#ifdef _DEBUG
		if (_dbgMesh)
		{
			_dbgMesh->Release();
			//delete _dbgMesh;
			_dbgMesh = nullptr;
		}
#endif
	}

	bool SphereCollider::CheckCollision(Collider* rhs) const noexcept
	{
		if (rhs->GetType() == Type::SPHERE)
		{
			SphereCollider* sphere = static_cast<SphereCollider*>(rhs);
			float diameter = _radius + sphere->_radius;

			Vector3 world = _transform->GetWorldPosition();
			Vector3 rhsWorld = rhs->GetTransform()->GetWorldPosition();

			if ((world - rhsWorld).SqrLength() <= diameter * diameter)
				return true;
			else
				return false;
		}
		else if (rhs->GetType() == Type::BOX)
		{
			BoxCollider* box = static_cast<BoxCollider*>(rhs);

			const D3DXVECTOR3& max = box->GetMax();
			const D3DXVECTOR3& min = box->GetMin();
			const D3DXVECTOR3& world = _transform->GetWorldPosition();

			if (max.x < (world.x - _radius) || min.x > (world.x + _radius)) return false;
			if (max.y < (world.y - _radius) || min.y > (world.y + _radius)) return false;
			if (max.z < (world.z - _radius) || min.z > (world.z + _radius)) return false;

			return true;
		}
		else if (rhs->GetType() == Type::TERRAIN)
		{

		}
		else
		{
			CE_ASSERT("ckswns", "Collider의 Type이 설정되지않았습니다.")
		}

		return false;
	}

	bool SphereCollider::CheckHitRaycast(const Ray& ray, RaycastHit& hit) const noexcept
	{
		Vector3 q = _transform->GetWorldPosition() - ray._origin;
		float c = q.SqrLength();
		Vector3 dir = ray._dir;
		
		float v = Vector3::Dot(q, dir);

		float d = _radius * _radius - (c - (v * v));

		if (d < 0.0f)
			return false;

		hit.collider = const_cast<SphereCollider*>(this);
		hit.transform = _transform;
		hit.distance = v - ::sqrt(d);
		hit.point = ray._origin + (ray._dir * hit.distance);

		return true;
	}

	void SphereCollider::Render(void) noexcept
	{
#ifdef _DEBUG
		if (_dbgMesh && _showDbg)
		{
			DWORD state = 0;
			auto device = D3D9DEVICE->GetDevice();
			device->GetRenderState(D3DRS_FILLMODE, &state);
			device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
			device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
			device->SetTransform(D3DTS_WORLD, &_transform->GetWorldMatrix());
			device->SetMaterial(&_material);
			_dbgMesh->DrawSubset(0);
			device->SetRenderState(D3DRS_FILLMODE, state);
			device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		}
#endif
	}
}