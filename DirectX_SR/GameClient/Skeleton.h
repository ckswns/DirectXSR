#pragma once
#include "Behaviour.h"

namespace ce 
{
	class Transform;
	class Texture;
}
class Skeleton : public Behaviour
{
public:		explicit					Skeleton() noexcept { __noop; }
public:		explicit					Skeleton(Transform* ownerTrans) noexcept;
public:		virtual					~Skeleton(void) noexcept { __noop; }

public:		virtual void				Start(void) noexcept;
public:		virtual void				FixedUpdate(float fElapsedTime) noexcept;

private:		Transform*				_pTrans;
private:		Transform*				_pOwnerTrans;
private:		Texture*					_pTexture;

private:		float						_fSpeed;
private:		float						_fMaxDist;
};

