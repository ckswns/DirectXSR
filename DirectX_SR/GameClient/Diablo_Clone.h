#pragma once
#include "Behaviour.h"
#include "Actor.h"

class Player;
class PathFinding;
class NaviMesh;
class Diablo;

namespace ce
{
	class SpriteRenderer;
	class AudioSource;
}

class Diablo_Clone : public Actor
{
public:		explicit			Diablo_Clone(Diablo* diablo) noexcept;
public:		virtual				~Diablo_Clone(void) noexcept { __noop; }

public:		void				Awake(void) noexcept override;
public:		void				Start(void) noexcept override;
public:		void				FixedUpdate(float) noexcept override;
public:		void				Update(float) noexcept override;
public:		void				LateUpdate(float) noexcept override;
public:		void				OnDestroy(void) noexcept override;

public:		void				OnCollisionEnter(Collider* mine, Collider* other) noexcept override;
public:		void				OnCollisionStay(Collider* mine, Collider* other) noexcept override;
public:		void				OnCollisionExit(Collider* mine, Collider* other) noexcept override;

public:		void				GetHit(int damage) noexcept override;

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

