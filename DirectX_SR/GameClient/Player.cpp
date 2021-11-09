#include "pch.h"
#include "Player.h"
#include "MeshRenderer.h"
#include "Quad.h"
#include "Transform.h"
#include "Texture.h"
#include "Skill.h"

void Player::Start(void) noexcept
{
	_bAtt = false;
	_bMove = false;

	_fSpeed = 5.f;
	_fRunSpeed = _fSpeed + 2.f;

	_pSkills.resize(SKILL_END);

	_pTrans = static_cast<Transform*>(GetGameObject()->GetTransform());

	_pTexture = new Texture();
	_pTexture->Init(D3D9DEVICE->GetDevice(), "Asset/Player/Player.png");

	Quad* quad = new Quad(4, 4);
	quad->Open(D3D9DEVICE->GetDevice());

	MeshRenderer* mr = new MeshRenderer(D3D9DEVICE->GetDevice(), quad);
	GetGameObject()->AddComponent(mr);
	//텍스처 셋팅
	mr->GetMaterialPTR()->SetTexture(_pTexture);
}

void Player::Update(float fElapsedTime) noexcept
{
	if (_bMove)
	{
		D3DXVECTOR3 vDir = _vDest - _pTrans->GetWorldPosition();

		if (D3DXVec3Length(&vDir) <= 1.f)
		{
			_bMove = false;
			if (_bAtt)
				Attack(_vDest);
		}
		else 
		{
			D3DXVec3Normalize(&vDir, &vDir);

			_pTrans->Translate(vDir * _fSpeed* fElapsedTime);
		}
	}
}

void Player::UsingSkill(SKILL_ID id)
{
	_pSkills[id]->Using();
}

void Player::Attack(D3DXVECTOR3 _vMonsterPos)
{	
	_bAtt = true;

//적과 거리가 가까운가?
	D3DXVECTOR3 vDir = _vMonsterPos - _pTrans->GetWorldPosition();
	if (D3DXVec3Length(&vDir) <= 2.f)
	{
		// >> 공격
		// 공격 애니메이션
		// 소리 
		//충돌판정
	}
	else 
	{
		_bMove = true;
		_vDest = _vMonsterPos;
		//이동 애니메이션
	}

}
