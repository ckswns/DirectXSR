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

bool BoneSpear::Using(D3DXVECTOR3 vPos, Transform* pTrans,bool isDir) noexcept
{
    GameObject* pBoneSpear = GameObject::Instantiate();
    if(isDir)
        pBoneSpear->GetTransform()->SetWorldPosition(pTrans->GetWorldPosition()+ vPos);
    else
        pBoneSpear->GetTransform()->SetWorldPosition(pTrans->GetWorldPosition());

    pBoneSpear->AddComponent(new Projectile(vPos,isDir));
    return true;
}
