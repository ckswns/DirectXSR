#include "pch.h"
#include "GameDataManager.h"

bool GameDataManager::Init(void) noexcept
{
	AssetManager::CONST_PTR_CSVDATA actorCSVData = ASSETMANAGER->GetCSVData("Asset\\Data\\MonsterData.csv");
	AssetManager::CONST_PTR_CSVDATA itemCSVData = ASSETMANAGER->GetCSVData("Asset\\Data\\ItemData.csv");
//	AssetManager::CONST_PTR_CSVDATA storeCSVData = ASSETMANAGER->GetCSVData("Asset\\Data\\StoreData.csv");

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

		ITEMDATA temp;

		memcpy(&temp.name, name.c_str(), name.size() + 1);
		temp.itype = std::stoi(((*itemCSVData)[i])[index++]);
		temp.damagemin = std::stoi(((*itemCSVData)[i])[index++]);
		temp.damagemax = std::stoi(((*itemCSVData)[i])[index++]);
		temp.needlevel = std::stoi(((*itemCSVData)[i])[index++]);
		temp.defense = std::stoi(((*itemCSVData)[i])[index++]);
		temp.sellgold = std::stoi(((*itemCSVData)[i])[index++]);
		temp.buygold = std::stoi(((*itemCSVData)[i])[index++]);
		temp.ability = std::stoi(((*itemCSVData)[i])[index++]);

		std::string path = ((*itemCSVData)[i])[index++];
		memcpy(&temp.imgPath, path.c_str(), path.size() + 1);

		_itemData.insert(std::make_pair(name, temp));
	}

	//for (int i = 1; i < (*storeCSVData).size(); i++)
	//{
	//	int index = 0;

	//	std::string name = ((*storeCSVData)[i])[index++];

	//	INVENITEMINFO temp;

	//	temp._strName = name;
	//	//memcpy(&temp._strName, name.c_str(), name.size() + 1);
	//	temp._eitemID = std::stoi(((*storeCSVData)[i])[index++]);
	//	temp._eSlotType = std::stoi(((*storeCSVData)[i])[index++]);
	//	temp._iValue = std::stoi(((*storeCSVData)[i])[index++]);
	//	temp._iGold = std::stoi(((*storeCSVData)[i])[index++]);

	//	_storeData.insert(std::make_pair(name, temp));
	//}

	return true;
}

const Actor::Data& GameDataManager::GetActorData(std::string key) noexcept
{
	auto iter = _actorData.find(key);

	if (iter == _actorData.end())
		CE_ASSERT("ckswns", "Key에 해당하는 값이 존재하지 않습니다");
	
	return iter->second;
}

const ITEMDATA& GameDataManager::GetItemData(std::string key) noexcept
{
	auto iter = _itemData.find(key);

	if (iter == _itemData.end())
		CE_ASSERT("subin", "Key에 해당하는 값이 존재하지 않습니다");

	return iter->second;
}

//const INVENITEMINFO& GameDataManager::GetStoreData(std::string key) noexcept
//{
//	auto iter = _storeData.find(key);
//
//	if (iter == _storeData.end())
//		CE_ASSERT("ckswns", "Key에 해당하는 값이 존재하지 않습니다");
//
//	return iter->second;
//}
