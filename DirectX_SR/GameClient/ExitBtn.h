#pragma once
#include "Behaviour.h"

namespace ce
{
	class Texture;
}


class ExitBtn : public Behaviour
{
public:		explicit		ExitBtn(void) noexcept;
public:		virtual			~ExitBtn(void) noexcept { __noop; }

public:		void			Start(void) noexcept override;
public:		void			Update(float) noexcept override;
public:		void			OnDestroy(void) noexcept override;

public:		void			OnMouseLeave(void) noexcept override;
public:		void			OnMouseOver(void) noexcept override;

public:		void			OnClickExit(void) noexcept;

public:		bool			GetIsOnMouse(void) const noexcept { return _onMouse; }

private:	bool			_onMouse = false;
private:	Texture*		_texture;
};

