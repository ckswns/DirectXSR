#pragma once

namespace ce
{
	namespace UI 
	{
		class Image;
	}
	class Coillder;
}
class Item 
{
public:		virtual INVENITEMINFO* GetItem() = 0;

protected: 	D3DXVECTOR3		_vPos;		//�ٴ� ��ǥ
protected: 	UI::Image*		_ImgGround; //�ٴڿ� ������ �̹���
protected: 	Coillder*		_Collier;

protected:	std::string		_strName;
protected: 	int				_iGold;

protected: 	INVENITEMINFO	_tInvenItem;
};

