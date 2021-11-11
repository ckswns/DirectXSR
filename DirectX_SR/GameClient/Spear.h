#pragma once
#include "Behaviour.h"

namespace ce
{
	class Transform;
}
class Spear : public Behaviour
{
public:		explicit					Spear()noexcept { __noop; }
//public:		explicit					Spear(D3DXVECTOR3 dir) noexcept;
public:		virtual					~Spear(void) noexcept { __noop; }

public:		virtual void				Start(void) noexcept;
public:		virtual void				Update(float fElapsedTime) noexcept;

//private:		Transform*				_pTrans;
//private:		D3DXVECTOR3		_vDir;
//private:		float						_fSpeed;
//private:		float						_fMaxDist;
//private:		float						_fDist; //날아가는 거리

};

