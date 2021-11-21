#pragma once
#include "ItemSlot.h"

class StoreWnd;
class StoreItem : public ItemSlot
{
public:		explicit				StoreItem(Slot::SLOTTYPE eType,StoreWnd* store) noexcept;
public:		virtual					~StoreItem() noexcept { __noop; }


public:		virtual	void			Start(void) noexcept override;
public:		virtual void			Update(float) noexcept { __noop; }

public:		virtual void			OnMouseDown(void) noexcept;
public:		virtual void			OnMouseOver(void) noexcept;
public:		virtual void			OnMouseLeave(void) noexcept;

private:	StoreWnd*				_pStore;
private:	bool					_InfoVisible;
};

