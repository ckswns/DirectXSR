#pragma once


// ColorDlg

class ColorDlg : public CColorDialog
{
	DECLARE_DYNAMIC(ColorDlg)

public:
	ColorDlg(CWnd* pParentWnd = nullptr);
	virtual ~ColorDlg();

protected:
	DECLARE_MESSAGE_MAP()
};


