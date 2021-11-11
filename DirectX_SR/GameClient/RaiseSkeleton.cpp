#include "pch.h"
#include "RaiseSkeleton.h"
#include "Skeleton.h"
#include "GameObject.h"
#include"Transform.h"

bool RaiseSkeleton::Using(D3DXVECTOR3 vPos, Transform* pTrans) noexcept
{
    if (_Skeletones.size() == _iMaxSkeleton) 
    {
        //하나 없앰
        Skeleton* sk = _Skeletones.front();
        sk->Destroy();
        _Skeletones.pop();
    }
    //클릭한 시체 위치에 스켈레톤 생성 
    GameObject* pSkeleton = GameObject::Instantiate();
    Skeleton* sk = new Skeleton(pTrans);
    pSkeleton->AddComponent(sk);
    pSkeleton->GetTransform()->SetWorldPosition(vPos);

    _Skeletones.push(sk);
    return true;
}

