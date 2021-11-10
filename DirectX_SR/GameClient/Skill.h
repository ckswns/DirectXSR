#pragma once

class Skill	abstract
{
public:		explicit 				Skill() = delete;
public:		explicit				Skill(SKILL_ID id) :_eID(id) { __noop; }
public:		virtual 				~Skill() noexcept { __noop; }

public:		virtual bool			Using()noexcept PURE;

private:		SKILL_ID			_eID;
};

