#pragma once
#include "Behaviour.h"

namespace ce
{
	class Transform;
	class Texture;
}

class Skill;
class Player : public Behaviour
{
public:		explicit					Player() noexcept { __noop; }
public:		virtual					~Player(void) noexcept { __noop; }

public:		virtual void				Start(void) noexcept;
public:		virtual void				Update(float fElapsedTime) noexcept;

public:		void						UsingSkill(SKILL_ID id);
public:		void						Attack(D3DXVECTOR3 _vMonsterPos);
public:		void						SetDestination(D3DXVECTOR3 dest) { _vDest = dest; _bMove = true; }

private:		Transform*				_pTrans;
private:		Texture*					_pTexture;
private:		STAT						_tStat;
private:		std::vector<Skill*>	_pSkills;

private:		bool						_bAtt;
private:		bool						_bMove;
private:		D3DXVECTOR3		_vDest;

private:		float						_fSpeed;
private:		float						_fRunSpeed;

private:		int							_iMaxSkeleton;
};

