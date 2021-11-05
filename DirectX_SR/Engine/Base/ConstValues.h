#pragma once

#ifndef __CONSTANT_VALUES_H__
#define __CONSTANT_VALUES_H__

namespace ce
{
	namespace CONST_VALUES
	{
		namespace COMPONENT_ID
		{
			using ID = unsigned short;

			static constexpr ID TRANSFORM		= (1 << 0);
			static constexpr ID ANIMATOR		= (1 << 1);
			static constexpr ID RENDERER		= (1 << 2);
			static constexpr ID PHYSICS2D		= (1 << 3);
			static constexpr ID COLLIDER2D		= (1 << 4);
			static constexpr ID RIGIDBODY2D		= (1 << 5);
			static constexpr ID CAMERA			= (1 << 6);
			static constexpr ID AUDIOSOURCE		= (1 << 7);
			static constexpr ID AUDIOLISTENER	= (1 << 8);
			static constexpr ID LIGHT			= (1 << 9);
			static constexpr ID BEHAVIOUR		= (1 << 10);
		}

		namespace KEY_CODES
		{
			using KEY_CODE = __int64;

			static constexpr KEY_CODE KEY_LBUTTON = 1 << 0;
			static constexpr KEY_CODE KEY_RBUTTON = 1 << 1;
			static constexpr KEY_CODE KEY_RETURN = 1 << 2;
			static constexpr KEY_CODE KEY_LEFT = 1 << 3;
			static constexpr KEY_CODE KEY_RIGHT = 1 << 4;
			static constexpr KEY_CODE KEY_UP = 1 << 5;
			static constexpr KEY_CODE KEY_DOWN = 1 << 6;

			static constexpr KEY_CODE KEY_Z = 1 << 7;
			static constexpr KEY_CODE KEY_X = 1 << 8;
			static constexpr KEY_CODE KEY_C = 1 << 9;

			static constexpr KEY_CODE KEY_A = 1 << 10;
			static constexpr KEY_CODE KEY_S = 1 << 11;
			static constexpr KEY_CODE KEY_D = 1 << 12;
			static constexpr KEY_CODE KEY_F = 1 << 13;
			static constexpr KEY_CODE KEY_G = 1 << 14;
			static constexpr KEY_CODE KEY_H = 1 << 15;
			static constexpr KEY_CODE KEY_J = 1 << 16;

			static constexpr KEY_CODE KEY_Q = 1 << 17;
			static constexpr KEY_CODE KEY_W = 1 << 18;
			static constexpr KEY_CODE KEY_E = 1 << 19;
			static constexpr KEY_CODE KEY_R = 1 << 20;
			static constexpr KEY_CODE KEY_T = 1 << 21;
			static constexpr KEY_CODE KEY_Y = 1 << 22;
			static constexpr KEY_CODE KEY_U = 1 << 23;

			static constexpr KEY_CODE KEY_ESCAPE = 1 << 24;
			static constexpr KEY_CODE KEY_SPACE = 1 << 25;
		}
		using namespace KEY_CODES;
	}

	using namespace CONST_VALUES;
}



#endif