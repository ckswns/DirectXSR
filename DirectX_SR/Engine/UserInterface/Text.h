#pragma once
#include "Component.h"

namespace ce
{
	class Transform;
	namespace UI
	{
		class RectTransform;

		class Text : public Component
		{
		public:		explicit		Text(void) noexcept;
		public:		explicit		Text(const char* str, D3DXCOLOR c = D3DCOLOR_ARGB(255, 50, 50, 50), DWORD alignFormat = 0) noexcept;
		public:		virtual			~Text(void) noexcept { __noop; }

		public:		void			Init(void) noexcept override;
		public:		void			FixedUpdate(float) noexcept override;
		public:		void			Update(float) noexcept override;
		public:		void			LateUpdate(float) noexcept override;
		public:		void			Render(void) noexcept override;
		public:		void			Release(void) noexcept override;

		public:		void			SetText(const char* str) noexcept { _str = str; }

		private:	D3DXCOLOR		_color = D3DCOLOR_ARGB(255, 50, 50, 50);
		private:	LPD3DXFONT		_pFont;
		private:	LPD3DXSPRITE	_pSprite;

		private:	DWORD			_align;
		private:	std::string		_str;

		private:	Transform*		_transform;
		private:	RectTransform*	_rectTransform;
		};
	}
}

