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

		_fDamage = _iStr * 0.5f;
		_fAttRating = _iDex * 5.f;
		_fDef = _iDex * 0.25f;
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

	float		_fDamage = _iStr * 0.5f;//0.01f;
	float		_fAttRating = _iDex * 5.f;
	float		_fDef = _iDex * 0.25f;

	void		Recovery(float fAmount)
	{
		/*if (_fHp < _fMaxHp)
		{
			_fHp += fAmount;
		
			if (_fHp > _fMaxHp)
				_fHp = _fMaxHp;
		}*/
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

struct ITEMDATA
{
	char	name[128];
	int		itype;
	int		damagemin;
	int		damagemax;
	int		needlevel;
	int		defense;
	int		sellgold;
	int		buygold;
	int		ability;
	char	imgPath[128];
};

typedef struct tagSlot
{
	D3DXVECTOR3 _vPos;
	RECT		_tRect;
	int			_iSlotSizeX;
	int			_iSlotSizeY;
	int			_iFlag;
	int			_iIndex;
	bool		_bSlotCheck;
	int			_iSlotCntX;
	int			_iSlotCntY;
	tagSlot()
	{
		_bSlotCheck = false;
		_iSlotSizeX = 46;
		_iSlotSizeY = 32;
	}

}SLOTINFO;

#endif // !__GAME_STRUCT_H__

