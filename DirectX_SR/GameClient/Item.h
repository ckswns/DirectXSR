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
private: 	D3DXVECTOR3		_vPos;		//�ٴ� ��ǥ
private: 	UI::Image*		_ImgGround; //�ٴڿ� ������ �̹���
private: 	UI::Image*		_ImgInven;
private: 	Coillder*		_Collier;
private: 	int				_iGold;
private: 	ITEM_ID::ID		_itemID;

};

