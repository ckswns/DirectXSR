#include "pch.h"
#include "TopBar.h"
#include "Transform.h"
#include "Image.h"
#include "Button.h"
#include "ExitBtn.h"

TopBar::TopBar(HWND hWnd) noexcept :
	_hWnd(hWnd)
{
	_texture = new Texture();
	_texture->Init(D3D9DEVICE->GetDevice(), "Asset\\UI\\top_bar.png");
}

void TopBar::Start(void) noexcept
{
	_img = new UI::Image(_texture);
	gameObject->AddComponent(_img);
	_img->SetFillAmount(0);

	gameObject->SetSortOrder(9998);
	gameObject->SetDontDestroy(true);

	GameObject* obj = GameObject::Instantiate();
	_exitBtn = new ExitBtn();
	obj->AddComponent(_exitBtn);
	obj->GetTransform()->SetParent(transform);
	obj->GetTransform()->SetLocalPosition(1262, 3, 0);
	obj->SetActive(false);
	obj->SetSortOrder(9999);
}

void TopBar::Update(float) noexcept
{
	if (_bDrag == true)
	{
		POINT cursor;

		GetCursorPos(&cursor);

		MoveWindow(_hWnd, cursor.x - _clientPos.x, cursor.y - _clientPos.y,
			WINCX, WINCY, TRUE);

		//SetWindowPos(g_hWND, NULL, m_clientPos.x + cursor.x, m_clientPos.y + cursor.y, 0, 0,
		//	SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);

		if (INPUT->GetKeyUp(VK_LBUTTON))
			_bDrag = false;
	}
}

void TopBar::OnDestroy(void) noexcept
{
	delete _texture;
	_texture = nullptr;
}

void TopBar::OnMouseEnter(void) noexcept
{

}

void TopBar::OnMouseLeave(void) noexcept
{
	if (_exitBtn->GetIsOnMouse() == true)
		return;

	_img->SetFillAmount(0);
	_exitBtn->GetGameObject()->SetActive(false);
}

void TopBar::OnMouseOver(void) noexcept
{
	_img->SetFillAmount(1);
	_exitBtn->GetGameObject()->SetActive(true);
}

void TopBar::OnMouseDown(void) noexcept
{
	GetCursorPos(&_prevMousePos);

	RECT rt;
	GetWindowRect(_hWnd, &rt);

	_clientPos.x = _prevMousePos.x - rt.left;
	_clientPos.y = _prevMousePos.y - rt.top;

	_bDrag = true;
}

void TopBar::OnMouseUp(void) noexcept
{

}

void TopBar::OnMouseHeldDown(void) noexcept
{

}
