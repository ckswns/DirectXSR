#include "pch.h"
#include "GameDataManager.h"

bool GameDataManager::Init(void) noexcept
{
	AssetManager::CONST_PTR_CSVDATA actorCSVData = ASSETMANAGER->GetCSVData("Asset\\Data\\MonsterData.csv");
	AssetManager::CONST_PTR_CSVDATA itemCSVData = ASSETMANAGER->GetCSVData("Asset\\Data\\ItemData.csv");

	for (int i = 1; i < (*actorCSVData).size(); i++)
	{
		int index = 0;

		std::string name = ((*actorCSVData)[i])[index++];

		Actor::Data temp;

		memcpy(&temp.name, name.c_str(), name.size() + 1);
		temp.damageMin		= std::stoi(((*actorCSVData)[i])[index++]);
		temp.damageMax		= std::stoi(((*actorCSVData)[i])[index++]);
		temp.maxHP			= std::stoi(((*actorCSVData)[i])[index++]);
		temp.moveSpeed		= std::stoi(((*actorCSVData)[i])[index++]);
		temp.aggroDistance	= std::stoi(((*actorCSVData)[i])[index++]);

		_actorData.insert(std::make_pair(name, temp));
	}

	for (int i = 1; i < (*itemCSVData).size(); i++)
	{
		int index = 0;

		std::string name = ((*itemCSVData)[i])[index++];

		InfoBox::ITEMDATA temp;

		memcpy(&temp.name, name.c_str(), name.size() + 1);
		temp.damagemin = std::stoi(((*itemCSVData)[i])[index++]);
		temp.damagemax = std::stoi(((*itemCSVData)[i])[index++]);
		temp.needlevel = std::stoi(((*itemCSVData)[i])[index++]);
		temp.defense = std::stoi(((*itemCSVData)[i])[index++]);
		temp.sellgold = std::stoi(((*itemCSVData)[i])[index++]);
		temp.buygold = std::stoi(((*itemCSVData)[i])[index++]);
		temp.ability = std::stoi(((*itemCSVData)[i])[index++]);

		_itemData.insert(std::make_pair(name, temp));
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

const InfoBox::ITEMDATA& GameDataManager::GetItemData(std::string key) noexcept
{
	auto iter = _itemData.find(key);

	if (iter == _itemData.end())
		CE_ASSERT("subin", "Key에 해당하는 값이 존재하지 않습니다");

	return iter->second;
}
