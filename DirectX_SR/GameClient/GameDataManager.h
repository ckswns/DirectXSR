#pragma once
#include "SingletonBase.h"
#include "Actor.h"
#include "InfoBox.h"

class GameDataManager : public SingletonBase<GameDataManager>
{
private:	explicit					GameDataManager(void) noexcept { __noop; }
private:	virtual						~GameDataManager(void) noexcept { __noop; }

public:		bool						Init(void) noexcept;

private:	using						ACTOR_DATA_MAP = std::map<std::string, Actor::Data>;
private:	using						ITEM_DATA_MAP = std::map<std::string, ITEMDATA>;

public:		const Actor::Data&			GetActorData(std::string key) noexcept;
public:		const ITEMDATA&	GetItemData(std::string key) noexcept;

private:	ACTOR_DATA_MAP				_actorData;
private:	ITEM_DATA_MAP				_itemData;

private:	friend						SingletonBase<GameDataManager>;
};

