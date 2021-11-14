#pragma once
#include "Behaviour.h"

namespace ce
{
	namespace UI
	{
		class Image;
	}
}
class InputHandler;
class MouseBtnUI : public Behaviour
{
public:		explicit		MouseBtnUI() = delete;
public:		explicit		MouseBtnUI(InputHandler* input,bool isLeft) noexcept;
public:		virtual			~MouseBtnUI(void) noexcept { __noop; }

public:		virtual void	Start(void) noexcept;
public:		virtual void	Update(float fElapsedTime) noexcept { __noop; }

public:		void			BtnClick();
public:		void			SetAttack();
public:		void			SetRaise();
public:		void			SetSpear();

private:	bool			_bLeft;
private:	InputHandler*	_pInputHandler;

private:	bool			_bBtn;
private:	UI::Image*		_pImg;
private:	GameObject*		_pBtnAttack;
private:	GameObject*		_pBtnRaise;
private:	GameObject*		_pBtnSpear;
};

