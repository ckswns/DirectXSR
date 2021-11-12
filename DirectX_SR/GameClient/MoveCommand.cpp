#include "pch.h"
#include "MoveCommand.h"
#include "Player.h"

void MoveCommand::Execute(GameObject* Actor, D3DXVECTOR3 curPos) noexcept
{
	static_cast<Player*>(Actor->GetComponent(COMPONENT_ID::BEHAVIOUR))->SetState(PLAYER_MOVE, FRONT,curPos);//->Move(curPos);
}
