// AllocateDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "AllocateDlg.h"
#include "MainFrm.h"
#include "RcpDlg.h"
#include "RcpView.h"
#include "RcpMultiStateChange.h"
#include "CustomMyAfxMessgagebox.h"
#include "DelayOrderDlg2.h"

// CAllocateDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CAllocateDlg, CMyDialog)
CAllocateDlg::CAllocateDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(IDD_ALLOCATE_DLG, pParent)
{
	m_nRCompanyCode = m_nCompanyCode;
	m_bChangeDisable = FALSE;
	m_nTNo = 0;
	m_nState = 0;
	m_nCarType = 0;

	m_pSelRecord = NULL;
	m_pRcpView = NULL;
}

CAllocateDlg::~CAllocateDlg()
{
}

void CAllocateDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_CAR_TYPE_STATIC, m_stcCarType);
	DDX_Control(pDX, IDC_RNO_EDIT, m_edtRNo);
	DDX_Control(pDX, IDC_COMPANY_STATIC, m_stcCompany);
	DDX_Control(pDX, IDC_COMPANY_COMBO, m_cmbCompany);
	DDX_Control(pDX, IDC_CROSS_STATIC, m_stcCross);
	
	DDX_Control(pDX, IDC_DUPLICATE_LIST, m_lstDuplicate);
}


BEGIN_MESSAGE_MAP(CAllocateDlg, CMyDialog)
	ON_BN_CLICKED(IDC_ORDER_INSERT_CHECK, OnBnClickedOrderInsertBtn)
	ON_BN_CLICKED(IDC_ALLOCATE_BTN, OnBnClickedAllocateBtn)
	ON_BN_CLICKED(IDC_CANCEL_BTN, OnBnClickedCancelBtn)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnNMClickList1)	
	ON_CBN_SELCHANGE(IDC_COMPANY_COMBO, OnCbnSelchangeCompanyCombo)
	ON_NOTIFY(NM_DBLCLK, IDC_DUPLICATE_LIST, OnNMDblclkDuplicateList)
	ON_NOTIFY(LVN_DELETEITEM, IDC_DUPLICATE_LIST, OnLvnDeleteitemDuplicateList)
	ON_EN_CHANGE(IDC_RNO_EDIT, &CAllocateDlg::OnEnChangeRnoEdit)
END_MESSAGE_MAP()


// CAllocateDlg 메시지 처리기입니다.
BOOL CAllocateDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	CenterWindow();

	BOOL bInsert = AfxGetApp()->GetProfileInt("AllocateDlg", "bInsert", 0);
	((CButton*)GetDlgItem(IDC_ORDER_INSERT_CHECK))->SetCheck(bInsert);

	const char *szKDelMask[] = {"오토바이", "다마스", "트럭", "봉고", "대리운전"};

    m_List.InsertColumn(0,"번호",	LVCFMT_LEFT,50);
	m_List.InsertColumn(1,"출발지",	LVCFMT_LEFT, 60);
	m_List.InsertColumn(2,"도착지",	LVCFMT_LEFT, 60);
	m_List.InsertColumn(3,"최초배차",	LVCFMT_CENTER,60);
	m_List.InsertColumn(4,"최종배차",	LVCFMT_CENTER,60);
	m_List.InsertColumn(5,"왕복",		LVCFMT_CENTER,37);
	m_List.InsertColumn(6,"기 사",	LVCFMT_LEFT,50);
	m_List.InsertColumn(7,"휴대폰",	LVCFMT_LEFT,90);
	m_List.InsertColumn(8,"건수",	LVCFMT_RIGHT,40);
	m_List.InsertColumn(9,"수입",	LVCFMT_RIGHT,60);
	m_List.InsertColumn(10,"수입/건수",LVCFMT_RIGHT,70);

	m_lstDuplicate.InsertColumn(0,"지사명", LVCFMT_CENTER, 120);
	m_lstDuplicate.InsertColumn(1,"기사번호",LVCFMT_CENTER, 80);
	m_lstDuplicate.InsertColumn(2,"기사명", LVCFMT_CENTER, 120);

	m_lstDuplicate.Populate();
	m_List.Populate();
	InsertListData();

	m_lstDuplicate.ShowWindow(TRUE);
	
	
	m_stcCarType.SetWindowText(szKDelMask[m_nCarType]);

	for(int i = 0; i < m_ba.GetCount(); i++) {
		CBranchInfo *pBi = m_ba.GetAt(i);
		int nItem = m_cmbCompany.AddString(pBi->strBranchName);
		m_cmbCompany.SetItemData(nItem, pBi->nCompanyCode); 
		
		if(m_nCompanyCode == pBi->nCompanyCode) 
			m_cmbCompany.SetCurSel(nItem);
	}

	for(int i = 0; i < m_ba2.GetCount(); i++) {
		CBranchInfo *pBi = m_ba2.GetAt(i);
		int nItem = m_cmbCompany.AddString(pBi->strBranchName);
		m_cmbCompany.SetItemData(nItem, pBi->nCompanyCode); 
		if(m_nCompanyCode == pBi->nCompanyCode) 
			m_cmbCompany.SetCurSel(nItem);
	}

	if(m_cmbCompany.GetCount() <= 1 ) {
		m_stcCompany.ShowWindow(SW_HIDE);
		m_cmbCompany.ShowWindow(SW_HIDE);
		m_stcCross.ShowWindow(SW_SHOW);
		m_stcCross.SetWindowText("기사번호만 입력가능");
	}


	//RefreshList(m_nCompanyCode);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CAllocateDlg::InsertListData()
{
	if(m_rm.size() == 0)
		LF->FillVaildRiderData();

	char buffer[10];

	MAP_RIDER::iterator it;
	long nItem = 0;

	for(it = m_rm.begin(); it != m_rm.end(); it++)
	{
		if(it->second.nWorkState > 0)
			continue;

		CXTPGridRecord *pRecord = m_lstDuplicate.InsertItem(nItem, m_ci.GetBranchName(it->second.nCompany));
		m_lstDuplicate.SetItemText(nItem, 1, itoa(it->second.nRNo, buffer, 10));
		m_lstDuplicate.SetItemText(nItem, 2, it->second.strName);
		m_lstDuplicate.SetItemLong(nItem++, it->second.nCompany);
	}	

	m_lstDuplicate.Populate();
}

void CAllocateDlg::OnBnClickedOrderInsertBtn()
{
	BOOL bInsert = ((CButton*)GetDlgItem(IDC_ORDER_INSERT_CHECK))->GetCheck();
	AfxGetApp()->WriteProfileInt("AllocateDlg", "bInsert", bInsert);
}

void CAllocateDlg::OnBnClickedAllocateBtn()
{
	CXTPGridSelectedRows *pRows = m_lstDuplicate.GetSelectedRows();

	if(pRows == NULL)
	{
		MessageBox("기사님을 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	if(pRows->GetCount() == 0)
	{
		MessageBox("기사님을 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	CXTPGridRecord *pRecord = pRows->GetAt(0)->GetRecord();

	int nCompany = m_lstDuplicate.GetItemLong(pRecord);
	int nRNo = atoi(pRecord->GetItem(1)->GetCaption(NULL));
	CString sRName = pRecord->GetItem(2)->GetCaption(NULL);

	

	CString sTemp = "";
	sTemp.Format("%d번 [%s] 기사님에게 배차하시겠습니까?", nRNo, sRName);

	if(MessageBox(sTemp, "확인", MB_OKCANCEL) == IDOK)
	{
		if(m_bToRcpView == TRUE)
		{
			if(m_nState == STATE_RESERVED)
			{
				CCustomMyAfxMessgagebox dlg;
				long nRet = dlg.DoModal();

				if(dlg.m_nType == 0)
					m_pRcpView->GetStateChange()->ChangeItemStateAllocate(m_nTNo, nRNo, nCompany);
				else if(dlg.m_nType == 1)
				{
					LU->UpdateRiderInfoForReserveOrder(m_nTNo, nCompany, nRNo); 
					m_pRcpView->AllRefresh();
				}
			}
			else
			{
				m_pRcpView->GetStateChange()->ChangeItemStateAllocate(m_nTNo, nRNo, nCompany);
				//m_pRcpView->Allocate(m_nTNo, nRNo, m_nState, nCompany);
			}
		}
			
		else if(m_pParent != NULL)
		{
			ST_RIDER_WORK_STATE_INFO *pInfo = new ST_RIDER_WORK_STATE_INFO;
			pInfo->nCompany = nCompany;
			pInfo->nRNo = nRNo;
			pInfo->strName = sRName;
			pInfo->strPhone = LF->GetRiderPhone(pInfo->nCompany, pInfo->nRNo);

			BOOL bInsert = ((CButton*)GetDlgItem(IDC_ORDER_INSERT_CHECK))->GetCheck();
			m_pParent->SendMessage(WM_GET_ALLOCATE_RIDER, (WPARAM)pInfo, (LPARAM)bInsert);
		}
		OnOK();
	}
}

void CAllocateDlg::OnBnClickedCancelBtn()
{
	OnCancel();
}


void CAllocateDlg::RefreshList(long nAdminCode)
{
	CWaitCursor wait;
	int cnt = 0;
	char buffer[20];

	int nState, nRNo;
	BOOL bDoc;
	CString strStart;
	CString strDest;
	COleDateTime dtFirst, dtLast;
	CString strRName, strTel;
	long nEarnning, nEarnningPer;
	long nCount;

	m_List.DeleteAllItems();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_dorder_rider_for_allocate_2011");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nAdminCode);

	if(!pRs.Execute(&pCmd)) return;
	pRs.SetSort("dtLast", TRUE);

	for(cnt = 0; cnt < pRs.GetRecordCount(); cnt++)
	{
		pRs.GetFieldValue("nRNo", nRNo);
		pRs.GetFieldValue("sStart", strStart);
		pRs.GetFieldValue("sDest", strDest);
		pRs.GetFieldValue("bDoc", bDoc);
		pRs.GetFieldValue("dtFirst", dtFirst);
		pRs.GetFieldValue("dtLast", dtLast);
		pRs.GetFieldValue("sName", strRName);
		pRs.GetFieldValue("sTel", strTel);
		pRs.GetFieldValue("nCount", nCount);
		pRs.GetFieldValue("nEarnning", nEarnning);
		pRs.GetFieldValue("nEarnningPer", nEarnningPer);
		pRs.GetFieldValue("nState", nState);
		
		m_List.InsertItem(cnt, ltoa(nRNo, buffer, 10), LF->GetImageNumber(nState)); 
		m_List.SetItemText(cnt, 1, strStart);
		m_List.SetItemText(cnt, 2, strDest);
		m_List.SetItemText(cnt, 3, dtFirst.Format("%H:%M:%S"));
		m_List.SetItemText(cnt, 4, dtLast.Format("%H:%M:%S"));
		m_List.SetItemText(cnt, 5, bDoc ? "왕복" : "");
		m_List.SetItemText(cnt, 6, strRName);
		m_List.SetItemText(cnt, 7, LF->GetDashPhoneNumber(strTel));
		m_List.SetItemText(cnt, 8, ltoa(nCount, buffer, 10));
		m_List.SetItemText(cnt, 9, LF->GetMyNumberFormat(ltoa(nEarnning, buffer, 10)));
		m_List.SetItemText(cnt, 10, LF->GetMyNumberFormat(ltoa(nEarnningPer, buffer, 10)));

		pRs.MoveNext();    
	}

//	m_stcRiderCount.SetWindowText(ltoa(pRs.GetRecordCount(), buffer, 10));
	pRs.Close();
}


void CAllocateDlg::OnBnClickedRefreshBtn()
{
	RefreshList((long)m_cmbCompany.GetItemData(m_cmbCompany.GetCurSel()));
}

void CAllocateDlg::OnCbnSelchangeCompanyCombo()
{
	OnBnClickedRefreshBtn();
}



void CAllocateDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nItem;

	if((nItem = m_List.GetNextItem(-1, LVNI_SELECTED)) < 0) 
		return;

	m_edtRNo.SetWindowText(m_List.GetItemText(nItem, 0));
	*pResult = 0;
}

void CAllocateDlg::OnNMDblclkDuplicateList(NMHDR *pNMHDR, LRESULT *pResult)
{
	CXTPGridSelectedRows *pRows = m_lstDuplicate.GetSelectedRows();

	if(pRows == NULL) 
		MessageBox("기사님을 선택하세요", "확인", MB_ICONINFORMATION);

	m_pSelRecord = pRows->GetAt(0)->GetRecord();
	OnBnClickedAllocateBtn();
}

BOOL CAllocateDlg::DestroyWindow()
{
	/*
	for(int i=0;i<m_lstDuplicate.GetItemCount(); i++)
	{
		ALLOCATE_RIDER_INFO *ari= NULL;
		ari = (ALLOCATE_RIDER_INFO*)m_lstDuplicate.GetItemData(i);
		if(ari != NULL)
		{
			delete ari;
			ari = NULL;
		}
	}
	*/
	return CMyDialog::DestroyWindow();
}

void CAllocateDlg::OnLvnDeleteitemDuplicateList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	
	ALLOCATE_RIDER_INFO *ari= NULL;
	ari = (ALLOCATE_RIDER_INFO*)m_lstDuplicate.GetItemData(pNMLV->iItem);

	if(ari != NULL)
	{
		delete ari;
		ari = NULL;
	}
	 
	*pResult = 0;
}

void CAllocateDlg::OnEnChangeRnoEdit()
{
	if(m_rm.size() == 0)
	{
		LF->FillVaildRiderData();
	}

	int nSynonyNotSearchCheck = AfxGetApp()->GetProfileInt("AllocateDlg", "SynonyNotSearch", 0);

	BOOL bFirst = TRUE;

	CString sSearch; m_edtRNo.GetWindowText(sSearch);
	CXTPGridRecords *pRecords = m_lstDuplicate.GetRecords(); 

	long nLength = sSearch.GetLength(); 

	for(int i=0; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);

		if(nLength == 0)
		{
			pRecord->SetVisible(TRUE);
			continue;
		}


		CString sRNo = pRecord->GetItem(1)->GetCaption(NULL);
		CString sRName = pRecord->GetItem(2)->GetCaption(NULL);

		if( !nSynonyNotSearchCheck )
		{

			if( sRName.Find(  sSearch) >= 0 ||  	(sRNo.Find(  sSearch) >= 0  && sRNo.Mid(0, nLength ) == sSearch.Mid(0,nLength )) )				
			{				
				pRecord->SetVisible(TRUE);

				if(bFirst)
					m_pSelRecord = pRecord;
			}
			else
				pRecord->SetVisible(FALSE);
		}
		else
		{
			if( sRName ==   sSearch  ||  sRNo ==    sSearch )
			{
				pRecord->SetVisible(TRUE);

				if(bFirst)
					m_pSelRecord = pRecord;
			}
			else
				pRecord->SetVisible(FALSE);

		}
	}

	m_lstDuplicate.Populate();
}

BOOL CAllocateDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_RETURN) 
		{
			if(pMsg->hwnd == m_lstDuplicate.GetSafeHwnd() ||
				pMsg->hwnd == m_edtRNo.GetSafeHwnd())
				OnBnClickedAllocateBtn();

			return TRUE;
		}
	}

	return CMyDialog::PreTranslateMessage(pMsg);
}

void CAllocateDlg::OnCancel()
{
	LU->GetRcpView()->SetRefreshStart();
	CMyDialog::OnCancel();
}

void CAllocateDlg::OnOK()
{
	LU->GetRcpView()->SetRefreshStart();

	CDelayOrderDlg2 *pDlg = LU->GetDelayOrderPane();
	if(pDlg->m_RcpReport->GetSafeHwnd() != NULL)
		pDlg->SendMessage(WM_REFRESH_DELAY_ORDER, 0, 0);
	CMyDialog::OnOK();
}
