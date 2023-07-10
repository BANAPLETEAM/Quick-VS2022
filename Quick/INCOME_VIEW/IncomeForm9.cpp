// Report4.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "IncomeForm9.h"
#include "Excel.h"
#include "VRRiderLogListDlg.h"
#include "CompanyBranchListDlg1.h"
#include "RcpView.h"
#include "IncomeView.h"

#define ID_BRANCH 10
#define ID_BRANCH_INTEGRATED 100
IMPLEMENT_DYNCREATE(CIncomeForm9, CMyFormView)
CIncomeForm9::CIncomeForm9()
: CMyFormView(CIncomeForm9::IDD)
, m_nSMSAmount(0)

, m_sSaveUseAmount(_T(""))
, m_sRecoveryAmount(_T(""))
{


}

CIncomeForm9::~CIncomeForm9()
{



}

void CIncomeForm9::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_REPORT, m_BaranchList);
	DDX_Control(pDX, IDC_LIST_REPORT2, m_SaveList);
	DDX_Control(pDX, IDC_NOACCOUNT_LIST3, m_NoAccountList);	
	DDX_Control(pDX, IDC_BRANCH_COMBO, m_cmbBranch);
	DDX_Control(pDX, IDC_SMS_SAVE_BUTTON, m_btnSMSSave);
	DDX_Control(pDX, IDC_SAVE_RECOVER_COMBO, m_cmbSaveRecovery);
	DDX_Text(pDX, IDC_SMS_AMOUNT_EDIT, m_nSMSAmount);
	DDV_MinMaxInt(pDX, m_nSMSAmount, 0, 1000000);

	DDX_Text(pDX, IDC_SAVE_USE_AMOUNT_STATIC, m_sSaveUseAmount);
	DDX_Text(pDX, IDC_RECOVERY_AMOUNT_STATIC, m_sRecoveryAmount);
	DDX_Control(pDX, IDC_REFRESH_BTN, m_RefreshBtn);
	DDX_Control(pDX, IDC_SMS_AMOUNT_EDIT, m_edtSMSAmount);

	DDX_Control(pDX, IDC_SERACH_EDIT, m_SearchEdt);
	//DDX_Control(pDX, IDC_ACCOUNT_OWNER_COMBO, m_cmbAccountOwner);
}


BEGIN_MESSAGE_MAP(CIncomeForm9, CMyFormView)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_COMMAND(ID_BRANCH, OnBranchAllot)
	ON_COMMAND(ID_BRANCH_INTEGRATED, OnBranchRecovery)

	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_BN_CLICKED(IDC_SMS_SAVE_BUTTON, OnBnClickedSmsSaveButton)
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_BRANCH_COMBO, OnCbnSelchangeBranchCombo)
	ON_BN_CLICKED(IDC_AUTO_ALLOT_BTN, OnBnClickedAutoAllotBtn)
	ON_BN_CLICKED(IDC_CHOICE_ALLOT_BTN, OnBnClickedChoiceAllotBtn)
	ON_BN_CLICKED(IDC_RECOVERT_BTN, OnBnClickedRecovertBtn)
	ON_BN_CLICKED(IDC_LOG_BTN, OnBnClickedLogBtn)
	ON_EN_CHANGE(IDC_SERACH_EDIT, OnEnChangeSerachEdit)
	ON_NOTIFY(HDN_ITEMCLICK, 0, OnHdnItemclickListReport2)
	ON_NOTIFY(NM_RCLICK, IDC_NOACCOUNT_LIST3, OnNMRclickNoaccountList)
END_MESSAGE_MAP()


// CIncomeForm9 메시지 처리기입니다.

void CIncomeForm9::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	m_BaranchList.InsertColumn(0,"소속",LVCFMT_LEFT,80);
	m_BaranchList.InsertColumn(1,"사용",LVCFMT_RIGHT, 45);
	m_BaranchList.InsertColumn(2,"미사용",LVCFMT_RIGHT, 55);
	m_BaranchList.InsertColumn(3,"구분",LVCFMT_LEFT, 55);
	m_BaranchList.Populate();

	m_SaveList.InsertColumn(0,"소속",LVCFMT_LEFT,75);
	m_SaveList.InsertColumn(1,"사번",LVCFMT_RIGHT, 40);
	m_SaveList.InsertColumn(2,"성명",LVCFMT_LEFT, 60);
	m_SaveList.InsertColumn(3,"계좌",LVCFMT_LEFT, 120);
	m_SaveList.InsertColumn(4,"등록일",LVCFMT_CENTER, 80);
	m_SaveList.InsertColumn(5,"작업자",LVCFMT_RIGHT, 60);
	m_SaveList.InsertColumn(6,"은행",LVCFMT_RIGHT, 70);
	m_SaveList.InsertColumn(7,"예금주",LVCFMT_RIGHT, 70);
	m_SaveList.InsertColumn(8,"기타",LVCFMT_LEFT, 80);
	m_SaveList.Populate();

	m_NoAccountList.InsertColumn(0,"No",LVCFMT_LEFT,35);
	m_NoAccountList.InsertColumn(1,"남은계좌",LVCFMT_LEFT,100);
	m_NoAccountList.InsertColumn(2,"은행",LVCFMT_LEFT,50);
	m_NoAccountList.InsertColumn(3,"예금주",LVCFMT_LEFT,60);	
	m_NoAccountList.InsertColumn(4,"기타",LVCFMT_LEFT,80);
	m_NoAccountList.Populate();


	SetResize(IDC_NOACCOUNT_LIST3, sizingRightBottom);
	SetResize(IDC_LIST_REPORT, sizingBottom);
	SetResize(IDC_LIST_REPORT2, sizingBottom);


	//RefreshList();
	m_edtSMSAmount.SetFocus();

}
void CIncomeForm9::RefreshList()
{
	CMyFormView::RefreshList();

	InitControl();	
	NoAccountList();
	AccountList();	
}	
void CIncomeForm9::BranchComboReset()
{
	for(int i = 0; i < m_cmbBranch.GetCount(); i++)
	{
		ST_RIDER_ACCOUNT_SIMPLE *pRiderAC = (ST_RIDER_ACCOUNT_SIMPLE *)m_cmbBranch.GetItemData(i);
		if(pRiderAC)
			delete pRiderAC;
	}
	m_cmbBranch.ResetContent();
}

void CIncomeForm9::InitControl()
{

	if(m_cmbBranch.GetCount() > 0)
		BranchComboReset();


	m_BaranchList.DeleteAllItems();	

	//CWaitCursor wait;dem
	UpdateData(TRUE);	
	CMkRecordset pRs(m_pMkDb);	
	CMkCommand pCmd(m_pMkDb, "select_vraccount_rider_count");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), LF->GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), LF->GetCurBranchInfo()->bIntegrated );	

	if(!pRs.Execute(&pCmd)) return;
	long nCompany = 0,nUseCount = 0, nNoUseCount = 0,nCount=0;
	CString sBranchName = "",sType = "";
	long nOwnerCompany =0, nOriginalOwnerCompany =0, nTotUseCount =0, nTotNoUseCount = 0;
	while(!pRs.IsEOF())
	{
		pRs.GetFieldValue("nCompany", nCompany);
		pRs.GetFieldValue("sBranchName", sBranchName);
		pRs.GetFieldValue("nUseCount", nUseCount);
		pRs.GetFieldValue("nNoUseCount", nNoUseCount);
		pRs.GetFieldValue("nOwnerCompany", nOwnerCompany);

		if (nOwnerCompany != -1)		
			nOriginalOwnerCompany = nOwnerCompany;


		ST_RIDER_ACCOUNT_SIMPLE *pRiderAC = new ST_RIDER_ACCOUNT_SIMPLE;
		pRiderAC->nCompany = nCompany;
		pRiderAC->nUseCount = nUseCount;
		pRiderAC->nNoUseCount = nNoUseCount;
		pRiderAC->nOwnerCompany = nOriginalOwnerCompany;

		m_cmbBranch.InsertString(nCount, sBranchName);
		m_cmbBranch.SetItemData(nCount,(DWORD_PTR)pRiderAC);

		if(nCompany == nOriginalOwnerCompany)
			sType = "본사";
		else
			sType = "지사";

		m_BaranchList.InsertItem(nCount, sBranchName);
		m_BaranchList.SetItemText(nCount, 1, LF->GetMyNumberFormat(nUseCount));
		m_BaranchList.SetItemText(nCount, 2, LF->GetMyNumberFormat(nNoUseCount));
		m_BaranchList.SetItemText(nCount, 3, sType);

		nTotUseCount += nUseCount;
		nTotNoUseCount += nNoUseCount;
		nCount++;
		pRs.MoveNext();
	}
	nCount++;
	pRs.Close();

	m_BaranchList.InsertItem(--nCount, "합계");
	m_BaranchList.SetItemText(nCount, 1, LF->GetMyNumberFormat(nTotUseCount));
	m_BaranchList.SetItemText(nCount, 2, LF->GetMyNumberFormat(nTotNoUseCount));

	m_sSaveUseAmount = "";
	m_sRecoveryAmount = "";


	if(LF->GetCurBranchInfo()->bIntegrated == 0)  //지사인경우 선택
	{
		m_cmbBranch.SetCurSel(0);	
		OnCbnSelchangeBranchCombo();
	}

	m_cmbSaveRecovery.SetCurSel(0);
	m_BaranchList.Populate();

}

void CIncomeForm9::NoAccountList()
{

	m_NoAccountList.DeleteAllItems();	


	UpdateData(TRUE);		

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_vraccount_rider_noaccount_list");	
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), LF->GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), LF->GetCurBranchInfo()->bIntegrated);

	if(!pRs.Execute(&pCmd)) return;

	int nIndex = 0;
	CString sAccount, sBankCode,sEtc, sAccountOwner;
	int nCompany = 0, nRNo =0;
	char buffer[10];
	while(!pRs.IsEOF())
	{
		int nCol = 1;
		pRs.GetFieldValue("Account", sAccount);
		pRs.GetFieldValue("nCompany", nCompany);	
		pRs.GetFieldValue("BankCode", sBankCode);
		pRs.GetFieldValue("sEtc", sEtc);
		pRs.GetFieldValue("sAccountOwner", sAccountOwner);

		m_NoAccountList.InsertItem(nIndex, itoa(nIndex + 1,buffer,10));
		m_NoAccountList.SetItemText(nIndex, 1,sAccount);
		m_NoAccountList.SetItemText(nIndex, 2,sBankCode);
		m_NoAccountList.SetItemText(nIndex, 3,sAccountOwner);
		m_NoAccountList.SetItemText(nIndex, 4,sEtc);
		m_NoAccountList.SetItemDataText(nIndex, sAccount);
		//m_NoAccountList.EndItem();
		nIndex++;

		pRs.MoveNext();
	}	

	pRs.Close(); 	
	m_NoAccountList.Populate();

}	

void CIncomeForm9::AccountList()
{

	m_SaveList.DeleteAllItems();	


	UpdateData(TRUE);		

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_vraccount_rider_allotment");	
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), LF->GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), LF->GetCurBranchInfo()->bIntegrated);

	if(!pRs.Execute(&pCmd)) return;

	COleDateTime dtRegister;

	int nIndex = 0;

	CString sBranchName, sWID, sName,sAccount, sAccountOwner,sEtc, sBankCode;
	int nCompany = 0, nRNo =0;
	char buffer[10];
	while(!pRs.IsEOF())
	{
		int nCol = 1;
		pRs.GetFieldValue("sBranchName", sBranchName);
		pRs.GetFieldValue("nRNo", nRNo);
		pRs.GetFieldValue("sName", sName);
		pRs.GetFieldValue("sAccount", sAccount);
		pRs.GetFieldValue("dtRegister", dtRegister);
		pRs.GetFieldValue("sWID", sWID);			
		pRs.GetFieldValue("nCompany", nCompany);	
		pRs.GetFieldValue("BankCode", sBankCode);	
		pRs.GetFieldValue("sAccountOwner", sAccountOwner);	

		m_SaveList.InsertItem(nIndex,  sBranchName);
		m_SaveList.SetItemText(nIndex, 1, itoa(nRNo,buffer,10) );
		m_SaveList.SetItemText(nIndex, 2, sName);
		m_SaveList.SetItemText(nIndex, 3, sAccount);		
		m_SaveList.SetItemText(nIndex, 4, dtRegister.Format("%y-%m-%d"));
		m_SaveList.SetItemText(nIndex, 5, sWID);
		m_SaveList.SetItemText(nIndex, 6, sBankCode);
		m_SaveList.SetItemText(nIndex, 7, sAccountOwner);
		m_SaveList.SetItemText(nIndex, 8, sEtc);
		m_SaveList.SetItemData(nIndex,(DWORD_PTR)nCompany);
		m_SaveList.SetItemLong(nIndex, nCompany);
		m_SaveList.SetItemLong2(nIndex, nRNo);
		m_SaveList.SetItemDataText(nIndex, sAccount);
		//m_SaveList.EndItem();
		nIndex++;
		pRs.MoveNext();
	}	

	m_SaveList.Populate();
}	


void CIncomeForm9::OnBnClickedRefreshBtn()
{
	RefreshList();
}



void CIncomeForm9::OnContextMenu(CWnd* pWnd, CPoint point)
{
	try
	{
		CRect rect, rectNoAccountList;
		m_SaveList.GetWindowRect(&rect);
		m_NoAccountList.GetWindowRect(rectNoAccountList);

		CMenu rMenu;
		rMenu.LoadMenu(IDR_CONTEXT_MENU);
		CMenu *pRMenu=rMenu.GetSubMenu(2);
		if(rect.PtInRect(point))
		{

			pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
		}
		else if(rectNoAccountList.PtInRect(point))
		{
			if(m_ba.GetCount() <= 1)
				throw("통합사이트에서만이 작업이 가능합니다.");

			long nIntegrationCode = 0;
			

			CBranchInfo * pBi = NULL;
			pBi = m_ba.GetAt(0);
			

			/*
			if(m_NoAccountList.GetSelectedRows()->GetCount() <= 0)
			throw("계좌가 1개이상이라도 선택 되어져야 합니다.");
			*/


			if(pBi->nCompanyCode == LF->GetCurBranchInfo()->nCompanyCode 
				&& !LF->GetCurBranchInfo()->bIntegrated )
			{
				pRMenu->AppendMenu(MF_STRING,ID_BRANCH,"지사 할당");			
			}
			else
			{
				pRMenu->AppendMenu(MF_STRING,ID_BRANCH_INTEGRATED,  "본사 회수");
			}

			pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
		}
	}
	catch (char* e)
	{
		MessageBox(e, "확인", MB_ICONINFORMATION);
	}




}

void CIncomeForm9::OnViewExcel()
{
	if(!LF->POWER_CHECK(3900, "정산 엑셀변환", TRUE))
		return;

	LF->AddSecurityLog(LF->GetCurBranchInfo()->nDOrderTable, 506, m_SaveList.GetItemCount());  
	CMyExcel::ToExcel(&m_SaveList);
}

void CIncomeForm9::OnBranchAllot()
{	
	return;
	/*
	try
	{
		UINT uNoAcoountSelectedCount = 0;
		int  nNoAccountItem = -1;
		long nResult = 0;
		CString sAccount = "";	
		CRcpView* pView = (CRcpView*)((CIncomeView*)GetOwner())->GetParent();// >GetRcpView();			 

		if(LF->GetCurBranchInfo()->bIntegrated == 1 )
			throw("통합에서는 지원되지 않고 지사를 선택하시고 작업하세요");

		CCompanyBranchListDlg1 dlg((CRcpView*) this);
		dlg.m_bPublicDialog = TRUE;
		dlg.DoModal();


		CBranchInfo* pBi = (CBranchInfo*)m_ba.GetAt(0);
		if(dlg.m_nBnClickCompany == 0)
			return;

		if(dlg.m_nBnClickCompany == pBi->nCompanyCode)
			throw("통합및 자기자신은 계좌를 할당할수가 없습니다.", "확인", MB_ICONINFORMATION);		


		if(uNoAcoountSelectedCount > 0)
		{			
			for (int i = 0;i < uNoAcoountSelectedCount; i++)
			{	 

				nNoAccountItem = m_NoAccountList.GetNextItem(nNoAccountItem, LVNI_SELECTED);
				if(nNoAccountItem < 0) break;

				sAccount = m_NoAccountList.GetItemText(nNoAccountItem,1);

				CMkRecordset pRs(m_pMkDb);
				CMkCommand pCmd(m_pMkDb, "insert_vraccount_personal_save_recovery");
				pCmd.AddParameter(typeLong, typeInput, sizeof(long), pBi->nCompanyCode );
				pCmd.AddParameter(typeLong, typeInput, sizeof(long), dlg.m_nBnClickCompany );
				pCmd.AddParameter(typeString, typeInput, sAccount.GetLength(), sAccount);			
				pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), FALSE);			
				pCmd.AddParameter(typeString, typeInput, m_ui.strID.GetLength(), m_ui.strID);				
				pCmd.AddParameter(typeInt, typeInput, sizeof(int), m_ui.nCompany );
				CMkParameter *parRet = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), nResult);

				if(pRs.Execute(&pCmd))
				{	
					parRet->GetValue(nResult);

					if(nResult == -1)
						throw("등록이 실패하였습니다 계좌수를 다시 확인해보세요");
					if(nResult == 10)
						throw("계좌수가 변동되어 있거나 계좌가 부족합니다. 계좌수를 다시 확인해보세요");
					else if(nResult == 20)
					{
						continue;
					}
				}
			}
			RefreshList();
			throw("정상 처리되었습니다.");

		}

	}	
	catch(char *szMsg)
	{
		MessageBox(szMsg,"확인",MB_ICONINFORMATION);

	}
	*/
}

void CIncomeForm9::OnBranchRecovery()
{
	try
	{
		UINT uNoAcoountSelectedCount = 0; /*m_NoAccountList.GetSelectedRows()->GetCount();*/
		int  nNoAccountItem = -1;
		long nResult = 0;
		CString sAccount = "";	


		if(LF->GetCurBranchInfo()->bIntegrated == 1 )
			throw("통합에서는 지원되지 않고 지사를 선택하시고 작업하세요");





		CBranchInfo* pBi = (CBranchInfo*)m_ba.GetAt(0);


		if(LF->GetCurBranchInfo()->nCompanyCode == pBi->nCompanyCode)
			throw("통합및 자기자신은 계좌를 회수할 수가 없습니다.", "확인", MB_ICONINFORMATION);		


		if(uNoAcoountSelectedCount > 0)
		{			
			for (int i = 0;i < uNoAcoountSelectedCount; i++)
			{	 

				nNoAccountItem = m_NoAccountList.GetNextItem(nNoAccountItem, LVNI_SELECTED);
				if(nNoAccountItem < 0) break;

				sAccount = m_NoAccountList.GetItemText(nNoAccountItem,1);

				CMkRecordset pRs(m_pMkDb);
				CMkCommand pCmd(m_pMkDb, "insert_vraccount_personal_save_recovery");
				pCmd.AddParameter(typeLong, typeInput, sizeof(long), LF->GetCurBranchInfo()->nCompanyCode  );
				pCmd.AddParameter(typeLong, typeInput, sizeof(long), pBi->nCompanyCode);
				pCmd.AddParameter(typeString, typeInput, sAccount.GetLength(), sAccount);			
				pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), TRUE);			
				pCmd.AddParameter(typeString, typeInput, m_ui.strID.GetLength(), m_ui.strID);				
				pCmd.AddParameter(typeInt, typeInput, sizeof(int), m_ui.nCompany );
				CMkParameter *parRet = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), nResult);

				if(pRs.Execute(&pCmd))
				{	
					parRet->GetValue(nResult);

					if(nResult == -1)
						throw("등록이 실패하였습니다 계좌수를 다시 확인해보세요");
					if(nResult == 10)
						throw("계좌수가 변동되어 있거나 계좌가 부족합니다. 계좌수를 다시 확인해보세요");
					else if(nResult == 20)
					{
						//MessageBox("정상 처리되었습니다.", "확인",MB_ICONINFORMATION);
						//RefreshList();
						continue;
					}
				}

			}
			RefreshList();
			throw("정상 처리되었습니다.");

		}
		/*

		long nResult = 0;
		CBranchInfo* pBi = (CBranchInfo*)m_ba.GetAt(0);


		if(LF->GetCurBranchInfo()->bIntegrated == 1 )
		throw("통합에서는 지원되지 않고 지사를 선택하시고 작업하세요");
		UINT nSelectedCount = m_NoAccountList.GetSelectedRows()->GetCount();

		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "insert_vraccount_personal_save_recovery");
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), pBi->nCompanyCode );
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), LF->GetCurBranchInfo()->nCompanyCode );
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), (long)nSelectedCount);			
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), TRUE);			
		pCmd.AddParameter(typeString, typeInput, m_ui.strID.GetLength(), m_ui.strID);				
		pCmd.AddParameter(typeInt, typeInput, sizeof(int), m_ui.nCompany );
		CMkParameter *parRet = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), nResult);

		if(pRs.Execute(&pCmd))
		{	
		parRet->GetValue(nResult);

		if(nResult == -1)
		throw("등록이 실패하였습니다 계좌수를 다시 확인해보세요");
		if(nResult == 10)
		throw("계좌수가 변동되어 있거나 계좌가 부족합니다. 계좌수를 다시 확인해보세요");
		else if(nResult == 20)
		{
		MessageBox("정상 처리되었습니다.", "확인",MB_ICONINFORMATION);		
		RefreshList();
		}
		}
		*/
	}		
	catch(char *szMsg)
	{
		MessageBox(szMsg,"확인",MB_ICONINFORMATION);

	}	

}

void CIncomeForm9::OnBnClickedSmsSaveButton()
{
	try
	{
		UpdateData(TRUE);
		int nCurSel = m_cmbBranch.GetCurSel();
		if(nCurSel < 0 ) return;

		if(!LF->GetCurBranchInfo()->bIntegrated)
			return;
		if(m_nSMSAmount <= 0)
			throw("최소한 1개이상 되어야 합니다.");
		if(m_cmbBranch.GetCurSel() < 0 )
			throw("회사를 선택하여 주시기 바랍니다.");

		ST_RIDER_ACCOUNT_SIMPLE *pIntegratedRiderAccount = (ST_RIDER_ACCOUNT_SIMPLE*)m_cmbBranch.GetItemData(0);		
		ST_RIDER_ACCOUNT_SIMPLE *pCurRiderAccount = NULL;	
		pCurRiderAccount = (ST_RIDER_ACCOUNT_SIMPLE*)m_cmbBranch.GetItemData(nCurSel);

		if(	pIntegratedRiderAccount->nOwnerCompany != pCurRiderAccount->nOwnerCompany && 
			// 계좌의 소유회사와 지사의 소유회사가 같고
			pIntegratedRiderAccount->nCompany == pCurRiderAccount->nCompany &&
			// 본사만이 충전할 수있기에
			LF->GetCurBranchInfo()->bIntegrated 
			)		// 통합이야 하며
			throw("충전하실수 있는 회사가 아닙니다.");

		BOOL bSaveRecovery = FALSE;
		if(m_cmbSaveRecovery.GetCurSel() == 0)  // 충전이면
		{
			bSaveRecovery = FALSE;
			if(pIntegratedRiderAccount->nNoUseCount <= 0)
				throw("본사에 충전하실수 있는 계좌가 없습니다 계좌를 추가로 할당받으세요");
		}
		if(m_cmbSaveRecovery.GetCurSel() == 1) // 회수이면
		{
			bSaveRecovery = TRUE;
			if(pCurRiderAccount->nNoUseCount <= 0)
				throw("해당지사에 회수하실수 있는 계좌가 없습니다");
		}

		UpdateData();


		int nResult = -1;
		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "insert_vraccount_rider_save");
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), pIntegratedRiderAccount->nCompany );
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), pCurRiderAccount->nCompany );
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nSMSAmount);			
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), bSaveRecovery);			
		pCmd.AddParameter(typeString, typeInput, m_ui.strID.GetLength(), m_ui.strID);				
		pCmd.AddParameter(typeInt, typeInput, sizeof(int), m_ui.nCompany );
		CMkParameter *parRet = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), nResult);

		if(pRs.Execute(&pCmd))
		{	
			parRet->GetValue(nResult);

			if(nResult == -1)
				throw("등록이 실패하였습니다 계좌수를 다시 확인해보세요");

			if(nResult == 10)
				throw("계좌수가 변동되어 있거나 계좌가 부족합니다. 계좌수를 다시 확인해보세요");
			else if(nResult == 20)
				throw("정상 처리되었습니다.");			

		}
		else
			throw("등록이 실패하였습니다.");


		m_sSaveUseAmount = "";
		m_sRecoveryAmount = "";		



	}
	catch(char *szMsg)
	{
		MessageBox(szMsg,"확인",MB_ICONINFORMATION);
		RefreshList();
	}



}


void CIncomeForm9::OnCbnSelchangeBranchCombo()
{
	/*if(!LF->GetCurBranchInfo()->bIntegrated)
	{
	MessageBox("통합에서만이 작업이 가능합니다.","확인", MB_ICONINFORMATION);
	return;
	}*/
	UpdateData(TRUE);
	int nCurSel = m_cmbBranch.GetCurSel();

	if(nCurSel < 0 ) return;

	ST_RIDER_ACCOUNT_SIMPLE *pAccount = NULL; 
	ST_RIDER_ACCOUNT_SIMPLE *pIntegrationAccount = NULL;
	pAccount = (ST_RIDER_ACCOUNT_SIMPLE*)m_cmbBranch.GetItemData(nCurSel);
	pIntegrationAccount = (ST_RIDER_ACCOUNT_SIMPLE*)m_cmbBranch.GetItemData(0);


	if(LF->GetCurBranchInfo()->bIntegrated && pIntegrationAccount->nCompany == pAccount->nCompany)
	{
		m_btnSMSSave.EnableWindow(0);
		m_sSaveUseAmount = "";
		m_sRecoveryAmount = "";
	}
	else
	{
		m_btnSMSSave.EnableWindow(1);
		m_sSaveUseAmount.Format("본사 충전계좌수:%s",LF->GetMyNumberFormat(pIntegrationAccount->nNoUseCount));
		m_sRecoveryAmount.Format("지사 회수계좌수:%s", LF->GetMyNumberFormat(pAccount->nNoUseCount));
	}

	UpdateData(FALSE);
}

void CIncomeForm9::OnBnClickedAutoAllotBtn()
{ 

	if( LF->GetCurBranchInfo()->bVRAccountNoRider )
	{
		MessageBox("옵션에의해 기사 가상계좌 할당을 할 수 없습니다", "확인", MB_ICONINFORMATION);
		return;
	}	

	CXTPGridSelectedRows *pRows = m_SaveList.GetSelectedRows();
	CXTPGridRecord *pFirstRecord = m_SaveList.GetSelectedRows()->GetAt(0)->GetRecord();

	if(pFirstRecord == NULL)
	{
		MessageBox("자동할당 하실 기사님을 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}	

	UINT i, uSelectedCount = m_SaveList.GetSelectedRows()->GetCount();
	int  nItem = -1;

	CString sAccount = "";

	nItem = -1;


	for (i = 0;i < uSelectedCount; i++)
	{
		CXTPGridRecord *pRecord = (CXTPGridRecord *)m_SaveList.GetSelectedRows()->GetAt(i)->GetRecord();

		long nCompany = m_SaveList.GetItemLong(pRecord);
		int nRNo = m_SaveList.GetItemLong2(pRecord);

		if(nCompany <= 0)
			throw("회사코드가 오류입니다.");

		if(nRNo <= 0)
			throw("기사 번호가 없습니다.");

		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "select_vraccount_rider_auto_allot");	
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), nCompany);
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), nRNo);
		pCmd.AddParameter(typeString, typeInput, m_ui.strID.GetLength(), m_ui.strID);
		CMkParameter *pPar = pCmd.AddParameter(typeInt, typeOutput, sizeof(int), 0);

		if(!pRs.Execute(&pCmd)) return;

		int nParameter = 0;
		pPar->GetValue(nParameter);

		if(nParameter == 100)
			throw("계좌가 없습니다");
		if(nParameter == 200)
			throw("해당직원은 등록되어있습니다.");
		else if(nParameter = 1000)
			continue;

	}

	RefreshList();
}


void CIncomeForm9::OnBnClickedChoiceAllotBtn()
{
	try
	{
		if(IsOnlyLogiAccount() )
		{
			MessageBox("로지전용 가상계좌를 사용하시면 계좌를 선택할당 할 수  없습니다.", "확인", MB_ICONINFORMATION);
			return;
		}

		if( LF->GetCurBranchInfo()->bVRAccountNoRider )
		{
			MessageBox("옵션에의해 기사 가상계좌 할당을 할 수 없습니다", "확인", MB_ICONINFORMATION);
			return;
		}	

		UINT i, uSaveSelectedCount = m_SaveList.GetSelectedRows()->GetCount();
		UINT uNoAcoountSelectedCount = m_NoAccountList.GetSelectedRows()->GetCount();

		if(LF->GetCurBranchInfo()->bIntegrated == 1 )
			throw("통합에서는 지원되지 않고 지사를 선택하시고 작업하세요");

		if(uSaveSelectedCount != uNoAcoountSelectedCount)
			throw("할당 하실기사와 계좌수가 불일치 합니다.");


		int  nSaveItem = -1;
		int  nNoAccountItem = -1;
		CString sAccount = "";

		for(int m =0; m < uSaveSelectedCount; m++)
		{
			sAccount = m_SaveList.GetItemDataText(m);

			if(sAccount.GetLength() > 0)
				throw("선택하신 기사에 계좌가 할당되어 있습니다. 기사를 다시선택해주세요");

		}	

		nSaveItem = -1; nNoAccountItem = -1;

		if(uSaveSelectedCount > 0)
		{			
			for (i = 0;i < uSaveSelectedCount; i++)
			{
				sAccount = m_NoAccountList.GetItemDataText(m_NoAccountList.GetSelectedRowsGetAtGetRecord(i));
				if(sAccount.GetLength() <= 0)
					throw("계좌가 없습니다.");

				long nCompany = (long)m_SaveList.GetItemLong(m_SaveList.GetSelectedRowsGetAtGetRecord(i));
				int nRNo = -1; 
				nRNo = (long)m_SaveList.GetItemLong2(m_SaveList.GetSelectedRowsGetAtGetRecord(i));
				if(nRNo == -1)
					throw("기사 번호가 없습니다.");

				CMkRecordset pRs(m_pMkDb);
				CMkCommand pCmd(m_pMkDb, "select_vraccount_rider_choice_allot");			
				pCmd.AddParameter(typeLong, typeInput, sizeof(int), nCompany);
				pCmd.AddParameter(typeLong, typeInput, sizeof(int), nRNo);
				pCmd.AddParameter(typeString, typeInput, sAccount.GetLength(), sAccount);
				pCmd.AddParameter(typeString, typeInput, m_ui.strID.GetLength(), m_ui.strID);
				CMkParameter *pPar = pCmd.AddParameter(typeInt, typeOutput, sizeof(int), 0);


				if(!pRs.Execute(&pCmd)) return;
				int nParameter = 0;
				pPar->GetValue(nParameter);
				if(nParameter == 100)
					throw("해당 기사님은 등록되어있습니다.");
				if(nParameter == 200)
					throw("해당 계좌는 사용하고 있습니다.");
				if(nParameter == 300)
					throw("해당 계좌는 없습니다..");
				if(nParameter == 400)
					throw("해당직원은 계좌가 있습니다.");
				else if(nParameter = 1000)
					continue;
			}

			RefreshList();
		}
	}
	catch (char* e)
	{
		MessageBox(e, "확인", MB_ICONINFORMATION);
		return;
	}
}

void CIncomeForm9::OnBnClickedRecovertBtn()
{
	if(IsOnlyLogiAccount() )
	{
		MessageBox("로지전용계좌가 아닌 자체(신청한)계좌가  있어야 계좌를 회수 할 수 있습니다.", "확인", MB_ICONINFORMATION);
		return;
	}

	long nCount = m_SaveList.GetSelectedRows()->GetCount();

	if(nCount <= 0)
	{
		MessageBox("가상계좌를 회수할 기사를 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	if( MessageBox("정말로 가상계좌를 회수하시겠습니까?", "확인", MB_YESNO) == IDNO)
		return;


	CXTPGridSelectedRows *pRows = m_SaveList.GetSelectedRows();
	CString sAccount = "";
	int m = 0;
	for(m = 0; m < nCount; m++)
	{
		CXTPGridRecord *pRecord = (CXTPGridRecord *)pRows->GetAt(m)->GetRecord();

		sAccount = m_SaveList.GetItemDataText(pRecord);

		if(sAccount.GetLength() == 0)
		{
			MessageBox("회수할 곳에 계좌가 없습니다. 계좌가 있는 기사를 다시선택해주세요", "확인", MB_ICONINFORMATION);
			return;
		}
	}

	for(int i = 0;i < nCount; i++)
	{
		CXTPGridRecord *pRecord = (CXTPGridRecord *)pRows->GetAt(m)->GetRecord();
		long nCompany = m_SaveList.GetItemLong(pRecord);
		int nRNo = -1; 
		nRNo = m_SaveList.GetItemLong2(pRecord);

		if(nRNo == -1)
		{
			MessageBox("기사 번호가 없습니다.", "확인", MB_ICONINFORMATION);			
			return;
		}

		sAccount = m_SaveList.GetItemDataText(pRecord);
		if(sAccount.GetLength() == 0)
		{
			MessageBox("계좌가 지정되어있지 않습니다.", "확인", MB_ICONINFORMATION);
			return;
		}

		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "select_vraccount_rider_recovery");	
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), nCompany);
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), nRNo);
		pCmd.AddParameter(typeString, typeInput, sAccount.GetLength(), sAccount);
		pCmd.AddParameter(typeString, typeInput, m_ui.strID.GetLength(), m_ui.strID);
		CMkParameter *pPar = pCmd.AddParameter(typeInt, typeOutput, sizeof(int), 0);

		if(!pRs.Execute(&pCmd)) return;

		int nParameter = 0;
		pPar->GetValue(nParameter);

		if(nParameter == 100)
		{
			MessageBox("계좌가 없습니다", "확인", MB_ICONINFORMATION);
			return;
		}
		else if(nParameter == 1000)
			continue;

	}

	RefreshList();
}

void CIncomeForm9::OnBnClickedLogBtn()
{
	CXTPGridRecord *pRecord = (CXTPGridRecord *)m_SaveList.GetSelectedRows()->GetAt(0)->GetRecord();

	if(pRecord == NULL)
		return;

	if(LF->GetCurBranchInfo()->bIntegrated )
	{
		LF->MsgBox("통합에서는 지원되지 않고 지사를 선택하시고 작업하세요");
		return;
	}

	long nCompany = m_SaveList.GetItemLong(pRecord);
	int nRNo = m_SaveList.GetItemLong2(pRecord);

	m_pVRRiderLogListDlg = new CVRRiderLogListDlg;
	m_pVRRiderLogListDlg->Create(IDD_VRRIDER_LOG_DLG,this);
	m_pVRRiderLogListDlg->m_nCompany = nCompany;
	m_pVRRiderLogListDlg->m_nRNo = nRNo;
	m_pVRRiderLogListDlg->ShowWindow(SW_SHOW);
	/*CREATE_MODALESS(CVRRiderLogListDlg, this);
	pDlg->m_nCompany = nCompany;
	pDlg->m_nRNo = nRNo;
	SHOW_MODALESS(CVRRiderLogListDlg, this);	*/
}


void CIncomeForm9::OnEnChangeSerachEdit()
{
	CString sSearch, sSearchRNo, sSearchName;
	m_SearchEdt.GetWindowText(sSearch); 

	m_SaveList.Filter(sSearch);


}


BOOL CIncomeForm9::IsOnlyLogiAccount()
{ 
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_vraccount_company_type");	
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), LF->GetCurBranchInfo()->nShareCode1);	
	CMkParameter *pPar = pCmd.AddParameter(typeInt, typeOutput, sizeof(int), 0);

	if(!pRs.Execute(&pCmd)) return FALSE;

	int nParameter = 0;
	pPar->GetValue(nParameter);
	int ONLY_LOGI_VRACCOUNT = 2;
	if(nParameter == ONLY_LOGI_VRACCOUNT)
		return TRUE;

	return FALSE;

}

void CIncomeForm9::OnHdnItemclickListReport2(NMHDR *pNMHDR, LRESULT *pResult)
{

	*pResult = 0;
}
void CIncomeForm9::OnNMRclickNoaccountList(NMHDR *pNMHDR, LRESULT *pResult)
{
	//try
	//{
	//	if(m_ba.GetCount() <= 1)
	//		throw("통합사이트에서만이 작업이 가능합니다.");
	//
	//	long nIntegrationCode = 0;
	//	CBranchInfo* pBi = NULL;
	//	pBi = (CBranchInfo*)m_ba.GetAt(0);
	//	
	//	if(m_NoAccountList.GetSelectedRows()->GetCount() <= 0)
	//		throw("계좌를 1개이상 선택해주세요");

	//	CMenu menu;
	//	if(pBi->nCompanyCode == LF->GetCurBranchInfo()->nCompanyCode 
	//							&& !LF->GetCurBranchInfo()->bIntegrated )
	//	
	//		menu.AppendMenu(MF_STRING, ID_BRANCH, "지사 할당");
	//	
	//	else
	//	
	//		menu.AppendMenu(MF_STRING, ID_BRANCH_INTEGRATED, "본사 회수");

	//	CPoint point;
	//	//m_NoAccountList.Get
	////	menu.TrackPopupMenu(,)


	//	
	//}
	//catch (CException* e)
	//{
	//	
	//}
	///*if(m_ba.GetCount() <= 1)

	//
	//m_ba.GetCount()
	//if(!LF->GetCurBranchInfo()->bIntegrated && */
	*pResult = 0;
}
