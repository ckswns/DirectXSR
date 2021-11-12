#pragma once
#include "Behaviour.h"

namespace ce
{
	class Transform;
	class Animator;
	class SpriteRenderer;
}

class Skill;
class PathFinding;
class Node;
class Player : public Behaviour
{
public:		explicit					Player() noexcept = delete;
public:		explicit					Player(PathFinding* pf) noexcept;
public:		virtual					~Player(void) noexcept { __noop; }

public:		virtual void				Start(void) noexcept;
public:		virtual void				Update(float fElapsedTime) noexcept;
public:		virtual void				OnDestroy(void) noexcept;

private:		void						InitAnimation(SpriteRenderer* mr);

public:		void						UsingSkill(SKILL_ID id,D3DXVECTOR3 vPos);
public:		void						Attack(D3DXVECTOR3 _vMonsterPos);
public:		void						Move(D3DXVECTOR3 dest);

public:		float						GetHPPer();
public:		float						GetMPPer();
public:		float						GetStaminaPer();

private:		Transform*				_pTrans;
private:		Animator*				_pAnimator;

private:		bool						_bFind;
private:		PathFinding*			_pPathFinding;
private:	   std::list<Node*>		_pPath;

private:		STAT*						_tStat;
private:		std::vector<Skill*>	_pSkills;

private:		bool						_bAtt;
private:		bool						_bMove;
private:		D3DXVECTOR3		_vDest;

private:		bool						_bRun;
private:		float						_fSpeed;
private:		float						_fRunSpeed;

};

