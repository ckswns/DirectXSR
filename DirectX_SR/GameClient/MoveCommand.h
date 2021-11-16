#pragma once
#include "Command.h"
class MoveCommand : public Command
{
public:		virtual				~MoveCommand() noexcept { __noop; }
public:		virtual void		Execute(GameObject* actor, D3DXVECTOR3 curPos, Transform* pTargetTrans = nullptr) noexcept;
};

