#include "pch.h"
#include "SkillCommand.h"
#include "Player.h"

void SkillCommand::Execute(GameObject* Actor, D3DXVECTOR3 curPos) noexcept
{
	//id�� �´� ��ų ���.
	static_cast<Player*>(Actor->GetComponent(COMPONENT_ID::BEHAVIOUR))->UsingSkill(_eID,curPos);
}
