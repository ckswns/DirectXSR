#pragma once

#ifndef __TYPE_DEFINE_H__
#define __TYPE_DEFINE_H__

namespace ce
{
//#define		NORETURN						[[noreturn]]				/* ȣ���ڿ��� ���ư��� ������ �ǹ� */
//#define		CARRIES_DEPENDENCY				[[carries_dependency]]		/* ���� ���α׷����� atomic ���ۿ� �־� ���� �����ϴ� ������ �Լ� ���ݿ� �����ϴ� ���� �ǹ� */
//#define		DEPRECATED(developer, reason)	[[deprecated(reason)]]		/* ������� �� ���� �ǰ����� �ǹ� */
//#define		FALLTHROUGH						[[fallthrough]]				/* switch������ break���� �ʰ� ������� ����ϴ� �ǹ� */
//#define		LIKELY							[[likely]]					/* ���� �б⿡�� ���� ���õǴ� ��츦 �ǹ� (����ȭ ��Ʈ) */
//#define		UNLIKELY						[[unlikely]]				/* ���� �б⿡�� ���� ���õ��� �ʴ� ��츦 �ǹ� (����ȭ ��Ʈ) */
//#define		NODISCARD						[[nodiscard]]				/* ��ȯ���� ������ ��� ��� ���ٰ��� �ǹ� */
//#define		MAYBE_UNUSED					[[maybe_unused]]			/* ���� �������� ��� ���� �������� �ǹ� */
//#define		NO_UNIQUE_ADDRESS				[[no_unique_address]]		/* ��� ������ �ٸ� ��� ������ ��������� �ٸ� �ּҸ� ���� �ʿ䰡 ���ٴ� ���� �ǹ� */

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

	constexpr DWORD		FVF_CUBE = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE3(0); // �ؽ�ó�� UV ��ǥ ���� FLOAT�� 3���� ǥ���ϰڴٴ� ��ũ��(��ȣ���� ���� 0�� �ǹ̴� ���� ���ؽ��� �ؽ��� UV���� �������� �� �� �ִµ� ���� 0��° ���� �����ϰڴٴ� �ǹ�)

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
	// �ؽ�ó�� UV ��ǥ ���� FLOAT�� 3���� ǥ���ϰڴٴ� ��ũ��(��ȣ���� ���� 0�� �ǹ̴� ���� ���ؽ��� �ؽ��� UV���� �������� �� �� �ִµ� ���� 0��° ���� �����ϰڴٴ� �ǹ�)

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