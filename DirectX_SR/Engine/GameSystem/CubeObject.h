#pragma once
#include "Behaviour.h"

namespace ce
{
	class Texture;

	class CubeObject final : public Behaviour
	{
	public:		explicit		CubeObject(D3DCOLORVALUE color = {1, 1, 1, 1}, float scaleFactor = 1) noexcept;
	public:		explicit		CubeObject(Texture* texure, D3DCOLORVALUE color = { 1, 1, 1, 1 }, float scaleFactor = 1) noexcept;
	public:		virtual			~CubeObject(void) noexcept;

	public:		void			Start(void) noexcept override;
	public:		void			Update(float fElapsedTime) noexcept override;

	private:	float			_scaleFactor;
	private:	Texture*		_texture;
	private:	D3DCOLORVALUE	_color;
	};
}
