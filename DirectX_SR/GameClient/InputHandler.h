#pragma once
#include "Behaviour.h"

namespace ce 
{
	class GameObject;
	class Transform;
}
class Command;
class Player;
class TargetCamera;
class InputHandler //: public Behaviour
{
public:		explicit				InputHandler() = delete;
public:		explicit				InputHandler(Player * player) noexcept;
public:								~InputHandler(void) noexcept { __noop; }

public:		void					Start(void) noexcept;
public:		void					Update(float fElapsedTime) noexcept;
public:		void					OnDestroy(void) noexcept;

public:		void					SetMouseBtn(bool isLeft, SKILL_ID id);
public:		void					SetInvenOpen(bool b) { _bInven = b; }
public:		void					SetPlayerDead();

public:		const D3DXVECTOR3&		GetDir(void) const noexcept { return _vDir; }

public:		void					ClosedStore();

private:	bool					_bUsingStore;
private:	bool					_bInven;

private:	bool					_bLBSkill;
private:	bool					_bRBSkill;
private:	Command*				_pLBCommand;
private:	Command*				_pRBCommand;
private:	Command*				_pMoveCommand;

private:	GameObject*				_pPlayerObj;
private:	Player*					_pPlayer;
private:	Transform*				_pPlayerTrans;

private:	TargetCamera*			_pTargetCamera;
private:	Transform*				_pCameraTrans;

private:	bool					_bDead;
private:	GameObject*				_DiedObj;

private:	bool					_bFPV;
private:	bool					_bDown;
private:	bool					_bAtt;
private:	bool					_isKeyDown = false;
private:	D3DXVECTOR3				_vDir;
private:	POINT					_ptStart;
};

