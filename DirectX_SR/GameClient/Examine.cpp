#include "pch.h"
#include "Examine.h"
#include "Slot.h"
#include "ItemSlot.h"

Examine::Examine() noexcept
{
}

SLOTINFO* Examine::EatingExamine1X1(std::vector<SLOTINFO*> InvenSlot)
{
	int Index = 0;
	int iInvenCntX = InvenSlot[0]->_iSlotCntX;
	int iInvenCntY = InvenSlot[0]->_iSlotCntY;

	int MaxIndex = (iInvenCntX * iInvenCntY) - 1;

	for (int i = 0; i < iInvenCntY; ++i)
	{
		for (int j = 0; j < iInvenCntX; ++j)
		{
			Index = i * iInvenCntX + j;

			if (MaxIndex >= Index)
			{
				if (!InvenSlot[Index]->_bSlotCheck)
				{
					InvenSlot[Index]->_bSlotCheck = true;
					return InvenSlot[Index];
				}
			}
			else
				return nullptr;
		}
	}
	return nullptr;
}

SLOTINFO* Examine::EatingExamine1X3(std::vector<SLOTINFO*> InvenSlot)
{
	int Index = 0;
	int iInvenCntX = InvenSlot[0]->_iSlotCntX;
	int iInvenCntY = InvenSlot[0]->_iSlotCntY;

	int MaxIndex = (iInvenCntX * iInvenCntY) - 1;

	for (int i = 0; i < iInvenCntY; ++i)
	{
		for (int j = 0; j < iInvenCntX; ++j)
		{
			Index = i * iInvenCntX + j;
			if (MaxIndex >= Index && MaxIndex >= (Index + iInvenCntX) && MaxIndex >= (Index + (iInvenCntX * 2)))
			{
				if (!InvenSlot[Index]->_bSlotCheck
					&& !InvenSlot[Index + iInvenCntX]->_bSlotCheck
					&& !InvenSlot[Index + (iInvenCntX * 2)]->_bSlotCheck)
				{
					InvenSlot[Index]->_bSlotCheck = true;
					InvenSlot[Index + iInvenCntX]->_bSlotCheck = true;
					InvenSlot[Index + (iInvenCntX * 2)]->_bSlotCheck = true;
					return InvenSlot[Index];
				}
			}
			else
				return nullptr;
		}
	}
	return nullptr;
}

SLOTINFO* Examine::EatingExamine2X1(std::vector<SLOTINFO*> InvenSlot)
{
	int Index = 0;
	int iInvenCntX = InvenSlot[0]->_iSlotCntX;
	int iInvenCntY = InvenSlot[0]->_iSlotCntY;

	int MaxIndex = (iInvenCntX * iInvenCntY) - 1;

	for (int i = 0; i < iInvenCntY; ++i)
	{
		for (int j = 0; j < iInvenCntX; ++j)
		{
			Index = i * iInvenCntX + j;

			if (MaxIndex >= Index && MaxIndex >= (Index + 1))
			{
				if (!InvenSlot[Index]->_bSlotCheck
					&& !InvenSlot[Index + 1]->_bSlotCheck)
				{
					InvenSlot[Index]->_bSlotCheck = true;
					InvenSlot[Index + 1]->_bSlotCheck = true;
					return InvenSlot[Index];
				}
			}
		}
	}
	return nullptr;
}

SLOTINFO* Examine::EatingExamine1X2(std::vector<SLOTINFO*> InvenSlot)
{
	int Index = 0;
	int iInvenCntX = InvenSlot[0]->_iSlotCntX;
	int iInvenCntY = InvenSlot[0]->_iSlotCntY;

	int MaxIndex = (iInvenCntX * iInvenCntY) - 1;

	for (int i = 0; i < iInvenCntY; ++i)
	{
		for (int j = 0; j < iInvenCntX; ++j)
		{
			Index = i * iInvenCntX + j;

			if (MaxIndex >= Index && MaxIndex >= (Index + iInvenCntX))
			{
				if (!InvenSlot[Index]->_bSlotCheck
					&& !InvenSlot[Index + iInvenCntX]->_bSlotCheck)
				{
					InvenSlot[Index]->_bSlotCheck = true;
					InvenSlot[Index + iInvenCntX]->_bSlotCheck = true;
					return InvenSlot[Index];
				}
			}
		}
	}
	return nullptr;
}

SLOTINFO* Examine::EatingExamine2X2(std::vector<SLOTINFO*> InvenSlot)
{
	int Index = 0;
	int iInvenCntX = InvenSlot[0]->_iSlotCntX;
	int iInvenCntY = InvenSlot[0]->_iSlotCntY;

	int MaxIndex = (iInvenCntX * iInvenCntY) - 1;

	for (int i = 0; i < iInvenCntY; ++i)
	{
		for (int j = 0; j < iInvenCntX; ++j)
		{
			Index = i * iInvenCntX + j;

			if (MaxIndex >= Index && MaxIndex >= Index + 1 && MaxIndex >= Index + iInvenCntX && MaxIndex >= Index + iInvenCntX + 1)
			{
				if (!InvenSlot[Index]->_bSlotCheck
					&& !InvenSlot[Index + 1]->_bSlotCheck
					&& !InvenSlot[Index + iInvenCntX]->_bSlotCheck
					&& !InvenSlot[Index + iInvenCntX + 1]->_bSlotCheck)
				{
					InvenSlot[Index]->_bSlotCheck = true;
					InvenSlot[Index + 1]->_bSlotCheck = true;
					InvenSlot[Index + iInvenCntX]->_bSlotCheck = true;
					InvenSlot[Index + iInvenCntX + 1]->_bSlotCheck = true;
					return InvenSlot[Index];
				}
			}
			else
				return nullptr;
		}
	}
	return nullptr;
}

SLOTINFO* Examine::EatingExamine2X3(std::vector<SLOTINFO*> InvenSlot)
{
	int Index = 0;
	int iInvenCntX = InvenSlot[0]->_iSlotCntX;
	int iInvenCntY = InvenSlot[0]->_iSlotCntY;

	int MaxIndex = (iInvenCntX * iInvenCntY) - 1;
	for (int i = 0; i < iInvenCntY; ++i)
	{
		for (int j = 0; j < iInvenCntX; ++j)
		{
			Index = i * iInvenCntX + j;

			if (MaxIndex >= Index && MaxIndex >= Index + 1 && MaxIndex >= Index + iInvenCntX && MaxIndex >= Index + iInvenCntX + 1
				&& MaxIndex >= Index + (iInvenCntX * 2) && MaxIndex >= Index + (iInvenCntX * 2) + 1)
			{
				if (!InvenSlot[Index]->_bSlotCheck
					&& !InvenSlot[Index + 1]->_bSlotCheck
					&& !InvenSlot[Index + iInvenCntX]->_bSlotCheck
					&& !InvenSlot[Index + iInvenCntX + 1]->_bSlotCheck
					&& !InvenSlot[Index + (iInvenCntX * 2)]->_bSlotCheck
					&& !InvenSlot[Index + (iInvenCntX * 2) + 1]->_bSlotCheck)
				{
					InvenSlot[Index]->_bSlotCheck = true;
					InvenSlot[Index + 1]->_bSlotCheck = true;
					InvenSlot[Index + iInvenCntX]->_bSlotCheck = true;
					InvenSlot[Index + iInvenCntX + 1]->_bSlotCheck = true;
					InvenSlot[Index + (iInvenCntX * 2)]->_bSlotCheck = true;
					InvenSlot[Index + (iInvenCntX * 2) + 1]->_bSlotCheck = true;
					return InvenSlot[Index];
				}
			}
			else
				return nullptr;
		}
	}
	return nullptr;
}

SLOTINFO* Examine::MouseExamine1X1(std::vector<SLOTINFO*> InvenSlot, POINT pt)
{
	int Index = 0;
	int iInvenCntX = InvenSlot[0]->_iSlotCntX;
	int iInvenCntY = InvenSlot[0]->_iSlotCntY;

	int MaxIndex = (iInvenCntX * iInvenCntY) - 1;

	for (int i = 0; i < iInvenCntY; ++i)
	{
		for (int j = 0; j < iInvenCntX; ++j)
		{
			Index = i * iInvenCntX + j;
			if (PtInRect(&InvenSlot[Index]->_tRect, pt))
			{
				if (MaxIndex >= Index)
				{
					if (!InvenSlot[Index]->_bSlotCheck)
					{
						InvenSlot[Index]->_bSlotCheck = true;
						return InvenSlot[Index];
					}
				}
				else
					return nullptr;
			}
		}
	}
	return nullptr;
}

SLOTINFO* Examine::MouseExamine1X3(std::vector<SLOTINFO*> InvenSlot, POINT pt)
{
	int Index = 0;
	int iInvenCntX = InvenSlot[0]->_iSlotCntX;
	int iInvenCntY = InvenSlot[0]->_iSlotCntY;

	int MaxIndex = (iInvenCntX * iInvenCntY) - 1;

	for (int i = 0; i < iInvenCntY; ++i)
	{
		for (int j = 0; j < iInvenCntX; ++j)
		{
			Index = i * iInvenCntX + j;
			if (PtInRect(&InvenSlot[Index]->_tRect, pt))
			{
				if (MaxIndex >= Index && MaxIndex >= (Index + iInvenCntX) && MaxIndex >= (Index + (iInvenCntX * 2)))
				{
					if (!InvenSlot[Index]->_bSlotCheck
						&& !InvenSlot[Index + iInvenCntX]->_bSlotCheck
						&& !InvenSlot[Index + (iInvenCntX * 2)]->_bSlotCheck)
					{
						InvenSlot[Index]->_bSlotCheck = true;
						InvenSlot[Index + iInvenCntX]->_bSlotCheck = true;
						InvenSlot[Index + (iInvenCntX * 2)]->_bSlotCheck = true;
						return InvenSlot[Index];
					}
				}
				else
					return nullptr;
			}
		}
	}
	return nullptr;
}

SLOTINFO* Examine::MouseExamine2X1(std::vector<SLOTINFO*> InvenSlot, POINT pt)
{
	int Index = 0;
	int iInvenCntX = InvenSlot[0]->_iSlotCntX;
	int iInvenCntY = InvenSlot[0]->_iSlotCntY;

	int MaxIndex = (iInvenCntX * iInvenCntY) - 1;

	for (int i = 0; i < iInvenCntY; ++i)
	{
		for (int j = 0; j < iInvenCntX; ++j)
		{
			Index = i * iInvenCntX + j;

			if (PtInRect(&InvenSlot[Index]->_tRect, pt))
			{
				if (MaxIndex >= Index && MaxIndex >= (Index + 1))
				{
					if (!InvenSlot[Index]->_bSlotCheck
						&& !InvenSlot[Index + 1]->_bSlotCheck)
					{
						InvenSlot[Index]->_bSlotCheck = true;
						InvenSlot[Index + 1]->_bSlotCheck = true;
						return InvenSlot[Index];
					}
				}
			}
		}
	}
	return nullptr;
}

SLOTINFO* Examine::MouseExamine1X2(std::vector<SLOTINFO*> InvenSlot, POINT pt)
{
	int Index = 0;
	int iInvenCntX = InvenSlot[0]->_iSlotCntX;
	int iInvenCntY = InvenSlot[0]->_iSlotCntY;

	int MaxIndex = (iInvenCntX * iInvenCntY) - 1;

	for (int i = 0; i < iInvenCntY; ++i)
	{
		for (int j = 0; j < iInvenCntX; ++j)
		{
			Index = i * iInvenCntX + j;

			if (PtInRect(&InvenSlot[Index]->_tRect, pt))
			{
				if (MaxIndex >= Index && MaxIndex >= (Index + iInvenCntX))
				{
					if (!InvenSlot[Index]->_bSlotCheck
						&& !InvenSlot[Index + iInvenCntX]->_bSlotCheck)
					{
						InvenSlot[Index]->_bSlotCheck = true;
						InvenSlot[Index + iInvenCntX]->_bSlotCheck = true;
						return InvenSlot[Index];
					}
				}
			}
		}
	}
	return nullptr;
}

SLOTINFO* Examine::MouseExamine2X2(std::vector<SLOTINFO*> InvenSlot, POINT pt)
{
	int iInvenCntX = InvenSlot[0]->_iSlotCntX;
	int iInvenCntY = InvenSlot[0]->_iSlotCntY;
	int Index = 0;
	int MaxIndex = (iInvenCntX * iInvenCntY) - 1;

	for (int i = 0; i < iInvenCntY; ++i)
	{
		for (int j = 0; j < iInvenCntX; ++j)
		{
			Index = i * iInvenCntX + j;

			if (PtInRect(&InvenSlot[Index]->_tRect, pt))
			{
				if (MaxIndex >= Index && MaxIndex >= Index + 1 && MaxIndex >= Index + iInvenCntX && MaxIndex >= Index + iInvenCntX + 1)
				{
					if (!InvenSlot[Index]->_bSlotCheck
						&& !InvenSlot[Index + 1]->_bSlotCheck
						&& !InvenSlot[Index + iInvenCntX]->_bSlotCheck
						&& !InvenSlot[Index + iInvenCntX + 1]->_bSlotCheck)
					{
						InvenSlot[Index]->_bSlotCheck = true;
						InvenSlot[Index + 1]->_bSlotCheck = true;
						InvenSlot[Index + iInvenCntX]->_bSlotCheck = true;
						InvenSlot[Index + iInvenCntX + 1]->_bSlotCheck = true;
						return InvenSlot[Index];
					}
				}
			}
		}
	}

	return nullptr;
}

SLOTINFO* Examine::MouseExamine2X3(std::vector<SLOTINFO*> InvenSlot, POINT pt)
{
	int Index = 0;
	int iInvenCntX = InvenSlot[0]->_iSlotCntX;
	int iInvenCntY = InvenSlot[0]->_iSlotCntY;

	int MaxIndex = (iInvenCntX * iInvenCntY) - 1;
	for (int i = 0; i < iInvenCntY; ++i)
	{
		for (int j = 0; j < iInvenCntX; ++j)
		{
			Index = i * iInvenCntX + j;

			if (PtInRect(&InvenSlot[Index]->_tRect, pt))
			{
				if (MaxIndex >= Index && MaxIndex >= Index + 1 && MaxIndex >= Index + iInvenCntX && MaxIndex >= Index + iInvenCntX + 1
					&& MaxIndex >= Index + (iInvenCntX * 2) && MaxIndex >= Index + (iInvenCntX * 2) + 1)
				{
					if (!InvenSlot[Index]->_bSlotCheck
						&& !InvenSlot[Index + 1]->_bSlotCheck
						&& !InvenSlot[Index + iInvenCntX]->_bSlotCheck
						&& !InvenSlot[Index + iInvenCntX + 1]->_bSlotCheck
						&& !InvenSlot[Index + (iInvenCntX * 2)]->_bSlotCheck
						&& !InvenSlot[Index + (iInvenCntX * 2) + 1]->_bSlotCheck)
					{
						InvenSlot[Index]->_bSlotCheck = true;
						InvenSlot[Index + 1]->_bSlotCheck = true;
						InvenSlot[Index + iInvenCntX]->_bSlotCheck = true;
						InvenSlot[Index + iInvenCntX + 1]->_bSlotCheck = true;
						InvenSlot[Index + (iInvenCntX * 2)]->_bSlotCheck = true;
						InvenSlot[Index + (iInvenCntX * 2) + 1]->_bSlotCheck = true;
						return InvenSlot[Index];
					}
				}
				else
					return nullptr;
			}
		}
	}
	return nullptr;
}

bool Examine::EquipItem(std::vector<Slot*> _vecSlotGroup, SLOTINFO* _pItem)
{

	if (_vecSlotGroup[0]->GetSlot()[0]->_iFlag == _pItem->_iFlag && _vecSlotGroup[0]->GetSlot()[0]->_bSlotCheck == false)
	{
		return true;
	}
	return false;
}