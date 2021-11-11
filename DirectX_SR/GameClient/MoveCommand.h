#pragma once
#include "Command.h"
class MoveCommand : public Command
{
public:		virtual				~MoveCommand() noexcept { __noop; }
public:		virtual void			Execute(GameObject* Actor, D3DXVECTOR3 curPos) noexcept;
};

