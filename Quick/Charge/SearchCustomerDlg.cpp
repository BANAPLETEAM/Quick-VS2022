// SearchGroupDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "SearchCustomerDlg.h"

#define ST_TEL_MOBILE  2
#define ST_COMPANY_NAMET  0
#define ST_NAME_DEPART  12


// CSearchGroupDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSearchCustomerDlg, CMyDialog)
CSearchCustomerDlg::CSearchCustomerDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(CSearchCustomerDlg::IDD, pParent)
{
	m_nCompany = 0;	
	m_strCNoList = "";
	m_strReturnCustomer = "";
	m_strReturnTel = "";
	m_strReturnDept = "";
	m_strReturnName = "";	
	m_strReturnHP = "";

	m_nReturnCNo = 0;
	m_nReturnMemCNo = 0;
	m_bTypeCustomerChange = FALSE;
}

CSearchCustomerDlg::~CSearchCustomerDlg()
{ 
}

void CSearchCustomerDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SEARCH_NAME_EDIT, m_edtSearchName);
	DDX_Control(pDX, IDC_TYPE_COMBO, m_cmbSearchType);
	DDX_Control(pDX, IDC_CUSTOM1, m_lstSearch);
	DDX_Control(pDX, IDC_HISTORY_CHARGE_INPUT_BTN, m_btnHistoryChargeInput);
}


BEGIN_MESSAGE_MAP(CSearchCustomerDlg, CMyDialog)
	ON_BN_CLICKED(IDC_SEARCH_BTN, &CSearchCustomerDlg::OnBnClickedSearchBtn)

	ON_BN_CLICKED(IDC_HISTORY_CHARGE_INPUT_BTN, &CSearchCustomerDlg::OnBnClickedHistoryChargeInputBtn)
	ON_BN_CLICKED(IDC_SELECT_CUSTOMER_BTN, &CSearchCustomerDlg::OnBnClickedSelectCustomerBtn)
	ON_NOTIFY(NM_DBLCLK, IDC_CUSTOM1, OnNMDblClkList)
END_MESSAGE_MAP()




BOOL CSearchCustomerDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	m_cmbSearchType.SetCurSel(0);
	m_edtSearchName.SetFocus();

	m_lstSearch.MyAddItem(0,"", "회사명", 100, FALSE, DT_LEFT);
	m_lstSearch.MyAddItem(1,"", "부서명", 60, FALSE, DT_LEFT);
	m_lstSearch.MyAddItem(2,"", "담당자", 60, FALSE, DT_LEFT);
	m_lstSearch.MyAddItem(3,"", "대표번호", 80, FALSE, DT_LEFT);
	m_lstSearch.MyAddItem(4,"", "휴대폰", 80, FALSE, DT_LEFT);
	m_lstSearch.MyAddItem(5,"", "해당동", 60, FALSE, DT_LEFT);		
	m_lstSearch.MyAddItem(6,"", "개별요금명", 100 , FALSE, DT_LEFT);
	m_lstSearch.MyAddItem(7,"", "그룹명", 70 , FALSE, DT_LEFT);
	m_lstSearch.MyAddItem(8,"", "등록일", 90, FALSE, DT_LEFT);
	m_lstSearch.EndItem();
	m_lstSearch.m_bHeader = TRUE;
	m_lstSearch.Populate();
	
	if(m_bTypeCustomerChange)
	{
		m_btnHistoryChargeInput.ShowWindow(SW_HIDE);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
void CSearchCustomerDlg::Apply()
{
	if(m_lstSearch.GetSelectedCount() <= 0)
	{
		MessageBox("한행이라도 선택하여 주세요", "확인", MB_ICONINFORMATION);
		return;
	}


	if(MessageBox("해당 고객들을 개별요금으로 편입하시겠습니까?", "확인", MB_YESNO) == IDNO)
		return;	

	CString sCNo = "", sTotalCNo = "";
	for(int i =0; i < m_lstSearch.GetSelectedCount(); i++)
	{
		CMyXTPGridRecord *pRecord = m_lstSearch.GetSelectedRecord(i);
		long nCNo = pRecord->GetItemDataLong();
		sCNo.Format("%ld", nCNo);
		sTotalCNo += sCNo + ",";

	}
	m_strCNoList = sTotalCNo;
	OnOK();
}

void CSearchCustomerDlg::OnNMDblClkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	XTP_NM_REPORTRECORDITEM* pNMListView = (XTP_NM_REPORTRECORDITEM*)pNMHDR;

	if (!pNMListView->pRow || !pNMListView->pColumn)
		return;

	ChangeCustomer();		
}

void CSearchCustomerDlg::OnBnClickedSelectCustomerBtn()
{
	ChangeCustomer();
}
void CSearchCustomerDlg::ChangeCustomer()
{
	if(m_lstSearch.GetSelectedCount() <= 0)
	{
		MessageBox("한행이라도 선택하여 주세요", "확인", MB_ICONINFORMATION);
		return;
	}

	CMyXTPGridRecord *pRecord = m_lstSearch.GetSelectedRecord(0);
	m_strReturnCustomer = pRecord->GetItemSValue(0);
	m_strReturnDept = pRecord->GetItemSValue(1);
	m_strReturnName = pRecord->GetItemSValue(2);
	m_strReturnTel = pRecord->GetItemSValue(2);
	m_strReturnHP = pRecord->GetItemSValue(4);
	m_nReturnMemCNo = pRecord->GetItemDataLong2();	
	m_nReturnCNo = pRecord->GetItemDataLong();	

	OnOK();
}



void CSearchCustomerDlg::OnBnClickedSearchBtn()
{
	CString strSearchData = "";
	m_edtSearchName.GetWindowText(strSearchData);
	int nSearchType = -1;

	switch(m_cmbSearchType.GetCurSel())
	{
		// 상호명;전화번호;담당자;
	case 0:
		nSearchType = ST_TEL_MOBILE;
		break;
	case 1:
		nSearchType = ST_COMPANY_NAMET;
		break;
	case 2:
		nSearchType = ST_NAME_DEPART;
		break;
	}
	if(m_lstSearch.GetRecords()->GetCount() > 0)
		m_lstSearch.DeleteAllItem();

	LU->LoadMemberCharge();
	MAP_MEMBER_CHARGE_CNO::iterator itMem;

	CMkRecordset pRs2(m_pMkDb);
	CMkCommand pCmd2(m_pMkDb, "search_customer_new13");	
	pCmd2.AddParameter(nSearchType);			
	pCmd2.AddParameter(m_nCompany);			
	pCmd2.AddParameter(strSearchData);
	pCmd2.AddParameter(FALSE);

	if(pRs2.Execute(&pCmd2))
	{		
		for(int i = 0; i < pRs2.GetRecordCount(); i++)
		{
			long nCNo, nCompany, nMemCNo, nGNo ;
			CString strCompany, strDepart, strName, strDong, strTel1, strMobile, strGroupName = "", strHistoryChargeName = "";
			COleDateTime dtRegister;
			
			pRs2.GetFieldValue("nCNo", nCNo);
			pRs2.GetFieldValue("nCompany", nCompany);
			pRs2.GetFieldValue("sCompany", strCompany);
			pRs2.GetFieldValue("sDepart", strDepart);
			pRs2.GetFieldValue("sName", strName);
			pRs2.GetFieldValue("sTel1", strTel1);
			pRs2.GetFieldValue("sMobile", strMobile);
			pRs2.GetFieldValue("sDong", strDong);
			pRs2.GetFieldValue("dtRegister", dtRegister);
			pRs2.GetFieldValue("nCustDisplayCharge", nMemCNo);
			pRs2.GetFieldValue("nGNo", nGNo);
			pRs2.GetFieldValue("sMemCompany", strHistoryChargeName);

			//itMem = m_mapMemberCharge.find(nMemCNo);
			//if(itMem != m_mapMemberCharge.end())
			//	strHistoryChargeName = (*itMem).second->strMemCompany;

			strGroupName = m_cg.GetGroupData(nGNo)->strGroupName;

			m_lstSearch.MyAddItem(0, strCompany, "회사명", 100, FALSE, DT_LEFT);
			m_lstSearch.MyAddItem(1, strDepart, "부서명", 60, FALSE, DT_LEFT);
			m_lstSearch.MyAddItem(2, strName, "담당자", 60, FALSE, DT_LEFT);
			m_lstSearch.MyAddItem(3, LF->GetDashPhoneNumber(strTel1), "대표번호", 80, FALSE, DT_LEFT);
			m_lstSearch.MyAddItem(4, LF->GetDashPhoneNumber(strMobile), "휴대폰", 80, FALSE, DT_LEFT);
			m_lstSearch.MyAddItem(5, strDong, "해당동", 60, FALSE, DT_LEFT);		
			m_lstSearch.MyAddItem(6, strHistoryChargeName, "개별요금명", 100 , FALSE, DT_LEFT);
			m_lstSearch.MyAddItem(7, strGroupName, "그룹명", 75 , FALSE, DT_LEFT);
			m_lstSearch.MyAddItem(8, dtRegister.Format("%Y-%m-%d"), "등록일", 85, FALSE, DT_LEFT);
			m_lstSearch.InsertItemDataLong(nCNo);		
			m_lstSearch.InsertItemDataLong2(nMemCNo);		

			m_lstSearch.EndItem();

			pRs2.MoveNext();	
		}
		
	}
	pRs2.Close();
	m_lstSearch.Populate();	
}


BOOL CSearchCustomerDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_RETURN) 
		{
			if(pMsg->hwnd == m_edtSearchName.GetSafeHwnd())
				OnBnClickedSearchBtn();

			return TRUE;
		}

	}
	
	return CMyDialog::PreTranslateMessage(pMsg);
}

void CSearchCustomerDlg::OnBnClickedHistoryChargeInputBtn()
{
	Apply();
}

