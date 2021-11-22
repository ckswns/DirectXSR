#pragma once
#include "Actor.h"

class Player;
class PathFinding;
class NaviMesh;
namespace ce
{
	class AudioSource;
	class AudioAsset;
}
class Witch : public Actor
{
public:		explicit		Witch(PathFinding* pf, D3DXVECTOR3 bornPos) noexcept;
public:		virtual			~Witch(void) noexcept { __noop; }

public:		void			Awake(void) noexcept override;
public:		void			Start(void) noexcept override;
public:		void			FixedUpdate(float fElapsedTime) noexcept override;
public:		void			Update(float fElapsedTime) noexcept override;
public:		void			LateUpdate(float fElapsedTime) noexcept override;
public:		void			OnDestroy(void) noexcept override;

public:		void			OnCollisionEnter(Collider* mine, Collider* other) noexcept override;
public:		void			OnCollisionStay(Collider* mine, Collider* other) noexcept override;
public:		void			OnCollisionExit(Collider* mine, Collider* other) noexcept override;

public:		void			GetHit(int damage) noexcept override;

public:		void			OnAnimationEvent(std::string str) noexcept override;

private:	D3DXVECTOR3			CaculateDir(Actor::Direction dir) const noexcept;

private:	D3DXVECTOR3			_bornPosition;
private:	Player*				_player;
private:	PathFinding*		_pathFinder;
		
private:	AudioSource*		_attackAudio;
private:	AudioSource*		_getHitAudio;
private:	AudioSource*		_deadAudio;
private:	AudioSource*		_hitEffectAudio;

private:	bool				_dirtyState = false;
private:	float				_fDeltaTime = 0;
private:	bool				_SkillCheck = false;
private:	D3DXVECTOR3			_vPirvPlayerPos;
private:	D3DXVECTOR3			_direction;
};