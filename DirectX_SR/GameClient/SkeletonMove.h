#pragma once
#include "FSMState.h"

class Skeleton;
class Node;
class PathFinding;
class SkeletonMove : public FSMState
{
public:		explicit				SkeletonMove() noexcept = delete;
public:		explicit				SkeletonMove(Animator* pAnim, Transform* trans, Transform* playerTrans, PathFinding* pf, float speed = 3.f) noexcept;
public:		virtual					~SkeletonMove() noexcept { __noop; }

public:		virtual void			Start() noexcept;
public:		virtual void			Update(float fElapsedTime) noexcept;

public:		void					SetAtt() { _bAtt = true; }

private:	Skeleton*				_pSk;
private:	Transform*				_pPlayerTrans;

private:	bool					_bFinding;
private:	PathFinding*			_pPathFinding;
private:	std::list<Node*>		_pPath;

private:	bool					_bAtt;
private:	float					_fSpeed;
};

