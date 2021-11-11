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
		bool Raycast(D3DXVECTOR3 origin, D3DXVECTOR3 direction, OUT RaycastHit& hit, float length, GameObjectLayer layer)
		{
			const std::vector<GameObject*>& objs =  SceneManager::Instance()->GetActiveScene()->GetSceneGameObjectXXXXXXXXXXXX(GameObjectLayer::OBJECT);
			Ray ray;
			ray._length = length;
			ray._origin = origin;
			ray._dir = direction;

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