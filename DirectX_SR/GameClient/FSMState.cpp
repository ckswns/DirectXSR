#include "pch.h"
#include "FSMState.h"

DIR FSMState::GetDirect(D3DXVECTOR3 vStart, D3DXVECTOR3 vEnd)
{
	vStart.y = 0;
	D3DXVECTOR3 vDir = vEnd - vStart;
	D3DXVec3Normalize(&vDir, &vDir);
	D3DXVECTOR3 vLook(0, 0, 1);

	float dot = D3DXVec3Dot(&vLook, &vDir);

	bool bSide = false;
	bool bFront = false;

	//�� Ȥ�� �� 
	if (CompareFloatAbsoulte(dot, 0) == 0)
		bSide = true;
	else if (dot < 0) 	//�� �� ����
	{
		bFront = true;

		//ĳ���� ����
		if (CompareFloatAbsoulte(dot, -1,0.2f) == 0)
			return FRONT;

	}//ĳ���� �ĸ�
	else if (CompareFloatAbsoulte(dot, 1,0.2f) == 0)
		return BACK; 

	//https://sulinep.blogspot.com/2020/07/blog-post_23.html
	D3DXVECTOR3 vUp(0, 1, 0);
	D3DXVECTOR3 vCross = *D3DXVec3Cross(&vCross, &vDir, &vLook);
	float dotValue = D3DXVec3Dot(&vCross, &vUp);
	if (!bFront)
	{	
		if (dotValue > 0) //��
		{
			if (bSide) return LEFT;
			return BACK_LEFT;
		}
		else//��
		{
			if (bSide) return RIGHT;
			return BACK_RIGHT;
		}
	}
	else
	{
		if (dotValue > 0) //��
		{
			if (bSide) return LEFT;
			return FRONT_LEFT;
		}
		else//��
		{
			if (bSide) return RIGHT;
			return FRONT_RIGHT;
		}
	}

}
