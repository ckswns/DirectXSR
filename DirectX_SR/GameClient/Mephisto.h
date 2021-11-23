#pragma once
#include "Actor.h"

namespace ce
{
	class AudioAsset;
	class AudioSource;
}

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

public:		bool			GetDead(void) const noexcept { return _bDeadAniDone; }

public:		virtual void	GetHit(int damage) noexcept;

public:		void			OnAnimationEvent(std::string str) noexcept override;
public:		void			UsingSkill();

public:		void			Intro(void) noexcept;
public:		void			IntroDone(void) noexcept { _bIntroDone = true; }

private:	float			GetAngle(D3DXVECTOR3 vDir);
private:	void			InitAnimation();

private:	D3DXVECTOR3		_bornPosition;
private:	Player*			_player;
private:	PathFinding*	_pathFinder;
private:	Lightning*		_lightning;

private:	bool			_bIntroDone = false;
private:	bool			_bIntro = false;
private:	bool			_bDeadAniDone = false;

private:	bool			_dirtyState;
private:	bool			_usingSkill;
private:	bool			_bLightningCool;
private:	float			_fDeltaTime;
private:	float			_fCoolDown;

private:	float			_fAttackRange;
private:	float			_fLightningRange;
private:	float			_fMisslieRange;

private:	AudioSource*	_pAudioSource;
private:	AudioAsset*		_pInitSound;
private:	AudioAsset*		_pAttackSound[4];
private:	AudioAsset*		_pDamagedSound[4];
private:	AudioAsset*		_pDeathSound;
};

