#pragma once
#include "Skill.h"

class Skeleton;
class PathFinding;
class RaiseSkeleton :	public Skill
{
public:		explicit 				RaiseSkeleton() noexcept;
public:		virtual 				~RaiseSkeleton() noexcept { __noop; }

public:		virtual bool			Using(D3DXVECTOR3 vPos, Transform* pTrans,bool isDir)noexcept;
public:		void					SetPathFinding(PathFinding* pf, D3DXVECTOR3 vPlayerPos);
public:		void					ResetSkeleton();
public:		void					DestroySekelton();

private:	int							_iMaxSkeleton;
private:	int							_iCount;
private:	int							_iIdx;
private:	std::vector<Skeleton*>		_Skeletones;
};	

