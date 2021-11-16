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
private:	std::string		_strName;
private: 	D3DXVECTOR3		_vPos;		//바닥 좌표
private: 	UI::Image*		_ImgGround; //바닥에 있을때 이미지
private: 	UI::Image*		_ImgInven;
private: 	Coillder*		_Collier;
private: 	int				_iGold;
private: 	ITEM_ID::ID		_itemID;

};

