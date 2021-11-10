#pragma once
#include "Component.h"

namespace ce
{
	class Transform;

	namespace UI
	{
		class RectTransform final : public Component
		{
		public:		explicit			RectTransform(void) noexcept;
		public:		virtual				~RectTransform(void) noexcept { __noop; }

		public:		void				Init(void) noexcept override;
		public:		void				FixedUpdate(float) noexcept override { __noop; }
		public:		void				Update(float) noexcept override { __noop; }
		public:		void				LateUpdate(float) noexcept override { __noop; }
		public:		void				Render(void) noexcept override { __noop; }
		public:		void				Release(void) noexcept override { __noop; }

		public:		void				SetPivot(D3DXVECTOR2 v) noexcept { _pivot = v; }
		public:		void				SetWidth(float w) noexcept { _width = w; }
		public:		void				SetHeight(float h) noexcept { _height = h; }

		public:		D3DXVECTOR3			GetPivot(void) noexcept { return D3DXVECTOR3(_pivot.x, _pivot.y, 0); }
		public:		float				GetWidth(void) noexcept { return _width; }
		public:		float				GetHeight(void) noexcept { return _height; }
		public:		Transform*			GetTransform(void) const noexcept { return _transform;}

		private:	Transform*			_transform;
		private:	D3DXVECTOR2			_pivot;
		private:	float				_width;
		private:	float				_height;
		};
	}
}
