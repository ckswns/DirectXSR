#include "pch.h"
#include "PoisonNova.h"
#include "PoisonProjectile.h"
#include "Transform.h"

bool PoisonNova::Using(D3DXVECTOR3 vPos, Transform* pTrans, bool isDir) noexcept
{
    float x = 0.125f;
    float z = 0.125f;

    D3DXVECTOR3 vLook(0, 0, 1);
    D3DXVECTOR3 vD(x, 0, z);
    float angle = D3DXVec3Dot(&vLook, &vD);
    angle = acosf(angle);

    for (int i = 0; i < 32; i++)
    {
        //각각 방향구하기
        D3DXVECTOR3 dir;
        dir.y = 0;
        if (i <= 8)
        {
            dir.x = -x * i;       // 0 -> -1
            dir.z = -1 + (z * i); // -1 -> 0
        }
        else if (i <= 16)
        {
            int num = i - 8;
            dir.x = -1 + (x * num); // -1 -> 0
            dir.z = (z * num);      // 0 -> 1
        }
        else if (i <= 24)
        {
            int num = i - 16;
            dir.x = x * num;        // 0 -> 1
            dir.z = 1-( z * num);   // 1 -> 0
        }
        else 
        {
            int num = i - 24;
            dir.x = 1 - (x * num);  // 1 -> 0
            dir.z = - (z * num);    // 0 -> -1
        }
    //    D3DXVec3Normalize(&dir, &dir);

        GameObject* pObj = GameObject::Instantiate();
        pObj->GetTransform()->SetWorldPosition(pTrans->GetWorldPosition());
//        pObj->GetTransform()->SetLocalEulerAngle(0, 0, angle * i);
        pObj->AddComponent(new PoisonProjectile(dir,i));
    }

    return true;
}
