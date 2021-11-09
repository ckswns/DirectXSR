#pragma once
#include "Skill.h"
class RaiseSkeleton :	public Skill
{
public:		explicit 				RaiseSkeleton() = delete;
public:		explicit				RaiseSkeleton(SKILL_ID id) :Skill(id) { __noop; }
public:		virtual 				~RaiseSkeleton() noexcept { __noop; }

public:		virtual bool			Using()noexcept;
};

