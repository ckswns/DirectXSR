#pragma once
#include "Component.h"
#include "Material.h"

namespace ce
{
	class Texture;
	class Component;

	namespace UI
	{
		class RectTransform;

		class Image : public Component
		{
		public:		enum class FillType
					{
						VERTICAL,
						HORIZONTAL
					};

		public:		explicit				Image(void) noexcept;
		public:		explicit				Image(Texture* tex) noexcept;
		public:		virtual					~Image(void) noexcept { __noop; }

		public:		void					Init(void) noexcept override;
		public:		void					FixedUpdate(float) noexcept override { __noop; }
		public:		void					Update(float) noexcept override { __noop; }
		public:		void					LateUpdate(float) noexcept override { __noop; }
		public:		void					Render(void) noexcept override;
		public:		void					Release(void) noexcept override;

		public:		const Texture* const	GetTexture(void) const noexcept { return _material.GetMainTexture(); }
		public:		D3DXCOLOR				GetColor(void) const noexcept { return _material.GetColor(); }
		public:		float					GetFillAmount(void) const noexcept { return _fillAmount; }

		public:		void					SetTexture(Texture* tex) noexcept;
		public:		void					SetColor(D3DXCOLOR c) noexcept { _material.SetColor(c); }
		public:		void					SetFillAmount(float rhs) noexcept;
		public:		Material*				GetMaterialPTR(void) noexcept { return &_material; }

		public:		void					SetFillType(FillType type) noexcept { _fillType = type; }

		private:	uint32					_texWidth;
		private:	uint32					_texHeight;

		private:	Material				_material;

		private:	LPD3DXSPRITE			_sprite = nullptr;
		private:	RectTransform*			_rtTransform = nullptr;
		private:	Transform*				_transform = nullptr;
		private:	RECT					_srcRect = { 0, 0, 0, 0 };

		private:	FillType				_fillType = FillType::HORIZONTAL;

		private:	float					_fillAmount = 1;
		};
	}
}

