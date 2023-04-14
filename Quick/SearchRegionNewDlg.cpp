// SearchRegionNewDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "SearchRegionNewDlg.h"


// CSearchRegionNewDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSearchRegionNewDlg, CMyDialog)

CSearchRegionNewDlg::CSearchRegionNewDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CSearchRegionNewDlg::IDD, pParent)
{
	m_bExpandLiData = FALSE;
	m_strLi = "";
	m_nDongID = 0;
	m_bAloneItemAutoClosed = TRUE;
	m_strDisplayDong = "";
}

CSearchRegionNewDlg::~CSearchRegionNewDlg()
{
}

void CSearchRegionNewDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_edtSearch);
	DDX_Text(pDX, IDC_SEARCH_EDIT, m_strSearch);
}


BEGIN_MESSAGE_MAP(CSearchRegionNewDlg, CMyDialog)
	ON_BN_CLICKED(IDC_SEARCH_BTN, OnBnClickedSearchBtn)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnNMDblclkList1)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CSearchRegionNewDlg 메시지 처리기입니다.


BOOL CSearchRegionNewDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	//	m_stc1.SetColor(RGB(255, 255, 255), RGB(101, 147, 207));
	//	m_stc1.SetOutlineColor(0, TRUE);

	CenterWindow();

	//m_List.InsertColumn(0, "ⓝ", LVCFMT_LEFT,  25);
	m_List.InsertColumn(0, "검색된 데이터", LVCFMT_LEFT, 160);
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

void CSearchRegionNewDlg::RefreshList()
{
	int nInBoundCount = 0;

	m_List.DeleteAllItems();
	m_edtSearch.GetWindowText(m_strSearch);

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "search_region_data_new");
	pCmd.AddParameter(m_strSearch);
	pCmd.AddParameter(m_ci.m_bound.nPosX);
	pCmd.AddParameter(m_ci.m_bound.nPosY);
	pCmd.AddParameter(m_bExpandLiData);

	if(pRs.Execute(&pCmd))
	{
		CString strSido, strGugun, strGugun2, strDong, strLi;
		long nDongID, nPosY, nPosX, nMeter;
		char buffer[10];
		CString strDistance;

		for(int i = 0; i < pRs.GetRecordCount(); i++)
		{
			pRs.GetFieldValue("sSido", strSido);
			pRs.GetFieldValue("sGugun", strGugun);
			pRs.GetFieldValue("sGugun2", strGugun2);
			pRs.GetFieldValue("sDong", strDong);
			pRs.GetFieldValue("sLi", strLi);
			pRs.GetFieldValue("nDongID", nDongID);
			pRs.GetFieldValue("nPosY", nPosY);
			pRs.GetFieldValue("nPosX", nPosX);
			pRs.GetFieldValue("nMeter", nMeter);

			strDistance.Format("%0.1f", nMeter / 1000.0);
			CString strName = strSido + " " + strGugun + " " + strGugun2 + " " + strDong;
			strName.Replace("  ", " ");

			if(nMeter / 1000 < m_ci.m_bound.nBoundary1)
				nInBoundCount++;

			if(strLi.GetLength() > 0)
				strName = strName + " " + strLi;

			//m_List.InsertItem(i, ltoa(i+1, buffer, 10));
			m_List.InsertItem(i, strName);
			//m_List.SetItemText(i, 2, strDistance);
			m_List.SetItemText(i, 1, ltoa(nPosY, buffer, 10));
			m_List.SetItemText(i, 2, ltoa(nPosX, buffer, 10));
			m_List.SetItemText(i, 3, strLi);
			m_List.SetItemData(i, nDongID);

			pRs.MoveNext();
		}

		if(nInBoundCount == 1 && m_bAloneItemAutoClosed)
		{
			//	m_List.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED);
			m_List.Populate();
			OnBnClickedOk();
		}
		else if(nInBoundCount == 0 && m_bAloneItemAutoClosed)
		{
			OnCancel();
		}
	}

	m_bAloneItemAutoClosed = FALSE;
	m_List.Populate();
}


void CSearchRegionNewDlg::OnBnClickedSearchBtn()
{
	RefreshList();
}

void CSearchRegionNewDlg::OnBnClickedOk()
{
	int nItem = m_List.GetNextItem(-1, LVNI_SELECTED);
	if(nItem < 0 && m_List.GetItemCount() > 0)
		nItem = 0;

	if(nItem >= 0)
	{
		//m_sDisplayDong = m_List.GetItemText(nItem, 0);
		//m_strLi = m_List.GetItemText(nItem, 3);
		//m_nPosY = atol(m_List.GetItemText(nItem, 1));
		//m_nPosX = atol(m_List.GetItemText(nItem, 2));
		m_nDongID = m_List.GetItemData(nItem);
		OnOK();
	}
	else
	{
		MessageBox("해당동을 선택하세요", "확인", MB_ICONINFORMATION);
	}
}

void CSearchRegionNewDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnBnClickedOk();
	*pResult = 0;
}

BOOL CSearchRegionNewDlg::PreTranslateMessage(MSG* pMsg)
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
			OnBnClickedOk(); 
			return FALSE;
		}
	}

	return CMyDialog::PreTranslateMessage(pMsg);
}


void CSearchRegionNewDlg::SelectUp()
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

void CSearchRegionNewDlg::SelectDown()
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

void CSearchRegionNewDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CMyDialog::OnPaint()을(를) 호출하지 마십시오.
}

HBRUSH CSearchRegionNewDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CMyDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	//if(pWnd->GetSafeHwnd() == this->GetSafeHwnd())
	//	return m_hWhiteBrush;

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}
