#include "pch.h"
#include "SkillCommand.h"
#include "Player.h"
#include "Transform.h"

void SkillCommand::Execute(GameObject* actor, D3DXVECTOR3 curPos, Transform* pTargetTrans)noexcept
{
	//id에 맞는 스킬 사용.
	static_cast<Player*>(actor->GetComponent(COMPONENT_ID::BEHAVIOUR))->UsingSkill(_eID, curPos);
}
