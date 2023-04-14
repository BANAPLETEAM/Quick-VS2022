// RcpDlgBase.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "RcpDlgBase.h"
#include "RcpView.h"

#define COLOR_TEXT	RGB(100, 100, 255)
#define COLOR_BACK	GetSysColor(COLOR_3DFACE)

// CRcpDlgBase 대화 상자입니다.

IMPLEMENT_DYNAMIC(CRcpDlgBase, CMyDialog)

CRcpDlgBase::CRcpDlgBase(CWnd* pParent /*=NULL*/)
	: CMyDialog(CRcpDlgBase::IDD, pParent)
{
	m_pRcpView = NULL;
	m_pFocusControl = NULL;
}

CRcpDlgBase::~CRcpDlgBase()
{
}


void CRcpDlgBase::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TITLE_STATIC, m_stcTitle);

	if(IsInsungDlg())
	{
		DDX_Control(pDX, IDC_BRANCH_COMBO, m_CMB_BRANCH.comboInsung);
		m_CMB_BRANCH.pCombo = &m_CMB_BRANCH.comboInsung;
	}
	else
	{
		DDX_Control(pDX, IDC_BRANCH_COMBO, m_CMB_BRANCH.combo);
		m_CMB_BRANCH.pCombo = &m_CMB_BRANCH.combo;
	}
}


BEGIN_MESSAGE_MAP(CRcpDlgBase, CMyDialog)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_MINI_SIZE_BTN, &CRcpDlgBase::OnBnClickedMiniSizeBtn)
	ON_BN_CLICKED(IDC_SEARCH_RCP_VIEW_BTN, &CRcpDlgBase::OnBnClickedSearchRcpViewBtn)
	ON_BN_CLICKED(IDC_NEW_RCP_DLG_BTN, &CRcpDlgBase::OnBnClickedNewRcpDlgBtn)
//	ON_MESSAGE(WM_MY_STATIC_CLICK, OnMyStaticClick)
ON_WM_TIMER()
END_MESSAGE_MAP()


BOOL CRcpDlgBase::IsInsungDlg()
{
	CRuntimeClass *p = GetRuntimeClass();
	CString strClassName(p->m_lpszClassName);

	return strClassName == "CRcpInsungDlg";
}
// CRcpDlgBase 메시지 처리기입니다.

BOOL CRcpDlgBase::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	SetGrade(0);

	m_stcTitle.SetFont(m_FontManager.GetFont("맑은 고딕", 21, FW_BOLD));

	MakeBranchCombo();

	SetTimer(5689, 1000, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CRcpDlgBase::MakeBranchCombo()
{
	if(m_pBi->bGroup) 
	{
		for(int i = 0; i < m_ba.GetCount(); i++)
		{
			CBranchInfo *pBi = m_ba.GetAt(i);

			if(pBi->bIntegrated)
				continue;
			
			if(pBi->nServiceType == m_pBi->nServiceType)
			{
				int nIndex = m_CMB_BRANCH.pCombo->AddString(pBi->strBranchName + "(" + pBi->strPhone + ")");
				m_CMB_BRANCH.pCombo->SetItemData(nIndex, pBi->nCompanyCode);

				if(m_pBi->nDOrderTable == pBi->nCompanyCode)
					m_CMB_BRANCH.pCombo->SetCurSel(nIndex);
			}
		}
	}
}

void CRcpDlgBase::OnBnClickedMiniSizeBtn()
{
	DWORD dwStyle = GetStyle();

	dwStyle |= WS_SYSMENU;
	dwStyle |= WS_MINIMIZEBOX;

	ModifyStyle(NULL, dwStyle);
	ShowWindow(SW_SHOWMINIMIZED);
	//SW_SHOWMINIMIZED
	//SW_MINIMIZE
}

void CRcpDlgBase::OnBnClickedSearchRcpViewBtn()
{
	m_pRcpView->OnBnClickedSearchBtn();
}

void CRcpDlgBase::OnBnClickedNewRcpDlgBtn()
{
	m_pRcpView->OnBnClickedNewRcpDlgBtn();
}

void CRcpDlgBase::OnLButtonDown(UINT nFlags, CPoint point)
{
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
	CMyDialog::OnLButtonDown(nFlags, point);
}

void CRcpDlgBase::DrawTop(CDC *pDC)
{
	CRect rc, rcDlg;
	GetClientRect(rcDlg);
	m_stcTitle.GetWindowRect(rc);
	ScreenToClient(rc);
	rc.right = rcDlg.right;

	if(m_crText == RGB(0, 0, 0) && m_crBack == RGB(255, 255, 255))
	{
		pDC->SetTextColor(COLOR_TEXT);
		pDC->SetBkColor(m_crOriBack);
	}
	else
	{
		pDC->SetTextColor(m_crText);
		LF->FillGradient(pDC, m_crBack, rc);
	}

	pDC->SetBkMode(TRANSPARENT);
	pDC->SelectObject(m_FontManager.GetFont("맑은 고딕", 23, FW_BOLD));


	m_rcBackPaint = rc;

	CRect rcMini;
	GetDlgItem(IDC_RESERVE_BTN)->GetWindowRect(rcMini);
	ScreenToClient(rcMini);
	m_rcBackPaint.right = rcMini.left - 5;

	if(m_strGrade.GetLength() > 0)
		pDC->DrawText(m_strRcpTitle + CString("/") + m_strGrade, m_rcBackPaint, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	else
		pDC->DrawText(m_strRcpTitle, m_rcBackPaint, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

	if(!GetDlgItem(IDC_RESERVE_DISPLAY_STATIC)->IsWindowVisible())
		pDC->DrawText(m_strRcpTitleTime, m_rcBackPaint, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);

	if(m_crOriBack == 0)
		m_crOriBack = pDC->GetBkColor();
}

/*
HBRUSH CRcpDlgBase::DrawTopControlColor(CDC *pDC)
{

	if(m_crText == RGB(0, 0, 0) && m_crBack == RGB(255, 255, 255))
	{
		pDC->SetTextColor(COLOR_TEXT);
		pDC->SetBkColor(m_crOriBack);
		pDC->SetBkMode(TRANSPARENT);
		if(m_crOriBack != 0)
			return m_HandleManager.GetBrushObject(m_crOriBack);
	}
	else
	{
		pDC->SetTextColor(m_crText);
		pDC->SetBkColor(m_crBack);
		pDC->SetBkMode(OPAQUE);
		return m_HandleManager.GetBrushObject(m_crBack);
	}

	return NULL;
}
*/
void CRcpDlgBase::SetTitleInfo(CString strText)
{ 
	m_strRcpTitle = m_nInitItem > 0 ? " (수정) " : " (등록) ";

	if(m_ba.GetCount() > 2)
		m_strRcpTitle += m_pBi->strBranchName + " - " + strText;
	else 
		m_strRcpTitle += strText;

	m_strRcpTitleTime.Empty();
	if(m_strGrade.GetLength() > 0)
		SetWindowText(strText + CString("/") + m_strGrade);
	else
		SetWindowText(strText);
	SetTitleTime();
}


void CRcpDlgBase::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent == 5689)
		SetTitleTime();

	CMyDialog::OnTimer(nIDEvent);
}

void CRcpDlgBase::SetTitleTime()
{
	if(m_nInitItem > 0 && IsWindowVisible())
	{
		COleDateTimeSpan dtSpan = COleDateTime::GetCurrentTime() - m_dtRcpTime + m_dtsDBTime;
		CString strRcpTitleTime = m_dtRcpTime.Format("%Y-%m-%d") + " " + LF->GetElapsedTimeString(dtSpan);
		if(m_strRcpTitleTime != strRcpTitleTime)
		{
			m_strRcpTitleTime = strRcpTitleTime;
			CRect rc = m_rcBackPaint;
			rc.left = rc.right - 210; 
			InvalidateRect(rc, 0);
		}
	}
}

void CRcpDlgBase::SetGrade(long nGrade)
{
	if(nGrade == -100)
	{
		m_crBack = RGB(255, 0, 0);
		m_crText = RGB(255, 255, 255);		
	}
	else if(m_pBi->bColorChange)
	{
		m_strGrade = ::GetGrade(nGrade, FALSE);
		if(nGrade != 0)
			m_crBack = ::GetGradeColor(nGrade);
		else
		{
			if(m_pBi->IsQuick())
			{
				m_crBack = RGB(107, 205, 90);
				m_crText = RGB(255, 255, 255);
			}
			else if(m_pBi->IsCargo())
			{
				m_crBack = RGB(210, 210, 0);
				m_crText = RGB(255, 255, 255);
			}
		}
	}
	else
	{
		if(m_pBi->IsQuick())
		{
			m_crBack = RGB(107, 205, 90);
			m_crText = RGB(255, 255, 255);
		}
		else if(m_pBi->IsCargo())
		{
			m_crBack = RGB(210, 210, 0);
			m_crText = RGB(255, 255, 255);
		}
	}
	
	RedrawWindow();
}