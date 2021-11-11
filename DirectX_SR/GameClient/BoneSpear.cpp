#include "pch.h"
#include "BoneSpear.h"
#include "GameObject.h"
#include "Transform.h"

#include "Projectile.h"

#include "Spear.h"
#include "SpearTrail.h"
BoneSpear::BoneSpear() noexcept
    :Skill(SKILL_ID::BONDE_SPEAR,40)
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
    /*
    GameObject* pBoneSpear = GameObject::Instantiate();
//    pBoneSpear->GetTransform()->SetWorldEulerAngle(0, 0, -80);
    pBoneSpear->GetTransform()->SetWorldPosition(pTrans->GetWorldPosition());
    pBoneSpear->AddComponent(new Spear(vPos));

    D3DXVECTOR3 vDir = vPos -pTrans->GetWorldPosition();
    vDir.y = 0;
    D3DXVec3Normalize(&vDir, &vDir);
    vDir *= -0.5f;
    GameObject* pTrail = GameObject::Instantiate();
    pTrail->AddComponent(new SpearTrail());
    pTrail->GetTransform()->SetParent(pBoneSpear->GetTransform());
    pTrail->GetTransform()->SetLocalPosition(vDir);
    */

    return true;
}
