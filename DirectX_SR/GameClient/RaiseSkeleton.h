#pragma once
#include "Skill.h"
class Skeleton;
class RaiseSkeleton :	public Skill
{
public:		explicit 				RaiseSkeleton() :Skill(SKILL_ID::RAISE_SKELETON), _iMaxSkeleton(2) { __noop; }
public:		virtual 				~RaiseSkeleton() noexcept { __noop; }

public:		virtual bool			Using(D3DXVECTOR3 vPos, Transform* pTrans)noexcept;


private:		int									_iMaxSkeleton;
private:		std::queue<Skeleton*>	_Skeletones;
};	

