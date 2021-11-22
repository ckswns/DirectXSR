#pragma once
#include "Behaviour.h"

class Actor;
namespace ce
{
	namespace UI
	{
		class Image;
		class Text;
	}
}

class MonsterHPBar : public Behaviour
{
public:		explicit		MonsterHPBar(void) noexcept;
public:		virtual			~MonsterHPBar(void) noexcept { __noop; }

public:		void			Start(void) noexcept override;
public:		void			Update(float) noexcept override;

public:		void			SetMonster(Actor* monster) noexcept;
public:		Actor* const	GetMonster(void) noexcept { return _monster; }

private:	Actor*			_monster;

private:	UI::Image*		_frame;
private:	UI::Image*		_hpBar;
private:	UI::Text*		_text;

public:		static MonsterHPBar* const	Instance(void) noexcept;
private:	static MonsterHPBar*		_instance;

private:	float			_deltaTime = 0;
};

