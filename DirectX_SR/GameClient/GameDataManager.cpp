#include "pch.h"
#include "GameDataManager.h"

bool GameDataManager::Init(void) noexcept
{
	AssetManager::CONST_PTR_CSVDATA actorCSVData = ASSETMANAGER->GetCSVData("Asset\\Data\\MonsterData.csv");

	for (int i = 1; i < (*actorCSVData).size(); i++)
	{
		int index = 0;

		std::string name = ((*actorCSVData)[i])[index++];

		Actor::Data temp;

		temp.damageMin		= std::stoi(((*actorCSVData)[i])[index++]);
		temp.damageMax		= std::stoi(((*actorCSVData)[i])[index++]);
		temp.maxHP			= std::stoi(((*actorCSVData)[i])[index++]);
		temp.moveSpeed		= std::stoi(((*actorCSVData)[i])[index++]);
		temp.aggroDistance	= std::stoi(((*actorCSVData)[i])[index++]);

		_actorData.insert(std::make_pair(name, temp));
	}

	return true;
}

const Actor::Data& GameDataManager::GetActorData(std::string key) noexcept
{
	auto iter = _actorData.find(key);

	if (iter == _actorData.end())
		CE_ASSERT("ckswns", "Key에 해당하는 값이 존재하지 않습니다");

	return iter->second;
}
