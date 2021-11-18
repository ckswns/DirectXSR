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
public:		virtual					~InputHandler(void) noexcept { __noop; }

public:		virtual void			Start(void) noexcept;
public:		virtual void			Update(float fElapsedTime) noexcept;
public:		virtual void			OnDestroy(void) noexcept;

public:		void					SetMouseBtn(bool isLeft, SKILL_ID id);

public:		const D3DXVECTOR3&		GetDir(void) const noexcept { return _vDir; }

public:		void					ClosedStore() { _bUsingStore = false; }
private:	bool					_bUsingStore;

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

private:	bool					_bFPV;
private:	bool					_bDown;
private:	bool					_bAtt;
private:	D3DXVECTOR3				_vDir;
private:	POINT					_ptStart;
};

