#pragma once
#include "Behaviour.h"

namespace ce
{
	class Transform;
	class Texture;
	class Animator;
	class SpriteRenderer;
}

class Skill;
class Player : public Behaviour
{
public:		explicit					Player() noexcept { __noop; }
public:		virtual					~Player(void) noexcept { __noop; }

public:		virtual void				Start(void) noexcept;
public:		virtual void				Update(float fElapsedTime) noexcept;

private:		void						SetAnimation(SpriteRenderer* mr);

public:		void						UsingSkill(SKILL_ID id);
public:		void						Attack(D3DXVECTOR3 _vMonsterPos);
public:		void						Move(D3DXVECTOR3 dest);

private:		Transform*				_pTrans;
private:		Animator*				_pAnimator;
private:		STAT						_tStat;
private:		std::vector<Skill*>	_pSkills;

private:		bool						_bAtt;
private:		bool						_bMove;
private:		D3DXVECTOR3		_vDest;

private:		float						_fSpeed;
private:		float						_fRunSpeed;

private:		int							_iMaxSkeleton;
};

