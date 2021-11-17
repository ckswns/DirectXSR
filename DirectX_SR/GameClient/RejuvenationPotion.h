#pragma once
#include "Item.h"
class RejuvenationPotion : public Item
{
public:		explicit					RejuvenationPotion() noexcept;
public:		virtual						~RejuvenationPotion(void) noexcept { __noop; }

public:		virtual void				Start(void) noexcept;
};

