#pragma once
#include "Behaviour.h"

namespace ce
{
	namespace UI
	{
		class Text;
	}
}

class DbgShowFrame : public Behaviour
{
public:		explicit	DbgShowFrame(void) noexcept;
public:		virtual		~DbgShowFrame(void) noexcept { __noop; }

public:		void		Start(void) noexcept override;
public:		void		Update(float) noexcept override;

private:	UI::Text*	_text;
};

