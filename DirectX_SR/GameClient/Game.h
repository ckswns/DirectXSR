#pragma once
#include "Scene.h"

namespace ce
{
	namespace UI
	{
		class Image;
	}
}
class Player;
class InputHandler;
class Game : public Scene
{
public:		explicit			Game(void) noexcept;
public:		virtual			~Game(void) noexcept { __noop; }

public:		bool				Init(void) noexcept override;
public:		void				FixedUpdate(float fElapsedTime) noexcept override;
public:		void				Update(float fElapsedTime) noexcept override;
public:		void				LateUpdate(float fElapsedTime) noexcept override;
public:		void				Render(float fElapsedTime) noexcept override;
public:		void				Release(void) noexcept override;

private:	void				InitUI() noexcept;

public:		void				RClick();
public:		void				SetRAttack() noexcept;
public:		void				SetRRaise() noexcept;
public:		void				SetRSpear() noexcept;

public:		void				LClick();
public:		void				SetLAttack() noexcept;
public:		void				SetLRaise() noexcept;
public:		void				SetLSpear() noexcept;

private:	UI::Image*			_imgStamina;
private:	UI::Image*			_imgHP;
private:	UI::Image*			_imgMP;
private:	Player*				_pPlayer;

private:	InputHandler*		_pInputHandler;
private:	bool				_bRChk;
private:	UI::Image*			_pImgR;
private:	GameObject*			_pBtnRAttack;
private:	GameObject*			_pBtnRRaise;
private:	GameObject*			_pBtnRSpear;

private:	bool				_bLChk;
private:	UI::Image*			_pImgL;
private:	GameObject*			_pBtnLAttack;
private:	GameObject*			_pBtnLRaise;
private:	GameObject*			_pBtnLSpear;
};

