#pragma once
#include "Item.h"
class PlateArmor : public Item
{
public:		explicit					PlateArmor() noexcept;
public:		virtual						~PlateArmor(void) noexcept { __noop; }

public:		virtual void				Start(void) noexcept;
};

