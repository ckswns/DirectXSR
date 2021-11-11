#pragma once
#ifndef __GAME_STRUCT_H__
#define __GAME_STRUCT_H__

typedef struct tagStat
{
	tagStat(float fMaxHp, int iMaxMp, float fMaxStamina)
	{
		_fMaxHp = fMaxHp;
		_iMaxMp = iMaxMp;
		_fMaxStamina = fMaxStamina;

		_fHp = _fMaxHp;
		_iMP = _iMaxMp;
		_fStamina = _fMaxStamina;

		_iStr = 15;
		_iDex = 25;
		_iVitality = 15;
		_iEnergy = 25;
	}

	float		_fMaxHp;
	int			_iMaxMp;
	float		_fMaxStamina;

	float		_fHp;
	int			_iMP;
	float		_fStamina;

	int			_iStr;
	int			_iDex;
	int			_iVitality;
	int			_iEnergy;

	float		_fDamage = _iStr * 0.01f;
	float		_fAttRating = _iDex * 5.f;
	float		_fDef = _iDex * 0.25f;

}STAT;

#endif // !__GAME_STRUCT_H__

