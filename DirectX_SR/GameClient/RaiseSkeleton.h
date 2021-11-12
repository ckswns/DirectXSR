#pragma once
#include "Skill.h"
class Skeleton;
class RaiseSkeleton :	public Skill
{
public:		explicit 				RaiseSkeleton() noexcept;
public:		virtual 				~RaiseSkeleton() noexcept { __noop; }

public:		virtual bool			Using(D3DXVECTOR3 vPos, Transform* pTrans)noexcept;


private:	int							_iMaxSkeleton;
private:	int							_iCount;
private:	int							_iIdx;
private:	std::vector<Skeleton*>		_Skeletones;
};	

