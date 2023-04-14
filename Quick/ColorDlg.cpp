// ColorDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ColorDlg.h"



// CColorDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CColorDlg, CMyDialog)
CColorDlg::CColorDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CColorDlg::IDD, pParent)
{
}

CColorDlg::~CColorDlg()
{
}

void CColorDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COLOR_BTN, m_cpColor);
	DDX_XTColorPicker(pDX, IDC_COLOR_BTN, m_clrColor);

	DDX_Control(pDX, IDC_TEXT_COLOR_BTN, m_cpTextColor);
	DDX_XTColorPicker(pDX, IDC_TEXT_COLOR_BTN, m_clrTextColor);
	DDX_Control(pDX, IDC_STATIC1, m_Stc);
}


BEGIN_MESSAGE_MAP(CColorDlg, CMyDialog)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_WM_PAINT()
	ON_CPN_XT_SELENDOK(IDC_TEXT_COLOR_BTN, OnSelEndOkTextClr)
	ON_CPN_XT_SELENDOK(IDC_COLOR_BTN, OnSelEndOkBackClr)
END_MESSAGE_MAP()


// CColorDlg 메시지 처리기입니다.

void CColorDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnCancel();
}

void CColorDlg::OnBnClickedOk()
{
	UpdateChangeColor();
	OnOK();
}

void CColorDlg::UpdateChangeColor()
{
	UpdateData(TRUE);

	int nRColor = GetRValue(m_clrColor);
	int nGColor = GetGValue(m_clrColor);
	int nBColor =GetBValue(m_clrColor);

	int nRTextColor = GetRValue(m_clrTextColor);
	int nGTextColor = GetGValue(m_clrTextColor);
	int nBTextColor =GetBValue(m_clrTextColor);

	m_nColor = nRColor + (nGColor << 8) + (nBColor << 16);
	m_nTextColor = nRTextColor + (nGTextColor << 8) + (nBTextColor << 16);
}

void CColorDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rc;
	m_Stc.GetClientRect(&rc);
	m_Stc.ClientToScreen(&rc);
	ScreenToClient(&rc);

	if(m_nColor == 0)
	{
		if(m_nCarType == 0)
			dc.FillSolidRect(CRect(rc.left, rc.top, rc.right, rc.bottom), RGB(133, 210, 65));
		else
			dc.FillSolidRect(CRect(rc.left, rc.top, rc.right, rc.bottom), RGB(150, 180, 210));
	}
	else
	{
		COLORREF clrRider = RGB(GetRValue(m_nColor), GetGValue(m_nColor), GetBValue(m_nColor));

		dc.FillSolidRect(CRect(rc.left, rc.top, rc.right, rc.bottom), clrRider);
	}

	if(m_nTextColor == 0)
		dc.SetTextColor(RGB(255, 255, 255));
	else
	{
		COLORREF clrRiderText = RGB(GetRValue(m_nTextColor), GetGValue(m_nTextColor), GetBValue(m_nTextColor));
		dc.SetTextColor(clrRiderText);
	}

	dc.SetBkMode(TRANSPARENT);


	CString str;
	str.Format("%d / %s", m_nRNo, m_sRName);

	dc.DrawText(str, CRect(rc.left + 10, rc.top, rc.right, rc.bottom), 
		DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	

}

void CColorDlg::OnSelEndOkTextClr()
{
	UpdateChangeColor();
	Invalidate();
}

void CColorDlg::OnSelEndOkBackClr()
{
	UpdateChangeColor();
	Invalidate();
}

BOOL CColorDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();


	if(m_nColor == 0)
	{
		if(m_nCarType == 0)
			m_clrColor = RGB(133, 210, 65);
		else 
			m_clrColor = RGB(150, 180, 210);
	}
	else 
		m_clrColor = RGB(GetRValue(m_nColor), GetGValue(m_nColor), GetBValue(m_nColor));

	if(m_nTextColor == 0)
	{
		m_clrTextColor = RGB(255, 255, 255);
	}
	else 
		m_clrTextColor = RGB(GetRValue(m_nTextColor), GetGValue(m_nTextColor), GetBValue(m_nTextColor));

	m_cpColor.SetColor(m_clrColor);
	m_cpColor.SetDefaultColor(GetSysColor(COLOR_WINDOW));

	m_cpTextColor.SetColor(m_clrTextColor);
	m_cpTextColor.SetDefaultColor(GetSysColor(COLOR_WINDOWTEXT));

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
