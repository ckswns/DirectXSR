#pragma once

#ifndef __TYPE_DEFINE_H__
#define __TYPE_DEFINE_H__

namespace ce
{
//#define		NORETURN						[[noreturn]]				/* 호출자에게 돌아가지 않음을 의미 */
//#define		CARRIES_DEPENDENCY				[[carries_dependency]]		/* 병령 프로그래밍의 atomic 조작에 있어 값에 의존하는 순서를 함수 전반에 전파하는 것을 의미 */
//#define		DEPRECATED(developer, reason)	[[deprecated(reason)]]		/* 사용하지 말 것을 권고함을 의미 */
//#define		FALLTHROUGH						[[fallthrough]]				/* switch문에서 break되지 않고 통과함을 명시하는 의미 */
//#define		LIKELY							[[likely]]					/* 조건 분기에서 자주 선택되는 경우를 의미 (최적화 힌트) */
//#define		UNLIKELY						[[unlikely]]				/* 조건 분기에서 자주 선택되지 않는 경우를 의미 (최적화 힌트) */
//#define		NODISCARD						[[nodiscard]]				/* 반환값이 버려질 경우 경고를 내줄것을 의미 */
//#define		MAYBE_UNUSED					[[maybe_unused]]			/* 값이 버려져도 경고를 내지 않을것을 의미 */
//#define		NO_UNIQUE_ADDRESS				[[no_unique_address]]		/* 멤버 변수가 다른 모든 비정적 멤버변수와 다른 주소를 가질 필요가 없다는 것을 의미 */

	using	byte = unsigned char;

	using	int8 = signed	 __int8;
	using	int16 = signed	 __int16;
	using	int32 = signed	 __int32;
	using	int64 = signed	 __int64;

	using	uint = unsigned int;

	using	uint8 = unsigned __int8;
	using	uint16 = unsigned __int16;
	using	uint32 = unsigned __int32;
	using	uint64 = unsigned __int64;

	enum class GameObjectLayer
	{
		BACKGROUND,
		OBJECT,
		EFFECT,
		UI,
		END
	};

	enum class GameObjectTag
	{
		DEFAULT,
		PLAYER,
		MONSTER,
		OBSTACLE,
		OBJECT,
		EFFECT,
		UI,
		CAMERA,
		END
	};

	enum class MOUSE_STATE
	{
		DOWN,
		HELD_DOWN,
		UP,
		END
	};

	enum class PICKING_STATE
	{
		NONE,
		OVER,
		DOWN,
		HELDDOWN,
		UP,
		LEAVE,
		END
	};

	typedef struct tagVertexColor
	{
		D3DXVECTOR3		vPosition;
		DWORD			dwColor;

	}VTXCOL;

	constexpr DWORD		FVF_COL = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX0;

	typedef struct tagVertexTexture
	{
		D3DXVECTOR3		vPosition;
		D3DXVECTOR2		vTexUV;

	}VTXTEX;

	constexpr DWORD		FVF_TEX = D3DFVF_XYZ | D3DFVF_TEX1;

	typedef struct tagVertexCubeTexture
	{
		D3DXVECTOR3		vPosition;
		D3DXVECTOR3		vTexUV;

	}VTXCUBE;

	constexpr DWORD		FVF_CUBE = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE3(0); // 텍스처의 UV 좌표 값을 FLOAT형 3개로 표현하겠다는 매크로(괄호안의 숫자 0의 의미는 본래 버텍스에 텍스쳐 UV값이 여러개가 올 수 있는데 그중 0번째 값을 지정하겠다는 의미)

	typedef struct tagVertexTextureNormal
	{
		D3DXVECTOR3		vPosition;
		D3DXVECTOR3		vNormal;
		D3DXVECTOR2		vTexUV;

	}VTXTEXNORM;

	constexpr DWORD		FVF_TEX_NORM = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;

	typedef struct tagVertexAlphaTextureNormal
	{
		D3DXVECTOR3		vPosition;
		D3DXVECTOR3		vNormal;
		D3DXVECTOR2		vAlphaUV;
		D3DXVECTOR2		vTexUV;
	}VTXALPHATEXNORM;

	constexpr DWORD		FVF_ALPHA_TEX_NORM = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 | D3DFVF_TEX2;

	typedef struct tagVertexCubeTextureNormal
	{
		D3DXVECTOR3		vPosition;
		D3DXVECTOR3		vNormal;
		D3DXVECTOR3		vTexUV;

	}VTXCUBENORM;

	constexpr DWORD		FVF_CUBE_NORM = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_NORMAL | D3DFVF_TEXCOORDSIZE3(0);
	// 텍스처의 UV 좌표 값을 FLOAT형 3개로 표현하겠다는 매크로(괄호안의 숫자 0의 의미는 본래 버텍스에 텍스쳐 UV값이 여러개가 올 수 있는데 그중 0번째 값을 지정하겠다는 의미)

	typedef struct tagIndex16
	{
		uint16  _0;
		uint16  _1;
		uint16  _2;

	}INDEX16;

	typedef struct tagIndex32
	{
		DWORD	_0;
		DWORD	_1;
		DWORD	_2;

	}INDEX32;

}

#endif