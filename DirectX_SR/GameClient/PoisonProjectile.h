#pragma once
#include "Behaviour.h"

namespace ce
{
	class Transform;
}
class PoisonProjectile: public Behaviour
{
public:		explicit					PoisonProjectile() = delete;
public:		explicit					PoisonProjectile(D3DXVECTOR3 dir,int iAniNum) noexcept;
public:		virtual						~PoisonProjectile(void) noexcept { __noop; }

public:		virtual void				Start(void) noexcept;
public:		virtual void				Update(float fElapsedTime) noexcept;

private:	Transform* _pTrans;
private:	D3DXVECTOR3					_vDir;

private:	int							_iAniNum;

private:	float						_fSpeed;
private:	float						_fMaxDist;
private:	float						_fDist; //날아가는 거리
};

