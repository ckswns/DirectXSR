#pragma once
#include "Skill.h"
class BoneSpear : public Skill
{
public:		explicit 					BoneSpear() noexcept;
public:		virtual 					~BoneSpear() noexcept { __noop; }

public:		virtual bool				Using(D3DXVECTOR3 vPos, Transform* pTrans)noexcept;
};

