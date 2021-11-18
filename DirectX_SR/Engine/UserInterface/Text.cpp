#include "pch.h"
#include "Text.h"
#include "ManagerDef.h"
#include "Transform.h"
#include "RectTransform.h"
#include "GameObject.h"

namespace ce
{
	namespace UI
	{
		Text::Text(void) noexcept :
			Component(COMPONENT_ID::TEXT)
		{
			_pFont = D3D9DEVICE->GetFont();
			_pSprite = D3D9DEVICE->GetSprite();
		}

		Text::Text(const char* str, D3DXCOLOR c, DWORD alignFormat) noexcept :
			Component(COMPONENT_ID::TEXT),
			_str(str),
			_color(c),
			_align(alignFormat)
		{
			_pFont = D3D9DEVICE->GetFont();
			_pSprite = D3D9DEVICE->GetSprite();
		}

		void Text::Init(void) noexcept
		{
			if (_owner->HasComponent(COMPONENT_ID::IMAGE))
				CE_ASSERT("ckswns", "Text Component는 Image Component와 같은 게임오브젝트에 존재할 수 없습니다");

			if (_owner == nullptr)
				CE_ASSERT("ckswns", "GameObject에 소속되지 않은 상태에서의 Init호출입니다");

			if (_owner->HasComponent(COMPONENT_ID::RENDERER))
			{
				CE_ASSERT("ckswns", "UI객체는 다른 Renderer를 가질 수 없습니다!");
			}

			Component* rt = _owner->GetComponent(COMPONENT_ID::RECT_TRANSFORM);

			if (rt == nullptr)
			{
				rt = _owner->AddComponent(new RectTransform());
			}

			_rectTransform = static_cast<RectTransform*>(rt);
			_transform = _owner->GetTransform();

			if (_owner->GetLayer() != GameObjectLayer::UI)
				_owner->SetLayer(GameObjectLayer::UI);
		}

		void Text::FixedUpdate(float) noexcept
		{

		}

		void Text::Update(float) noexcept
		{

		}

		void Text::LateUpdate(float) noexcept
		{

		}

		void Text::Render(void) noexcept
		{
			_pSprite->SetTransform(&_transform->GetWorldMatrix());
			RECT rt = _rectTransform->GetPickingRect();

			rt.right -= rt.left;
			rt.bottom -= rt.top;
			rt.top = 0;
			rt.left = 0;

			if (_align == 0)
				_pFont->DrawTextA(_pSprite, _str.c_str(), _str.size(), nullptr, 0, _color);
			else
				_pFont->DrawTextA(_pSprite, _str.c_str(), _str.size(), &rt, _align, _color);
		}

		void Text::Release(void) noexcept
		{
			_pSprite = nullptr;
			_pFont = nullptr;
		}
	}
}