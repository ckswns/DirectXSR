#pragma once
#include "Behaviour.h"

namespace ce
{
	namespace UI
	{
		class Image;
		class Text;
	}
}
class Player;
class StatusBall : public Behaviour
{
public:		explicit		StatusBall() = delete;
public:		explicit		StatusBall(Player* player,bool isHP) noexcept;
public:		virtual			~StatusBall(void) noexcept { __noop; }

public:		virtual void	Start(void) noexcept;
public:		virtual void	Update(float fElapsedTime) noexcept;

public:		virtual void			OnMouseLeave(void) noexcept;
public:		virtual void			OnMouseOver(void) noexcept;

private:	bool			_bHp;
private:	UI::Image*		_img;
private:	UI::Text*		_text;
private:	GameObject*		_txtObj;
private:	Player*			_pPlayer;
private:	float			_fPer;
};

