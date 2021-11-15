#pragma once
#include "SingletonBase.h"
#include "Actor.h"

class GameDataManager : public SingletonBase<GameDataManager>
{
private:	explicit			GameDataManager(void) noexcept { __noop; }
private:	virtual				~GameDataManager(void) noexcept { __noop; }

public:		bool				Init(void) noexcept;

private:	using				ACTOR_DATA_MAP = std::map<std::string, Actor::Data>;

public:		const Actor::Data&	GetActorData(std::string key) noexcept;

private:	ACTOR_DATA_MAP		_actorData;
private:	friend				SingletonBase<GameDataManager>;
};

