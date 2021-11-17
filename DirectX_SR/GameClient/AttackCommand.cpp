#include "pch.h"
#include "AttackCommand.h"
#include "Player.h"
#include "Transform.h"

void AttackCommand::Execute(GameObject* actor, D3DXVECTOR3 curPos, Transform* pTargetTrans) noexcept
{
	static_cast<Player*>(actor->GetComponent(COMPONENT_ID::BEHAVIOUR))->SetState(PLAYER_ATTACK, pTargetTrans);//->Attack(curPos);
}
