#pragma once
#include "Item.h"
class Gold :  public Item
{
public:		explicit					Gold() noexcept;
public:		virtual						~Gold(void) noexcept { __noop; }

public:		virtual void				Start(void) noexcept;

};

