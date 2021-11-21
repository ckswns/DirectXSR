#pragma once
#include "Behaviour.h"

namespace ce
{
	namespace UI
	{
		class Image;
	}
}

class FadeController : public Behaviour
{
private:	explicit		FadeController(void) noexcept;
public:		virtual			~FadeController(void) noexcept { __noop; }

public:		void			Start(void) noexcept override;
public:		void			Update(float) noexcept override;

private:	bool			_fadeIn = false;
private:	bool			_fadeOut = false;
private:	bool			_doing = false;

private:	float			_alpha;
private:	float			_fadeTime;
private:	float			_deltaTime;

private:	UI::Image*		_image;

public:		static void		FadeIn(float time) noexcept;
public:		static void		FadeOut(float time) noexcept;
public:		static bool		IsEnd(void) noexcept;

private:	static	FadeController* _instance;
};

