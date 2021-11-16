#pragma once
#include "Command.h"

class SkillCommand :public Command
{
public:		virtual				~SkillCommand() noexcept { __noop; }
public:		virtual void		Execute(GameObject* actor, D3DXVECTOR3 curPos, Transform* pTargetTrans) noexcept;

public:		void				SetSkill(SKILL_ID id) { _eID = id; }

private:	SKILL_ID			_eID;
};

