// SearchRegionDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "SearchRegionDlg.h"
#include "POIDataNew.h"


// CSearchRegionDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSearchRegionDlg, CMyDialog)
CSearchRegionDlg::CSearchRegionDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(CSearchRegionDlg::IDD, pParent)
{
	m_bExpandLiData = FALSE;
	m_strLi = "";
	m_nDongID = 0;
	m_bAloneItemAutoClosed = TRUE;
	m_strDisplayDong = "";
	m_bReturnLiID = FALSE;
}

CSearchRegionDlg::~CSearchRegionDlg()
{
}

void CSearchRegionDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_edtSearch);
	DDX_Text(pDX, IDC_SEARCH_EDIT, m_strSearch);
}


BEGIN_MESSAGE_MAP(CSearchRegionDlg, CMyDialog)
	ON_BN_CLICKED(IDC_SEARCH_BTN, OnBnClickedSearchBtn)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnNMDblclkList1)
	ON_BN_CLICKED(IDC_SEAECH_BUTTON, &CSearchRegionDlg::OnBnClickedSeaechButton)
	ON_EN_CHANGE(IDC_SEARCH_EDIT, &CSearchRegionDlg::OnEnChangeSearchEdit)
END_MESSAGE_MAP()


// CSearchRegionDlg 메시지 처리기입니다.

BOOL CSearchRegionDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	CenterWindow();

	m_List.InsertColumn(0, "검색된 데이터", LVCFMT_LEFT, 200);
	m_List.InsertColumn(1, "x", LVCFMT_LEFT, 0);
	m_List.InsertColumn(2, "y", LVCFMT_LEFT, 0);
	m_List.InsertColumn(3, "리", LVCFMT_LEFT, 0);
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_FLATSB | LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE);
	m_List.ShowHeader(FALSE);

	if(m_strSearch.GetLength() > 0)
		RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CSearchRegionDlg::RefreshList()
{
	int i = 0;
	
	m_List.DeleteAllItems();
	m_edtSearch.GetWindowText(m_strSearch);

	POI_VEC_POINT vecDong;
	if(m_poiNew.SearchDong(m_strSearch, vecDong))
	{
		POI_VEC_POINT::iterator it;
		for(it = vecDong.begin(); it != vecDong.end(); it++)
		{
			m_List.InsertItem(i, (*it)->GetRegionName());
			m_List.SetItemText(i, 1, LF->GetStringFromLong((*it)->GetPosX()));
			m_List.SetItemText(i, 2, LF->GetStringFromLong((*it)->GetPosY()));
			m_List.SetItemText(i, 3, (*it)->GetLi());
			m_List.SetItemData(i, (*it)->GetDongID(!m_bReturnLiID));
			i++;
		}
	}

	m_List.Populate();
}


void CSearchRegionDlg::OnBnClickedSearchBtn()
{
	RefreshList();
}

void CSearchRegionDlg::OnBnClickedOk()
{
	int nItem = m_List.GetNextItem(-1, LVNI_SELECTED);
	if(nItem < 0 && m_List.GetItemCount() > 0)
		nItem = 0;

	if(nItem >= 0)
	{
		m_nDongID = m_List.GetItemData(nItem);
		OnOK();
	}
	else
	{
		MessageBox("해당동을 선택하세요", "확인", MB_ICONINFORMATION);
	}
}

void CSearchRegionDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnBnClickedOk();
	*pResult = 0;
}

BOOL CSearchRegionDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_UP)
		{
			SelectUp();
			return TRUE;
		}
		else if(pMsg->wParam == VK_DOWN)
		{
			SelectDown();
			return TRUE;
		}
		else if(pMsg->wParam == VK_RETURN)
		{
			if(::GetDlgCtrlID(pMsg->hwnd) == IDC_SEARCH_EDIT)
			{
				RefreshList();
				GetDlgItem(IDOK)->SetFocus();
			}
			else
				OnBnClickedOk(); 
			return FALSE;
		}
	}

	return CMyDialog::PreTranslateMessage(pMsg);
}


void CSearchRegionDlg::SelectUp()
{
	CXTPGridRow *pRow = NULL;
	CXTPGridRows *pRows = m_List.GetRows();
	CXTPGridSelectedRows *pSelRows = m_List.GetSelectedRows();
	CXTPGridRow *pSelRow = pSelRows->GetAt(0);

	if(pRows == NULL)
		pRow = pRows->GetAt(m_List.GetItemCount() - 1);
	else
		pRow = pRows->GetAt(max(pSelRow->GetIndex() -1, 0));

	m_List.GetSelectedRows()->Select(pRow);
}

void CSearchRegionDlg::SelectDown()
{
	CXTPGridRow *pRow = NULL;
	CXTPGridRows *pRows = m_List.GetRows();
	CXTPGridSelectedRows *pSelRows = m_List.GetSelectedRows();
	CXTPGridRow *pSelRow = pSelRows->GetAt(0);

	if(pRows == NULL)
		pRow = pRows->GetAt(0);
	else
		pRow = pRows->GetAt(min(pSelRow->GetIndex() + 1, m_List.GetItemCount()));

	m_List.GetSelectedRows()->Select(pRow);
}

void CSearchRegionDlg::OnBnClickedSeaechButton()
{
	RefreshList();
}

void CSearchRegionDlg::OnEnChangeSearchEdit()
{
	RefreshList();
}
