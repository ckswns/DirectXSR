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

protected: 	D3DXVECTOR3		_vPos;		//바닥 좌표
protected: 	UI::Image*		_ImgGround; //바닥에 있을때 이미지
protected: 	Coillder*		_Collier;

protected:	std::string		_strName;
protected: 	int				_iGold;

protected: 	INVENITEMINFO	_tInvenItem;
};

