#pragma once
#include "Behaviour.h"

namespace ce
{
	class Transform;
	class Animator;
	class SpriteRenderer;
}
class FSMState;
class PathFinding;
class TargetCamera;
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

public:		explicit				Skeleton() noexcept;
public:		virtual					~Skeleton(void) noexcept { __noop; }

public:		virtual void			Start(void) noexcept;
public:		virtual void			Update(float fElapsedTime) noexcept;
public:		virtual void			OnDestroy(void) noexcept;

public:		void					Create(Transform* trans);
public:		void					SetState(SK_STATE newState, DIR eDir = DIR_END, D3DXVECTOR3 vTarget= D3DXVECTOR3(0, -5, 0), bool bAtt = false);
public:		void					SetPathFinding(PathFinding* pf);

private:	void					InitAnimation(SpriteRenderer* sr);
private:	void					InitState();

private:	Transform*				_pTrans;
private:	Transform*				_pOwnerTrans;
private:	Animator*				_pAnimator;
private:	PathFinding*			_pPathFinding;

private:	TargetCamera*			_pCamera;

private:	std::vector<FSMState*>	_pFSM;
private:	SK_STATE				_eCurState;

private:	SK_STAT					_tStat;
private:	float					_fMaxDist;
private:	float					_fSpeed;
};

