#pragma once
#include "Skill.h"
class PoisonNova : public Skill
{
public:		explicit 			PoisonNova():Skill(POISON_NOVA,20) { __noop; }
public:		virtual 			~PoisonNova() noexcept { __noop; }

public:		virtual bool		Using(D3DXVECTOR3 vPos, Transform* pTrans, bool isDir)noexcept;


};

