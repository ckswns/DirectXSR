#pragma once
#include "../Base/GameObject.h"

namespace ce
{
	class Terrain : public GameObject
	{
	public:		explicit				Terrain(uint16 width, uint16 height) noexcept;
	public:		virtual					~Terrain(void) noexcept;

	public:		bool					Init(void) noexcept override;
	public:		void					FixedUpdate(float fElapsedTime) noexcept override;
	public:		void					Update(float fElapsedTime) noexcept override;
	public:		void					LateUpdate(float fElapsedTime) noexcept override;
	public:		void					Render(void) noexcept override;
	public:		void					Release(void) noexcept override;

	private:	uint16					_height;
	private:	uint16					_width;
	};
}
