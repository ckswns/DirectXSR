#include "pch.h"
#include "BoneSpear.h"
#include "GameObject.h"
#include "Transform.h"

#include "Projectile.h"

#include "Spear.h"
#include "SpearTrail.h"
BoneSpear::BoneSpear() noexcept
    :Skill(SKILL_ID::BONE_SPEAR,40)
{
}

bool BoneSpear::Using(D3DXVECTOR3 vPos, Transform* pTrans) noexcept
{
    D3DXMATRIX  world = pTrans->GetWorldMatrix();
    D3DXVECTOR3 look = D3DXVECTOR3(world.m[2][0], world.m[2][1], world.m[2][2]);
    float angle = D3DXVec3Dot(&look, &vPos);

    GameObject* pBoneSpear = GameObject::Instantiate();
    pBoneSpear->GetTransform()->SetWorldPosition(pTrans->GetWorldPosition());
    pBoneSpear->AddComponent(new Projectile(vPos));
     return true;
}
