// CustomerDlgSub1.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "CustomerDlgSub1.h"
#include "CustomerDlg.h"
#include "SearchGroupDlg.h"
#include "MoveGroupDlg.h"
#include "CustomerGroup.h"
#include "RcpPlaceInfo.h"
#include "CustomerSmsDlg2.h"
#include "CustomerDlgSub2.h"
#include "SearchPOIDlg.h"
#include "AddManagerDlg.h"
#include "CustomerData.h"
#include "RcpView.h"
#include "CustomerSmsDlg2.h"
// CCustomerDlgSub1

#define HIDE_SEARCH_DONG_LIST_TIMER 0

#define ID_MENU_MAKE_PHONE1 WM_USER + 100
#define ID_MENU_MAKE_PHONE2 WM_USER + 101

static LOGFONT lfTel = {14,0,0,0,FW_BOLD,0,0,0,HANGUL_CHARSET,0,0,0,0,"맑은 고딕"};

IMPLEMENT_DYNCREATE(CCustomerDlgSub1, CMyFormView)

CCustomerDlgSub1::CCustomerDlgSub1()
	: CMyFormView(CCustomerDlgSub1::IDD)
{
	m_pCustomerDlg = NULL;
	m_strTempPhone = "";
}

CCustomerDlgSub1::~CCustomerDlgSub1()
{
}

void CCustomerDlgSub1::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_ETC_STATIC1, m_stcEtc1);
	DDX_Control(pDX, IDC_TYPE_STATIC, m_stcType);
	DDX_Control(pDX, IDC_TEL_LIST, m_lstTel);
	DDX_Text(pDX, IDC_TYPE_EDIT, m_strCustomerType);
	DDX_Control(pDX, IDC_TYPE_EDIT, m_edtType);
	DDX_Control(pDX, IDC_CUSTOMER_CODE_STATIC, m_stcCustomerCode);

	DDX_Text(pDX, IDC_CNO_EDIT, m_strID);
	DDX_Control(pDX, IDC_CNO_EDIT, m_edtCNo);
	DDX_Control(pDX, IDC_GROUP_NAME_STATIC, m_stcGroupName);
	DDX_Control(pDX, IDC_GROUP_NAME_EDIT, m_edtGroupName);
	DDX_Text(pDX, IDC_GROUP_NAME_EDIT, m_strGroupName);
	DDX_Control(pDX, IDC_GROUP_REFRESH_BTN, m_btnGroupRefresh);
	DDX_Control(pDX, IDC_CUSTOMER_NO_STATIC, m_stcCNo);

	DDX_Text(pDX, IDC_USER_ID_EDIT, m_strUserID);
	DDX_Control(pDX, IDC_USER_ID_EDIT, m_edtUserID);

	DDX_Text(pDX, IDC_COMPANY_EDIT, m_strCompany);
	DDX_Control(pDX, IDC_COMPANY_EDIT, m_edtCompany);

	DDX_Control(pDX, IDC_DEPART_STATIC, m_stcDepart);
	DDX_Control(pDX, IDC_MANAGER_STATIC, m_stcManager);
	DDX_Control(pDX, IDC_TEL_STATIC, m_stcTel);
	DDX_Control(pDX, IDC_MOBILE_STATIC, m_stcMobile);

	DDX_Text(pDX, IDC_DEPART_EDIT, m_strDepart);
	DDX_Control(pDX, IDC_DEPART_EDIT, m_edtDepart);
	DDX_Control(pDX, IDC_SNAME_EDIT, m_edtName);
	DDX_Text(pDX, IDC_SNAME_EDIT, m_strName);
	DDX_Text(pDX, IDC_MOBILE_EDIT, m_strMobile);
	DDX_Control(pDX, IDC_MOBILE_EDIT, m_edtMobile);
	DDX_Text(pDX, IDC_TEL_EDIT, m_strTel);
	DDX_Control(pDX, IDC_TEL_EDIT, m_edtTel);

	DDX_Control(pDX, IDC_RIDER_MEMO_STATIC, m_stcRiderMemo);
	DDX_Control(pDX, IDC_MEMO_STATIC, m_stcMemo);

	DDX_Control(pDX, IDC_USECOUNT_STATIC, m_stcUseCount);
	DDX_Control(pDX, IDC_FIRST_USE_STATIC, m_stcFirstUse);
	DDX_Control(pDX, IDC_LAST_STATIC, m_stcLastUse);
	DDX_Control(pDX, IDC_LOCATE_STATIC, m_stcLocate);
	DDX_Control(pDX, IDC_ADDRESS_STATIC, m_stcAddress);
	DDX_Control(pDX, IDC_BASEDONG_STATIC, m_stcBaseDong);
	DDX_Control(pDX, IDC_COMPANY_STATIC, m_stcCompany);

	DDX_Control(pDX, IDC_RIDER_MEMO_EDIT, m_edtRiderMemo);
	DDX_Text(pDX, IDC_RIDER_MEMO_EDIT, m_strRiderMemo);

	DDX_Control(pDX, IDC_MEMO_EDIT, m_edtMemo);
	DDX_Text(pDX, IDC_MEMO_EDIT, m_strMemo);

	DDX_Control(pDX, IDC_USECOUNT_EDIT, m_edtUseCount);
	DDX_Text(pDX, IDC_USECOUNT_EDIT, m_strUseCount);

	DDX_Text(pDX, IDC_FIRST_USE_EDIT, m_strFirstUse);
	DDX_Control(pDX, IDC_FIRST_USE_EDIT, m_edtFirstUse);

	DDX_Text(pDX, IDC_LAST_EDIT, m_strLastUse);
	DDX_Control(pDX, IDC_LAST_EDIT, m_edtLastUse);

	DDX_Control(pDX, IDC_ADDR_TITLE_EDIT, m_editAddrTitle);
	DDX_Text(pDX, IDC_ADDR_TITLE_EDIT, m_strAddrTitle);

	DDX_Control(pDX, IDC_LOCATE_EDIT, m_edtLocate);
	DDX_Text(pDX, IDC_LOCATE_EDIT, m_strLocation);

	DDX_Control(pDX, IDC_ADDR_DONG_EDIT, m_edtAddrDong);
	DDX_Text(pDX, IDC_ADDR_DONG_EDIT, m_strAddrDong);

	DDX_Control(pDX, IDC_DISPLAY_DONG_EDIT, m_edtDisplayDong);
	DDX_Text(pDX, IDC_DISPLAY_DONG_EDIT, m_strDisplayDong);

	DDX_Control(pDX, IDC_CREDIT_CHECK, m_chkCredit);
	DDX_Check(pDX, IDC_CREDIT_CHECK, m_bCredit);

	DDX_Control(pDX, IDC_ADDRESS_DISPLAY_STATIC, m_stcAddressDisplay);
	DDX_Control(pDX, IDC_CREDIT_STATIC, m_stcCredit);

	DDX_Control(pDX, IDC_TEL_ADD_STATIC, m_stcTelAdd);
	DDX_Control(pDX, IDC_TEL_ADD_EDIT, m_edtTelAdd);
	DDX_Control(pDX, IDC_TEL_ADD_BTN, m_btnTelAdd);
	DDX_Control(pDX, IDC_TEL_DEL_BTN, m_btnTelDel);

	DDX_Control(pDX, IDC_ETC_INFO_STATIC, m_stcEtcInfo);
	DDX_Control(pDX, IDC_STATIC1, m_stc1);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_edtSearch);
	DDX_Control(pDX, IDC_CHANGE_GROUP_BTN, m_btnChangeGroup);
	DDX_Control(pDX, IDC_NO_GROUP_BTN, m_btnNoGroup);
	DDX_Control(pDX, IDC_SHOW_MAP_BTN, m_btnShowMap);
}

BEGIN_MESSAGE_MAP(CCustomerDlgSub1, CMyFormView)
	ON_NOTIFY(NM_RCLICK, IDC_TEL_LIST, OnNMRClickList1)
	ON_NOTIFY(NM_DBLCLK, IDC_TEL_LIST, OnNMDblClickList1)
	ON_COMMAND(ID_CALL, OnMenuDelete)
	ON_COMMAND(ID_SMS, OnMenuMakePhone2)
	ON_COMMAND(ID_CALL_1, OnMenuMakeCall)
	ON_COMMAND(ID_SMS_1, OnMenuMakeSms)

	ON_BN_CLICKED(IDC_GROUP_REFRESH_BTN, &CCustomerDlgSub1::OnBnClickedGroupRefreshBtn)
	ON_BN_CLICKED(IDC_CHANGE_GROUP_BTN, &CCustomerDlgSub1::OnBnClickedChangeGroupBtn)
	ON_BN_CLICKED(IDC_NO_GROUP_BTN, &CCustomerDlgSub1::OnBnClickedNoGroupBtn)
	ON_EN_CHANGE(IDC_USER_ID_EDIT, &CCustomerDlgSub1::OnEnChangeUserIdEdit)
	ON_EN_CHANGE(IDC_COMPANY_EDIT, &CCustomerDlgSub1::OnEnChangeCompanyEdit)
	ON_BN_CLICKED(IDC_SMS_BUTTON, &CCustomerDlgSub1::OnBnClickedSmsButton)
	ON_EN_CHANGE(IDC_DEPART_EDIT, &CCustomerDlgSub1::OnEnChangeDepartEdit)
	ON_EN_CHANGE(IDC_SNAME_EDIT, &CCustomerDlgSub1::OnEnChangeSnameEdit)
	ON_EN_CHANGE(IDC_TEL_EDIT, &CCustomerDlgSub1::OnEnChangeTelEdit)
	ON_EN_CHANGE(IDC_MOBILE_EDIT, &CCustomerDlgSub1::OnEnChangeMobileEdit)
	ON_EN_CHANGE(IDC_MEMO_EDIT, &CCustomerDlgSub1::OnEnChangeMemoEdit)
	ON_EN_CHANGE(IDC_RIDER_MEMO_EDIT, &CCustomerDlgSub1::OnEnChangeRiderMemoEdit)
	ON_EN_CHANGE(IDC_ADDR_TITLE_EDIT, &CCustomerDlgSub1::OnEnChangeAddrTitleEdit)
	ON_EN_CHANGE(IDC_LOCATE_EDIT, &CCustomerDlgSub1::OnEnChangeLocateEdit)
	ON_EN_CHANGE(IDC_ADDR_DONG_EDIT, &CCustomerDlgSub1::OnEnChangeAddrDongEdit)
	ON_BN_CLICKED(IDC_SHOW_MAP_BTN, &CCustomerDlgSub1::OnBnClickedShowMapBtn)
	ON_BN_CLICKED(IDC_CREDIT_CHECK, &CCustomerDlgSub1::OnBnClickedCreditCheck)
	ON_BN_CLICKED(IDC_TEL_ADD_BTN, &CCustomerDlgSub1::OnBnClickedTelAddBtn)
	ON_BN_CLICKED(IDC_TEL_DEL_BTN, &CCustomerDlgSub1::OnBnClickedTelDelBtn)

	
	ON_COMMAND_RANGE_SINGLE(ID_MENU_SEND_SMS, OnMenuContextSms)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_RIDER_INFO, OnMenuContextSms)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_DELAY, OnMenuContextSms)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_INS_INFO, OnMenuContextSms)

	ON_NOTIFY(XTP_NM_REPORT_SELCHANGED, IDC_TEL_LIST, OnTelReportItemChange)

	ON_WM_PAINT()
	ON_EN_SETFOCUS(IDC_ADDR_DONG_EDIT, &CCustomerDlgSub1::OnEnSetfocusAddrDongEdit)
	ON_WM_CONTEXTMENU()
	ON_EN_CHANGE(IDC_SEARCH_EDIT, &CCustomerDlgSub1::OnEnChangeSearchEdit)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CCustomerDlgSub1 진단입니다.

#ifdef _DEBUG
void CCustomerDlgSub1::AssertValid() const
{
	CMyFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CCustomerDlgSub1::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCustomerDlgSub1 메시지 처리기입니다.

void CCustomerDlgSub1::OnBnClickedGroupRefreshBtn()
{
	char buffer[20];
	CXTPReportSelectedRows *pRows = m_pCustomerDlg->m_List.GetSelectedRows();

	if(pRows == NULL)
	{
		MessageBox("조회하실 그룹을 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	CUSTOMER_INFO *pc = (CUSTOMER_INFO*)m_pCustomerDlg->m_List.GetItemData(pRows->GetAt(0)->GetRecord());
	long nGNo = pc->nGNo;

	if(pc->nGNo <= 0)
	{
		MessageBox("해당 고객은 그룹에 등록되어 있지 않습니다.", "확인", MB_ICONINFORMATION);
		return;
	}


	m_pCustomerDlg->m_List.DeleteAllItems();
	m_pCustomerDlg->SearchGroupData((CString)itoa(pc->nGNo, buffer, 10), TRUE);
}

void CCustomerDlgSub1::OnBnClickedChangeGroupBtn()
{
	int nItem = m_pCustomerDlg->m_List.GetNextItem(-1, LVNI_SELECTED);
	if(nItem == -1) 
	{
		MessageBox("고객을 선택하시기 바랍니다", "확인", MB_ICONINFORMATION);
		return;
	}

	CUSTOMER_INFO *pc = (CUSTOMER_INFO*)m_pCustomerDlg->m_List.GetItemData(nItem);

	if(pc->bGroupOwner)
	{
		MessageBox("그룹오너를 해제하시고 그룹변경을 해주시기 바랍니다.", "확인", MB_ICONINFORMATION);
		return;
	}


	CSearchGroupDlg dlg;
	dlg.m_nCompany = m_pCustomerDlg->m_nCustomerTable;
	dlg.m_nDataType = SG_GROUP;

	char buffer[20];	

	if(dlg.DoModal() == IDOK)
	{
		CString strMsg;
		if(pc->nGNo <= 0)
			strMsg.Format("[%s]고객을 [%s] 멤버로 등록하시겠습니까?", pc->strCompany,
			dlg.m_strGroupName + "/" + dlg.m_strDeptName);
		else
			strMsg.Format("[%s]을 [%s] -> [%s] \n\r\n\r이동하시겠습니까?", pc->strCompany,
			m_cg.GetGroupData(pc->nGNo)->sGroupName + "/" + m_cg.GetGroupData(pc->nGNo)->sDept,
			dlg.m_strGroupName + "/" + dlg.m_strDeptName);

		COleDateTime dtDate(2000, 1, 1, 0, 0, 0);
		CString sNeedReportID ="";

		if(CMoveGroupDlg::CheckGroupReport(CString(itoa(pc->nGNo, buffer, 10)) + ";", dlg.m_nGNo, dtDate, 1, sNeedReportID) == FALSE) // 재정산이 필요한 리포트를 선정
			return;

		if(IDYES == MessageBox(strMsg, "그룹변경", MB_ICONQUESTION | MB_YESNO))
		{
			CMkCommand pCmd2(m_pMkDb, "update_group_input_1");
			pCmd2.AddParameter(typeLong, typeInput, sizeof(long), m_pCustomerDlg->m_nCustomerTable);    
			pCmd2.AddParameter(typeLong, typeInput, sizeof(long), pc->nCNo);    
			pCmd2.AddParameter(typeLong, typeInput, sizeof(long), dlg.m_nGNo);    
			pCmd2.AddParameter(typeLong, typeInput, sizeof(long), TRUE);    
			if(pCmd2.Execute())
			{
				if(sNeedReportID != "")
				{
					if(CMoveGroupDlg::ReReport(sNeedReportID))
						MessageBox("소속 그룹이 변경되었습니다", "확인", MB_ICONINFORMATION);
				}
				else
					MessageBox("소속 그룹이 변경되었습니다", "확인", MB_ICONINFORMATION);	

				m_pCustomerDlg->InitList();
			}

		}
	}
}

void CCustomerDlgSub1::OnBnClickedNoGroupBtn()
{
	char buffer[20];
	int nItem = m_pCustomerDlg->m_List.GetNextItem(-1, LVNI_SELECTED);

	if(nItem == -1) 
	{
		MessageBox("고객을 선택하시기 바랍니다", "확인", MB_ICONINFORMATION);
		return;
	}

	CUSTOMER_INFO *pc = (CUSTOMER_INFO*)m_pCustomerDlg->m_List.GetItemData(nItem);
	if(pc->nGNo <= 0)
	{
		MessageBox("해당고객은 그룹고객이 아닙니다.", "확인", MB_ICONINFORMATION);
		return;
	}

	CString strMsg;
	strMsg.Format("[%s] 고객을 [%s]그룹에서 배제하시겠습니까?", pc->strCompany,
		m_cg.GetGroupData(pc->nGNo)->sGroupName);

	if(IDYES == MessageBox(strMsg, "그룹해제", MB_ICONQUESTION | MB_YESNO))
	{
		COleDateTime dtDate(2000, 1, 1, 0, 0, 0);
		CString sNeedReportID ="";

		if(CMoveGroupDlg::CheckGroupReport(CString(itoa(pc->nGNo, buffer, 10)) + ";", pc->nGNo, dtDate, 1, sNeedReportID) == FALSE) // 재정산이 필요한 리포트를 선정
			return;


		CMkCommand pCmd2(m_pMkDb, "update_group_input_1");
		pCmd2.AddParameter(typeLong, typeInput, sizeof(long), m_pCustomerDlg->m_nCustomerTable);    
		pCmd2.AddParameter(typeLong, typeInput, sizeof(long), pc->nCNo);    
		pCmd2.AddParameter(typeLong, typeInput, sizeof(long), pc->nGNo);    
		pCmd2.AddParameter(typeLong, typeInput, sizeof(long), FALSE);    
		if(pCmd2.Execute())
		{
			if(sNeedReportID != "")
			{
				if(CMoveGroupDlg::ReReport(sNeedReportID))
					MessageBox("소속 그룹이 변경되었습니다", "확인", MB_ICONINFORMATION);
			}
			else
				MessageBox("소속 그룹이 변경되었습니다", "확인", MB_ICONINFORMATION);	

			m_pCustomerDlg->InitList();
		}
	}
}

void CCustomerDlgSub1::OnEnChangeUserIdEdit()
{
	m_pCustomerDlg->m_bDirty = TRUE;
}

void CCustomerDlgSub1::OnEnChangeCompanyEdit()
{
	m_pCustomerDlg->m_bDirty = TRUE;
}

void CCustomerDlgSub1::OnBnClickedSmsButton()
{
	CPoint pt;
	GetCursorPos(&pt);
	
	BCMenu rMenu;
	rMenu.LoadMenu(IDR_SMS_MENU);
	BCMenu *pRMenu = (BCMenu*)rMenu.GetSubMenu(0);

	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);	
}

void CCustomerDlgSub1::OnEnChangeDepartEdit()
{
	m_pCustomerDlg->m_bDirty = TRUE;
}

void CCustomerDlgSub1::OnEnChangeSnameEdit()
{
	m_pCustomerDlg->m_bDirty = TRUE;
}

void CCustomerDlgSub1::OnEnChangeTelEdit()
{
	m_pCustomerDlg->m_bDirty = TRUE;
}

void CCustomerDlgSub1::OnEnChangeMobileEdit()
{
	m_pCustomerDlg->m_bDirty = TRUE;
}

void CCustomerDlgSub1::OnEnChangeMemoEdit()
{
	m_pCustomerDlg->m_bDirty = TRUE;
}

void CCustomerDlgSub1::OnEnChangeRiderMemoEdit()
{
	m_pCustomerDlg->m_bDirty = TRUE;
}

void CCustomerDlgSub1::OnEnChangeAddrTitleEdit()
{
	m_pCustomerDlg->m_bDirty = TRUE;
}

void CCustomerDlgSub1::OnEnChangeLocateEdit()
{
	m_pCustomerDlg->m_bDirty = TRUE;
}

void CCustomerDlgSub1::OnEnChangeAddrDongEdit()
{
	SearchDong(FALSE);
}

void CCustomerDlgSub1::OnBnClickedShowMapBtn()
{
	m_pCustomerDlg->m_pPlace->ShowMap();
}

void CCustomerDlgSub1::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	//CXTPReportColumn *pCol = m_lstTel.InsertColumnReturn(0, "", LVCFMT_LEFT, 135);
	CXTPReportColumn *pCol = m_lstTel.AddColumn(new CXTPReportColumn(0, "", 135));
	m_lstTel.ShowHeader(FALSE);
	m_lstTel.GetPaintManager()->m_strNoItems = "";
	//m_lstTel.SetPaintManager(new CustomerPaintManager());
	m_lstTel.SetGridStyle(TRUE, xtpGridSolid);
	m_lstTel.SetGridColor(RGB(212, 208, 200));
	m_lstTel.GetPaintManager()->m_strNoItems = "";
	m_lstTel.SetFont(m_FontManager.GetFont("맑은 고딕", 20));
	m_lstTel.Populate();

	m_edtSearch.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtSearch.SetUserOption(RGB(0, 0, 0), RGB(555, 255, 255), "검 색");

	m_edtLocate.SetLimitText(500); 

	SetTimer(HIDE_SEARCH_DONG_LIST_TIMER, 100, NULL);
}

void CCustomerDlgSub1::OnBnClickedCreditCheck()
{
	m_pCustomerDlg->m_bDirty = TRUE;
}

void CCustomerDlgSub1::OnBnClickedTelAddBtn()
{
	CAddManagerDlg dlg(this);
	dlg.m_nCompany = m_pCustomerDlg->m_nCompanyCode;
	dlg.m_nCNo = m_pCustomerDlg->m_nCNo;
	m_edtName.GetWindowText(dlg.m_strManager);
	m_edtDepart.GetWindowText(dlg.m_strDepart);

	if(dlg.DoModal() == IDOK)
	{
		m_pCustomerDlg->InitOneList();
		m_cus.GetNewCustomer();
		//m_pCustomerDlg->RefreshTelList(dlg.m_nTelID);
		//m_pCustomerDlg->ChangeTelDepartInfo();
	}

	/*
	CString strTelAdd; m_edtTelAdd.GetWindowText(strTelAdd);
	strTelAdd = GetRemoveDDDNumber(strTelAdd);
	strTelAdd.Replace("-", "");

	CString strTel;
	CXTPReportRows *pRows = m_lstTel.GetRows();

	for(int i=0; i<pRows->GetCount(); i++)
	{
		CXTPReportRecord *pRecord = pRows->GetAt(i)->GetRecord();
		strTel = GetRemoveDDDNumber(m_lstTel.GetItemText(pRecord, 0));

		if(strTelAdd == strTel)
		{
			MessageBox("동일한 전화번호가 등록되어 있습니다", "확인", MB_ICONINFORMATION);
			return;
		}
	}

	if(m_pCustomerDlg->m_nCNo > 0 && strTelAdd.GetLength() > 0) 
	{
		CMkCommand pCmd(m_pMkDb, "insert_customer_phone");
		pCmd.AddParameter(m_pCustomerDlg->m_nCustomerTable);
		pCmd.AddParameter(m_pCustomerDlg->m_nCNo);
		pCmd.AddParameter(strTelAdd);

		if(pCmd.Execute())
			m_pCustomerDlg->SetTimer(TIMER_TEL_LIST, 500, NULL);		
	}
	*/
}

void CCustomerDlgSub1::OnBnClickedTelDelBtn()
{
	CXTPReportSelectedRows *pRows = m_lstTel.GetSelectedRows();

	if(pRows == NULL) {
		MessageBox("삭제할 데이터를 선택하시기 바랍니다.", 
			"확인", MB_ICONINFORMATION);
		return;
	}

	CXTPReportRow *pRow = pRows->GetAt(0);
	CXTPReportRecord *pRecord = pRow->GetRecord();

	CString strTel = pRecord->GetItem(0)->GetCaption(NULL);//m_lstTel.GetItemText(pRecord, 0);
	strTel = GetNoneDashNumber(strTel);

	if(strTel == "")
		return; 

	CString strMainTel; m_edtTel.GetWindowText(strMainTel);
	CString strMobile; m_edtMobile.GetWindowText(strMobile);

	strMainTel = GetNoneDashNumber(strMainTel);
	strMobile = GetNoneDashNumber(strMobile);

	BOOL bMainTelSame = FALSE;
	BOOL bHpSame = FALSE;

	if(strTel == strMainTel)
	{
		bMainTelSame = TRUE;

		if(MessageBox("전화1 번호가 삭제 됩니다", "확인", MB_OKCANCEL) != IDOK)
			 return;
	}

	if(strTel == strMobile)
	{
		bHpSame = TRUE;

		if(MessageBox("전화2 번호가 삭제 됩니다", "확인", MB_OKCANCEL) != IDOK)
			return;
	}
	

	//CWaitCursor wait;
	CMkCommand pCmd(m_pMkDb, "delete_customertel_2011");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_pCustomerDlg->m_nCustomerTable);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_pCustomerDlg->m_nCNo);
	pCmd.AddParameter(typeString, typeInput, strTel.GetLength(), strTel);
	pCmd.AddParameter(bMainTelSame);
	pCmd.AddParameter(bHpSame);
	pCmd.Execute();
	 
	//m_pCustomerDlg->SetTimer(TIMER_TEL_LIST, 500, NULL);

	m_lstTel.GetRecords()->RemoveAt(pRecord->GetIndex());

	//m_lstTel.GetRows()->RemoveAt(pRow->GetIndex());
	m_lstTel.Populate();

	if(bMainTelSame)
		m_edtTel.SetWindowText("");

	if(bHpSame)
		m_edtMobile.SetWindowText("");
}

void CCustomerDlgSub1::OnTimer(UINT_PTR nIDEvent)
{ 
	if(nIDEvent == HIDE_SEARCH_DONG_LIST_TIMER)
	{
		//if(GetFocus() != this)
		//	return;

		if(m_pCustomerDlg == NULL)
			return;		

		if(m_pCustomerDlg->m_pAddCustomerDlg)
		{
			if(m_pCustomerDlg->IsWindowVisible())
				return;
		}


		CSearchPOIDlg *pDlg = LU->GetSearchPOIDlg();
		if(pDlg)
		{
			if(pDlg->IsWindowVisible() &&
				GetForegroundWindow() != pDlg &&
				!pDlg->m_chkAlwaysShow.GetCheck())
			{ 
				CWnd *pWnd = GetFocus();
				if(pWnd->GetSafeHwnd() != NULL)			
				{
					if(pWnd != (CWnd*)&m_edtAddrDong)
					{
						LU->HideSearchPOIDlg();
					}
					else if(pWnd == (CWnd*)&m_edtAddrDong && m_edtAddrDong.GetWindowTextLength() == 0)
					{
						LU->HideSearchPOIDlg();				
					}
				}
				else
				{
					LU->HideSearchPOIDlg();
				}
			}
		}
	}

	CMyFormView::OnTimer(nIDEvent);
}

void CCustomerDlgSub1::OnMenuContextSms(UINT nFlag)
{
	if(nFlag == ID_MENU_SEND_SMS)
	{
		CCustomerSmsDlg2 dlg;

	m_edtTel.GetWindowText(dlg.m_strCustomerPN);

	if(dlg.m_strCustomerPN.Left(2) != "01")
		m_edtMobile.GetWindowText(dlg.m_strCustomerPN);


	dlg.m_strCustomerPN = dlg.m_strCustomerPN.GetLength() > 0 ? GetNoneDashNumber(dlg.m_strCustomerPN) : "";
	dlg.m_strRecvPN = m_ci.m_strOfficePhone;
	//dlg.m_strRecvPN = m_ci.m_strPhone;
	dlg.m_nCompany = m_pCustomerDlg->m_nCompanyCode;
	dlg.m_nContent = 0; //  임의 고객에 메세지전송
	//dlg.m_strRecvPN = encProfile.GetString("sms", "callback", "");
	//dlg.m_strMsg = 

	if(IDOK == dlg.DoModal())
	{
		CString strEtc;
		//encProfile.WriteString("sms", "callback", dlg.m_strRecvPN);

		dlg.m_strRecvPN = GetNoneDashNumber(dlg.m_strRecvPN);
		dlg.m_strCustomerPN = GetNoneDashNumber(dlg.m_strCustomerPN);

		SMS_INFO smsi;
		smsi = ::GetSMSBalance(::GetNowBranchCode()); 
		if(smsi.nSMSType >= 10)
		{
			if(DEFINE_SMS_AMOUNT > smsi.nSMSBarance)
			{
				MessageBox("SMS잔액이 부족합니다.","확인", MB_ICONINFORMATION);
				return;
			}
		}


		CString sql = "";

		if(dlg.m_bReservation)
			sql = "insert_sms_data_reservation";
		else
			sql = "insert_sms_data2";

		COleDateTime dtDate(COleDateTime::GetCurrentTime());

		dtDate.SetDateTime(dlg.m_dtReservationDate.GetYear(), dlg.m_dtReservationDate.GetMonth(),
			dlg.m_dtReservationDate.GetDay(), dlg.m_dtReservationTime.GetHour(), 
			dlg.m_dtReservationTime.GetMinute(), dlg.m_dtReservationTime.GetSecond());	


		CMkCommand pCmd(m_pMkDb, sql);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), dlg.m_nCompany);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), 100);
		pCmd.AddParameter(typeString, typeInput, dlg.m_strCustomerPN.GetLength(), dlg.m_strCustomerPN);
		pCmd.AddParameter(typeString, typeInput, dlg.m_strRecvPN.GetLength(), dlg.m_strRecvPN);
		pCmd.AddParameter(typeString, typeInput, dlg.m_strMsg.GetLength(), dlg.m_strMsg);
		pCmd.AddParameter(typeString, typeInput, strEtc.GetLength(), strEtc);
		if(dlg.m_bReservation)
		{
			pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), TRUE);
			pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtDate);
		}

		if(!pCmd.Execute()) 
		{
			MessageBox("SMS 전송을 실패하였습니다.", "전송실패", MB_ICONINFORMATION);
		}
		else {
			MessageBox("전송되었습니다.", "전송성공", MB_ICONINFORMATION);
		}
	}
	}
	else if(nFlag == ID_MENU_RIDER_INFO)
	{
		MessageBox("아직지원되지 않는 기능입니다.", "확인", MB_ICONINFORMATION);
	}
	else if(nFlag == ID_MENU_DELAY)
	{
		MessageBox("아직지원되지 않는 기능입니다.", "확인", MB_ICONINFORMATION);
	}
	else if(nFlag == ID_MENU_INS_INFO)
	{
		MessageBox("아직지원되지 않는 기능입니다.", "확인", MB_ICONINFORMATION);
	}
}
void CCustomerDlgSub1::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{

	CMyFormView::OnPrint(pDC, pInfo);
}

void CCustomerDlgSub1::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CLogiFunc::FillBackground(&dc, this); 

	if(m_pCustomerDlg == NULL) return;
	if(m_pCustomerDlg->m_pSub2 == NULL) return;

	m_stcEtcInfo.SetMarkupText(m_pCustomerDlg->m_pSub2->GetEtcInfo());
}

BOOL CCustomerDlgSub1::PreTranslateMessage(MSG* pMsg)
{  
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
 		if(pMsg->hwnd == m_edtUserID.GetSafeHwnd()) {
			m_edtCompany.SetFocus();
			m_edtCompany.SetSel(0xFFFF);
			return TRUE;
		}
		else if(pMsg->hwnd == m_edtCompany.GetSafeHwnd()) {
			m_edtTel.SetFocus();
			m_edtTel.SetSel(0xFFFF);
			return TRUE;
		}
		else if(pMsg->hwnd == m_edtTel.GetSafeHwnd()) {
			m_edtName.SetFocus();
			m_edtName.SetSel(0xFFFF);
			return TRUE;
		}
		else if(pMsg->hwnd == m_edtName.GetSafeHwnd()) {
			m_edtDepart.SetFocus();
			m_edtDepart.SetSel(0xFFFF);
			return TRUE;
		}
		else if(pMsg->hwnd == m_edtDepart.GetSafeHwnd()) {
			m_edtMobile.SetFocus();
			m_edtMobile.SetSel(0xFFFF);
			return TRUE;
		}
		else if(pMsg->hwnd == m_edtMobile.GetSafeHwnd()) 
		{
			m_edtAddrDong.SetFocus();
			return TRUE;
		}
		else if(pMsg->hwnd == m_edtDisplayDong.GetSafeHwnd()) {
			m_edtLocate.SetFocus();
			return TRUE;
		}
		else if(pMsg->hwnd == m_edtLocate.GetSafeHwnd()) {
			m_edtMemo.SetFocus();
			return TRUE;
		}
		else if(pMsg->hwnd == m_edtMemo.GetSafeHwnd()) {
			m_edtRiderMemo.SetFocus();
			return TRUE;
		}
		else if(pMsg->hwnd == m_edtRiderMemo.GetSafeHwnd()) {
			m_pCustomerDlg->m_btnOK.SetFocus();
			return TRUE;
		}
		else if(pMsg->hwnd == m_edtAddrDong.GetSafeHwnd()) 
		{
			//LU->OnAutoSelectEvent(TYPE_DONG, TRUE, 0, FALSE);
			LU->OnAutoSelectEvent(TYPE_AUTO, TRUE, 0, FALSE);

			if(m_pCustomerDlg->m_pPlace->GetPOI())
			{
				m_pCustomerDlg->SetDisplayAddrEdt();
				m_edtDisplayDong.SetFocus();
			}
			
			return TRUE;
		}
	}
	else if(pMsg->message == WM_LBUTTONDOWN && 
		pMsg->hwnd == m_edtMobile.GetSafeHwnd())
	{ 
		m_pCustomerDlg->OpenTelDlg();
		//return TRUE;
	}

	
	return CMyFormView::PreTranslateMessage(pMsg);
}

void CCustomerDlgSub1::OnEnSetfocusAddrDongEdit()
{
	SearchDong(TRUE);
}

void CCustomerDlgSub1::SearchDong(BOOL bFocus)
{
	if(LU->GetSearchPOIDlg())
	{
		if(bFocus == TRUE && LU->GetSearchPOIDlg()->m_bClosedByUser)
			return;
	} 

	CString strDong; m_edtAddrDong.GetWindowText(strDong);
	LU->ShowSearchPOIDlg(strDong, m_pCustomerDlg->m_pPlace, m_pCustomerDlg->m_nCustomerTable, m_pCustomerDlg, &m_edtAddrDong, &m_edtDisplayDong);
	m_pCustomerDlg->m_bDirty = TRUE; 
}

void CCustomerDlgSub1::OnMenuDelete()
{
	CXTPReportSelectedRows *pRows = m_lstTel.GetSelectedRows();

	if(pRows == NULL) return;
	if(pRows->GetCount() == ZERO) return;

	CXTPReportRecord *pRecord = (CXTPReportRecord*)pRows->GetAt(ZERO)->GetRecord();

	if(pRecord == NULL)
		return;

	STRUCT_TEL *st = (STRUCT_TEL*)m_lstTel.GetItemData(pRecord);

	if(st->nType == ONE)
	{
		MessageBox("대표번호는 삭제 하실 수 없습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	CMkCommand pCmd(m_pMkDb, "delete_customer_phone_with_manager");
	pCmd.AddParameter(m_pCustomerDlg->m_nCNo);
	pCmd.AddParameter(m_pCustomerDlg->m_nTelID);

	if(pCmd.Execute())
	{
		m_pCustomerDlg->InitOneList();
		m_cus.GetNewCustomer();
	}
}

void CCustomerDlgSub1::OnMenuMakePhone2()
{	
	CXTPReportSelectedRows *pRows = m_lstTel.GetSelectedRows();

	if(pRows == NULL) return;
	if(pRows->GetCount() == ZERO) return;

	CXTPReportRecord *pRecord = (CXTPReportRecord*)pRows->GetAt(ZERO)->GetRecord();

	if(pRecord == NULL)
		return;

	CMkCommand pCmd(m_pMkDb, "change_customer_main_phone");
	pCmd.AddParameter(m_pCustomerDlg->m_nCNo);
	pCmd.AddParameter(m_pCustomerDlg->m_nTelID);

	if(pCmd.Execute())
	{
		m_pCustomerDlg->InitOneList();
		m_cus.GetNewCustomer();
	}
}

void CCustomerDlgSub1::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{	
	CPoint pt;
	GetCursorPos(&pt);
	OnContextMenu(&m_lstTel, pt);
}

void CCustomerDlgSub1::OnNMDblClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{	
	m_pCustomerDlg->OnBnClickedOk();
}

void CCustomerDlgSub1::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_lstTel.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CXTPReportSelectedRows *pRows = m_lstTel.GetSelectedRows();

	if(pRows == NULL) return;
	if(pRows->GetCount() == ZERO) return;

	CXTPReportRecord *pRecord = (CXTPReportRecord*)pRows->GetAt(ZERO)->GetRecord();
	STRUCT_TEL *st = (STRUCT_TEL*)m_lstTel.GetItemData(pRecord);

	CString strTemp = "[" + ::GetDashPhoneNumber(st->strTel) + "]";

	CPoint pt; 
	GetCursorPos(&pt); 

	BCMenu rMenu;
	rMenu.LoadMenu(IDR_PHONE_MENU); 
	BCMenu *pRMenu = (BCMenu*)rMenu.GetSubMenu(2); 

	
	
	pRMenu->SetMenuText(ID_CALL, strTemp + " 삭제", MF_BYCOMMAND);
	pRMenu->SetMenuText(ID_SMS, strTemp + " 대표번호로 등록", MF_BYCOMMAND);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y,this);
}

void CCustomerDlgSub1::OnTelReportItemChange(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	//return;
	m_pCustomerDlg->ChangeTelDepartInfo();
}

void CCustomerDlgSub1::OnEnChangeSearchEdit()
{
	CString strSearch; m_edtSearch.GetWindowText(strSearch);
	CXTPReportRecords *pRecords = m_lstTel.GetRecords();

	for(int i=ZERO; i<pRecords->GetCount(); i++)
	{
		CXTPReportRecord *pRecord = pRecords->GetAt(i);
		STRUCT_TEL *st = (STRUCT_TEL*)m_lstTel.GetItemData(pRecord);

		CString strTel = st->strTel; 
		strTel.Replace("-", ""); 
  
		if(st->strTel.Find(strSearch) >= ZERO ||
			strTel.Find(strSearch) >= ZERO)
			pRecord->SetVisible(TRUE);
		else
			pRecord->SetVisible(FALSE);
	}

	m_lstTel.Populate();
}

void CCustomerDlgSub1::SelectFirstTelItem()
{
	CXTPReportSelectedRows *pRows = m_lstTel.GetSelectedRows();

	if(pRows == NULL) return;
	if(pRows->GetCount() == ZERO) return;

	CustomerDepartRecord *pRecord = (CustomerDepartRecord*)pRows->GetAt(ZERO)->GetRecord();

	if(pRecord == NULL)
		return;

	m_pCustomerDlg->ChangeTelDepartInfo();
	m_pCustomerDlg->m_btnOK.SetFocus();
}

void CCustomerDlgSub1::OnMenuMakeCall()
{
	CXTPReportSelectedRows *pRows = m_lstTel.GetSelectedRows();

	if(pRows == NULL) return;
	if(pRows->GetCount() == ZERO) return;

	CXTPReportRecord *pRecord = (CXTPReportRecord*)pRows->GetAt(ZERO)->GetRecord();

	if(pRecord == NULL)
		return;

	STRUCT_TEL *st = (STRUCT_TEL*)m_lstTel.GetItemData(pRecord);

	LU->GetRcpView()->MakeCall(m_pCustomerDlg->m_nCompanyCode, st->strTel);
}

void CCustomerDlgSub1::OnMenuMakeSms()
{
	CXTPReportSelectedRows *pRows = m_lstTel.GetSelectedRows();

	if(pRows == NULL) return;
	if(pRows->GetCount() == ZERO) return;

	CXTPReportRecord *pRecord = (CXTPReportRecord*)pRows->GetAt(ZERO)->GetRecord();

	if(pRecord == NULL)
		return;

	STRUCT_TEL *st = (STRUCT_TEL*)m_lstTel.GetItemData(pRecord);

	CCustomerSmsDlg2 dlg;
	dlg.m_strCustomerPN = st->strTel;

	dlg.m_strCustomerPN = dlg.m_strCustomerPN.GetLength() > 0 ? GetNoneDashNumber(dlg.m_strCustomerPN) : "";
	dlg.m_strRecvPN = m_ci.m_strOfficePhone;
	//dlg.m_strRecvPN = m_ci.m_strPhone;
	dlg.m_nCompany = m_ci.m_nCompanyCode;
	dlg.m_nContent = 0; //  임의 고객에 메세지전송

	if(IDOK == dlg.DoModal())
	{
		CString strEtc;

		dlg.m_strRecvPN = GetNoneDashNumber(dlg.m_strRecvPN);
		dlg.m_strCustomerPN = GetNoneDashNumber(dlg.m_strCustomerPN);

		COleDateTime dtDate(COleDateTime::GetCurrentTime());

		dtDate.SetDateTime(dlg.m_dtReservationDate.GetYear(), dlg.m_dtReservationDate.GetMonth(),
			dlg.m_dtReservationDate.GetDay(), dlg.m_dtReservationTime.GetHour(), 
			dlg.m_dtReservationTime.GetMinute(), dlg.m_dtReservationTime.GetSecond());

		BOOL bOk = FALSE;

		if(dlg.m_bReservation)
			bOk = ::SendSmsNewRev(m_ci.m_nCompanyCode, 777, dlg.m_strCustomerPN, dlg.m_strRecvPN, dlg.m_strMsg, "접수프로그램(임의)", "", "", dtDate);
		else
			bOk = ::SendSmsNew(m_ci.m_nCompanyCode, 777, dlg.m_strCustomerPN, dlg.m_strRecvPN, dlg.m_strMsg, "접수프로그램(임의)", "", "");


		if(bOk) 
		{
			MessageBox("전송되었습니다.", "전송성공", MB_ICONINFORMATION);
		}
		else {
			MessageBox("SMS 전송을 실패하였습니다.", "전송실패", MB_ICONINFORMATION);
		}
	}

}