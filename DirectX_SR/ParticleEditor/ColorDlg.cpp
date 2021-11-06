// ColorDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ParticleEditor.h"
#include "ColorDlg.h"

#ifndef _WIN32_WCE // Windows CE에서는 CColorDialog이(가) 지원되지 않습니다.

// ColorDlg

IMPLEMENT_DYNAMIC(ColorDlg, CColorDialog)

ColorDlg::ColorDlg(CWnd* pParentWnd)
	:CColorDialog(RGB(255, 255, 255), CC_RGBINIT|CC_FULLOPEN, pParentWnd)
{
}

ColorDlg::~ColorDlg() {}

BEGIN_MESSAGE_MAP(ColorDlg, CColorDialog)
END_MESSAGE_MAP()



// ColorDlg 메시지 처리기


#endif // !_WIN32_WCE
