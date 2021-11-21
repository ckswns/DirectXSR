#pragma once
#include "Behaviour.h"

class Item :public Behaviour
{
public:		explicit					Item() noexcept { __noop; }
public:		virtual						~Item(void) noexcept { __noop; }

public:		virtual void				Start(void) noexcept;
public:		virtual void				Update(float) noexcept;

public:		INVENITEMINFO*				GetItem() { return _tInvenItem; }

protected: 	INVENITEMINFO*				_tInvenItem;
private:	GameObject*					_pTxtName;
private:	bool						_bLook;
};

