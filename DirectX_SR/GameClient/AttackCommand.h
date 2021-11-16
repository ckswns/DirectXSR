#pragma once
#include "Command.h"
class AttackCommand : public Command
{
public:		virtual				~AttackCommand() noexcept { __noop; }
public:		virtual void		Execute(GameObject* actor, D3DXVECTOR3 curPos, Transform* pTargetTrans) noexcept;
};

