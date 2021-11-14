#pragma once
#include "Behaviour.h"

namespace ce
{
	class Transform;
}
class Projectile :	public Behaviour
{
public:		explicit					Projectile() = delete;
public:		explicit					Projectile(D3DXVECTOR3 dir, bool isDir) noexcept;
public:		virtual						~Projectile(void) noexcept { __noop; }

public:		virtual void				Start(void) noexcept;
public:		virtual void				Update(float fElapsedTime) noexcept;

private:	Transform*					_pTrans;
private:	D3DXVECTOR3					_vDir;
private:	bool						_bDir;
private:	float						_fSpeed;
private:	float						_fMaxDist;
private:	float						_fDist; //날아가는 거리

private:	GameObject*					_pSpear;
private:	std::vector<GameObject*>	_pTrails;
private:	bool						_bRot;
};

