#pragma once
#include "TypeDefine.h"

#ifndef OUT
#define OUT
#endif

namespace ce
{
	class Collider;
	class Transform;

	struct RaycastHit
	{
		Collider* collider;
		Transform* transform;
		D3DXVECTOR3 point;
		float distance;
	};

	struct Ray
	{
		D3DXVECTOR3		_origin;
		D3DXVECTOR3		_dir;

		float			_length;
	};

	namespace Physics
	{
		bool Raycast(Ray ray, OUT RaycastHit& hit, GameObjectLayer layer = GameObjectLayer::OBJECT);
		bool Raycast(D3DXVECTOR3 origin, D3DXVECTOR3 direction, OUT RaycastHit& hit, float length = 1000.f, GameObjectLayer layer = GameObjectLayer::OBJECT);
	}
}
