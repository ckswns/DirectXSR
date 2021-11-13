#pragma once
#ifndef __GAME_STRUCT_H__
#define __GAME_STRUCT_H__

typedef struct tagStat
{
	tagStat(float fMaxHp, float fMaxMp, float fMaxStamina)
	{
		_fMaxHp = fMaxHp;
		_fMaxMp = fMaxMp;
		_fMaxStamina = fMaxStamina;

		_fHp = _fMaxHp;
		_fMP = _fMaxMp;
		_fStamina = _fMaxStamina;

		_iStr = 15;
		_iDex = 25;
		_iVitality = 15;
		_iEnergy = 25;
	}

	float		_fMaxHp;
	float		_fMaxMp;
	float		_fMaxStamina;

	float		_fHp;
	float		_fMP;
	float		_fStamina;

	int			_iStr;
	int			_iDex;
	int			_iVitality;
	int			_iEnergy;

	float		_fDamage = _iStr * 0.01f;
	float		_fAttRating = _iDex * 5.f;
	float		_fDef = _iDex * 0.25f;

	void		Recovery(float fAmount)
	{
		if (_fHp < _fMaxHp)
		{
			_fHp += fAmount;
		
			if (_fHp > _fMaxHp)
				_fHp = _fMaxHp;
		}
		if (_fMP < _fMaxMp) 
		{
			_fMP += fAmount;

			if (_fMP > _fMaxMp)
				_fMP = _fMaxMp;
		}
		if (_fStamina < _fMaxStamina) 
		{
			_fStamina += fAmount;

			if (_fStamina > _fMaxStamina)
				_fStamina = _fMaxStamina;
		}
	}

}STAT;

#endif // !__GAME_STRUCT_H__

