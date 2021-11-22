#pragma once
#include "Behaviour.h"

class Item :public Behaviour
{
public:		explicit					Item() { __noop; }
public:		explicit					Item(ITEMDATA* item,D3DXVECTOR3 vPos) noexcept;
public:		virtual						~Item(void) noexcept { __noop; }

public:		virtual void				Start(void) noexcept;
public:		virtual void				Update(float) noexcept { __noop; }

public:		ITEMDATA*					GetItem() { return _tInvenItem; }

protected: 	ITEMDATA*					_tInvenItem;
private:	D3DXVECTOR3					_vPos;
};

