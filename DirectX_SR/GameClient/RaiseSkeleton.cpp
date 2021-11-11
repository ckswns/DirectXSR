#include "pch.h"
#include "RaiseSkeleton.h"
#include "Skeleton.h"
#include "GameObject.h"
#include"Transform.h"

RaiseSkeleton::RaiseSkeleton() noexcept
    :Skill(SKILL_ID::RAISE_SKELETON,30), _iMaxSkeleton(2), _iCount(0), _iIdx(0)
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

bool RaiseSkeleton::Using(D3DXVECTOR3 vPos, Transform* pTrans) noexcept
{
    if (_iCount == _iMaxSkeleton)
    {
        int index = (_iIdx + 1) > 2 ? 0 : (_iIdx + 1);
        
        //�ϳ� ����
        Skeleton* sk = _Skeletones[index];
        sk->Destroy();

        _iCount = 1;

    }
    //Ŭ���� ��ü ��ġ�� ���̷��� ���� 
    GameObject* pSkeleton = _Skeletones[_iIdx]->GetGameObject();
    pSkeleton->GetTransform()->SetWorldPosition(vPos);
    _Skeletones[_iIdx]->Create(pTrans);

    _iCount++;
    _iIdx++;
    if (_iIdx == 3)
        _iIdx = 0;

    return true;
}

