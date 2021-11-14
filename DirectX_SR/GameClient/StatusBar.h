#pragma once
#include "Behaviour.h"

namespace ce
{
	class GameObject;
	namespace UI
	{
		class Image;
	}
}
class Player;
class InputHandler;
class StatusBar : public Behaviour
{

public:		explicit			StatusBar() = delete;
public:		explicit			StatusBar(InputHandler* input,Player* player) noexcept 
											:_pInputHandler(input), _pPlayer(player) {__noop;}
public:		virtual				~StatusBar(void) noexcept { __noop; }

public:		virtual void		Start(void) noexcept;
public:		virtual void		Update(float fElapsedTime) noexcept;

private:	void				InitUI() noexcept;

private:	UI::Image*			_imgStamina;
private:	UI::Image*			_imgHP;
private:	UI::Image*			_imgMP;

private:	Player*				_pPlayer;
private:	InputHandler*		_pInputHandler;

};

