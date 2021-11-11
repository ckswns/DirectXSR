#pragma once
#include "Component.h"
#include "Assertion.h"
#include "Material.h"
#include "Image.h"

namespace ce
{
	//class Material;

	namespace UI 
	{
		enum class ButtonTranslation
		{
			COLOR_TINT,
			TEXTURE_SWAP
		};

		template <typename T>
		class Button : public Component
		{
		public:		class Event
					{
					public:		explicit Event() noexcept { __noop; }
					public:				~Event() noexcept { __noop; }

					public:		void operator+=(std::function<void(T&)> _fp)
								{
									_callbacks.emplace_back(_fp);
								}

					private:	void Notify(T* listener)
								{
									for (int i = 0; i < _callbacks.size(); i++)
									{
										_callbacks[i](*listener);
									}
								}

					private:	std::vector<std::function<void(T&)>> _callbacks;
					private:	friend Button<T>;
					};

		public:		explicit			Button(T* listener) noexcept;
		public:		virtual				~Button(void) noexcept { __noop; }

		public:		void				Init(void) noexcept override;
		public:		void				FixedUpdate(float) noexcept override { __noop; }
		public:		void				Update(float) noexcept override { __noop; }
		public:		void				LateUpdate(float) noexcept override { __noop; }
		public:		void				Render(void) noexcept override { __noop; }
		public:		void				Release(void) noexcept override { __noop; }

		public:		void				OnMouseEnter(void) noexcept override;
		public:		void				OnMouseLeave(void) noexcept override;
		public:		void				OnMouseOver(void) noexcept override;
		public:		void				OnMouseDown(void) noexcept override;
		public:		void				OnMouseUp(void) noexcept override;
		public:		void				OnMouseHeldDown(void) noexcept override;

		public:		void				SetInteractable(bool able) noexcept;
		public:		void				SetTranslation(ButtonTranslation t) noexcept { _translation = t; }

		public:		void				SetNormalColor(D3DXCOLOR c) noexcept { _colorNormal = c; }
		public:		void				SetHilightedlColor(D3DXCOLOR c) noexcept { _colorNormal = c; }
		public:		void				SetPressedColor(D3DXCOLOR c) noexcept { _colorNormal = c; }
		public:		void				SetDisabledColor(D3DXCOLOR c) noexcept { _colorNormal = c; }
		public:		void				SetColor(D3DXCOLOR normal, D3DXCOLOR highlited, D3DXCOLOR pressed, D3DXCOLOR disabled) noexcept;

		public:		void				SetNormalTexture(Texture* tex) noexcept { _textureNormal = tex; }
		public:		void				SetHilightedlTexture(Texture* tex) noexcept { _textureHilighted = tex; }
		public:		void				SetPressedTexture(Texture* tex) noexcept { _texturePressed = tex; }
		public:		void				SetDisabledTexture(Texture* tex) noexcept { _textureDisabled = tex; }
		public:		void				SetTexture(Texture* normal, Texture* highlited, Texture* pressed, Texture* disabled) noexcept;

		private:	bool				_bInteractable = true;

		public:		Event				onMouseEnter;
		public:		Event				onMouseOver;
		public:		Event				onMouseLeave;
		public:		Event				onMouseDown;
		public:		Event				onMouseHeldDown;
		public:		Event				onMouseUp;

		private:	D3DXCOLOR			_colorNormal;
		private:	D3DXCOLOR			_colorHilighted;
		private:	D3DXCOLOR			_colorPressed;
		private:	D3DXCOLOR			_colorDisabled;

		private:	Texture*			_textureNormal;
		private:	Texture*			_textureHilighted;
		private:	Texture*			_texturePressed;
		private:	Texture*			_textureDisabled;

		private:	T*					_pListener;
		private:	Material*			_material;
		private:	ButtonTranslation	_translation;
		private:	RectTransform*		_rectTransform;
		};
	}
}
#include "Button.hpp"