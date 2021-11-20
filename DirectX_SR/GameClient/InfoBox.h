#pragma once
#include "Behaviour.h"
#include "Slot.h"
namespace ce
{
	namespace UI
	{
		class Text;
	}
}


class InfoBox : public Behaviour
{
public: explicit InfoBox(Slot::SLOTTYPE eType);
public: virtual ~InfoBox();

public: struct ITEMDATA
{
	char	name[128];
	int		type;
	int		damagemin;
	int		damagemax;
	int		needlevel;
	int		defense;
	int		sellgold;
	int		buygold;
	int		ability;
};
public:	virtual void	Awake(void) noexcept override;
public: virtual void	Start(void) noexcept override;
public: virtual void	Update(float) noexcept override;

public: void			SetPosition(float x, float y);
public: void			ShowInfoBox(bool Check) { gameObject->SetActive(Check); }
public: void			MissingItem();

private: ITEMDATA			_data;
private: UI::Text*			_pText;
private: UI::Text*			_pTex[9];
private: Transform*			_pPare;
private: Slot::SLOTTYPE		_eType;

};

