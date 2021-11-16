#pragma once

#include "Item.h"
class HpPotion : public Item
{
public:		explicit					HpPotion() noexcept;
public:		virtual						~HpPotion(void) noexcept { __noop; }

public:		virtual void				Start(void) noexcept;
};