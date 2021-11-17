#pragma once
#ifndef MapTool_Define_h__
#define MapTool_Define_h__

//#define MAPWIDTH		32
//#define MAPHEIGHT		32
#define WINCX 1280
#define WINCY 720
#define MAXTEXNUM		4
//#define TEXALPHASIZE	512 // totla vertex /2 
//#define MINIALPHASIZE	128

#define SAFE_DELETE_(p)       {if(p) {delete (p);     (p)=NULL;}}
#define SAFE_DELETE_ARRAY_(p) {if(p) {delete[] (p);   (p)=NULL;}}
#define SAFE_RELEASE_(p)      {if(p) {(p)->Release(); (p)=NULL;}}

extern	HWND			g_hWnd;
extern	GameController*	g_pGameController;
extern	bool			g_bInitGame;
extern	RECT			g_rtMfc;
extern CPoint			g_MousePos;
extern	bool			g_bWireMode;

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