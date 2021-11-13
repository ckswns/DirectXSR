#pragma once
#include "Behaviour.h"

namespace ce 
{
	class GameObject;
	class Terrain;
}
class Command;
class InputHandler : public Behaviour
{
public:		explicit		InputHandler() = delete;
public:		explicit		InputHandler(GameObject * player, Terrain * terrain) noexcept;
public:		virtual			~InputHandler(void) noexcept { __noop; }

public:		virtual void	Start(void) noexcept;
public:		virtual void	Update(float fElapsedTime) noexcept;
public:		virtual void	OnDestroy(void) noexcept;

public:		void			SetLB(SKILL_ID id) noexcept;
public:		void			SetRB(SKILL_ID id) noexcept;

private:	D3DXVECTOR3		MousePicking();

private:	Command*		_pLBCommand;
private:	Command*		_pRBCommand;
private:	Command*		_pMoveCommand;

private:	GameObject*		_pPlayer;
private:	Terrain*		_pTerrain;

};

