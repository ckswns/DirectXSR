#pragma once
#include "Behaviour.h"

namespace ce
{
	class Transform;
	class Animator;
	class SphereCollider;
	class BoxCollider;
	class SpriteRenderer;
	class AudioSource;
	class AudioAsset;
}

class Skill;
class PathFinding;
class InputHandler;
class PlayerFSMState;
class Inventory;
class Player : public Behaviour
{
private:	using		VEC_FSM = std::vector<PlayerFSMState*>;

public:		explicit				Player() noexcept = delete;
public:		explicit				Player(PathFinding* pf) noexcept;
public:		virtual					~Player(void) noexcept { __noop; }

public:		virtual void			Start(void) noexcept;
public:		virtual void			FixedUpdate(float fElapsedTime) noexcept;
public:		virtual void			Update(float fElapsedTime) noexcept;
public:		virtual void			OnDestroy(void) noexcept;

public:		void					OnCollisionEnter(Collider* mine, Collider* other) noexcept override;
public:		void					OnCollisionStay(Collider* mine, Collider* other) noexcept override;
public:		void					OnCollisionExit(Collider* mine, Collider* other) noexcept override;

private:	void					InitAnimation(SpriteRenderer* mr);
private:	void					InitState();

public:		void					SetFPV();
public:		void					SetState(PLAYER_STATE newState,DIR eDir,D3DXVECTOR3 vTarget = D3DXVECTOR3(0,-5,0));
public:		void					SetState(PLAYER_STATE newState,Transform* targetTrans, bool bAtt =false);
public:		void					UsingSkill(SKILL_ID id,D3DXVECTOR3 vPos);

public:		void					SetAttCollider(bool b);
public:		void					OnAnimationEvent(std::string str) noexcept override;

public:		float					GetAtt() { return _tStat->_fDamage; } //아이템 장착하면 아이템값까지 
public:		void					GetHit(float fDamage, D3DXVECTOR3 vPos);

public:		bool					IsRunning(float fElapsedTime);
public:		float					GetHPPer();
public:		float					GetMPPer();
public:		float					GetStaminaPer();
public:		InputHandler*			GetInpuHandler() { return _pInputHandler; }
public:		Inventory*				GetInventory() { return _pInven; }

private:	Transform*				_pTrans;
private:	Animator*				_pAnimator;
private:	SphereCollider*			_pCollider;
private:	BoxCollider*			_pAttCollider;

private:	InputHandler*			_pInputHandler;

private:	VEC_FSM					_pFSM;
private:	PLAYER_STATE			_eCurState;

private:	GameObject*				_pInvenObj;
private:	Inventory*				_pInven;
private:	PathFinding*			_pPathFinding;
private:	AudioSource*			_pAudioSource;
private:	AudioAsset*				_pManaSound[3];
private:	AudioAsset*				_pDamagedSound[3];

private:	STAT*					_tStat;
private:	std::vector<Skill*>		_pSkills;

private:	bool					_bCollWithObstacle = false;
private:	D3DXVECTOR3				_prevPos;

private:	bool					_bFPV;
private:	float					_fRecovery;
private:	float					_fSpeed;
private:	float					_fRunSpeed;


};

