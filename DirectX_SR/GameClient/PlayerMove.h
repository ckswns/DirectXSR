#pragma once
#include "FSMState.h"

class Node;
class PathFinding;
class PlayerMove :public FSMState
{
public:		explicit			PlayerMove() noexcept = delete;
public:		explicit			PlayerMove(Player* owner,Animator* pAnim, Transform* trans, PathFinding* pf, float speed = 3.f) noexcept;
public:		virtual			~PlayerMove() noexcept { __noop; }

public:		virtual void		Start() noexcept;
public:		virtual void		Update(float fElapsedTime) noexcept;

public:		void				SetAtt() { _bAtt = true; }

private:		PathFinding*			_pPathFinding;
private:	   std::list<Node*>		_pPath;

private:		bool						_bAtt;
private:		bool						_bRun;
private:		float						_fSpeed;
private:		float						_fRunSpeed;
};

