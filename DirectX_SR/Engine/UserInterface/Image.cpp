#include "pch.h"
#include "Image.h"
#include "Texture.h"

namespace ce
{
	namespace UI
	{
		Image::Image(void) noexcept :
			Component(CONST_VALUES::COMPONENT_ID::IMAGE)
		{

		}

		void Image::Init(void) noexcept
		{

		}

		void Image::Update(float) noexcept
		{

		}

		void Image::Render(void) noexcept
		{

		}

		void Image::Release(void) noexcept
		{

		}

		void Image::SetTexture(Texture* tex) noexcept
		{
			_mainTex = tex;
		}
	}
}