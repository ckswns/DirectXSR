#pragma once
#include "SingletonBase.h"

class GameDataManager : public SingletonBase<GameDataManager>
{
private:	explicit		GameDataManager(void) noexcept { __noop; }
private:	virtual			~GameDataManager(void) noexcept { __noop; }

private:	friend			SingletonBase<GameDataManager>;
};

