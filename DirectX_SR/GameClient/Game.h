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

private:	UI::Image*			_imgStamina;
private:	UI::Image*			_imgHP;
private:	UI::Image*			_imgMP;
private:	Player*				_pPlayer;

};

