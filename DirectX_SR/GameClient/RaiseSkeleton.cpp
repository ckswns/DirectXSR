#include "pch.h"
#include "RaiseSkeleton.h"
#include "Skeleton.h"
#include "GameObject.h"
#include"Transform.h"

RaiseSkeleton::RaiseSkeleton() noexcept
    :Skill(SKILL_ID::RAISE_SKELETON,30), _iMaxSkeleton(20), _iCount(0), _iIdx(0)
{
    for (int i = 0; i < (_iMaxSkeleton + 1); i++)
    {
        GameObject* pSkeleton = GameObject::Instantiate();
        Skeleton* sk = new Skeleton();
        pSkeleton->AddComponent(sk);
        pSkeleton->SetActive(false);
        _Skeletones.push_back(sk);
   }
}

bool RaiseSkeleton::Using(D3DXVECTOR3 vPos, Transform* pTrans, bool isDir) noexcept
{
    if (_iCount == _iMaxSkeleton)
    {
        int index = (_iIdx + 1) > 2 ? 0 : (_iIdx + 1);
        
        //하나 없앰
        Skeleton* sk = _Skeletones[index];
        sk->SetState(SK_DEAD);

        _iCount = 1;

    } 
    //클릭한 시체 위치에 스켈레톤 생성 
    GameObject* pSkeleton = _Skeletones[_iIdx]->GetGameObject();
    if(!isDir)
        pSkeleton->GetTransform()->SetWorldPosition(vPos);
    else
        pSkeleton->GetTransform()->SetWorldPosition(pTrans->GetWorldPosition()+vPos);
    _Skeletones[_iIdx]->Create(pTrans);

    _iCount++;
    _iIdx++;
    if (_iIdx == _iMaxSkeleton+1)
        _iIdx = 0;

    return true;
}

void RaiseSkeleton::SetPathFinding(PathFinding* pf)
{
    for (size_t i= 0; i < _Skeletones.size(); i++)
    {
        _Skeletones[i]->SetPathFinding(pf);
    }
}

