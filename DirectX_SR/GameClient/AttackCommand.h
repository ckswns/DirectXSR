#pragma once
#include "Command.h"
class AttackCommand : public Command
{
public:		virtual				~AttackCommand() noexcept { __noop; }
public:		virtual void		Execute(GameObject*Actor, D3DXVECTOR3 curPos) noexcept;
};

