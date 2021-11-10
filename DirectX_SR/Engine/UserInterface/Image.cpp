#include "pch.h"
#include "Image.h"
#include "Texture.h"
#include "D3D9Device.h"
#include "Transform.h"
#include "RectTransform.h"
#include "GameObject.h"

namespace ce
{
	namespace UI
	{
		Image::Image(void) noexcept :
			Component(CONST_VALUES::COMPONENT_ID::IMAGE, true)
		{
			_sprite = D3D9Device::Instance()->GetSprite();
		}

		Image::Image(Texture* tex) noexcept :
			Component(CONST_VALUES::COMPONENT_ID::IMAGE, true)
		{
			_sprite = D3D9Device::Instance()->GetSprite();
			SetTexture(tex);
		}

		void Image::Init(void) noexcept
		{
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

				if (_material.GetMainTexture() != nullptr)
				{
					_rtTransform = static_cast<RectTransform*>(rt);
					_rtTransform->SetWidth(_material.GetMainTexture()->Width());
					_rtTransform->SetHeight(_material.GetMainTexture()->Height());
				}
			}

			_rtTransform = static_cast<RectTransform*>(rt);
			_transform = _rtTransform->GetTransform();

			_owner->SetLayer(GameObjectLayer::UI);
		}

		void Image::Render(void) noexcept
		{
			if (_material.GetMainTexture() == nullptr)
				return;

			D3DXVECTOR3 pivot = _rtTransform->GetPivot();
			pivot.x *= (_texWidth);// *(_rtTransform->GetWidth() / _texWidth));
			pivot.y *= (_texHeight);// *(_rtTransform->GetHeight() / _texHeight));
			pivot.z = 0;

			D3DXMATRIX scale;
			D3DXMATRIX world;

			float scaleX = _rtTransform->GetWidth() / _texWidth;
			float scaleY = _rtTransform->GetHeight() / _texHeight;

			D3DXMatrixScaling(&scale, scaleX, scaleY, 1);
			world = scale * _transform->GetWorldMatrix();

			_sprite->SetTransform(&world);
			_sprite->Draw((LPDIRECT3DTEXTURE9)_material.GetMainTexture()->GetTexturePTR(), &_srcRect, &pivot, NULL, _material.GetColor());
		}

		void Image::Release(void) noexcept
		{
			_sprite = nullptr;
		}

		void Image::SetTexture(Texture* tex) noexcept
		{
			_material.SetMainTexture(tex);

			if (tex == nullptr)
			{
				_texWidth = 0;
				_texHeight = 0;
				_srcRect = { 0, 0, 0, 0 };

				return;
			}

			_srcRect = { 0, 0, (long)(tex->Width() * _fillAmount), (long)tex->Height() };
			_texWidth = tex->Width();
			_texHeight = tex->Height();
		}

		void Image::SetFillAmount(float rhs) noexcept
		{
			_fillAmount = rhs;

			_srcRect.right = _texWidth * rhs;
		}
	}
}