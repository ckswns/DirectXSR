#pragma once
#include "Command.h"

class SkillCommand :public Command
{
public:		virtual				~SkillCommand() noexcept { __noop; }
public:		virtual void			Execute(GameObject* Actor, D3DXVECTOR3 curPos) noexcept;

public:		void					SetSkill(SKILL_ID id) { _eID = id; }

private:		SKILL_ID			_eID;
};

