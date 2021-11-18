#pragma once
#include "Actor.h"

class Player;
class PathFinding;
class NaviMesh;

class Cow : public Actor
{
public:		explicit		Cow(PathFinding* pf, D3DXVECTOR3 bornPos) noexcept;
public:		virtual			~Cow(void) noexcept { __noop; }

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

private:	D3DXVECTOR3		_bornPosition;
private:	Player*			_player;
private:	PathFinding*	_pathFinder;

private:	bool			_dirtyState = false;
private:	float			_fDeltaTime = 0;
};

