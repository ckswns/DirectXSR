#include "pch.h"
#include "StoreItem.h"
#include "StoreWnd.h"
StoreItem::StoreItem(Slot::SLOTTYPE eType, StoreWnd* store) noexcept
	:ItemSlot(eType, nullptr), _pStore(store), _InfoVisible(false)
{
}

void StoreItem::Start(void) noexcept
{
	ItemSlot::Start();
	_pInfoBox->SetStoreItem(true);
	
}

void StoreItem::OnMouseDown(void) noexcept
{
	_pInfoBox->ShowInfoBox(false);
	_pStore->Sell(gameObject);
}

void StoreItem::OnMouseOver(void) noexcept
{
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (!_InfoVisible)
	{
		_InfoVisible = true;
		_pInfoBox->ShowInfoBox(true);
	}
	_pInfoBox->SetPosition(pt.x, pt.y);
}

void StoreItem::OnMouseLeave(void) noexcept
{
	if (_InfoVisible)
	{
		_InfoVisible = false;
		_pInfoBox->ShowInfoBox(false);
	}
}
