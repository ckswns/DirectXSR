#include "pch.h"
#include "MoveCommand.h"
#include "Player.h"
#include "Transform.h"

void MoveCommand::Execute(GameObject* actor, D3DXVECTOR3 curPos, Transform* pTargetTrans) noexcept
{
	static_cast<Player*>(actor->GetComponent(COMPONENT_ID::BEHAVIOUR))->SetState(PLAYER_MOVE, DIR_END, curPos);//->Move(curPos);
}
