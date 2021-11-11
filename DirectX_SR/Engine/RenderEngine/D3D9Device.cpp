#include "pch.h"
#include "D3D9Device.h"
#include "../Base/Assertion.h"

namespace ce
{
	D3D9Device::D3D9Device() noexcept :
		_pSDK(nullptr),
		_pDevice(nullptr),
		_pSprite(nullptr)
	{
		__noop;
	}

	bool D3D9Device::Init(HWND hWnd, uint16 winWidth, uint16 winHeight, D3DXCOLOR clearColor, const char* fontFilePath, const char* fontFaceName) noexcept
	{
		_pSDK = Direct3DCreate9(D3D_SDK_VERSION);

		if (_pSDK == nullptr)
		{
			CE_ASSERT("ckswns", "Direct3DCreate9은 nullptr일 수 없습니다");

			return false;
		}

		D3DCAPS9 DeveiceCaps;
		ZeroMemory(&DeveiceCaps, sizeof(D3DCAPS9));

		if (FAILED(_pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeveiceCaps)))
		{
			CE_ASSERT("ckswns", "GetDeviceCaps에 실패하였습니다");
			return false;
		}

		DWORD uFlag = 0;

		if (DeveiceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
			uFlag |= D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;
		else
			uFlag |= D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;

		D3DPRESENT_PARAMETERS Present_Parameter;
		ZeroMemory(&Present_Parameter, sizeof(D3DPRESENT_PARAMETERS));

		Present_Parameter.BackBufferWidth = winWidth;
		Present_Parameter.BackBufferHeight = winHeight;
		Present_Parameter.BackBufferFormat = D3DFMT_A8R8G8B8;
		Present_Parameter.BackBufferCount = 1;

		Present_Parameter.MultiSampleType = D3DMULTISAMPLE_NONE;
		Present_Parameter.MultiSampleQuality = 0;

		Present_Parameter.SwapEffect = D3DSWAPEFFECT_DISCARD;
		Present_Parameter.hDeviceWindow = hWnd;
		Present_Parameter.Windowed = true;
		Present_Parameter.EnableAutoDepthStencil = true;
		Present_Parameter.AutoDepthStencilFormat = D3DFMT_D24S8;

		Present_Parameter.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		Present_Parameter.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

		_windowWidth = winWidth;
		_windowHeight = winHeight;

		if (FAILED(_pSDK->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, uFlag, &Present_Parameter, &_pDevice)))
		{
			CE_ASSERT("ckswns", "디바이스 생성에 실패하였습니다");
			return false;
		}

		if (FAILED(D3DXCreateSprite(_pDevice, &_pSprite)))
		{
			CE_ASSERT("ckswns", "D3DXCreateSprite함수 호출이 실패하였습니다");
			return false;
		}

		AddFontResourceA(fontFilePath);

		D3DXFONT_DESCA tDesc;
		ZeroMemory(&tDesc, sizeof(D3DXFONT_DESCA));
		tDesc.Height = 15;
		tDesc.Width = 12;
		tDesc.Weight = 500;
		tDesc.CharSet = HANGUL_CHARSET;
		memcpy(tDesc.FaceName, fontFaceName, strlen(fontFaceName) + 1);

		if (FAILED(D3DXCreateFontIndirectA(_pDevice, &tDesc, &_pFont)))
			return false;

		_nClearColor = clearColor;

		return true;
	}

	void D3D9Device::Begin(void) noexcept
	{
		_pDevice->Clear(0, NULL, D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, _nClearColor, 1.f, 0);
		_pDevice->BeginScene();
		_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		_pDevice->SetRenderState(D3DRS_LIGHTING, true);
		_pDevice->SetRenderState(D3DRS_AMBIENT, 0x00202020);
		_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}

	void D3D9Device::End(void) noexcept
	{
		_pDevice->EndScene();
		_pDevice->Present(NULL, NULL, NULL, NULL);
	}

	void D3D9Device::UIBegin(void) noexcept
	{
		_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
		//_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
		//_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	}

	void D3D9Device::UIEnd(void) noexcept
	{
		_pSprite->End();
	}

	void D3D9Device::Release(void) noexcept
	{
		if (_pFont)
			_pFont->Release();
		if (_pSprite)
			_pSprite->Release();
		if (_pDevice)
			_pDevice->Release();
		if (_pSDK)
			_pSDK->Release();

		_pDevice = nullptr;
		_pSDK = nullptr;
	}
}