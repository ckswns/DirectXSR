#include "pch.h"
#include "LightningCollider.h"
#include "RigidBody.h"
#include "SphereCollider.h"
#include "Player.h"
#include "Transform.h"
void LightningCollider::Start() noexcept
{
	gameObject->AddComponent(new SphereCollider(0.4f));
	gameObject->AddComponent(new Rigidbody);
}

void LightningCollider::OnCollisionEnter(Collider* mine, Collider* other) noexcept
{
	if (other->GetGameObject()->GetTag() == GameObjectTag::PLAYER && other->GetTag() == "hitbox")
	{
		other->GetGameObject()->GetComponent<Player>(COMPONENT_ID::BEHAVIOUR)->GetHit(Random::GetValue(_fMinDamage, _fMaxDamage), GetTransform()->GetWorldPosition());
	}
}
