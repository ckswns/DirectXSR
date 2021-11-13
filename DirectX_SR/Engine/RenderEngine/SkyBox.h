#pragma once

namespace ce
{
	class Cube;

	class SkyBox
	{
	public:		explicit	SkyBox(void) noexcept;
	public:		virtual		~SkyBox(void) noexcept { __noop; }
	
	private:	Cube*		_cube;
	};
}
