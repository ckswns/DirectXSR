#pragma once
#ifndef __GAME_ENUM_H__
#define __GAME_ENUM_H__

enum SKILL_ID		{ RAISE_SKELETON, BONE_SPEAR, POISON_NOVA, SKILL_END };
enum PLAYER_STATE	{ PLAYER_STAND, PLAYER_MOVE, PLAYER_ATTACK,PLAYER_SKILL, PLAYER_END };
enum SK_STATE		{ SK_CREATE, SK_STAND, SK_MOVE, SK_ATTACK, SK_DEAD, SK_END };
enum DIR			{ BACK, BACK_RIGHT, RIGHT, FRONT_RIGHT, FRONT, FRONT_LEFT, LEFT, BACK_LEFT,DIR_END };

enum ITEM_ID {HP,MP,EQUIP,ITEM_END};
namespace EQUIP_ID
{
	using ID = unsigned __int32;

//	static constexpr ID POSION = (1 << 0);
	static constexpr ID WAND = (1 << 1);
	static constexpr ID SHIELD = (1 << 2);
}

#endif // !__GAME_ENUM_H__

