// CustomerPage11.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "CustomerPage11.h"

#include "AddGroupDlg.h"
#include "VarietyDlg.h"
#include "AddGroupMemberDlg.h"
#include "ChargeListDlg.h"
#include "SearchGroupDlg.h"
#include "MoveGroupDlg.h"
#include "GroupReportSettingDlg.h"
#include "CustomerDlg.h"
// CCustomerPage11




//IMPLEMENT_DYNAMIC(CGroupWorkButton, CButtonST)
CGroupWorkButton::CGroupWorkButton()
{
	m_pWnd = NULL;
}

CGroupWorkButton::~CGroupWorkButton()
{
}


BEGIN_MESSAGE_MAP(CGroupWorkButton, CButtonST)
	//{{AFX_MSG_MAP(CDlgAdvanced)
	ON_COMMAND(ID_ADD_GROUP_TOP, OnMenuGroupTop)
	ON_COMMAND(ID_ADD_GROUP, OnMenuAddGroup)
	ON_COMMAND(ID_DELETE_GROUP, OnMenuDeleteGroup)
	ON_COMMAND(ID_UPDATE_GROUP, OnMenuUpdateGroup)
	ON_COMMAND(ID_MOVE_GROUP, OnMenuMoveGroup)

	
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_USER + 100, On_MenuCallback)
END_MESSAGE_MAP()


void CGroupWorkButton::InitButton()
{
	short	shBtnColor = 40;
	

//	m_DateBtn.SetIcon(IDI_TOOLS4);
	OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
	OffsetColor(CButtonST::BTNST_COLOR_BK_OUT, 28);

//#ifdef	BTNST_USE_BCMENU
//	pBtn->SetMenu(IDR_DATE_MENU, m_hParent, TRUE, IDR_TOOLBAR);
	
	
	SetMenu(IDR_GROUP_MENU1,GetSafeHwnd());
	
	this->SetDefaultColors();
	SetMenuCallback(GetSafeHwnd(), WM_USER + 100);		
}    



// CSmsButton 메시지 처리기입니다.
LRESULT CGroupWorkButton::On_MenuCallback(WPARAM wParam, LPARAM lParam)
{
//#ifdef	BTNST_USE_BCMENU
//	BCMenu*	pMenu = (BCMenu*)wParam;
//	pMenu->EnableMenuItem(IDM_ITEM3, TRUE);
	//::EnableMenuItem((HMENU)wParam, IDM_ITEM3, MF_BYCOMMAND | MF_GRAYED);
	return 0;
} 


void CGroupWorkButton::OnMenuGroupTop()
{
	m_pWnd->OnAddGroupTop();
		
}
void CGroupWorkButton::OnMenuAddGroup()
{
	m_pWnd->OnAddGroup();
}
void CGroupWorkButton::OnMenuDeleteGroup()
{
	m_pWnd->OnDeleteGroup();
}
void CGroupWorkButton::OnMenuUpdateGroup()
{
	m_pWnd->OnUpdateGroup();
}

void CGroupWorkButton::OnMenuMoveGroup()
{
	m_pWnd->OnMoveGroup();
}

IMPLEMENT_DYNCREATE(CCustomerPage11, CMyFormView)

CCustomerPage11::CCustomerPage11()
	: CMyFormView(CCustomerPage11::IDD)
{
	m_nGNo = 0;
	m_pAddGroupMemberDlg = NULL;
}

CCustomerPage11::~CCustomerPage11()
{
	if(m_pAddGroupMemberDlg != NULL)
	{
		delete m_pAddGroupMemberDlg;
		m_pAddGroupMemberDlg = NULL;
	}
}

void CCustomerPage11::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GROUP_LIST, m_lstGroup);
	DDX_Control(pDX, IDC_CUSTOMER_LIST, m_lstCustomer);

	DDX_Control(pDX, IDC_GROUP_NAME_EDIT, m_edtGroupName);
	DDX_Control(pDX, IDC_DEPT_EDIT, m_edtDept);
	DDX_Control(pDX, IDC_NAME_EDIT, m_edtName);
	DDX_Control(pDX, IDC_EMAIL_EDIT, m_edtEMail);
	DDX_Control(pDX, IDC_ID_EDIT, m_edtID);
	DDX_Control(pDX, IDC_PWD_EDIT, m_edtPwd);
	DDX_Control(pDX, IDC_MEMBER_TEL_EDIT, m_edtMemberTel);
	DDX_Control(pDX, IDC_RIDER_DEPOSIT_EDIT, m_edtRiderDeposit);
	DDX_Control(pDX, IDC_COPORATION_CHARGE_CHECK, m_chkCorporationCharge);
	DDX_Control(pDX, IDC_DETAIL_ETC_EDIT, m_edtDetail);
	DDX_Control(pDX, IDC_PRESIDENT_EDIT, m_edtPresident);
	DDX_Control(pDX, IDC_BUSINEESS_NO_EDIT, m_edtBussinessNo);
	DDX_Control(pDX, IDC_BUSINESS_STATUS_EDIT, m_edtBussnessStatus);
	DDX_Control(pDX, IDC_BUSINESS_CATEGORY_EDIT, m_edtBusinessCategory);
	DDX_Control(pDX, IDC_COMPANY_AREA_EDIT, m_edtCompanyArea);
	DDX_Control(pDX, IDC_CHARGE_TYPE_COMBO, m_cmbChargeTypeName);
	DDX_Control(pDX, IDC_BATCHCHARGE_TYPE_COMBO, m_cmbBatchChargeTypeName);

	DDX_Control(pDX, IDC_REPORT_FIRST_DAY_COMBO, m_cmbReportFirstDay);
	DDX_Control(pDX, IDC_REPORT_SECOND_DAY_COMBO, m_cmbReportSecondDay);
	DDX_Control(pDX, IDC_SEARCH_GROUP_EDIT, m_edtSearchGroupName);
	DDX_Control(pDX, IDC_PART_SEARCH_CHECK, m_chkPartAll);
	DDX_Control(pDX, IDC_GROUP_WORK_BTN, m_btnGroupWork);

	DDX_Control(pDX, IDC_CREDIT_CHK, m_chkCredit);
	DDX_Control(pDX, IDC_CASH_OPTION_CHECK, m_chkCashOption);
	DDX_Control(pDX, IDC_CREDIT_OPTION_CHECK, m_chkCreditOption);
	DDX_Control(pDX, IDC_ACTIVE_OPTION_CHECK, m_chkActiveOption);
	DDX_Control(pDX, IDC_UNACTIVE_OPTION_CHECK, m_chkUnActiveOption);
	DDX_Control(pDX, IDC_DISCOUNT_EDT, m_edtDiscount);
	DDX_Control(pDX, IDC_NOT_SHOW_CASH_CHECK, m_chkNotShowCash);
	DDX_Control(pDX, IDC_MANAGER_SEARCH_EDIT, m_edtManagerSearch);
	DDX_Control(pDX, IDC_GROUP_NUMBER_STATIC, m_stcGroupNumber);
	
	
}

BEGIN_MESSAGE_MAP(CCustomerPage11, CMyFormView)
	ON_NOTIFY(NM_RCLICK, IDC_GROUP_LIST, OnReportItemRClick)
	ON_NOTIFY(NM_DBLCLK, IDC_GROUP_LIST, OnReportItemDblClick)

	ON_NOTIFY(NM_DBLCLK, IDC_CUSTOMER_LIST, OnCustomerReportItemDblClick)
	
	ON_NOTIFY(XTP_NM_GRID_SELCHANGED, IDC_GROUP_LIST, OnReportItemChange)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_COMMAND(ID_ADD_GROUP_TOP, OnAddGroupTop)
	ON_COMMAND(ID_ADD_GROUP, OnAddGroup)
	ON_COMMAND(ID_DELETE_GROUP, OnDeleteGroup)
	ON_COMMAND(ID_UPDATE_GROUP, OnUpdateGroup)
	ON_COMMAND(ID_DELETE_CUSTOMER, OnDeleteCustomer)
	ON_COMMAND(ID_MOVE_GROUP, OnMoveGroup)
	ON_WM_CONTEXTMENU()
	ON_BN_CLICKED(IDC_NEW_CHARGE_DLG, OnBnClickedNewChargeDlg)
	ON_BN_CLICKED(IDC_DELETE_CHARGE_DLG2, OnBnClickedDeleteChargeDlg2)
	ON_BN_CLICKED(IDC_SAVE_BTN, OnBnClickedSaveBtn)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_SEARCH_CUSTOMER_BTN, OnBnClickedSearchCustomerBtn)
	ON_CBN_SELCHANGE(IDC_REPORT_SECOND_DAY_COMBO, OnCbnSelchangeReportSecondDayCombo)
	ON_CBN_SELCHANGE(IDC_REPORT_FIRST_DAY_COMBO, OnCbnSelchangeReportFirstDayCombo)
	ON_EN_CHANGE(IDC_SEARCH_GROUP_EDIT, OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_GROUP_CHARGE_BTN, OnBnClickedGroupChargeBtn)
	ON_BN_CLICKED(IDC_CHARGE_TYPE_SEARCH_BTN, OnBnClickedChargeTypeSearchBtn)
	
	ON_BN_CLICKED(IDC_GROUP_SETTING_BTN, OnBnClickedGroupSettingBtn)
	ON_COMMAND(ID_EXCEL_VIEW, OnViewExcel)
	ON_BN_CLICKED(IDC_BATCHCHARGE_TYPE_SEARCH_BTN, OnBnClickedBatchchargeTypeSearchBtn)
	ON_BN_CLICKED(IDC_CHARGETYPENAME_BATCH_BTN, OnBnClickedChargetypenameBatchBtn)
	ON_EN_CHANGE(IDC_MANAGER_SEARCH_EDIT, &CCustomerPage11::OnEnChangeManagerSearchEdit)

	ON_COMMAND(ID_SET_OWNER, OnSetGroupOwner)
	ON_COMMAND(ID_RELEASE_OWNER, OnSetReleaseGroupOwner)
	
END_MESSAGE_MAP()


void CCustomerPage11::OnCustomerReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	CXTPGridSelectedRows *pRows = m_lstCustomer.GetSelectedRows();
	if(pRows == NULL) return;

	return;
	long nCNo = m_lstCustomer.GetItemLong(pRows->GetAt(0)->GetRecord());
	
	OpenCustomerDlgByCNo(nCNo);	
}

void CCustomerPage11::OpenCustomerDlgByCNo(long nCNo)
{
	char buffer[10];

	CBranchInfo *pBi = LF->GetCurBranchInfo();
	CCustomerDlg dlg;

	dlg.m_pRcpDlg = NULL;
	dlg.m_bNoneItemAutoCanceled = FALSE;
	dlg.m_strKeyword = itoa(nCNo, buffer, 10);
	dlg.m_nSearchType = 4; //ST_CNO
	dlg.m_nBranchCode = pBi->nBranchCode;
	dlg.m_strBranchName = pBi->strBranchName;
	dlg.m_nCompanyCode = pBi->nCompanyCode;
	dlg.m_nDOrderTable = pBi->nDOrderTable;
	dlg.m_nCustomerTable = pBi->nCustomerTable;
	dlg.m_nPayTable = pBi->nPayTable;
	dlg.m_bGroup = pBi->bGroup;
	dlg.m_nTempCNo = nCNo;
	dlg.m_bModalMode = TRUE;

	dlg.DoModal();
}

void CCustomerPage11::OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	OnUpdateGroup();
}

void CCustomerPage11::RefreshCustomerList()
{
	m_lstCustomer.DeleteAllItems();

	if(m_nGNo == 0 ) 
		return;

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_group_member_Q");

	pCmd.AddParameter(m_cg.GetGroupData(m_nGNo)->nCompany);
	pCmd.AddParameter(m_nGNo); 

	if(!pRs.Execute(&pCmd))
		return;

	BOOL bGroupOwner = FALSE;
	CString strCompany, strName, strTel, strDate, strMemo, strMainTel, strDong, strManager, strUserID;
	long nID,nCNo, nGNo;
	COleDateTime dtRegister;
	char buffer [20];

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("sCompany", strCompany);
		pRs.GetFieldValue("sManager", strManager);
		pRs.GetFieldValue("sMainTel", strMainTel);
		pRs.GetFieldValue("sMemo", strMemo);
		pRs.GetFieldValue("nID", nID);
		pRs.GetFieldValue("nCNo", nCNo);
		pRs.GetFieldValue("nGNo", nGNo);
		pRs.GetFieldValue("dtRegister", dtRegister);
		pRs.GetFieldValue("bGroupOwner", bGroupOwner);
		pRs.GetFieldValue("sDong", strDong);
		pRs.GetFieldValue("sUserID", strUserID);

		m_lstCustomer.InsertItem(i, m_cg.GetGroupData(nGNo)->strGroupName);
		m_lstCustomer.SetItemText(i, 1, m_cg.GetGroupData(nGNo)->strDept);
		m_lstCustomer.SetItemText(i, 2, itoa(nID, buffer, 10));
		m_lstCustomer.SetItemText(i, 3, strCompany);
		m_lstCustomer.SetItemText(i, 4, strMainTel);
		m_lstCustomer.SetItemText(i, 5, dtRegister.Format("%y-%m-%d"));
		m_lstCustomer.SetItemText(i, 6, strMemo);
		m_lstCustomer.SetItemText(i, 7, strDong);
		m_lstCustomer.SetItemText(i, 8, strUserID);
		m_lstCustomer.SetItemText(i, 9, strManager);

		m_lstCustomer.SetItemLong(i, nCNo);
		m_lstCustomer.SetItemLong2(i, bGroupOwner);		
		m_lstCustomer.SetItemData(i, nGNo);

		pRs.MoveNext();
	}

	m_lstCustomer.Populate();
}

void CCustomerPage11::OnViewExcel()
{
	if(!LF->POWER_CHECK(6900, "엑셀변환", TRUE))
		return;

	LF->AddSecurityLog(LF->GetCurBranchInfo()->nCompanyCode, 206, m_lstGroup.GetItemCount());  
	m_lstGroup.ToExcel("그룹리포트");
}
void CCustomerPage11::OnReportItemChange(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	ChangeGroupInfo();
}

void CCustomerPage11::ChangeGroupInfo()
{
	CXTPGridRow *pRow = m_lstGroup.GetSelectedRows()->GetAt(0);

	if(pRow == NULL)
		return;

	CCustomerGroupRecord *pRecord = (CCustomerGroupRecord*)pRow->GetRecord();
	m_nGNo = pRecord->m_nGNo;

	char buffer[20];

	m_edtGroupName.SetWindowText(m_cg.GetGroupData(m_nGNo)->strGroupName);
	m_edtDept.SetWindowText(m_cg.GetGroupData(m_nGNo)->strDept);
	m_edtName.SetWindowText(m_cg.GetGroupData(m_nGNo)->strName);
	m_edtEMail.SetWindowText(m_cg.GetGroupData(m_nGNo)->strEmail);
	m_edtID.SetWindowText(m_cg.GetGroupData(m_nGNo)->strID);
	m_edtPwd.SetWindowText(m_cg.GetGroupData(m_nGNo)->strPassword);
	m_edtMemberTel.SetWindowText(m_cg.GetGroupData(m_nGNo)->strMemberTel);
	m_edtRiderDeposit.SetWindowText(itoa(m_cg.GetGroupData(m_nGNo)->nDepositRate, buffer, 10));
	m_edtDiscount.SetWindowText(itoa(m_cg.GetGroupData(m_nGNo)->nDiscount, buffer, 10));
	m_chkNotShowCash.SetCheck(m_cg.GetGroupData(m_nGNo)->bNotShowCash);

	if(m_cg.GetGroupData(m_nGNo)->nCharge == 0)
	{
		m_chkCorporationCharge.SetCheck(FALSE);
		m_cmbChargeTypeName.SetCurSel(-1);
		//m_cmbChargeTypeName.SetWindowText("");
	}
	else
	{
		m_chkCorporationCharge.SetCheck(TRUE);
		m_cmbChargeTypeName.SetCurSel(GetComboData(m_cg.GetGroupData(m_nGNo)->nCharge));
	}

	m_edtDetail.SetWindowText(m_cg.GetGroupData(m_nGNo)->strDetail);
	m_edtPresident.SetWindowText(m_cg.GetGroupData(m_nGNo)->strPresident);
	m_edtBussinessNo.SetWindowText(m_cg.GetGroupData(m_nGNo)->strBusinessNo);
	m_edtBussnessStatus.SetWindowText(m_cg.GetGroupData(m_nGNo)->strBusinessStatus);
	m_edtBusinessCategory.SetWindowText(m_cg.GetGroupData(m_nGNo)->strBusinessCategory);
	m_edtCompanyArea.SetWindowText(m_cg.GetGroupData(m_nGNo)->strArea);

	m_cmbReportFirstDay.SetCurSel(m_cg.GetGroupData(m_nGNo)->nReportFirstDay);
	m_cmbReportSecondDay.SetCurSel(m_cg.GetGroupData(m_nGNo)->nReportSecondDay);
	m_chkCredit.SetCheck(m_cg.GetGroupData(m_nGNo)->nCredit);

	SetTimer(0, 500, NULL);
}

long CCustomerPage11::GetComboData(long nCharge)
{
	for(int i=0; m_cmbChargeTypeName.GetCount(); i++)
	{
		long nChargeData = (long)m_cmbChargeTypeName.GetItemData(i);

		if(nCharge == nChargeData)
			return i;
	}

	return -1;

}


#ifdef _DEBUG
void CCustomerPage11::AssertValid() const
{
	CMyFormView::AssertValid();
}

void CCustomerPage11::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif //_DEBUG

void CCustomerPage11::OnUpdateGroup()
{
	CXTPGridRow *pRow = m_lstGroup.GetSelectedRows()->GetAt(0);

	if(pRow == NULL)
		return;

	CCustomerGroupRecord *pRecord = (CCustomerGroupRecord*)pRow->GetRecord();

	CAddGroupDlg dlg;
	dlg.m_nGNo = pRecord->m_nGNo;
	dlg.m_bAdd = FALSE;

	if(dlg.DoModal() == IDOK)
	{
		pRecord->m_nCredit = dlg.m_bCredit;
		ChangeGroupInfo();
		RefreshList();
	}
		
}

// CCustomerPage11 메시지 처리기입니다.

void CCustomerPage11::OnBnClickedRefreshBtn()
{ 
	RefreshList();
	OnEnChangeEdit1();
}

void CCustomerPage11::RefreshListCheck()
{
	m_lstGroup.GetRecords()->RemoveAll();
	m_lstGroup.Populate();

	CString sGNo = "";
	char buffer[20];

	std::vector<long> vec;
	std::vector<long>::iterator pos;

	VEC_CUSTOMER_GROUP::iterator it;
	VEC_CUSTOMER_GROUP *pGroup = m_cg.GetRefreshGroup();

	for(it = pGroup->begin(); it != pGroup->end(); it++)
	{    
		ST_CUSTOMER_GROUP_INFOMATION *st = (*it);

		if(st->nLevel == 0)
		{
			BOOL bInsert = FALSE;

			if((m_chkCashOption.GetCheck() == BST_CHECKED) &&
				(m_chkCreditOption.GetCheck() == BST_CHECKED))
				bInsert = TRUE;
			else
			{
				if(m_chkCashOption.GetCheck() == BST_CHECKED)
				{
					if(st->nGroupCredit == 0)
						bInsert = TRUE;
					else
						continue;
				}

				if(m_chkCreditOption.GetCheck() == BST_CHECKED)
				{
					if(st->nGroupCredit == 1)
						bInsert = TRUE;
					else
						continue;
				}
			}

			if((m_chkActiveOption.GetCheck() == BST_CHECKED) &&
				(m_chkUnActiveOption.GetCheck() == BST_CHECKED))
				bInsert = TRUE;
			else
			{
				if(m_chkActiveOption.GetCheck() == BST_CHECKED)
				{
					if(st->nActiveGroupLevel == 1)
						bInsert = TRUE;
					else
						continue;
				}

				if(m_chkUnActiveOption.GetCheck() == BST_CHECKED) 
				{
					if(st->nActiveGroupLevel == 0)
						bInsert = TRUE; 
					else
						continue;
				}
			}
			
			if(bInsert)
			{
				pos = find(vec.begin(), vec.end(), st->nGNo);

				if(pos == vec.end())
				{
					vec.push_back(st->nGNo);
					sGNo += (CString)itoa(st->nGNo, buffer, 10) + ";";
				}
			}
		} // if(st->nLevel == 0)
	}

	if(vec.size() > 0)
	{
		VEC_CUSTOMER_GROUP::iterator pCur;

		for(int nItem=0; nItem<(int)vec.size(); nItem++)
		{
			ST_CUSTOMER_GROUP_INFOMATION *pSt = m_cg.GetGroupData(vec[nItem]);
			pCur = find(pGroup->begin(), pGroup->end(), pSt);
			MakeListTree(vec[nItem], pCur );
		}

		m_lstGroup.Populate();
	}
}



void CCustomerPage11::MakeListTree(long nGNo, VEC_CUSTOMER_GROUP::iterator it)
{
	if(nGNo <= 0)
		return;

	CXTPGridRecord *pReocrdTop = NULL;
	CXTPGridRecord *pReocrdLevel1 = NULL;
	CXTPGridRecord *pReocrdLevel2 = NULL;
	CXTPGridRecord *pReocrdLevel3 = NULL;
	CXTPGridRecord *pReocrdLevel4 = NULL;
	CXTPGridRecord *pReocrdLevel5 = NULL;

	//CUSTOMER_GROUP_VEC::iterator it;
	VEC_CUSTOMER_GROUP *pVec = 	m_cg.GetRefreshGroup();
	long nLevel = m_cg.GetGroupData(nGNo)->nLevel;

	BOOL bFind = FALSE;

	
	while(it != pVec->end())
	{
		ST_CUSTOMER_GROUP_INFOMATION *st = (*it);

		if(st->nGNo == nGNo)
		{
			pReocrdTop = m_lstGroup.AddRecord(new CCustomerGroupRecord(st));
			pReocrdTop->SetExpanded(TRUE);
			bFind = TRUE;
			it++;
			continue;
		}

		if(st->nParentGNo == nGNo ||
			st->nParentGNo2 == nGNo ||
			st->nParentGNo3 == nGNo ||
			st->nParentGNo4 == nGNo ||
			st->nParentGNo5 == nGNo)
		{
			switch(st->nLevel)
			{
			case 0:
				pReocrdTop = m_lstGroup.AddRecord(new CCustomerGroupRecord(st));
				((CCustomerGroupRecord*)pReocrdTop)->AddSearchData(st);
				pReocrdTop->SetExpanded(TRUE);
				break;
			case 1:
				pReocrdLevel1 = pReocrdTop->GetChilds()->Add(new CCustomerGroupRecord(st));
				((CCustomerGroupRecord*)pReocrdTop)->AddSearchData(st);
				pReocrdLevel1->SetExpanded(TRUE);
				break;
			case 2:
				pReocrdLevel2 = pReocrdLevel1->GetChilds()->Add(new CCustomerGroupRecord(st));
				((CCustomerGroupRecord*)pReocrdTop)->AddSearchData(st);
				pReocrdLevel2->SetExpanded(TRUE);
				break;
			case 3:
				pReocrdLevel3 = pReocrdLevel2->GetChilds()->Add(new CCustomerGroupRecord(st));
				((CCustomerGroupRecord*)pReocrdTop)->AddSearchData(st);
				pReocrdLevel3->SetExpanded(TRUE);
				break;
			case 4:
				pReocrdLevel4 = pReocrdLevel3->GetChilds()->Add(new CCustomerGroupRecord(st));
				((CCustomerGroupRecord*)pReocrdTop)->AddSearchData(st);
				pReocrdLevel4->SetExpanded(TRUE);
				break;
			case 5:
				pReocrdLevel5 =pReocrdLevel4->GetChilds()->Add(new CCustomerGroupRecord(st));
				((CCustomerGroupRecord*)pReocrdTop)->AddSearchData(st);
				pReocrdLevel5->SetExpanded(TRUE);
				break;
			}
		}
		else
		{
			if(bFind)
				break;
		}

		it++;
	}
}

void CCustomerPage11::RefreshList()
{	
	CMyFormView::RefreshList();

	if((m_chkCashOption.GetCheck() != BST_CHECKED) ||
		(m_chkCreditOption.GetCheck() != BST_CHECKED) || 
		(m_chkActiveOption.GetCheck() != BST_CHECKED) ||
		(m_chkUnActiveOption.GetCheck() != BST_CHECKED ))
	{
		RefreshListCheck();
		return;
	}

	m_lstGroup.DeleteAllItem();	


	long nSel = 0;
	
	if(m_lstGroup.GetSelectedRows()->GetCount() != 0)
		nSel = m_lstGroup.GetSelectedRows()->GetAt(0)->GetIndex();

	m_lstGroup.GetRecords()->RemoveAll();

	CXTPGridRecord *pReocrdTop = NULL;
	CXTPGridRecord *pReocrdLevel1 = NULL;
	CXTPGridRecord *pReocrdLevel2 = NULL;
	CXTPGridRecord *pReocrdLevel3 = NULL;
	CXTPGridRecord *pReocrdLevel4 = NULL;
	CXTPGridRecord *pReocrdLevel5 = NULL;

	VEC_CUSTOMER_GROUP::iterator it;
	VEC_CUSTOMER_GROUP *pGroup = m_cg.GetRefreshGroup();

	long nCompany = LF->GetCurBranchInfo()->nCompanyCode;
	BOOL bIntegrated = LF->GetCurBranchInfo()->bIntegrated;
	CString sMainGroupNumber = "";
	long nPreLevel = 0,nMainGroupNumber = 0;
    int i = 0;
	for(it = pGroup->begin(); it != pGroup->end(); it++)
	{
		ST_CUSTOMER_GROUP_INFOMATION *st = (*it);

		if(bIntegrated == FALSE &&
			nCompany != st->nCompany)
			continue;

		switch(st->nLevel)
		{
		case 0:
			pReocrdTop = m_lstGroup.AddRecord(new CCustomerGroupRecord(st));
			pReocrdTop->SetExpanded(TRUE);
			nMainGroupNumber ++;
			break;
		case 1:
			pReocrdLevel1 = pReocrdTop->GetChilds()->Add(new CCustomerGroupRecord(st));
			pReocrdLevel1->SetExpanded(TRUE);
			break;
		case 2:
			pReocrdLevel2 = pReocrdLevel1->GetChilds()->Add(new CCustomerGroupRecord(st));
			pReocrdLevel2->SetExpanded(TRUE);
			break;
		case 3:
			pReocrdLevel3 = pReocrdLevel2->GetChilds()->Add(new CCustomerGroupRecord(st));
			pReocrdLevel3->SetExpanded(TRUE);
			break;
		case 4:
			pReocrdLevel4 = pReocrdLevel3->GetChilds()->Add(new CCustomerGroupRecord(st));
			pReocrdLevel4->SetExpanded(TRUE);
			break;
		case 5:
			pReocrdLevel5 =pReocrdLevel4->GetChilds()->Add(new CCustomerGroupRecord(st));
			pReocrdLevel5->SetExpanded(TRUE);
			break;
		default:
			
			MessageBox("kkk");
			break;
		}
		i++;
	}
	TRACE("nCount =%d, nGroupCount = %d" , i, (int)pGroup->size());
	m_lstGroup.Populate();
	sMainGroupNumber.Format("총그룹: %d", nMainGroupNumber);
	m_stcGroupNumber.SetWindowText(sMainGroupNumber);

	CXTPGridRows *pRows = m_lstGroup.GetRows();
	CXTPGridRow *pRow = pRows->GetAt(min(nSel, m_lstGroup.GetRows()->GetCount() -1));

	m_lstGroup.GetSelectedRows()->Select(pRow);
}

void CCustomerPage11::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	m_chkCashOption.SetCheck(TRUE);
	m_chkCreditOption.SetCheck(TRUE);
	m_chkActiveOption.SetCheck(TRUE);
	m_chkUnActiveOption.SetCheck(TRUE);

	CXTPGridColumn* pCol0 = m_lstGroup.AddColumn(new CXTPGridColumn(0, "그룹이름", 120, FALSE));
	CXTPGridColumn *pCol1 = m_lstGroup.AddColumn(new CXTPGridColumn(1, "부서명", 90, FALSE));
	CXTPGridColumn *pCol2 = m_lstGroup.AddColumn(new CXTPGridColumn(2, "담당자", 70, FALSE));
	CXTPGridColumn *pCol3 = m_lstGroup.AddColumn(new CXTPGridColumn(3, "인원", 35, FALSE));
	CXTPGridColumn *pCol4 = m_lstGroup.AddColumn(new CXTPGridColumn(4, "법인요금", 90, FALSE));	
	CXTPGridColumn *pCol5 = m_lstGroup.AddColumn(new CXTPGridColumn(5, "사용", 40, FALSE));	
	CXTPGridColumn *pCol6 = m_lstGroup.AddColumn(new CXTPGridColumn(6, "취소", 40, FALSE));
	CXTPGridColumn *pCol7 = m_lstGroup.AddColumn(new CXTPGridColumn(7, "마지막사용", 80, FALSE));
	CXTPGridColumn *pCol8 = m_lstGroup.AddColumn(new CXTPGridColumn(8, "이메일", 90, FALSE));
	CXTPGridColumn *pCol9 = m_lstGroup.AddColumn(new CXTPGridColumn(9, "비고", 90, FALSE));
	CXTPGridColumn *pCol10 = m_lstGroup.AddColumn(new CXTPGridColumn(10, "한도", 100, FALSE));
	CXTPGridColumn *pCol11 = m_lstGroup.AddColumn(new CXTPGridColumn(11, "초기화", 40, FALSE));
	CXTPGridColumn *pCol12 = m_lstGroup.AddColumn(new CXTPGridColumn(12, "사업장주소", 170, FALSE));
	//CXTPGridColumn *pCol8 = m_lstGroup.AddColumn(new CXTPGridColumn(9, "대표전화", 90, TRUE));
	

	pCol4->SetAlignment(DT_RIGHT);
	pCol5->SetAlignment(DT_RIGHT);
	pCol6->SetAlignment(DT_RIGHT);

	m_lstGroup.GetPaintManager()->SetColumnStyle(xtpGridColumnResource);
	
	m_lstGroup.GetReportHeader()->AllowColumnResize(TRUE);
	m_lstGroup.GetReportHeader()->SetAutoColumnSizing(FALSE);	
	m_lstGroup.GetReportHeader()->AllowColumnRemove(FALSE);
	m_lstGroup.GetReportHeader()->AllowColumnSort(TRUE);

	m_lstGroup.AllowEdit(FALSE);
	m_lstGroup.SetGridColor(RGB(222, 222, 222));
	m_lstGroup.GetPaintManager()->m_strNoItems = "표시할 대상이 존재하지 않음";

	pCol0->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol0->SetTreeColumn(1);	
	m_lstGroup.SetTreeIndent(10);

	m_lstGroup.Populate();

	CXTPGridColumn* pCol20 = m_lstCustomer.AddColumn(new CXTPGridColumn(0, "그룹이름", 120, FALSE));
	CXTPGridColumn *pCol21 = m_lstCustomer.AddColumn(new CXTPGridColumn(1, "부서명", 90, FALSE));
	CXTPGridColumn *pCol22 = m_lstCustomer.AddColumn(new CXTPGridColumn(2, "고객No", 50, FALSE));
	CXTPGridColumn *pCol23 = m_lstCustomer.AddColumn(new CXTPGridColumn(3, "상호명", 90, FALSE));
	CXTPGridColumn *pCol24 = m_lstCustomer.AddColumn(new CXTPGridColumn(4, "대표번호", 90, FALSE));
	CXTPGridColumn *pCol25 = m_lstCustomer.AddColumn(new CXTPGridColumn(5, "등록일", 70, FALSE));
	CXTPGridColumn *pCol26 = m_lstCustomer.AddColumn(new CXTPGridColumn(6, "메모", 120, FALSE));
	CXTPGridColumn *pCol27 = m_lstCustomer.AddColumn(new CXTPGridColumn(7, "기준동", 80, FALSE));
	CXTPGridColumn *pCol28 = m_lstCustomer.AddColumn(new CXTPGridColumn(8, "한도", 80, FALSE));
	CXTPGridColumn *pCol29 = m_lstCustomer.AddColumn(new CXTPGridColumn(9, "초기화", 120, FALSE));
	
	//pCol19->SetVisible(FALSE);

	m_lstCustomer.GetPaintManager()->SetColumnStyle(xtpGridColumnResource);
	m_lstCustomer.GetReportHeader()->AllowColumnResize(FALSE);
	m_lstCustomer.GetReportHeader()->SetAutoColumnSizing(FALSE);
	m_lstCustomer.GetReportHeader()->AllowColumnSort(FALSE);
	m_lstCustomer.GetReportHeader()->AllowColumnRemove(FALSE);

	m_lstCustomer.GetReportHeader()->SetAutoColumnSizing(FALSE);
	m_lstCustomer.AllowEdit(FALSE);
	m_lstCustomer.SetGridColor(RGB(222, 222, 222));
	m_lstCustomer.GetPaintManager()->m_strNoItems = "표시할 대상이 존재하지 않음";

	pCol0->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol0->SetTreeColumn(1);	
	m_lstCustomer.SetTreeIndent(1);

	m_lstCustomer.Populate();
	ChargeTypeNameRefresh();

	m_cmbReportFirstDay.SetCurSel(0);
	m_cmbReportSecondDay.SetCurSel(0);

	m_chkPartAll.SetCheck(TRUE);
	
	m_btnGroupWork.InitButton();
	m_btnGroupWork.m_pWnd = this;

	SetResize(IDC_GROUP_LIST, sizingBottom);
	SetResize(IDC_CUSTOMER_LIST, sizingRightBottom);	
}

void CCustomerPage11::OnAddGroupTop()
{
	CAddGroupDlg dlg;
	dlg.m_nGNo = 0;
	dlg.m_bAdd = TRUE;
	if(dlg.DoModal() == IDOK)
	{
		ChargeTypeNameRefresh();
		OnBnClickedRefreshBtn();
	}

}

void CCustomerPage11::OnAddGroup()
{
	CXTPGridRow *pRow = m_lstGroup.GetSelectedRows()->GetAt(0);

	if(pRow == NULL)
		return;

	CCustomerGroupRecord *pRecord = (CCustomerGroupRecord*)pRow->GetRecord();

	if(m_cg.GetGroupData(pRecord->m_nGNo)->nLevel == 5)
	{
		MessageBox("5단 이상의 트리는 만드실 수 없습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	CAddGroupDlg dlg;
	dlg.m_nGNo = pRecord->m_nGNo;
	dlg.m_bAdd = TRUE;
	if(dlg.DoModal() == IDOK)
		OnBnClickedRefreshBtn();
}

void CCustomerPage11::OnDeleteGroup()
{
	CXTPGridRow *pRow = m_lstGroup.GetSelectedRows()->GetAt(0);

	if(pRow == NULL)
		return;
	

	if(MessageBox("해당 그룹삭제시 하위그룹이 동시삭제됩니다!\r\n그룹에 속한 고객은 모두 일반그룹으로 돌아갑니다.\r\n\r\n 정말로 삭제하시겠습니까?", "홛인", MB_OKCANCEL) == IDOK)
	{
		for(int i = 0; i  < m_lstGroup.GetSelectedRows()->GetCount(); i++)
		{
			CXTPGridRow *pRow = m_lstGroup.GetSelectedRows()->GetAt(i);
			CCustomerGroupRecord *pRecord = (CCustomerGroupRecord*)pRow->GetRecord();
			CMkCommand pCmd(m_pMkDb, "delete_group_2008");
			pCmd.AddParameter(m_cg.GetGroupData(pRecord->m_nGNo)->nCompany);
			pCmd.AddParameter(pRecord->m_nGNo);
			if(!pCmd.Execute())return;
		}

		m_cg.FillData();
		OnBnClickedRefreshBtn();
	}
}

void CCustomerPage11::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_lstGroup.GetWindowRect(&rect);

	if(rect.PtInRect(point))
	{
		CMenu rMenu;
		rMenu.LoadMenu(IDR_GROUP_MENU);
		CMenu *pRMenu=rMenu.GetSubMenu(2);
		pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}

	m_lstCustomer.GetWindowRect(&rect);

	if(rect.PtInRect(point))
	{
		CMenu rMenu;
		rMenu.LoadMenu(IDR_GROUP_MENU);
		CMenu *pRMenu=rMenu.GetSubMenu(3);
		pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}


}

void CCustomerPage11::OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	CPoint pt;
	GetCursorPos(&pt);
	OnContextMenu(&m_lstGroup, pt);
}

void CCustomerPage11::OnBnClickedNewChargeDlg()
{
	CVarietyDlg dlg;
	dlg.m_sTitleDlg = "신규요금명을 적으세요";

	long nReturnValue = 0;
	CString sChargeName = "";

	if(dlg.DoModal() == IDOK)
	{

		sChargeName = dlg.m_sValue;
		if(sChargeName.GetLength() == 0)
			return;

		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "insert_chargetype_name_2008");
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), LF->GetCurBranchInfo()->nPayTable);
		pCmd.AddParameter(typeString, typeInput, sChargeName.GetLength(), sChargeName);
		pCmd.AddParameter(typeString, typeInput, m_ui.strName.GetLength(), m_ui.strName);
		CMkParameter *pPar = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);

		if(!pRs.Execute(&pCmd)) return;
		pPar->GetValue(nReturnValue);

		if(nReturnValue < 0)
			MessageBox("기존의 등록할 이름과 일치합니다.", "확인", MB_ICONINFORMATION);
		else
			MessageBox("요금제가 신규로 생성되었습니다.","확인", MB_ICONINFORMATION);

	}

	if(nReturnValue > 0)
	{
		ST_CHARGE_TYPE_NAME_INFO st;
		st.nID = nReturnValue;
		st.nCompany = LF->GetCurBranchInfo()->nCompanyCode;
		st.strChargeName = sChargeName;
		
		m_mapChargeType[nReturnValue] = st;

		ChargeTypeNameRefresh();
	}
}

void CCustomerPage11::ChargeTypeNameRefresh()
{
	m_cmbChargeTypeName.ResetContent();
	m_cmbBatchChargeTypeName.ResetContent();
	MAP_CHARGE_TYPE_NAME::iterator it;
	long nItem = 0;

	m_cmbBatchChargeTypeName.InsertString(nItem,"요금 적용안함");
	m_cmbBatchChargeTypeName.SetItemData(nItem, -1);

	for(it = m_mapChargeType.begin(); it != m_mapChargeType.end(); it++)
	{
		m_cmbChargeTypeName.InsertString(nItem, it->second.strChargeName);
		m_cmbChargeTypeName.SetItemData(nItem++, it->first);

		m_cmbBatchChargeTypeName.InsertString(nItem, it->second.strChargeName);
		m_cmbBatchChargeTypeName.SetItemData(nItem, it->first);
	}

	m_cmbChargeTypeName.SetCurSel(0);
	m_cmbBatchChargeTypeName.SetCurSel(0);
}

void CCustomerPage11::OnBnClickedDeleteChargeDlg2()
{
	if(m_cmbChargeTypeName.GetCount() <= 0 )
		return;

	CString strChargeTypeName = "", sTemp = "";

	int nCur = m_cmbChargeTypeName.GetCurSel();
	m_cmbChargeTypeName.GetLBText(nCur,strChargeTypeName);
	long nChargeTypeID = (long)m_cmbChargeTypeName.GetItemData(nCur);
	sTemp = strChargeTypeName + " 의 해당요금제를 삭제하시겠습니까?\n\r\n\r 요금제가 삭제되면 법인등록된 요금제도 삭제됩니다.\n\r\n\r 삭제하시려면 예(Y)를 눌러주세요";
	if(MessageBox(sTemp,"확인", MB_ICONINFORMATION| MB_YESNO) == IDYES)
	{

		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "delete_chargetype_name");
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), LF->GetCurBranchInfo()->nPayTable);
		pCmd.AddParameter(typeString, typeInput, strChargeTypeName.GetLength(), strChargeTypeName);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), nChargeTypeID);
		CMkParameter *pPar = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);

		if(!pRs.Execute(&pCmd)) return;
		long nReturnValue = 0;
		pPar->GetValue(nReturnValue);

		if(nReturnValue < 0)
			MessageBox("삭제할 해당요금이 서버에 없습니다.", "확인", MB_ICONINFORMATION);
		else
		{
			MessageBox("요금제가 삭제 되었습니다.","확인", MB_ICONINFORMATION);
			
			MAP_CHARGE_TYPE_NAME::iterator it = m_mapChargeType.find(nChargeTypeID);

			if(it != m_mapChargeType.end())
				m_mapChargeType.erase(it);				
			
			ChargeTypeNameRefresh();
		}

	}
}

void CCustomerPage11::OnBnClickedSaveBtn()
{
	if(m_nGNo <= 0)
		return;

	ST_CUSTOMER_GROUP_INFOMATION *pData =	m_cg.GetGroupData(m_nGNo);

	GetViewGroupData(pData);

	if(m_cg.SetGroupData(m_nGNo, pData))
	{
		MessageBox("수정되었습니다", "확인", MB_ICONINFORMATION);

		if(m_lstGroup.GetSelectedRows()->GetCount() > 0)
		{
			CCustomerGroupRecord *pRecord = (CCustomerGroupRecord*)m_lstGroup.GetSelectedRows()->GetAt(0)->GetRecord();
			pRecord->m_nCredit = pData->nCredit;
		}
	}
}

ST_CUSTOMER_GROUP_INFOMATION* CCustomerPage11::GetViewGroupData(ST_CUSTOMER_GROUP_INFOMATION *pData)
{
	CString strDepositRate = "";
	CString strDiscount = "";

	m_edtGroupName.GetWindowText(pData->strGroupName);
	m_edtDept.GetWindowText(pData->strDept);
	m_edtName.GetWindowText(pData->strName);
	m_edtEMail.GetWindowText(pData->strEmail);
	m_edtID.GetWindowText(pData->strID);
	m_edtPwd.GetWindowText(pData->strPassword);
	m_edtMemberTel.GetWindowText(pData->strMemberTel);
	m_edtRiderDeposit.GetWindowText(strDepositRate);
	pData->nDepositRate = _ttoi(strDepositRate);

	m_edtDiscount.GetWindowText(strDiscount);
	pData->nDiscount = _ttoi(strDiscount);

	if(m_chkCorporationCharge.GetCheck())
	{
		pData->nCharge = (long)m_cmbChargeTypeName.GetItemData(m_cmbChargeTypeName.GetCurSel());
		m_cmbChargeTypeName.GetLBText(m_cmbChargeTypeName.GetCurSel(), pData->strChargeName);
	}
	else
	{
		pData->nCharge = 0;
		pData->strChargeName = "";
	}

	m_edtDetail.GetWindowText(pData->strDetail);
	m_edtPresident.GetWindowText(pData->strPresident);
	m_edtBussinessNo.GetWindowText(pData->strBusinessNo);
	m_edtBussnessStatus.GetWindowText(pData->strBusinessStatus);
	m_edtBusinessCategory.GetWindowText(pData->strBusinessCategory);
	m_edtCompanyArea.GetWindowText(pData->strArea);

	pData->nReportFirstDay = m_cmbReportFirstDay.GetCurSel();
	pData->nReportSecondDay = m_cmbReportSecondDay.GetCurSel();

	pData->nCredit = m_chkCredit.GetCheck();
	pData->bNotShowCash = m_chkNotShowCash.GetCheck();

	return pData;
}

void CCustomerPage11::OnTimer(UINT nIDEvent)
{
	KillTimer(nIDEvent);

	RefreshCustomerList();

	CMyFormView::OnTimer(nIDEvent);
}

void CCustomerPage11::OnBnClickedSearchCustomerBtn()
{
	if(m_pAddGroupMemberDlg != NULL)
	{
		delete m_pAddGroupMemberDlg;
		m_pAddGroupMemberDlg = NULL;
	}

	m_pAddGroupMemberDlg = new CAddGroupMemberDlg(this);
	m_pAddGroupMemberDlg->Create(IDD_ADD_GROUP_MEMBER_DLG, this);

	CRect rcLst, rcDlg, rcNew;

	m_lstGroup.GetWindowRect(&rcLst);
	m_pAddGroupMemberDlg->GetWindowRect(rcDlg);

	rcNew.left = rcLst.right + 2;
	rcNew.right = rcNew.left + rcDlg.Width();
	rcNew.bottom = rcLst.bottom;
	rcNew.top = rcNew.bottom - rcDlg.Height();

	m_pAddGroupMemberDlg->MoveWindow(rcNew);
	m_pAddGroupMemberDlg->ShowWindow(TRUE);
}

void CCustomerPage11::OnDeleteCustomer()
{
	CXTPGridSelectedRows * pRows = m_lstCustomer.GetSelectedRows();
	long nCount = pRows->GetCount();

	for(int i = 0; i < nCount; i++)
	{ 
		CXTPGridRow * pRow = pRows->GetAt(0);
		
		long nCNo = m_lstCustomer.GetItemLong(pRow->GetRecord());
		long nGNo = (long)m_lstCustomer.GetItemData(pRow->GetRecord());

		CMkCommand pCmd(m_pMkDb, "update_group_input");
		pCmd.AddParameter(LF->GetCurBranchInfo()->nCustomerTable);    
		pCmd.AddParameter(nCNo);    
		pCmd.AddParameter(nGNo);    
		pCmd.AddParameter(FALSE);    
		pCmd.Execute();		

		m_cg.GetGroupData(nGNo)->nMembers--;

		m_lstCustomer.GetRecords()->RemoveRecord(pRow->GetRecord());
	}

	m_lstCustomer.Populate();

    MessageBox("삭제되었습니다", "확인", MB_ICONINFORMATION);
	//RefreshList();

	//SetTimer(0, 500, NULL);
}

void CCustomerPage11::AddGroupMember()
{
	if(m_pAddGroupMemberDlg == NULL)
		return;

	char buffer[20];

	long nCNo = 0;
	if(m_pAddGroupMemberDlg->m_lstCustomer.GetSelectedCount() == 0) 	
	{
		MessageBox("포함시킬 고객을 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}
    if(m_lstGroup.GetSelectedRows()->GetCount() == 0) 	
	{
		MessageBox("그룹을 선택하여 주세요", "확인", MB_ICONINFORMATION);
		return;
	}
	if(m_lstGroup.GetSelectedRows()->GetCount() > 1) 
	{
		MessageBox("그룹선택이 1개 이상입니다.", "확인", MB_ICONINFORMATION);
		return;
	}

	COleDateTime dtDate(2000, 1, 1, 0, 0, 0);
	CString strNeedReportID = "";
	CString strGNo = "";

	for(int i = 0; i < m_pAddGroupMemberDlg->m_lstCustomer.GetSelectedCount(); i++)
	{
		CMyXTPGridRecord *pRecord = (CMyXTPGridRecord*)m_pAddGroupMemberDlg->m_lstCustomer.GetSelectedRows()->GetAt(i)->GetRecord();
		long nGNo = (long)pRecord->GetItemDataLong2();

		if(nGNo != 0)
			strGNo += (CString)itoa(nGNo, buffer, 10) + ";";
	}

	if(strGNo == "")
		strGNo = "0;";

	if(LF->CheckGroupReport(strGNo, m_nGNo, dtDate, m_pAddGroupMemberDlg->m_lstCustomer.GetSelectedCount(), strNeedReportID) == FALSE) // 재정산이 필요한 리포트를 선정
		return;

	for(int i = 0; i < m_pAddGroupMemberDlg->m_lstCustomer.GetSelectedCount(); i++)
	{
		CMyXTPGridRecord *pRecord = (CMyXTPGridRecord*)m_pAddGroupMemberDlg->m_lstCustomer.GetSelectedRows()->GetAt(i)->GetRecord();
		nCNo = pRecord->GetItemDataLong();

		CMkCommand pCmd(m_pMkDb, "update_group_input_1");
		pCmd.AddParameter(LF->GetCurBranchInfo()->nCustomerTable);    
		pCmd.AddParameter(nCNo);    
		pCmd.AddParameter(m_nGNo);    
		pCmd.AddParameter(TRUE);    
		pCmd.Execute();

		int nItem = m_pAddGroupMemberDlg->m_lstCustomer.GetSelectedRows()->GetAt(i)->GetIndex();
		m_pAddGroupMemberDlg->m_lstCustomer.SetItemText(nItem,1,m_cg.GetGroupData(m_nGNo)->strTotalName);
		m_cg.GetGroupData(m_nGNo)->nMembers++;
	}

	if(strNeedReportID != "")
	{
		if(LF->ReReport(strNeedReportID))
			MessageBox("그룹에 편입되었습니다.", "확인", MB_ICONINFORMATION);
	}
	else
		MessageBox("그룹에 편입되었습니다.", "확인", MB_ICONINFORMATION);	

	//RefreshList();
	 RefreshCustomerList();
}

void CCustomerPage11::OnCbnSelchangeReportSecondDayCombo()
{
	CheckCombo();
}

void CCustomerPage11::CheckCombo()
{
	long nFirstSel = m_cmbReportFirstDay.GetCurSel();
	long nSecondSel = m_cmbReportSecondDay.GetCurSel();

	if((nSecondSel < nFirstSel) &&
		nSecondSel != 0)
	{
		MessageBox("첫번째 정산일의 날짜가 두번째 정산일 날짜보다 큽니다", "확인", MB_ICONINFORMATION);
		m_cmbReportSecondDay.SetCurSel(0);
		return;
	}

	if((nSecondSel == nFirstSel) &&
		nFirstSel != 0)
	{
		MessageBox("첫번째 정산일과 두번째 정산일의 날짜가 같습니다", "확인", MB_ICONINFORMATION);
		m_cmbReportSecondDay.SetCurSel(0);
		return;
	}

	if(nFirstSel == 0 && nSecondSel > 0) 
	{
		MessageBox("첫번째 정산일로 설정해주세요", "확인", MB_ICONINFORMATION);
		m_cmbReportFirstDay.SetCurSel(m_cmbReportSecondDay.GetCurSel());
		m_cmbReportSecondDay.SetCurSel(0);
		return;
	}
}

void CCustomerPage11::OnCbnSelchangeReportFirstDayCombo()
{
	CheckCombo();
}

void CCustomerPage11::OnEnChangeEdit1()
{
	CString strSearchWord = "";
	m_edtSearchGroupName.GetWindowText(strSearchWord);
	strSearchWord.MakeUpper();

	CXTPGridRecords *pRecords = m_lstGroup.GetRecords();
	long nCount = pRecords->GetCount();
  
	for(int i=0; i<nCount; i++)
	{
		CXTPGridRecord* pRecord = (CXTPGridRecord*)pRecords->GetAt(i);

		if(pRecord->HasChildren())
		{
			CXTPGridRecords *pRecords1 = pRecord->GetChilds();

			BOOL bChildFind = FALSE;

			for(int j=0; j<pRecords1->GetCount(); j++)
			{				
				CXTPGridRecord* pRecord1 = (CXTPGridRecord*)pRecords1->GetAt(j);
				BOOL bFindRecord = FindRecord(pRecord1, strSearchWord);
				pRecord1->SetVisible(bFindRecord);

				if(bFindRecord)
					bChildFind = TRUE;				
			}

			if(!bChildFind) {
				BOOL bParentFind = FindRecord(pRecord, strSearchWord);

				if(bParentFind)
					AllRecordShow(pRecord);
				else 
					pRecord->SetVisible(bChildFind);
			}				
			else 
				pRecord->SetVisible(bChildFind);
		}
		else
		{
			pRecord->SetVisible(FindRecord(pRecord, strSearchWord));
		}
	}

	m_lstGroup.Populate();
	m_lstGroup.ExpandAll();
}

void CCustomerPage11::AllRecordShow(CXTPGridRecord *pRecord)
{
	CXTPGridRecords *pChildRecord = pRecord->GetChilds(); 

	for(int j=0; j<pChildRecord->GetCount(); j++)
		pChildRecord->GetAt(j)->SetVisible(TRUE);

	pRecord->SetVisible(TRUE);
}

BOOL CCustomerPage11::FindRecord(CXTPGridRecord *pRecord, CString strSearchWord) 
{
	CString str0 = pRecord->GetItem(0)->GetCaption(NULL);
	CString str1 = pRecord->GetItem(1)->GetCaption(NULL);
	CString str2 = pRecord->GetItem(2)->GetCaption(NULL);

	str0.MakeUpper();
	str1.MakeUpper();
	str2.MakeUpper();

	if(str0.Find(strSearchWord) >= 0 ||
		str1.Find(strSearchWord) >= 0 ||
		str2.Find(strSearchWord) >= 0)
	{
		return TRUE;
	}
	else
		return FALSE;
}

void CCustomerPage11::OnBnClickedGroupChargeBtn()
{
	CChargeListDlg dlg;
	dlg.m_nCompany = LF->GetCurBranchInfo()->nPayTable;
	dlg.DoModal();
}

void CCustomerPage11::OnBnClickedChargeTypeSearchBtn()
{

	CSearchGroupDlg dlg;
	dlg.m_nCompany = LF->GetCurBranchInfo()->nPayTable;
	dlg.m_nDataType = SG_DISCOUNT_COMPANY;
	if(dlg.DoModal() == IDOK)
	{
		CString sChargeName = dlg.m_strChargeName;
		long nChargeID = dlg.m_nChargeID;

		for(int i = 0; i < m_cmbChargeTypeName.GetCount(); i++)
		{
			long nCmbChargeTypeID = (long)m_cmbChargeTypeName.GetItemData(i);
			if(nCmbChargeTypeID == nChargeID)
			{
				m_cmbChargeTypeName.SetCurSel(i);
				return;
			}
		}
	}
}

void CCustomerPage11::OnMoveGroup()
{
	CMoveGroupDlg Dlg;
	m_edtSearchGroupName.GetWindowText(Dlg.m_strSearch);
	Dlg.DoModal();
}
void CCustomerPage11::OnBnClickedGroupSettingBtn()
{
	CGroupReportSettingDlg dlg;
	dlg.m_nGNo = m_nGNo;

	
	if(dlg.DoModal() == IDOK)
	{
		if(m_nGNo <= 0)
			return;

		ST_CUSTOMER_GROUP_INFOMATION *pData =	m_cg.GetGroupData(m_nGNo);

		GetViewGroupData(pData);

		pData->nAddTaxApplyType = dlg.m_nAddTaxApplyType;
		pData->bCashApply = dlg.m_bCashApply;
		pData->bCreditApply = dlg.m_bCreditApply;
		pData->bOnlineApply = dlg.m_bOnlineApply;
		pData->bTransApply = dlg.m_bTransApply;
		pData->nDiscount = _ttoi(dlg.m_strDiscount);
		pData->nReportFirstDay = dlg.m_nReportFirstDay;
		pData->nReportSecondDay = dlg.m_nReportSecondDay;
		pData->bShowOrder = dlg.m_bShowOrder;
        pData->strColumnChk.Copy(dlg.m_strColumn);
		pData->bNotShowCash = dlg.m_bNotShowCash;
	
		if(m_cg.SetGroupReportData(m_nGNo, pData, pData->nLevel == 0 ? TRUE : FALSE))
		{
			MessageBox("수정되었습니다", "확인", MB_ICONINFORMATION);
			ChangeGroupInfo();
		}
	}

}

void CCustomerPage11::OnBnClickedBatchchargeTypeSearchBtn()
{
	CSearchGroupDlg dlg;
	dlg.m_nCompany = LF->GetCurBranchInfo()->nPayTable;
	dlg.m_nDataType = SG_DISCOUNT_COMPANY;
	if(dlg.DoModal() == IDOK)
	{
		CString sChargeName = dlg.m_strChargeName;
		long nChargeID = dlg.m_nChargeID;

		for(int i = 0; i < m_cmbChargeTypeName.GetCount(); i++)
		{
			long nCmbChargeTypeID = (long)m_cmbBatchChargeTypeName.GetItemData(i);
			if(nCmbChargeTypeID == nChargeID)
			{
				m_cmbBatchChargeTypeName.SetCurSel(i);
				return;
			}
		}
	}
}

void CCustomerPage11::OnBnClickedChargetypenameBatchBtn()
{

	
	if(m_lstGroup.GetSelectedCount() == 0)
	{
		LF->MsgBox("요금셋팅을 하실 그룹을 선택하세요");
		return;
	}
	long nChargeTypeID = 0;	BOOL bApply = TRUE; long nGroupCode = 0;

	nChargeTypeID = (long)m_cmbBatchChargeTypeName.GetItemData(m_cmbBatchChargeTypeName.GetCurSel());
	if(nChargeTypeID < 0)
		bApply = FALSE;


	for(int i = 0; i < m_lstGroup.GetSelectedCount(); i++)
	{

		CCustomerGroupRecord *pRecord = (CCustomerGroupRecord*)m_lstGroup.GetSelectedRows()->GetAt(i)->GetRecord();
		nGroupCode = pRecord->m_nGNo;

		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "update_chargetype_name_apply_setting");		
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), nGroupCode);		
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), bApply);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), nChargeTypeID);	

		if(!pRs.Execute(&pCmd))
		{
			MessageBox("삭제할 해당요금이 서버에 없거나 실행중 오류가 났습니다.", "확인", MB_ICONINFORMATION);
			return;
		}
		else
		{
			if(!bApply)
			{
				m_cg.GetGroupData(nGroupCode)->nCharge = 0;
				m_cg.GetGroupData(nGroupCode)->strChargeName = "";
			}
			else
			{
				m_cg.GetGroupData(nGroupCode)->nCharge = nChargeTypeID;
				m_cg.GetGroupData(nGroupCode)->strChargeName = m_mapChargeType[nChargeTypeID].strChargeName;
			}			
		}
	}

	MessageBox("요금제가 셋팅 되었습니다.","확인", MB_ICONINFORMATION);
	RefreshList();
}

void CCustomerPage11::OnEnChangeManagerSearchEdit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CMyFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strManager = "";
	this->m_edtManagerSearch.GetWindowText(strManager);
	m_lstCustomer.Filter(strManager, 0, -1);
}

void CCustomerPage11::OnSetGroupOwner()
{
	int nItem = m_lstCustomer.GetNextItem(-1, LVNI_SELECTED);
	if(nItem == -1) 
	{
		MessageBox("고객을 선택하시기 바랍니다", "확인", MB_ICONINFORMATION);
		return;
	}
	if(m_lstCustomer.GetSelectedRows()->GetCount() <= 0)
	{
		MessageBox("고객을 선택하여 주세요","확인", MB_ICONINFORMATION);
		return;
	}	
	CXTPGridRecord *pRecord = m_lstCustomer.GetSelectedRows()->GetAt(0)->GetRecord();
	
	long nCNo = (long)m_lstCustomer.GetItemLong(pRecord);
	long nGNo = (long)m_lstCustomer.GetItemData(pRecord);
	if(nCNo <= 0 )
	{
		MessageBox("선택하신 고객의 데이터 오류입니다. 로지소프트로 문의하세요","확인", MB_ICONINFORMATION);
		return;
	}
	
	if(nGNo <= 0 )
	{
		MessageBox("해당고객은 그룹고객이 아닙니다.", "확인", MB_ICONINFORMATION);
		return;
	}

	CMkCommand pCmd(m_pMkDb, "update_customer_group_owner2");
	pCmd.AddParameter(LF->GetCurBranchInfo()->nCustomerTable);
	pCmd.AddParameter(nCNo);
	pCmd.AddParameter(1);
	if(!pCmd.Execute()) return;

	m_lstCustomer.SetItemLong2(pRecord, 1);
	
	MessageBox("해당고객을 그룹오너로 설정하였습니다.\n","확인",MB_ICONINFORMATION);
	m_lstCustomer.RedrawControl();

	
}


void CCustomerPage11::OnSetReleaseGroupOwner()
{
	int nItem = m_lstCustomer.GetNextItem(-1, LVNI_SELECTED);
	if(nItem == -1) 
	{
		MessageBox("고객을 선택하시기 바랍니다", "확인", MB_ICONINFORMATION);
		return;
	}

	if(m_lstCustomer.GetSelectedRows()->GetCount() <= 0)
	{
		MessageBox("고객을 선택하여 주세요","확인", MB_ICONINFORMATION);
		return;
	}	
	CXTPGridRecord *pRecord = m_lstCustomer.GetSelectedRows()->GetAt(0)->GetRecord();

	long nCNo = (long)m_lstCustomer.GetItemLong(pRecord);
	long nGNo = (long)m_lstCustomer.GetItemData(pRecord);
	if(nCNo <= 0 )
	{
		MessageBox("선택하신 고객의 데이터 오류입니다. 로지소프트로 문의하세요","확인", MB_ICONINFORMATION);
		return;
	}

	if(nGNo <= 0 )
	{
		MessageBox("해당고객은 그룹고객이 아닙니다.", "확인", MB_ICONINFORMATION);
		return;
	}

	CMkCommand pCmd(m_pMkDb, "update_customer_group_owner2");
	pCmd.AddParameter(LF->GetCurBranchInfo()->nCustomerTable);
	pCmd.AddParameter(nCNo);
	pCmd.AddParameter(0);
	if(!pCmd.Execute()) return;

	m_lstCustomer.SetItemLong2(pRecord,0);

	MessageBox("해당고객을 그룹오너로 해제하였습니다.\n","확인",MB_ICONINFORMATION);
	m_lstCustomer.RedrawControl();

}