#include "pch.h"
#include "StoreItem.h"
#include "StoreWnd.h"
StoreItem::StoreItem(Slot::SLOTTYPE eType, StoreWnd* store) noexcept
	:ItemSlot(eType, 0), _pStore(store)
{
}

void StoreItem::OnMouseDown(void) noexcept
{
	_pStore->Sell(gameObject);
}
