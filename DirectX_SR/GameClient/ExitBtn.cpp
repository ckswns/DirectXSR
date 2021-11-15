#include "pch.h"
#include "ExitBtn.h"
#include "Texture.h"
#include "Button.h"
#include "Image.h"

ExitBtn::ExitBtn(void) noexcept
{
	_texture = new Texture();
	_texture->Init(D3D9DEVICE->GetDevice(), "Asset\\UI\\close.png");
}

void ExitBtn::Start(void) noexcept
{
	gameObject->AddComponent(new UI::Image(_texture));
	UI::Button<ExitBtn>* btn = static_cast<UI::Button<ExitBtn>*>(gameObject->AddComponent(new UI::Button<ExitBtn>(this)));
	btn->onMouseUp += &ExitBtn::OnClickExit;

	gameObject->SetDontDestroy(true);
}

void ExitBtn::Update(float) noexcept
{
	
}

void ExitBtn::OnDestroy(void) noexcept
{
	delete _texture;
	_texture = nullptr;
}

void ExitBtn::OnClickExit(void) noexcept
{
	PostMessage(g_hWnd, WM_CLOSE, 0, 0);
}

void ExitBtn::OnMouseLeave(void) noexcept
{
	_onMouse = false;
}

void ExitBtn::OnMouseOver(void) noexcept
{
	_onMouse = true;
}
