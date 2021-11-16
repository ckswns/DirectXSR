#pragma once
#include "Item.h"
class MpPotion : public Item
{
public:		explicit					MpPotion() noexcept;
public:		virtual						~MpPotion(void) noexcept { __noop; }

public:		virtual void				Start(void) noexcept;
};

