#pragma once

class Examine
{
public: Examine() noexcept;
public: ~Examine()	noexcept { __noop; }

public: SLOTINFO* EatingExamine1X1(std::vector<SLOTINFO*> InvenSlot);
public: SLOTINFO* EatingExamine1X3(std::vector<SLOTINFO*> InvenSlot);
public: SLOTINFO* EatingExamine2X1(std::vector<SLOTINFO*> InvenSlot);
public: SLOTINFO* EatingExamine2X2(std::vector<SLOTINFO*> InvenSlot);
public: SLOTINFO* EatingExamine2X3(std::vector<SLOTINFO*> InvenSlot);

public: SLOTINFO* MouseExamine1X1(std::vector<SLOTINFO*> InvenSlot, POINT pt);
public: SLOTINFO* MouseExamine1X3(std::vector<SLOTINFO*> InvenSlot, POINT pt);
public: SLOTINFO* MouseExamine2X1(std::vector<SLOTINFO*> InvenSlot, POINT pt);
public: SLOTINFO* MouseExamine2X2(std::vector<SLOTINFO*> InvenSlot, POINT pt);
public: SLOTINFO* MouseExamine2X3(std::vector<SLOTINFO*> InvenSlot, POINT pt);
};

