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
public:		explicit					Skeleton() noexcept { __noop; }
public:		explicit					Skeleton(Transform* ownerTrans) noexcept;
public:		virtual					~Skeleton(void) noexcept { __noop; }

public:		virtual void				Start(void) noexcept;
public:		virtual void				Update(float fElapsedTime) noexcept;

public:		void						Destroy();

private:		void						SetAnimation(SpriteRenderer* sr);

private:		Transform*				_pTrans;
private:		Transform*				_pOwnerTrans;
private:		Animator*				_pAnimator;
private:		bool						_bOnce;
private:		bool						_bDestroy;

private:		float						_fSpeed;
private:		float						_fMaxDist;
};

