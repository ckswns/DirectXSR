#pragma once

namespace ce
{
	class Transform;
}
class Skill	abstract
{
public:		explicit 					Skill() = delete;
public:		explicit					Skill(SKILL_ID id) :_eID(id) { __noop; }
public:		virtual 					~Skill() noexcept { __noop; }

public:		const SKILL_ID		GetSkillID() const { return _eID; }
public:		virtual bool				Using(D3DXVECTOR3 vPos, Transform* pTrans)noexcept PURE;

private:		SKILL_ID			_eID;
};

