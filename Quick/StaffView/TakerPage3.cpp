// TakerPage3.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "TakerPage3.h"
#include "SMSRegister.h"
#include "SMSDocViewDlg.h"
#include "SmsRegisterManagerDlg.h"
#include "SmsRegisterLogDlg.h"
#include "CallBackPhoneRoleDlg.h"
// CTakerPage3

#define  TYPE_DAERI 0
#define  TYPE_QUICK 1

#define EMPTY_STATE		0
#define REGISTER_STATE	1
#define LOGI_STATE		2
#define FINISH_STATE	3
#define REJECT_STATE	4
#define ERROR_STATE		5

#define LOGI_STATE_CONTENT		"로지에서 진행상태"
#define FINISH_STATE_CONTENT	"로지에서 종료상태"


#define TELECOM_DOC_COLUMN 8
#define IDENTITY_CARD_DOC_COLUMN 10


#define  TELECOM_DOC 0
#define  BUSINESS_DOC 1

#define  SMSCALBACK_MEMO					53   // 메모

IMPLEMENT_DYNCREATE(CTakerPage3, CMyFormView)

CTakerPage3::CTakerPage3()
: CMyFormView(CTakerPage3::IDD)
{
	m_pSMSDocViewDlg = NULL;
}

CTakerPage3::~CTakerPage3()
{
	DELETE_OBJECT(m_pSMSDocViewDlg);
}

void CTakerPage3::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT_LIST100, m_lstReport);

	DDX_Control(pDX, IDC_TEL_TYPE_COMBO, m_cmbTelType);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_edtSearch);
	DDX_Control(pDX, IDC_STATIC1, m_stc1);
	DDX_Control(pDX, IDC_STATIC10, m_stc10);
	DDX_Control(pDX, IDC_STATIC75, m_stc75);
}

BEGIN_MESSAGE_MAP(CTakerPage3, CMyFormView)	
	
	ON_BN_CLICKED(IDC_SEARCH_BTN, &CTakerPage3::OnBnClickedSearchBtn)
	ON_EN_CHANGE(IDC_SEARCH_EDIT, &CTakerPage3::OnEnChangeSearchEdit)
	ON_NOTIFY(NM_RCLICK, IDC_REPORT_LIST100, OnReportItemRClick)
	ON_NOTIFY(NM_DBLCLK, IDC_REPORT_LIST100, OnReportItemDblClick)
	ON_NOTIFY(NM_CLICK, IDC_REPORT_LIST100, OnReportItemSMSCallBackLog)
	ON_WM_CONTEXTMENU()
	//ON_BN_CLICKED(IDC_ALL_REGISTER_BTN, &CTakerPage3::OnBnClickedAllRegisterBtn)
	ON_MESSAGE(WM_USER + 200, OnReportRefresh)
	ON_NOTIFY(XTP_NM_GRID_HYPERLINK, IDC_REPORT_LIST100, OnReportHyperlinkClick)
	ON_BN_CLICKED(IDC_REGISTER_BTN, &CTakerPage3::OnBnClickedRegisterBtn)
	ON_BN_CLICKED(IDC_MODIFY_BTN, &CTakerPage3::OnBnClickedModifyBtn)

	/*ON_COMMAND(ID_TO_EXCEL, OnToExcel)*/
	ON_COMMAND(ID_MENU_USE, OnMenuUse)
	ON_COMMAND(ID_MENU_NOT_USE, OnMenuNotUse)
	ON_COMMAND(ID_MENU_CORP_TYPE0, OnMenCorpType0)
	ON_COMMAND(ID_MENU_CORP_TYPE1, OnMenCorpType1)
	ON_COMMAND(ID_MENU_MANAGER, OnMenuManager)

	ON_COMMAND(ID_MENU_SHOW_DETAIL, OnMenuShowDetail)
	ON_COMMAND(ID_MENU_SHOW_LOG, OnMenuShowLog)
	ON_COMMAND(ID_MENU_CANCEL_AGREE, OnMenuCancelAgree)
	
	ON_BN_CLICKED(IDC_SHOW_BTN, &CTakerPage3::OnBnClickedShowBtn)
END_MESSAGE_MAP()

// CTakerPage3 진단입니다.

#ifdef _DEBUG
void CTakerPage3::AssertValid() const
{
	CMyFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CTakerPage3::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTakerPage3 메시지 처리기입니다.

void CTakerPage3::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();
	int nLogCol = 0;

	m_lstReport.InsertColumn(0, "순번",		LVCFMT_CENTER, 40);
	m_lstReport.InsertColumn(1, "지사명",	LVCFMT_LEFT, 90);
	m_lstReport.InsertColumn(2, "대표/상황실", LVCFMT_LEFT, 90);
	m_lstReport.InsertColumn(3, "발신번호", LVCFMT_LEFT, 98);
	m_lstReport.InsertColumn(4, "내용",		LVCFMT_LEFT, 65);
	m_lstReport.InsertColumn(5, "번호사용",		LVCFMT_CENTER, 50);
	m_lstReport.InsertColumn(6, "진행상태",		LVCFMT_CENTER, 70);
	m_lstReport.InsertColumn(7, "사업자/개인",	LVCFMT_LEFT, 65);
	m_lstReport.InsertColumn(8, "통신사실상태",		LVCFMT_CENTER, 80);
	m_lstReport.InsertColumn(9, "신분증상태",	LVCFMT_CENTER, 70);

	m_lstReport.InsertColumn(10, "담당자",	LVCFMT_LEFT, 90);
	m_lstReport.InsertColumn(11, "담당자전화번호",	LVCFMT_LEFT, 110);

	m_lstReport.SetOrderIndexCol(0);

	/*
	m_lstReport.InsertColumn(12, "등록일",	LVCFMT_CENTER, 90);
	m_lstReport.InsertColumn(13, "등록자",	LVCFMT_CENTER, 60);
	m_lstReport.InsertColumn(14, "등록회사",LVCFMT_CENTER, 90);
	*/

	m_lstReport.Populate();
	m_lstReport.SetFreezeColumnsCount(6);
	//////////////////////////////////
	

	//m_stc1.SetBkColor(RGB(255, 230 , 230));

	m_cmbTelType.SetCurSel(0);

	m_stc10.SetWindowText("※ 서류 등록(수정) 후 반드시 로지소프트(1599-0707)로 연락주세요");
	m_stc10.SetTextColor(RGB(255, 0, 0));
	m_stc10.SetAlign(DT_LEFT);
	m_stc75.SetWindowText("※ 발신전화번호는 <통신사실증명원>에 기재된 번호와 동일한 경우에만 승인 가능합니다");
	m_stc75.SetTextColor(RGB(255, 0, 0));
	m_stc75.SetAlign(DT_LEFT);

	RefreshList();

	SetResize(IDC_REPORT_LIST100, sizingRightBottom);
}

void CTakerPage3::RefreshList()
{
	CMyFormView::RefreshList();

	UpdateData(TRUE); 


	InnerDeleteAllItem();


	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_smscallback_tel_customer_1");
	cmd.AddParameter(GetCurBranchInfo()->nCompanyCode);
	cmd.AddParameter(GetCurBranchInfo()->bIntegrated);
	cmd.AddParameter(m_cmbTelType.GetCurSel());
	if(!rs.Execute(&cmd)) return;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		RefreshSub(&rs, NULL);
		rs.MoveNext();
	}

	m_lstReport.Populate();
}

void CTakerPage3::RefreshSub(CMkRecordset *pRs, CXTPGridRecord *pRecord)
{
	CString strBranchName, strName, strTel, strEtc, strTelecomUrl, strIdentityCardUrl,strWComapnyName;
	CString strDelCompanyName, strOriginalTel;
	long	nNo, nCompany,nTelType, nUse, nState, nCorpType, nTelecomState, nIdentityCardState,nWNo, nWCompany;
	long	nDelWNo, nDelCompany,    nPBXBoth, nPBXDocState;
	COleDateTime dtRegister, dtRelease;
	CString strTelecomUrlView = "",  strIdentityCardView = "", strPBXView = "", strRandChar = "", strPBXDocUrl = "";
	CString strContactName = "", strContactNumber = "";

	pRs->GetFieldValue("sBranchName",			strBranchName);
	pRs->GetFieldValue("nNo",					nNo);
	pRs->GetFieldValue("nCompany",			nCompany);
	pRs->GetFieldValue("sOriginalTel",		strOriginalTel);
	pRs->GetFieldValue("sTel",				strTel);
	pRs->GetFieldValue("nTelType",			nTelType);
	pRs->GetFieldValue("sEtc",				strEtc);
	pRs->GetFieldValue("nUse",				nUse);
	pRs->GetFieldValue("nState",				nState);
	pRs->GetFieldValue("nCorpType",			nCorpType);
	pRs->GetFieldValue("nTelecomState",		nTelecomState);
	pRs->GetFieldValue("sTelecomUrl",			strTelecomUrl);
	pRs->GetFieldValue("nIdentityCardState",	nIdentityCardState);
	pRs->GetFieldValue("sIdentityCardUrl",	strIdentityCardUrl);
	pRs->GetFieldValue("dtRegister",			dtRegister);
	pRs->GetFieldValue("dtRelease",			dtRelease);
	pRs->GetFieldValue("nWNo",				nWNo);
	pRs->GetFieldValue("nWCompany",			nWCompany);
	pRs->GetFieldValue("sWCompanyName",		strWComapnyName);

	pRs->GetFieldValue("nDelWNo",				nDelWNo);
	pRs->GetFieldValue("nDelCompany",			nDelCompany);
	pRs->GetFieldValue("sDelCompanyName",		strDelCompanyName);

	pRs->GetFieldValue("nPBXBoth",			nPBXBoth);
	pRs->GetFieldValue("sPBXDocUrl",			strPBXDocUrl);
	pRs->GetFieldValue("nPBXDocState",		nPBXDocState);
	pRs->GetFieldValue("sRandChar",			strRandChar);

	pRs->GetFieldValue("sContactName",		strContactName);
	pRs->GetFieldValue("sContactNumber",		strContactNumber);

	TakePage3Struct *pTakerPage3 = NULL;
	
	if(pRecord == NULL)
		pTakerPage3 = new TakePage3Struct;
	else
		pTakerPage3 = (TakePage3Struct*)m_lstReport.GetItemData(pRecord);
	
	if(nIdentityCardState >= REGISTER_STATE)
		strIdentityCardView = "보기(클릭)";

	if(nTelecomState >= REGISTER_STATE)
		strTelecomUrlView = "보기(클릭)";

	if(nPBXDocState >= REGISTER_STATE)
		strPBXView = "보기";	

	if(pRecord == NULL)
		pRecord = m_lstReport.InsertItemReturn(m_lstReport.GetRecords()->GetCount(), "");


	pTakerPage3->nNo				=  nNo;
	pTakerPage3->nCompany			=  nCompany;
	pTakerPage3->strTel				=  strTel;
	pTakerPage3->nState				=  nState;
	pTakerPage3->nIdentityCardState =  nIdentityCardState;
	pTakerPage3->strIdentityCardUrl	=  strIdentityCardUrl;
	pTakerPage3->nTelecomState		=  nTelecomState;
	pTakerPage3->strTelecomUrl		=  strTelecomUrl;

	pTakerPage3->nPBXBoth			=  nPBXBoth;
	pTakerPage3->sPBXDocUrl			=  strPBXDocUrl;
	pTakerPage3->nPBXDocState		=  nPBXDocState;
	pTakerPage3->sRandChar			=  strRandChar;

	m_lstReport.SetItemText(pRecord, 1, strBranchName);		
	m_lstReport.SetItemText(pRecord, 2, ::GetDashPhoneNumber(strOriginalTel));
	m_lstReport.SetItemText(pRecord, 3, ::GetDashPhoneNumber(strTel));
	m_lstReport.SetItemText(pRecord, 4, strEtc);
	m_lstReport.SetItemText(pRecord, 5, ::GetSMSTelUse(nUse));
	m_lstReport.SetItemText(pRecord, 6, ::GetSMSFileStateType(nState));
	m_lstReport.SetItemText(pRecord, 7, ::GetSMSTelCorp(nCorpType));
	m_lstReport.SetItemText(pRecord, 8, ::GetSMSFileStateType(nTelecomState, nTelType));
	m_lstReport.SetItemText(pRecord, 9, ::GetSMSFileStateType(nIdentityCardState, nTelType));
	m_lstReport.SetItemText(pRecord, 10, strContactName);
	m_lstReport.SetItemText(pRecord, 11, strContactNumber);

	m_lstReport.SetItemLong(pRecord, nCompany);
	m_lstReport.SetItemLong2(pRecord, nNo);
	m_lstReport.SetItemLong3(pRecord, nState);
	m_lstReport.SetItemDataText(pRecord,::GetSMSFileStateType(nState));
	m_lstReport.SetItemDataText2(pRecord,strTelecomUrl);
	m_lstReport.SetItemDataText3(pRecord,strIdentityCardUrl);

	m_lstReport.SetItemData(pRecord,(DWORD)pTakerPage3);
}

void CTakerPage3::OnReportHyperlinkClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;
	if(!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	/*
	// if click on Hyperlink in Item
	if (pItemNotify->nHyperlink >= 0)
	{



		int nRow = pItemNotify->pRow->GetIndex();
		int nCol = pItemNotify->pColumn->GetItemIndex();

		CXTPGridRecord *pRecord = pItemNotify->pRow->GetRecord();


		CString strTelecomUrl = m_lstReport.GetItemDataText2(pRecord);
		CString strIdentyCardUrl = m_lstReport.GetItemDataText3(pRecord);

		int TYPE_DAERI = 0;
		CString strHTTP = "";


		if(nCol == TELECOM_DOC_COLUMN)
		{
			strHTTP = CSMSAllRegisterDlg::GetWebFolder(TYPE_DAERI, TELECOM_DOC);
			ShowDocView(strHTTP + strTelecomUrl);
		}
		else
		{
			strHTTP = CSMSAllRegisterDlg::GetWebFolder(TYPE_DAERI, BUSINESS_DOC);
			ShowDocView(strHTTP +strIdentyCardUrl);
		}
	}
	*/
}


void CTakerPage3::ShowDocView(CString strUrl)
{
	if(m_pSMSDocViewDlg == NULL)
	{
		m_pSMSDocViewDlg = new CSMSDocViewDlg(this);
		m_pSMSDocViewDlg->Create(CSMSDocViewDlg::IDD);
	}

	m_pSMSDocViewDlg->m_strUrl = strUrl	;
	m_pSMSDocViewDlg->DocView();

	m_pSMSDocViewDlg->ShowWindow(SW_SHOW);

	/*
	CREATE_MODALESS(CSMSDocViewDlg, this);
	pDlg->m_strUrl = strUrl	;
	SHOW_MODALESS(CSMSDocViewDlg, this);
	*/
}


void CTakerPage3::InnerDeleteAllItem()
{
	for(int i = 0; i < m_lstReport.GetRecords()->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = m_lstReport.GetRecords()->GetAt(i);
		TakePage3Struct *pTakepage =(TakePage3Struct *)m_lstReport.GetItemData(pRecord);
		if(pTakepage)
		{
			delete pTakepage;
			pTakepage = NULL;
		}

	}

	m_lstReport.DeleteAllItems();
}

void CTakerPage3::OnBnClickedSearchBtn()
{
	RefreshList();
}
void CTakerPage3::OnBnClickedAllRegisterBtn()
{
	//CSMSAllRegisterDlg dlg;
	//dlg.DoModal();

	/*CREATE_MODALESS(CSMSAllRegisterDlg, this);
	SHOW_MODALESS(CSMSAllRegisterDlg, this);*/
}


void CTakerPage3::OnEnChangeSearchEdit()
{
	FilterList();
}

void CTakerPage3::FilterList()
{
	CXTPGridRecords *pRecords = m_lstReport.GetRecords();
	CString strSearch; m_edtSearch.GetWindowText(strSearch);
	CString strTelSearch = strSearch;
	strTelSearch.Replace("-", "");
	
	 
	if( ::IsStringDigit(strTelSearch) && strTelSearch.GetLength() > 6 )
	{
		strTelSearch = ::GetDashPhoneNumber(strTelSearch);
		m_lstReport.Filter(strTelSearch);
	}
	else
		m_lstReport.Filter(strSearch);



	m_lstReport.Populate();
}

void CTakerPage3::OnToExcel()
{
	if(!POWER_CHECK(5900, "엑셀변환", TRUE))
		return;

	AddSecurityLog(GetCurBranchInfo()->nCompanyCode, 404, m_ui.nWNo, m_lstReport.GetItemCount());  
	CMyExcel::ToExcel(&m_lstReport);
}

void CTakerPage3::OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow/* || !pItemNotify->pColumn*/)
		return;

	CPoint pt;
	GetCursorPos(&pt);
	OnContextMenu(&m_lstReport, pt);
}


void CTakerPage3::OnReportItemSMSCallBackLog(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	//CBranchInfo *pBi = m_cBranch.GetBranchInfo();

	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	CXTPGridRecord *pRecord = pItemNotify->pRow->GetRecord();
	long nTelNo = 0, nCompany = 0;
	nTelNo		= m_lstReport.GetItemLong2(pRecord);
	nCompany	= m_lstReport.GetItemLong(pRecord);
	
	long nCol = pItemNotify->pColumn->GetItemIndex();

	if( nCol == TELECOM_DOC_COLUMN || nCol == IDENTITY_CARD_DOC_COLUMN )
	{

		CString strHTTP = "";

		TakePage3Struct *pTakerPage3;
		pTakerPage3 = (TakePage3Struct *)m_lstReport.GetItemData(pRecord);

		BOOL bIntegrated = FALSE; 
		long nDocViewCount = 0;
		bIntegrated = m_ci.GetShareCode1() == pTakerPage3->nCompany ? TRUE : FALSE;
		nDocViewCount += pTakerPage3->nTelecomState			> 0 ? 1 : 0;
		nDocViewCount += pTakerPage3->nIdentityCardState	> 0 ? 2 : 0;

		if(nCol == TELECOM_DOC_COLUMN)
		{ 
			CString strTelecomUrl = m_lstReport.GetItemDataText2(pRecord);

			if( strTelecomUrl.GetLength() > 0)
			{
				strHTTP = GetWebFolder(TYPE_QUICK, TELECOM_DOC); 
				ShowDocView(strHTTP + strTelecomUrl);

			}
			else
			{
				if(pTakerPage3->nTelecomState > 0)
					MessageBox("업로드 된 데이터가 없습니다.", "확인", MB_ICONINFORMATION);
			}

		}
		else
		{
			CString strIdentyCardUrl = m_lstReport.GetItemDataText3(pRecord);

			if(strIdentyCardUrl.GetLength() > 0)
			{
				strHTTP = GetWebFolder(TYPE_QUICK, BUSINESS_DOC);
				ShowDocView(strHTTP + strIdentyCardUrl);
			}
			else
			{
				if(pTakerPage3->nIdentityCardState > 0)
					MessageBox("업로드 된 데이터가 없습니다.", "확인", MB_ICONINFORMATION);
			}
		}
	}
}

void CTakerPage3::OnBnClickedModifyBtn()
{

	if( m_lstReport.GetSelectedRows()->GetCount() <= 0)
	{
		MessageBox("적용할 행을 클릭후 수정버튼을 눌러주세요", "확인", MB_ICONINFORMATION);
		return;
	}
	long nModifyNo = 0;
	CXTPGridRow *pRow = m_lstReport.GetSelectedRows()->GetAt(0);
	CXTPGridRecord *pRecord = (CXTPGridRecord *)pRow->GetRecord();

	if(pRecord)
	{
		long nCompany = m_lstReport.GetItemLong(pRecord);
		nModifyNo =  m_lstReport.GetItemLong2(pRecord);
		long nLogiState =  m_lstReport.GetItemLong3(pRecord);
		if( nLogiState == 2 || nLogiState == 3)
		{
			MessageBox("로지에서 진행중인건은 비고및 발신번호 사용/미사용만 수정가능합니다", "확인", MB_ICONINFORMATION);		
		}

		if(nModifyNo <= 0) return;

		CREATE_MODALESS(CSMSRegister, this);
		pDlg->m_nModifyNo = nModifyNo;
		pDlg->m_nModifyCompany = nCompany;
		pDlg->m_pParent = this;
		SHOW_MODALESS(CSMSRegister, this);

	}
	WorkGofromRefresh(nModifyNo);

}


void CTakerPage3::OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow/* || !pItemNotify->pColumn*/)
		return;
	
	//CXTPGridRecord *pRecord = (CXTPGridRecord *)pItemNotify->pRow->GetRecord();

	/*
	CXTPGridRecord *pRecord = m_lstReport.GetFirstSelectedRecord();

	if(pRecord == NULL)
		return;

	long nCompany = m_lstReport.GetItemLong(pRecord);
	long nModifyNo =  m_lstReport.GetItemLong2(pRecord);
	long nLogiState =  m_lstReport.GetItemLong3(pRecord);

	if( nLogiState == 2 || nLogiState == 3)
	{
		MessageBox("로지에서 진행중인건은 비고및 발신번호 사용/미사용만 수정가능합니다", "확인", MB_ICONINFORMATION);		
	}

	if(nModifyNo <= 0) return;

	CREATE_MODALESS(CSMSRegister, this);
	pDlg->m_nModifyNo = nModifyNo;
	pDlg->m_nModifyCompany = nCompany;
	pDlg->m_pParent = this;
	SHOW_MODALESS(CSMSRegister, this);

	WorkGofromRefresh(nModifyNo);
	*/

	OnBnClickedModifyBtn();
}

void CTakerPage3::WorkGofromRefresh(long nModifyNo)
{
	long nCount = m_lstReport.GetRows()->GetCount();

	for(int i = 0; i < nCount; i ++)
	{
		long nSMSNo = 0;
		CXTPGridRow *pRow = m_lstReport.GetRows()->GetAt(i);
		CXTPGridRecord *pRecord =	pRow->GetRecord();
		nSMSNo = m_lstReport.GetItemLong2(pRecord);
		if(nModifyNo == nSMSNo)
		{
			pRow->SetSelected(TRUE);
			m_lstReport.SetFocusedRow(pRow, FALSE,FALSE);
			return;
		}
	}
}

void CTakerPage3::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_lstReport.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU_1);
	CMenu *pRMenu=rMenu.GetSubMenu(16);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}

void CTakerPage3::OnBnClickedRegisterBtn()
{
	/*
	CREATE_MODALESS(CSMSRegister, this);
	pDlg->m_bNew = TRUE;
	pDlg->m_pParent = this;
	SHOW_MODALESS(CSMSRegister, this);
	*/
}

CXTPGridRecord* CTakerPage3::FindRecordFromNo(long nNo)
{
	CXTPGridRecords *pRcords = m_lstReport.GetRecords();

	for(int i=0; i<pRcords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRcords->GetAt(i);
		TakePage3Struct *pTakepage = (TakePage3Struct *)m_lstReport.GetItemData(pRecord);

		if(pTakepage->nNo == nNo)
		{
			return pRecord;
		}
	}

	return NULL;
}

BOOL CTakerPage3::RefreshOneRecord(long nNo, CXTPGridRecord *pRecord)
{
	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_smscallback_tel_customer_one"); 
	cmd.AddParameter(nNo);

	if(!rs.Execute(&cmd)) 
		return -1;

	if(rs.GetRecordCount() == 0)
		return  -1;

	RefreshSub(&rs, pRecord);

	return 0;
}

LONG CTakerPage3::OnReportRefresh(WPARAM wParam, LPARAM lParam)
{
	long nModifyID = (UINT)wParam;
	if(nModifyID <= 0) return -1;

	CXTPGridRecord *pFindRecord = FindRecordFromNo(nModifyID);

	if(pFindRecord == NULL)
		return -1;

	RefreshOneRecord(nModifyID, pFindRecord);
	m_lstReport.RedrawControl();
	

	return 0;


}

void CTakerPage3::UpdateMenuUse(BOOL bUse)
{
	long nCount = 0;

	CXTPGridSelectedRows *pRows = m_lstReport.GetSelectedRows();

	for(int i=0; i<pRows->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRows->GetAt(i)->GetRecord();

		TakePage3Struct *pTakepage = (TakePage3Struct *)m_lstReport.GetItemData(pRecord);
		
		CMkCommand cmd(m_pMkDb, "update_sms_call_back_1");
		CMkParameter *parRet = cmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
		cmd.AddParameter(pTakepage->nNo);
		cmd.AddParameter(bUse);
		cmd.AddParameter(m_ui.nCompany);
		cmd.AddParameter(m_ui.nWNo);
		cmd.AddParameter(m_ui.strName);

		if(!cmd.Execute())
			return;

		long nTemp; parRet->GetValue(nTemp);

		if(nTemp > 0)
		{
			nCount++;
			RefreshOneRecord(pTakepage->nNo, pRecord);
		}
	}

	CString strTemp = "";
	strTemp.Format("%d건에 적용 되었습니다", nCount);
	MessageBox(strTemp, "확인", MB_ICONINFORMATION);
	m_lstReport.RedrawControl();
}

void CTakerPage3::UpdateMenuCorpType(long nCorpType)
{
	long nCount = 0;

	CXTPGridSelectedRows *pRows = m_lstReport.GetSelectedRows();

	for(int i=0; i<pRows->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRows->GetAt(i)->GetRecord();

		TakePage3Struct *pTakepage = (TakePage3Struct *)m_lstReport.GetItemData(pRecord);

		CMkCommand cmd(m_pMkDb, "update_sms_call_back_corp_type_1");
		CMkParameter *parRet = cmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
		cmd.AddParameter(pTakepage->nNo);
		cmd.AddParameter(nCorpType);
		cmd.AddParameter(m_ui.nCompany);
		cmd.AddParameter(m_ui.nWNo);
		cmd.AddParameter(m_ui.strName);

		if(!cmd.Execute())
			return;

		long nTemp; parRet->GetValue(nTemp);

		if(nTemp > 0)
		{
			nCount++;
			RefreshOneRecord(pTakepage->nNo, pRecord);
		}
	}

	CString strTemp = "";
	strTemp.Format("%d건에 적용 되었습니다", nCount);
	MessageBox(strTemp, "확인", MB_ICONINFORMATION);
	m_lstReport.RedrawControl();
}

void CTakerPage3::OnMenuUse()
{
	UpdateMenuUse(TRUE);
}

void CTakerPage3::OnMenuNotUse()
{
	UpdateMenuUse(FALSE);
}

void CTakerPage3::OnMenCorpType0()
{
	UpdateMenuCorpType(1);
}

void CTakerPage3::OnMenCorpType1()
{
	UpdateMenuCorpType(2);
}

void CTakerPage3::OnMenuManager()
{
	CSmsRegisterManagerDlg dlg;
	 
	
	if(dlg.DoModal() != IDOK)
		return;
	
	long nCount = 0;

	CXTPGridSelectedRows *pRows = m_lstReport.GetSelectedRows();

	for(int i=0; i<pRows->GetCount(); i++)
	{ 
		CXTPGridRecord *pRecord = pRows->GetAt(i)->GetRecord();

		TakePage3Struct *pTakepage = (TakePage3Struct *)m_lstReport.GetItemData(pRecord);

		CMkCommand cmd(m_pMkDb, "update_sms_call_back_contact_1");
		CMkParameter *parRet = cmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
		cmd.AddParameter(pTakepage->nNo);
		cmd.AddParameter(dlg.m_strName);
		cmd.AddParameter(dlg.m_strJobTitle);
		cmd.AddParameter(dlg.m_strNumber);
		cmd.AddParameter(m_ui.nCompany);
		cmd.AddParameter(m_ui.nWNo);
		cmd.AddParameter(m_ui.strName);

		if(!cmd.Execute())
			return;

		long nTemp; parRet->GetValue(nTemp);

		if(nTemp > 0)
		{
			nCount++;
			RefreshOneRecord(pTakepage->nNo, pRecord);
		}
	}

	CString strTemp = "";
	strTemp.Format("%d건에 적용 되었습니다", nCount);
	MessageBox(strTemp, "확인", MB_ICONINFORMATION);
	m_lstReport.RedrawControl();
}

void CTakerPage3::OnMenuShowDetail()
{
	OnBnClickedModifyBtn();
}

void CTakerPage3::OnMenuShowLog()
{
	CXTPGridRecord *pRecord = m_lstReport.GetFirstSelectedRecord();

	if(pRecord == NULL)
		return;

	CREATE_MODALESS(CSmsRegisterLogDlg, this);
	pDlg->m_nCompany = m_lstReport.GetItemLong(pRecord);
	pDlg->m_nTelNo = m_lstReport.GetItemLong2(pRecord);
	SHOW_MODALESS(CSmsRegisterLogDlg, this);	
}

void CTakerPage3::OnMenuCancelAgree()
{
	CXTPGridRecord *pRecord = m_lstReport.GetFirstSelectedRecord();

	if(pRecord == NULL)
		return;

	TakePage3Struct *pTakepage = (TakePage3Struct *)m_lstReport.GetItemData(pRecord);

	if(pTakepage->nState != 3)
	{
		MessageBox("승인 상태만 미승인 상태로 변경 하실 수 있습니다", "확인",  MB_ICONINFORMATION);
		return;
	}

	if(MessageBox("미승인 상태로 변경하시겠습니까?\r\n변경하면 SMS전송을 하실 수 없습니다.", "확인", MB_OKCANCEL) != IDOK)
		return;
	
	CMkCommand cmd(m_pMkDb, "update_sms_call_back_state_1");
	cmd.AddParameter(pTakepage->nNo);
	cmd.AddParameter(1);
	cmd.AddParameter(m_ui.nCompany);
	cmd.AddParameter(m_ui.nWNo);
	cmd.AddParameter(m_ui.strName);

	if(cmd.Execute())
		RefreshOneRecord(pTakepage->nNo, pRecord);
}


void CTakerPage3::OnBnClickedShowBtn()
{
	CREATE_MODALESS(CCallBackPhoneRoleDlg, this);
	SHOW_MODALESS(CCallBackPhoneRoleDlg, this);
}

CString CTakerPage3::GetWebFolder(long nServiceType, long nDocType)
{
	CString strUrl = "";
	if(nServiceType == TYPE_DAERI) strUrl = "http://smsdoc.logisoft.co.kr/Daeri/";
	if(nServiceType == TYPE_QUICK) strUrl = "http://smsdoc.logisoft.co.kr/Quick/";

	strUrl += (nDocType == TELECOM_DOC) ?  "telecom/" : "bussiness/";
	return strUrl;
}