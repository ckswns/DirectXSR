#include "pch.h"
#include "AttackCommand.h"
#include "Player.h"

void AttackCommand::Execute(GameObject* Actor, D3DXVECTOR3 curPos) noexcept
{
	static_cast<Player*>(Actor->GetComponent(COMPONENT_ID::BEHAVIOUR))->SetState(PLAYER_ATTACK, curPos);//->Attack(curPos);
}
