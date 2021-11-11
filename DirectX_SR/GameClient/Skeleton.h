#pragma once
#include "Behaviour.h"

namespace ce 
{
	class Transform;
	class Animator;
	class SpriteRenderer;
}
class Skeleton : public Behaviour
{
public:		typedef struct SkeletonStat
				{
					SkeletonStat(float fMaxHp, float fDmg,float fSpeed)
					{
						_fMaxHp	= fMaxHp;
						_fHp			= _fMaxHp;
						_fDamage	= fDmg;
						fSpeed		= fSpeed;
					}
					float		_fMaxHp;
					float		_fHp;
					float		_fDamage;
					float		_fSpeed;
				}SK_STAT;

public:		explicit					Skeleton() noexcept;
public:		virtual					~Skeleton(void) noexcept { __noop; }

public:		virtual void				Start(void) noexcept;
public:		virtual void				Update(float fElapsedTime) noexcept;

public:		void						Create(Transform* trans);
public:		void						Destroy();

private:		void						SetAnimation(SpriteRenderer* sr);

private:		Transform*				_pTrans;
private:		Transform*				_pOwnerTrans;
private:		Animator*				_pAnimator;
private:		bool						_bOnce;
private:		bool						_bDestroy;

private:		SK_STAT				_tStat;
private:		float						_fMaxDist;
};

