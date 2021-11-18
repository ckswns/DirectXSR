#pragma once
#include "ItemSlot.h"
class StoreWnd;
class StoreItem : public ItemSlot
{
public: explicit	 StoreItem(Slot::SLOTTYPE eType,StoreWnd* store) noexcept;
public: virtual		 ~StoreItem() noexcept { __noop; }

public:		virtual void			OnMouseDown(void) noexcept;

private:	StoreWnd*				_pStore;
};

