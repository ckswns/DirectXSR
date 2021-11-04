#pragma once
#ifndef MapTool_Define_h__
#define MapTool_Define_h__

#define WINCX 800
#define WINCY 600

extern	HWND			g_hWnd;
extern GameController*	g_pGameController;
extern bool				g_bInitGame;


template<typename T>
void	Safe_Delete(T& Pointer)
{
	if (nullptr != Pointer)
	{
		delete Pointer;
		Pointer = nullptr;
	}

}

#endif // MapTool_Define_h__