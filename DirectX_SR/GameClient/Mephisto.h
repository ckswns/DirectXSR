#pragma once
#include "Actor.h"

class Player;
class PathFinding;
class NaviMesh;
class Lightning;
class Mephisto :public Actor
{
public:		explicit		Mephisto(PathFinding* pf, D3DXVECTOR3 bornPos) noexcept;
public:		virtual			~Mephisto(void) noexcept { __noop; }

public:		void			Awake(void) noexcept override;
public:		void			Start(void) noexcept override;
public:		void			FixedUpdate(float fElapsedTime) noexcept override;
public:		void			Update(float fElapsedTime) noexcept override;
public:		void			LateUpdate(float fElapsedTime) noexcept override;
public:		void			OnDestroy(void) noexcept override;

public:		virtual void	GetHit(int damage) noexcept;
public:		void			OnAnimationEvent(std::string str) noexcept override;
public:		void			UsingSkill();

private:	float			GetAngle(D3DXVECTOR3 vDir);
private:	void			InitAnimation();

private:	D3DXVECTOR3		_bornPosition;
private:	Player*			_player;
private:	PathFinding*	_pathFinder;
private:	Lightning*		_lightning;

private:	bool			_dirtyState;
private:	bool			_usingSkill;
private:	bool			_bLightningCool;
private:	float			_fDeltaTime;
private:	float			_fCoolDown;

private:	float			_fAttackRange;
private:	float			_fLightningRange;
private:	float			_fMisslieRange;
};

