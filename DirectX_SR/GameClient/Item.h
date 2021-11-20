#pragma once
#include "Behaviour.h"

class Item :public Behaviour
{
public:		explicit					Item() noexcept { __noop; }
public:		virtual						~Item(void) noexcept { __noop; }

public:		virtual void				Start(void) noexcept;
public:		virtual void				Update(float) noexcept;

public:		ITEMDATA*				GetItem() { return _tInvenItem; }

protected: 	ITEMDATA*				_tInvenItem;
private:	GameObject*					_pTxtName;
private:	bool						_bLook;
};

