#pragma once
#include "Actor.h"

class Player;
class PathFinding;
class NaviMesh;

namespace ce
{
	class SpriteRenderer;
	class AudioSource;
}

class Diablo : public Actor
{
public:		explicit			Diablo(void) noexcept { __noop; }
public:		virtual				~Diablo(void) noexcept { __noop; }

public:		void				Awake(void) noexcept override;
public:		void				Start(void) noexcept override;
public:		void				FixedUpdate(float fElapsedTime) noexcept override;
public:		void				Update(float fElapsedTime) noexcept override;
public:		void				LateUpdate(float fElapsedTime) noexcept override;
public:		void				OnDestroy(void) noexcept override;

public:		void				OnCollisionEnter(Collider* mine, Collider* other) noexcept override;
public:		void				OnCollisionStay(Collider* mine, Collider* other) noexcept override;
public:		void				OnCollisionExit(Collider* mine, Collider* other) noexcept override;

public:		void				GetHit(int damage) noexcept override;

public:		void				OnAnimationEvent(std::string str) noexcept override;

private:	SpriteRenderer*		_spriteRenderer;
private:	Player*				_player;
private:	PathFinding*		_pathFinder;

private:	AudioSource*		_fireAudio;
private:	AudioSource*		_breathAudio;
private:	AudioSource*		_castAudio;
private:	AudioSource*		_initAudio;
private:	AudioSource*		_laughAudio;
private:	AudioSource*		_attackAudio;
private:	AudioSource*		_getHitAudio;
private:	AudioSource*		_deadAudio;
private:	AudioSource*		_hitEffectAudio;

private:	bool				_dirtyState = false;
private:	float				_fDeltaTime = 0;
};

