#pragma once
#include "Component.h"

namespace ce
{
	class Texture;
	class Component;

	namespace UI
	{
		class RectTransform;

		class Image : public Component
		{
		public:		explicit				Image(void) noexcept;
		public:		explicit				Image(Texture* tex) noexcept;
		public:		virtual					~Image(void) noexcept { __noop; }

		public:		void					Init(void) noexcept override;
		public:		void					Update(float) noexcept override;
		public:		void					Render(void) noexcept override;
		public:		void					Release(void) noexcept override;

		public:		const Texture* const	GetTexture(void) const noexcept { return _mainTex; }
		public:		D3DXCOLOR				GetColor(void) const noexcept { return _color; }
		public:		float					GetFillAmount(void) const noexcept { return _fillAmount; }

		public:		void					SetTexture(Texture* tex) noexcept;
		public:		void					SetColor(D3DXCOLOR c) noexcept { c = _color; }
		public:		void					SetFillAmount(float rhs) noexcept;

		private:	uint32					_texWidth;
		private:	uint32					_texHeight;

		private:	Texture*				_mainTex = nullptr;
		private:	D3DXCOLOR				_color = D3DCOLOR_ARGB(255, 255, 255, 255);

		private:	LPD3DXSPRITE			_sprite = nullptr;
		private:	RectTransform*			_rtTransform = nullptr;
		private:	Transform*				_transform = nullptr;
		private:	RECT					_srcRect = { 0, 0, 0, 0 };

		private:	float					_fillAmount = 1;
		};
	}
}

