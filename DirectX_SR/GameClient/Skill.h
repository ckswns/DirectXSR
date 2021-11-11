#pragma once

namespace ce
{
	class Transform;
}
class Skill	abstract
{
public:		explicit 					Skill() = delete;
public:		explicit					Skill(SKILL_ID id, float mp) :_eID(id), _fMp(mp) { __noop; }
public:		virtual 					~Skill() noexcept { __noop; }

public:		const SKILL_ID		GetSkillID() const { return _eID; }
public:		const	 float				GetUsingMp() const { return _fMp; }
public:		virtual bool				Using(D3DXVECTOR3 vPos, Transform* pTrans)noexcept PURE;

private:		SKILL_ID			_eID;
protected:	float					_fMp;
};

