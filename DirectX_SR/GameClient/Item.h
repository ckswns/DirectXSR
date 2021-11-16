#pragma once
#include "Behaviour.h"

namespace ce
{
	namespace UI 
	{
		class Image;
	}
	class Coillder;
}
class Item :public Behaviour
{
public:		explicit					Item() noexcept { __noop; }
public:		virtual						~Item(void) noexcept { __noop; }

public:		virtual void				Start(void) noexcept { __noop; }
public:		virtual void			Update(float) noexcept { __noop; }

public:		INVENITEMINFO* GetItem() { return &_tInvenItem; }

protected: 	INVENITEMINFO	_tInvenItem;
};

