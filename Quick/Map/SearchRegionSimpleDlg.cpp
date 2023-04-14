// SearchRegionSimpleDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "SearchRegionSimpleDlg.h"
#include "POIDataNew.h"


// CSearchRegionSimpleDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSearchRegionSimpleDlg, CMyDialog)

CSearchRegionSimpleDlg::CSearchRegionSimpleDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CSearchRegionSimpleDlg::IDD, pParent)
{
	
}

CSearchRegionSimpleDlg::~CSearchRegionSimpleDlg()
{
}

void CSearchRegionSimpleDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DONG_LIST, m_List);
	DDX_Control(pDX, IDC_SHOW_ALL_DONG_CHECK, m_chkShowAllDong);
}


BEGIN_MESSAGE_MAP(CSearchRegionSimpleDlg, CMyDialog)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_SHOW_ALL_DONG_CHECK, &CSearchRegionSimpleDlg::OnBnClickedShowAllDongCheck)
	ON_NOTIFY(NM_CLICK, IDC_DONG_LIST, OnReportItemClick)
END_MESSAGE_MAP()


// CSearchRegionSimpleDlg 메시지 처리기입니다.

BOOL CSearchRegionSimpleDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_List.InsertColumn(0, "", LVCFMT_LEFT, 200);
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_FLATSB | LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE);
	m_List.ShowHeader(FALSE);
	m_List.GetPaintManager()->m_strNoItems = "";

	return FALSE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CSearchRegionSimpleDlg::Search(CString strKeyword)
{
	m_strKeyword = strKeyword;
	m_List.ResetContent();

	POI_VEC_POINT vecDong;
	if(m_poiNew.SearchDong(strKeyword, vecDong))
	{
		long nItem = 0;
		POI_VEC_POINT::iterator it;
		for(it = vecDong.begin(); it != vecDong.end(); it++)
		{
			m_List.InsertItem(nItem, (*it)->GetRegionName());
			m_List.SetItemData(nItem++, (DWORD)(*it));
		}
	}

	m_List.Populate();
}

void CSearchRegionSimpleDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
	CMyDialog::OnLButtonDown(nFlags, point);
}

void CSearchRegionSimpleDlg::OnBnClickedShowAllDongCheck()
{
	m_poiNew.SetMainSidoDongOnly(!m_chkShowAllDong.GetCheck());
	Search(m_strKeyword);
}

void CSearchRegionSimpleDlg::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	long nRow = pItemNotify->pRow->GetIndex();
	//long nCol = pItemNotify->pColumn->GetIndex();

	m_pPOI = (CPOIUnit*)m_List.GetItemData(nRow);
	GetParent()->PostMessage(WM_COMMAND, 1000, 0);
	OnOK();
}

void CSearchRegionSimpleDlg::SelectPOI(int nRow)
{
	m_pPOI = (CPOIUnit*)m_List.GetItemData(nRow);
	GetParent()->PostMessage(WM_COMMAND, 1000, 0);
}

BOOL CSearchRegionSimpleDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_RETURN)
		{
			if(m_List.GetItemCount() > 0)
			{
				int nRow = m_List.GetSelectedItem();
				SelectPOI(nRow >= 0 ? nRow : 0);
				return FALSE;
			}
		}
		else if(pMsg->wParam == VK_UP || pMsg->wParam == VK_DOWN)
		{
			if(pMsg->hwnd != m_List.GetSafeHwnd())
			{
				if(m_List.GetItemCount() > 1)
				{
					m_List.SetFocus();
					m_List.PostMessage(pMsg->message, pMsg->wParam, pMsg->lParam);
				}
				else if(m_List.GetItemCount() > 1)
				{
					m_List.SetFocus();
					m_List.PostMessage(pMsg->message, pMsg->wParam, pMsg->lParam);
				}
				return FALSE;
			}
		}
	}

	return CMyDialog::PreTranslateMessage(pMsg);
}
