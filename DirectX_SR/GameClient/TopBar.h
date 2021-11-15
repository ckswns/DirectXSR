#pragma once
#include "Behaviour.h"

namespace ce
{
	namespace UI
	{
		class Image;
	}
	class Texture;
}

class ExitBtn;

class TopBar : public Behaviour
{
public:		explicit		TopBar(HWND hWnd) noexcept;
public:		virtual			~TopBar(void) noexcept { __noop; }

public:		void			Start(void) noexcept override;
public:		void			Update(float) noexcept override;
public:		void			OnDestroy(void) noexcept override;

public:		void			OnMouseEnter(void) noexcept override;
public:		void			OnMouseLeave(void) noexcept override;
public:		void			OnMouseOver(void) noexcept override;
public:		void			OnMouseDown(void) noexcept override;
public:		void			OnMouseUp(void) noexcept override;
public:		void			OnMouseHeldDown(void) noexcept override;

private:	HWND			_hWnd;
private:	UI::Image*		_img = nullptr;
private:	Texture*		_texture = nullptr;

private:	ExitBtn*		_exitBtn = nullptr;

private:	POINT			_prevMousePos = { 0, 0 };
private:	POINT			_clientPos = { 0, 0 };
private:	bool			_bDrag = false;
private:	bool			_bShow = false;
};

