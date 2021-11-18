#pragma once
#include "NPC.h"

class StoreWnd;
class StoreNPC : public NPC
{
public:		explicit				StoreNPC() noexcept { __noop; }
public:		virtual					~StoreNPC(void) noexcept { __noop; }

public:		virtual void			Start(void) noexcept;
public:		virtual void			Update(float fElapsedTime) noexcept { __noop; }

public:		virtual void			OnClick(Player* player);

private:	StoreWnd*				_pStoreWnd;
//private:	GameObject*				_pStoreWndObj;
};

