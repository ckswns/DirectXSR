#include "Button.h"

namespace ce
{
	namespace UI
	{
		template<typename T>
		inline Button<T>::Button(T* listener) noexcept :
			Component(COMPONENT_ID::BUTTON, true, true, COMPONENT_ID::IMAGE),
			_colorNormal(D3DCOLOR_ARGB(255, 255, 255, 255)),
			_colorHilighted(D3DCOLOR_ARGB(255, 255, 255, 255)),
			_colorPressed(D3DCOLOR_ARGB(255, 200, 200, 200)),
			_colorDisabled(D3DCOLOR_ARGB(128, 200, 200, 200)),
			_textureNormal(nullptr),
			_textureHilighted(nullptr),
			_texturePressed(nullptr),
			_textureDisabled(nullptr),
			_pListener(listener)
		{
		}

		template<typename T>
		inline void Button<T>::Init(void) noexcept
		{
			if (_owner->HasComponent(COMPONENT_ID::IMAGE) == false && _owner->HasComponent(COMPONENT_ID::TEXT) == false)
				CE_ASSERT("ckswns", "Button은 Image Comonent 혹은 Text Component 가 있어야 동작할 수 있습니다");

			if (_owner->GetLayer() != GameObjectLayer::UI)
				_owner->SetLayer(GameObjectLayer::UI);

			_material = static_cast<Image*>(_owner->GetComponent(COMPONENT_ID::IMAGE))->GetMaterialPTR();
			_rectTransform = static_cast<RectTransform*>(_owner->GetComponent(COMPONENT_ID::RECT_TRANSFORM));
			_rectTransform->SetInteractive(_bInteractable);
		}

		template<typename T>
		inline void Button<T>::OnMouseEnter(void) noexcept
		{
			if (_translation == ButtonTranslation::COLOR_TINT)
				_material->SetColor(_colorHilighted);
			else if (_textureHilighted)
				_material->SetMainTexture(_textureHilighted);
			onMouseEnter.Notify(_pListener);
		}

		template<typename T>
		inline void Button<T>::OnMouseLeave(void) noexcept
		{
			if (_translation == ButtonTranslation::COLOR_TINT)
				_material->SetColor(_colorNormal);
			else if (_textureNormal)
				_material->SetMainTexture(_textureNormal);
			onMouseLeave.Notify(_pListener);
		}

		template<typename T>
		inline void Button<T>::OnMouseOver(void) noexcept
		{
			if (_translation == ButtonTranslation::COLOR_TINT)
				_material->SetColor(_colorHilighted);
			else if (_textureHilighted)
				_material->SetMainTexture(_textureHilighted);
			onMouseOver.Notify(_pListener);
		}

		template<typename T>
		inline void Button<T>::OnMouseDown(void) noexcept
		{
			if (_translation == ButtonTranslation::COLOR_TINT)
				_material->SetColor(_colorPressed);
			else if (_texturePressed)
				_material->SetMainTexture(_texturePressed);
			onMouseDown.Notify(_pListener);
		}

		template<typename T>
		inline void Button<T>::OnMouseUp(void) noexcept
		{
			if (_translation == ButtonTranslation::COLOR_TINT)
				_material->SetColor(_colorNormal);
			else if (_textureNormal)
				_material->SetMainTexture(_textureNormal);
			onMouseUp.Notify(_pListener);
		}

		template<typename T>
		inline void Button<T>::OnMouseHeldDown(void) noexcept
		{
			if (_translation == ButtonTranslation::COLOR_TINT)
				_material->SetColor(_colorPressed);
			else if (_texturePressed)
				_material->SetMainTexture(_texturePressed);
			onMouseHeldDown.Notify(_pListener);
		}

		template<typename T>
		inline void Button<T>::SetInteractable(bool able) noexcept
		{
			_bInteractable = able;

			if (_bInteractable == false)
			{
				if (_translation == ButtonTranslation::COLOR_TINT)
					_material->SetColor(_colorDisabled);
				else if (_textureDisabled)
					_material->SetMainTexture(_textureDisabled);
			}
			else
			{
				if (_translation == ButtonTranslation::COLOR_TINT)
					_material->SetColor(_colorNormal);
				else if (_textureNormal)
					_material->SetMainTexture(_textureNormal);
			}

			_rectTransform->SetInteractive(_bInteractable);
		}

		template<typename T>
		inline void Button<T>::SetColor(D3DXCOLOR normal, D3DXCOLOR highlited, D3DXCOLOR pressed, D3DXCOLOR disabled) noexcept
		{
			_colorNormal = normal;
			_colorHilighted = highlited;
			_colorPressed = pressed;
			_colorDisabled = disabled;
		}

		template<typename T>
		inline void Button<T>::SetTexture(Texture* normal, Texture* highlited, Texture* pressed, Texture* disabled) noexcept
		{
			_textureNormal = normal;
			_textureHilighted = highlited;
			_texturePressed = pressed;
			_textureDisabled = disabled;
		}
	}
}