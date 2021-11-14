#include "pch.h"
#include "Ray.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "Collider.h"
#include "Transform.h"
#include "Scene.h"

namespace ce
{
	namespace Physics
	{
		bool Raycast(Ray ray, OUT RaycastHit& hit, GameObjectLayer layer)
		{
			std::vector<GameObject*>& objs = const_cast<std::vector<GameObject*>&>(SceneManager::Instance()->GetActiveScene()->GetSceneGameObjectXXXXXXXXXXXX(layer));

			std::sort(objs.begin(), objs.end(), [&ray](GameObject* lhs, GameObject* rhs) {
				D3DXVECTOR3 a = (ray._origin - lhs->GetTransform()->GetWorldPosition());
				a.x = a.x * a.x;
				a.y = a.y * a.y;
				a.z = a.z * a.z;

				D3DXVECTOR3 b = (ray._origin - rhs->GetTransform()->GetWorldPosition());
				b.x = b.x * b.x;
				b.y = b.y * b.y;
				b.z = b.z * b.z;

				return (a > b);
				});

			std::reverse(objs.begin(), objs.end());

			for (int i = 0; i < objs.size(); i++)
			{
				if (objs[i]->HasComponent(COMPONENT_ID::COLLIDER))
				{
					if (static_cast<Collider*>(objs[i]->GetComponent(COMPONENT_ID::COLLIDER))->CheckHitRaycast(ray, hit))
						return true;
				}
			}

			hit.collider = nullptr;
			hit.transform = nullptr;
			hit.distance = ray._length;
			hit.point = { 0, 0, 0 };

			return false;
		}

		bool Raycast(D3DXVECTOR3 origin, D3DXVECTOR3 direction, OUT RaycastHit& hit, float length, GameObjectLayer layer)
		{
			std::vector<GameObject*>& objs = const_cast<std::vector<GameObject*>&>(SceneManager::Instance()->GetActiveScene()->GetSceneGameObjectXXXXXXXXXXXX(layer));
			Ray ray;
			ray._length = length;
			ray._origin = origin;
			ray._dir = direction;

			std::sort(objs.begin(), objs.end(), [&ray](GameObject* lhs, GameObject* rhs) {
				D3DXVECTOR3 a = (ray._origin - lhs->GetTransform()->GetWorldPosition());
				a.x = a.x * a.x;
				a.y = a.y * a.y;
				a.z = a.z * a.z;

				D3DXVECTOR3 b = (ray._origin - rhs->GetTransform()->GetWorldPosition());
				b.x = b.x * b.x;
				b.y = b.y * b.y;
				b.z = b.z * b.z;

				return (a > b);
				});

			std::reverse(objs.begin(), objs.end());

			for (int i = 0; i < objs.size(); i++)
			{
				if (objs[i]->HasComponent(COMPONENT_ID::COLLIDER))
				{
					if (static_cast<Collider*>(objs[i]->GetComponent(COMPONENT_ID::COLLIDER))->CheckHitRaycast(ray, hit))
						return true;
				}
			}

			hit.collider = nullptr;
			hit.transform = nullptr;
			hit.distance = length;
			hit.point = { 0, 0, 0 };

			return false;
		}
	}
}