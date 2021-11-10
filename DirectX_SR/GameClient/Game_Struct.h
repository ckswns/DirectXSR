#pragma once
#ifndef __GAME_STRUCT_H__
#define __GAME_STRUCT_H__

typedef struct tagStat
{
	int _iHp;
	int _iMP;
	int _fStamina;

	int _iStr;
	int _iDex;
	int _iVitality;
	int _iEnergy;

	float _fDamage = _iStr * 0.01f;
	float _fAttRating = _iDex * 5.f;
	float _fDef = _iDex * 0.25f;

}STAT;

#endif // !__GAME_STRUCT_H__

