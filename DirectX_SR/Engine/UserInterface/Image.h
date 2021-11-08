#pragma once
#include "Component.h"

namespace ce
{
	class Texture;

	namespace UI
	{
		class Image : public Component
		{
		public:		explicit		Image(void) noexcept;
		public:		virtual			~Image(void) noexcept { __noop; }

		public:		void			Init(void) noexcept override;
		public:		void			Update(float) noexcept override;
		public:		void			Render(void) noexcept override;
		public:		void			Release(void) noexcept override;

		public:		void			SetTexture(Texture* tex) noexcept;

		private:	LPD3DXSPRITE	_sprite = nullptr;
		private:	Texture*		_mainTex = nullptr;
		private:	D3DXCOLOR		_color = D3DCOLOR_ARGB(255, 255, 255, 255);
		};
	}
}
