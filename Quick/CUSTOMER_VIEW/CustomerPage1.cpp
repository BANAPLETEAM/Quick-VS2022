// CustomerDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "CustomerDlg.h"
#include "CustomerPage1.h"
#include "AddCustomerDlg.h"
#include "RcpView.h"
#include "RcpDlg.h"
#include "SumCnoDlg.h"

#define ST_WORD_RANGE_NEW1 10
#define ST_WORD_RANGE_NEW2 11
#define ST_WORD_RANGE_NEW3 12
#define ST_CNO_NEW 13

// CCustomerPage1 대화 상자입니다.

IMPLEMENT_DYNCREATE(CCustomerPage1, CMyFormView)
CCustomerPage1::CCustomerPage1()
: CMyFormView(CCustomerPage1::IDD)
, m_stredtID(_T(""))
{
	m_sCompany = "";
	m_sTel1 = "";
	m_sDong = "";
	m_sLocation = "";
	m_nItem = 0;
	m_bCredit = FALSE;
	m_sDepart = "";
	m_sName = "";
	m_nDiscount = 0;
	m_strData = "";
	iReturnVal = 0;
	m_bFirst = FALSE;
	m_strFilter = "";
	m_strSort = "";

	m_nCNo = 0;
	m_nSearchType = 0;

	m_pDragImage = NULL;
	m_pDragWnd = NULL;
}

CCustomerPage1::~CCustomerPage1()
{
}

void CCustomerPage1::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_CNO, m_strID);
	DDX_Text(pDX, IDC_EDIT_COMPANY, m_sCompany);
	DDX_Text(pDX, IDC_EDIT_TEL, m_sTel1);
	DDX_Text(pDX, IDC_EDIT_DONG, m_sDong);
	DDX_Text(pDX, IDC_EDIT_LOCATE, m_sLocation);
	DDX_Text(pDX, IDC_EDIT_DEPART, m_sDepart);
	DDX_Text(pDX, IDC_EDIT_SNAME, m_sName);
	DDX_Text(pDX, IDC_EDIT_DISCOUNT, m_nDiscount);
	DDX_Text(pDX, IDC_EDIT_DATA, m_strData);
	DDX_Text(pDX, IDC_MOBILE_EDIT, m_strMobile);
	DDX_Text(pDX, IDC_MEMO_EDIT, m_strMemo);

	DDX_Control(pDX, IDC_LIST1, m_lcData);
	DDX_Control(pDX, IDC_LIST_TEL, m_lcTel);
	DDX_Control(pDX, IDC_EDIT_DATA, m_ctrlData);
	DDX_Control(pDX, IDC_EDIT_LOCATE, m_LocateEdit);
	DDX_Control(pDX, IDC_EDIT_CNO, m_CNoEdit);
	DDX_Control(pDX, IDC_EDIT_COMPANY, m_CompanyEdit);
	DDX_Control(pDX, IDC_EDIT_DEPART, m_DepartEdit);
	DDX_Control(pDX, IDC_EDIT_DISCOUNT, m_DiscountEdit);
	DDX_Control(pDX, IDC_EDIT_DONG, m_DongEdit);
	DDX_Control(pDX, IDC_EDIT_SNAME, m_SNameEdit);
	DDX_Control(pDX, IDC_EDIT_TEL, m_TelEdit);
	DDX_Control(pDX, IDC_TEL_ADD_EDIT, m_TelAddEdit);
	DDX_Control(pDX, IDC_MEMO_EDIT, m_MemoEdit);
	DDX_Control(pDX, IDC_MOBILE_EDIT, m_MobileEdit);

	DDX_Control(pDX, IDC_LOCATE_STATIC, m_LocateStatic);
	DDX_Control(pDX, IDC_TEL_ADD_STATIC, m_TelAddStatic);
	DDX_Control(pDX, IDC_SEARCH_STATIC, m_SearchStatic);
	DDX_Control(pDX, IDC_CUSTOMER_NO_STATIC, m_CustomerNoStatic);
	DDX_Control(pDX, IDC_COMPANY_STATIC, m_CompanyStatic);
	DDX_Control(pDX, IDC_CREDIT_STATIC, m_CreditStatic);
	DDX_Control(pDX, IDC_BASEDONG_STATIC, m_BaseDongStatic);
	DDX_Control(pDX, IDC_DEPART_STATIC, m_DepartStatic);
	DDX_Control(pDX, IDC_TEL_STATIC, m_TelStatic);
	DDX_Control(pDX, IDC_DISCOUNT_STATIC, m_DiscountStatic);
	DDX_Control(pDX, IDC_MANAGER_STATIC, m_ManagerStatic);
	DDX_Control(pDX, IDC_MOBILE_STATIC, m_MobileStatic);
	DDX_Control(pDX, IDC_MEMO_STATIC, m_MemoStatic);
	DDX_Control(pDX, IDC_ALLOC_GROUP_STATIC2, m_AllocGroupStatic);
	DDX_Control(pDX, IDC_COUPON_STATIC, m_CouponStatic);

	DDX_Control(pDX, IDC_CHECK1, m_CreditCheck);
	DDX_Control(pDX, IDC_TEAM_STATIC, m_TeamStatic);
	DDX_Control(pDX, IDC_TEAM_COMBO, m_TeamCombo);
	DDX_Control(pDX, IDC_TEAM_SEARCH_COMBO, m_TeamSearchCombo);
	DDX_Control(pDX, IDC_ALLOC_GROUP_COMBO, m_AllocGroupCombo);
	DDX_Control(pDX, IDC_COUPON_COMBO, m_CouponCombo);

	DDX_Check(pDX, IDC_CHECK1, m_bCredit);
	DDX_Check(pDX, IDC_MIDWORD_CHECK, m_bCheckMidWord);

	DDX_Control(pDX, IDC_BUTTON_0, m_IndexBtn0);
	DDX_Control(pDX, IDC_BUTTON_1, m_IndexBtn1);
	DDX_Control(pDX, IDC_BUTTON_2, m_IndexBtn2);
	DDX_Control(pDX, IDC_BUTTON_3, m_IndexBtn3);
	DDX_Control(pDX, IDC_BUTTON_4, m_IndexBtn4);
	DDX_Control(pDX, IDC_BUTTON_5, m_IndexBtn5);
	DDX_Control(pDX, IDC_BUTTON_6, m_IndexBtn6);
	DDX_Control(pDX, IDC_BUTTON_7, m_IndexBtn7);
	DDX_Control(pDX, IDC_BUTTON_8, m_IndexBtn8);
	DDX_Control(pDX, IDC_BUTTON_9, m_IndexBtn9);
	DDX_Control(pDX, IDC_BUTTON_10, m_IndexBtn10);
	DDX_Control(pDX, IDC_BUTTON_11, m_IndexBtn11);
	DDX_Control(pDX, IDC_BUTTON_12, m_IndexBtn12);
	DDX_Control(pDX, IDC_BUTTON_13, m_IndexBtn13);
	DDX_Control(pDX, IDC_BUTTON_14, m_IndexBtn14);

	DDX_Control(pDX, IDC_BUTTON_SEARCH, m_SearchBtn);
	DDX_Control(pDX, IDC_TEAM_SEARCH_BTN, m_TeamSearchBtn);
	DDX_Control(pDX, IDC_BUTTON_TELADD, m_TelAddBtn);
	DDX_Control(pDX, IDC_BUTTON_TELDEL, m_TelDelBtn);
	DDX_Control(pDX, IDC_BUTTON_NEW, m_NewBtn);
	DDX_Control(pDX, IDC_BUTTON_EDIT, m_EditBtn);
	DDX_Control(pDX, IDC_BUTTON_DEL, m_DelBtn);

	DDX_Control(pDX, IDC_ID_STATIC, m_IdStc);
	DDX_Control(pDX, IDC_EDIT_ID, m_edtID);
	DDX_Text(pDX, IDC_EDIT_ID, m_stredtID);
	DDX_Control(pDX, IDC_SEARCH_COMBO, m_cmbSearch);
	DDX_Control(pDX, IDC_EDIT_SEARCH, m_edtSearch);
}


BEGIN_MESSAGE_MAP(CCustomerPage1, CMyFormView)
	ON_NOTIFY(NM_CLICK , IDC_LIST1 , OnReportItemClick) //아이템 선택
	ON_NOTIFY(LVN_BEGINDRAG, IDC_LIST1, OnReportBeginDrag)
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_NEW, OnBnClickedButtonNew)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, OnBnClickedButtonEdit)
	ON_BN_CLICKED(IDC_BUTTON_DEL, OnBnClickedButtonDel)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, OnBnClickedButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_TELADD, OnBnClickedButtonTeladd)
	ON_BN_CLICKED(IDC_BUTTON_TELDEL, OnBnClickedButtonTeldel)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_BN_CLICKED(IDC_BUTTON_0, OnBnClickedButton0)
	ON_BN_CLICKED(IDC_BUTTON_1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_2, OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON_3, OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON_4, OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON_5, OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON_6, OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON_7, OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON_8, OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON_9, OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON_10, OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON_11, OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON_12, OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON_13, OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON_14, OnBnClickedButton14)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_TEAM_SEARCH_BTN, OnBnClickedTeamSearchBtn)
	ON_EN_CHANGE(IDC_EDIT_SEARCH, &CCustomerPage1::OnEnChangeEditSearch)
END_MESSAGE_MAP()


// CCustomerPage1 메시지 처리기입니다.

void CCustomerPage1::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	m_bFirst = true;
	m_TeamCombo.SetCurSel(0);
	m_LocateEdit.SetFontSize(17);
	m_MemoEdit.SetFontSize(17);

	LU->MakeAllocateGroupCombo(&m_AllocGroupCombo);
	m_AllocGroupCombo.SetCurSel(0);

	CImageList m_ImageList; 
	m_ImageList.Create(1,17,ILC_COLOR,1,1); 

	m_lcData.SetImageList(&m_ImageList,LVSIL_SMALL); 

	m_lcData.SetFont(m_FontManager.GetFont("돋움", 13));
	m_lcData.ModifyStyle(0, LVS_SHOWSELALWAYS);
	m_lcData.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_FLATSB | 
		LVS_EX_GRIDLINES | LVS_EX_SUBITEMIMAGES);

	//컬럼 생성
	m_lcData.InsertColumn(0 , "번호" , LVCFMT_LEFT   , 60);
	m_lcData.InsertColumn(1, "상호", LVCFMT_LEFT,140);
	m_lcData.InsertColumn(2, "부서", LVCFMT_LEFT,100);
	m_lcData.InsertColumn(3, "담당", LVCFMT_LEFT,80);
	m_lcData.InsertColumn(4, "전화번호", LVCFMT_LEFT,110);
	m_lcData.InsertColumn(5, "검색코드", LVCFMT_LEFT,90);
	m_lcData.InsertColumn(6, "고객ID", LVCFMT_LEFT,90);
	m_lcData.InsertColumn(7, "기준동", LVCFMT_LEFT,90);
	m_lcData.InsertColumn(8, "위치", LVCFMT_LEFT,140);
	m_lcData.InsertColumn(9, "신용", LVCFMT_LEFT,45);
	m_lcData.InsertColumn(10, "가산금", LVCFMT_LEFT,140);
	m_lcData.InsertColumn(11, "주소", LVCFMT_LEFT,140);
	m_lcData.InsertColumn(12, "고객메모", LVCFMT_LEFT,150);
	m_lcData.InsertColumn(13, "기사메모", LVCFMT_LEFT,150);


	m_LocateEdit.SetLimitText(500);
	m_lcData.SetFocus();

	m_hcArrow = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
	m_hcNo = AfxGetApp()->LoadStandardCursor(IDC_NO);
	m_hcMoveHold = AfxGetApp()->LoadCursor(IDC_MOVEHOLD);

	m_cmbSearch.SetCurSel(0);

	UpdateData(FALSE);
	m_lcData.Populate();


	SetResize(IDC_LIST1, sizingRightBottom);
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CCustomerPage1::OnRefreshList()
{
	CString csCNo;
	CString csTemp;
	int nItem = 0;

	m_lcData.DeleteAllItems();
	m_lcData.Populate();

	CString sSearchData; m_ctrlData.GetWindowText(sSearchData);

	long nCNo, nID, nTeamNo;
	CString strCompany, strDepart, strName;
	CString strTel1, strDong, strLocation, strPost, strMemo, strMobile, strUserID, strAddress, strRiderMemo, strLoginID;
	BOOL bCredit;
	int nDiscount, nAllocGroup, nCouponCharge;
	long nPreID = -1;
	
	if(m_strKeyword.IsEmpty()) return;

	CMkCommand pCmd(m_pMkDb, "search_customer8");
	CMkRecordset pRs(m_pMkDb);

	CMkParameter * pPar = pCmd.AddParameter(typeLong, typeReturn, sizeof(long));
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nSearchType);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), LF->GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeString, typeInput, m_strKeyword.GetLength(), m_strKeyword);

	if(!pRs.Execute(&pCmd)) return;

	long nRet; pPar->GetValue(nRet);

	if(nRet == 1)
	{
		MessageBox("기준동이 정확하지 않습니다", "확인", MB_ICONINFORMATION);
		return;
	}


	while(!pRs.IsEOF())
	{	
		pRs.GetFieldValue("nCNo", nCNo);
		pRs.GetFieldValue("nID", nID);
		pRs.GetFieldValue("sCompany", strCompany);
		pRs.GetFieldValue("sDepart", strDepart);
		pRs.GetFieldValue("sName", strName);
		pRs.GetFieldValue("sTel1", strTel1);
		pRs.GetFieldValue("sDong", strDong);
		pRs.GetFieldValue("sLocation", strLocation);
		pRs.GetFieldValue("bCredit", bCredit);
		pRs.GetFieldValue("nDiscount", nDiscount);
		pRs.GetFieldValue("nTeamNo", nTeamNo);
		pRs.GetFieldValue("nAllocGroup", nAllocGroup);
		pRs.GetFieldValue("nCouponCharge", nCouponCharge);
		pRs.GetFieldValue("sMemo", strMemo);
		pRs.GetFieldValue("sMobile", strMobile);
		pRs.GetFieldValue("sUserID", strUserID);
		pRs.GetFieldValue("sAddress", strAddress);
		pRs.GetFieldValue("sRiderMemo", strRiderMemo);
		pRs.GetFieldValue("sLoginID", strLoginID);

		m_lcData.InsertItem(nItem , nPreID == nID ? "" : LF->GetStringFromLong(nID));
		m_lcData.SetItemText(nItem, 1, strCompany);
		m_lcData.SetItemText(nItem, 2, strDepart);
		m_lcData.SetItemText(nItem, 3, strName);
		m_lcData.SetItemText(nItem, 4, LF->GetDashPhoneNumber(strTel1));
		m_lcData.SetItemText(nItem, 5, strUserID);
		m_lcData.SetItemText(nItem, 6, strLoginID);		
		m_lcData.SetItemText(nItem, 7, strDong);
		m_lcData.SetItemText(nItem, 8, strLocation);
		m_lcData.SetItemText(nItem, 9, bCredit ? "신용" : "");
		m_lcData.SetItemText(nItem, 10 , LF->GetStringFromLong(nDiscount));
		m_lcData.SetItemText(nItem, 11, strAddress);
		m_lcData.SetItemText(nItem , 12 , strMemo);
		m_lcData.SetItemText(nItem , 13 , strRiderMemo);

		m_lcData.SetItemData(nItem , nCNo);

		nPreID = nID;
		++nItem;
		pRs.MoveNext();

	}

	pRs.Close();

	UpdateData(FALSE);

	OnEnChangeEditSearch();
	//m_lcData.Populate();
}

void CCustomerPage1::OnBnClickedButtonNew()
{
	CAddCustomerDlg dlg;
	dlg.m_nCustomerTable = LF->GetCurBranchInfo()->nCustomerTable;

	//dlg.m_strCompany = m_strSearchName;
	//dlg.m_strTel = m_strCID.IsEmpty() ? m_strSearchPhone : m_strCID;

	if(dlg.DoModal() == IDOK)
	{
		if(dlg.m_nCNo > 0) {
			m_nCNo = dlg.m_nCNo;
			AddPhoneNumber(dlg.m_strTel, dlg.m_strMobile);
			m_strKeyword.Format("%d ", m_nCNo);
			m_nSearchType = ST_CNO_NEW;
			OnRefreshList();
		}
	}
}

void CCustomerPage1::OnBnClickedButtonEdit()
{
	if(MessageBox("고객 정보를 수정하시겠습니까?","고객수정", MB_YESNO | MB_ICONQUESTION)== IDYES)
	{
		
		CString strPhone1, strPhone2;
		UpdateData(TRUE);
		m_lcData.Populate();

		//remove some dash
		strPhone1 = LF->GetNoneDashNumber(m_sTel1);
		strPhone2 = LF->GetNoneDashNumber(m_strMobile);

		if(!LF->IsPhoneNumber(strPhone1) || !LF->IsPhoneNumber(strPhone2))
		{
			MessageBox("전화번호에 숫자/대쉬 이외의 문자는 사용하실수 없습니다.",
				"조건확인", MB_ICONINFORMATION);
			return;
		}

		if(strPhone1.Left(m_ci.m_strDDD.GetLength()) == m_ci.m_strDDD)
			strPhone1 = strPhone1.Right(strPhone1.GetLength() - m_ci.m_strDDD.GetLength());

		if(strPhone2.Left(m_ci.m_strDDD.GetLength()) == m_ci.m_strDDD)
			strPhone2 = strPhone2.Right(strPhone2.GetLength() - m_ci.m_strDDD.GetLength());


		if(m_sCompany.GetLength() < 2) 
		{
			MessageBox("상호명을 입력하여 주시기바랍니다.", 
				"조건확인", MB_ICONINFORMATION);
			return;
		}

		CString strTeam, strCouponCharge;
		m_TeamCombo.GetWindowText(strTeam);
		m_CouponCombo.GetWindowText(strCouponCharge);

		CMkCommand pCmd(m_pMkDb, "edit_customer6");
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nCNo);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), LF->GetCurBranchInfo()->nCompanyCode);
		pCmd.AddParameter(typeString, typeInput, m_sCompany.GetLength(), m_sCompany);
		pCmd.AddParameter(typeString, typeInput, m_sDepart.GetLength(), m_sDepart);
		pCmd.AddParameter(typeString, typeInput, m_sName.GetLength(), m_sName);
		pCmd.AddParameter(typeString, typeInput, strPhone1.GetLength(), strPhone1);
		pCmd.AddParameter(typeString, typeInput, m_sDong.GetLength(), m_sDong);
		pCmd.AddParameter(typeString, typeInput, m_sLocation.GetLength(), m_sLocation);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_bCredit);
		pCmd.AddParameter(typeInt, typeInput, sizeof(int), m_nDiscount);
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), (strTeam == "일반") ? 0 : atol(strTeam));
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), 
			(int)m_AllocGroupCombo.GetItemData(m_AllocGroupCombo.GetCurSel()));
		pCmd.AddParameter(typeString, typeInput, m_strMobile.GetLength(), m_strMobile);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), atol(strCouponCharge));
		pCmd.AddParameter(typeString, typeInput, m_strMemo.GetLength(), m_strMemo);
		pCmd.AddParameter(typeString, typeInput, m_stredtID.GetLength(), m_stredtID);
		if(!pCmd.Execute()) return;
		AddPhoneNumber(strPhone1, strPhone2, TRUE);
	}
}

void CCustomerPage1::OnBnClickedButtonDel()
{
	if(MessageBox("해당 고객을 정말 삭제하시겠습니까?", 
		"확인", MB_YESNO | MB_ICONINFORMATION) == IDYES)
	{
		
		UpdateData(TRUE);
		//m_lcData.Populate();
		CMkCommand pCmd(m_pMkDb, "delete_customer_1");
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nCNo);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), LF->GetCurBranchInfo()->nCompanyCode);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nWNo);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nCompany);

		CString sEtc = "고객관리탭 삭제";
		pCmd.AddParameter(sEtc);

		pCmd.Execute();
		OnRefreshList();
	}
}

void CCustomerPage1::OnBnClickedButtonSearch()
{
	UpdateData(TRUE);
	m_lcData.Populate();

	m_ctrlData.GetWindowText(m_strKeyword); 

	if(m_strData.IsEmpty()) return;
	m_nSearchType = m_cmbSearch.GetCurSel();

	OnRefreshList();
}

void CCustomerPage1::OnBnClickedOk()
{
	//OnOK();
}

void CCustomerPage1::OnBnClickedButtonTeladd()
{
	CString strTel;
	UpdateData(TRUE);
	m_lcData.Populate();

	if(m_nCNo > 0) {
		m_TelAddEdit.GetWindowText(strTel);
		AddPhoneNumber(strTel);
	}
}

void CCustomerPage1::AddPhoneNumber(CString strTel, CString strMobile, BOOL bMsgHide)
{
	CString strTemp;

	//remove some dash
	strTel = LF->GetNoneDashNumber(strTel);
	strMobile = LF->GetNoneDashNumber(strMobile);

	if(strTel.GetLength() < 5 && 
		strMobile.GetLength() < 5) return;

	if(!LF->IsPhoneNumber(strTel) || !LF->IsPhoneNumber(strMobile))
	{
		if(!bMsgHide) 
			MessageBox("숫자/대쉬 이외의 문자는 사용하실수 없습니다.", 
			"확인", MB_ICONEXCLAMATION);
		return;
	}

	//remove a local DDD number, if the number is not this country...just go~
	if(strTel.Left(m_ci.m_strDDD.GetLength()) == m_ci.m_strDDD)
		strTel = strTel.Right(strTel.GetLength() - m_ci.m_strDDD.GetLength());

	if(strMobile.Left(m_ci.m_strDDD.GetLength()) == m_ci.m_strDDD)
		strMobile = strMobile.Right(strMobile.GetLength() - m_ci.m_strDDD.GetLength());


	for(int i = 0; i < m_lcTel.GetCount(); i++)
	{
		m_lcTel.GetText(i, strTemp);
		if(LF->GetNoneDashNumber(strTemp) == strTel) 
		{
			strTel = "";
		}

		if(LF->GetNoneDashNumber(strTemp) == strMobile) 
		{
			strMobile = "";
		}
	}

	m_lcTel.AddString(LF->GetDashPhoneNumber(strTel));
	m_lcTel.SetCaretIndex(m_lcTel.GetCount());

	
	CMkCommand pCmd(m_pMkDb, "insert_phone_number2");
	CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(long)); 
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), LF->GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nCNo);
	pCmd.AddParameter(typeString, typeInput, strTel.GetLength(), strTel);
	pCmd.AddParameter(typeString, typeInput, strMobile.GetLength(), strMobile);
	pCmd.Execute();
}


void CCustomerPage1::OnBnClickedButtonTeldel()
{
	CString csTemp;
	int nIndex = m_lcTel.GetCurSel();
	if(nIndex < 0) {
		MessageBox("삭제할 데이터를 선택하시기 바랍니다.", 
			"확인", MB_ICONINFORMATION);
		return;
	}

	m_lcTel.GetText(nIndex,csTemp);
	csTemp = LF->GetNoneDashNumber(csTemp);

	
	CMkCommand pCmd(m_pMkDb, "delete_customertel");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), LF->GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nCNo);
	pCmd.AddParameter(typeString, typeInput, csTemp.GetLength(), csTemp);
	pCmd.Execute();
	m_lcTel.DeleteString(nIndex);
}

void CCustomerPage1::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_lcData.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(2);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}

void CCustomerPage1::OnViewExcel()
{	
	if(!LF->POWER_CHECK(6900, "엑셀변환", TRUE))
		return

		LF->AddSecurityLog(LF->GetCurBranchInfo()->nCompanyCode, 201, m_ui.nWNo, m_lcData.GetItemCount());  
	CMyExcel::ToExcel(&m_lcData); //조성일1005
}

void CCustomerPage1::OnBnClickedButton0()
{
	m_nSearchType = ST_WORD_RANGE_NEW1;
	m_strKeyword = "가";
	OnRefreshList();
}

void CCustomerPage1::OnBnClickedButton1()
{
	m_nSearchType = ST_WORD_RANGE_NEW2;
	m_strKeyword = "가나";
	OnRefreshList();
}


void CCustomerPage1::OnBnClickedButton2()
{
	m_nSearchType = ST_WORD_RANGE_NEW2;
	m_strKeyword = "나다";
	OnRefreshList();
}

void CCustomerPage1::OnBnClickedButton3()
{
	m_nSearchType = ST_WORD_RANGE_NEW2;
	m_strKeyword = "다라";
	OnRefreshList();
}

void CCustomerPage1::OnBnClickedButton4()
{
	m_nSearchType = ST_WORD_RANGE_NEW2;
	m_strKeyword = "라마";
	OnRefreshList();
}

void CCustomerPage1::OnBnClickedButton5()
{
	m_nSearchType = ST_WORD_RANGE_NEW2;
	m_strKeyword = "마바";
	OnRefreshList();
}

void CCustomerPage1::OnBnClickedButton6()
{
	m_nSearchType = ST_WORD_RANGE_NEW2;
	m_strKeyword = "바사";
	OnRefreshList();
}

void CCustomerPage1::OnBnClickedButton7()
{
	m_nSearchType = ST_WORD_RANGE_NEW2;
	m_strKeyword = "사아";
	OnRefreshList();
}

void CCustomerPage1::OnBnClickedButton8()
{
	m_nSearchType = ST_WORD_RANGE_NEW2;
	m_strKeyword = "아자";
	OnRefreshList();
}

void CCustomerPage1::OnBnClickedButton9()
{
	m_nSearchType = ST_WORD_RANGE_NEW2;
	m_strKeyword = "자차";
	OnRefreshList();
}

void CCustomerPage1::OnBnClickedButton10()
{
	m_nSearchType = ST_WORD_RANGE_NEW2;
	m_strKeyword = "차카";
	OnRefreshList();
}

void CCustomerPage1::OnBnClickedButton11()
{
	m_nSearchType = ST_WORD_RANGE_NEW2;
	m_strKeyword = "카타";
	OnRefreshList();
}

void CCustomerPage1::OnBnClickedButton12()
{
	m_nSearchType = ST_WORD_RANGE_NEW2;
	m_strKeyword = "타파";
	OnRefreshList();
}

void CCustomerPage1::OnBnClickedButton13()
{
	m_nSearchType = ST_WORD_RANGE_NEW2;
	m_strKeyword = "파하";
	OnRefreshList();
}

void CCustomerPage1::OnBnClickedButton14()
{
	m_nSearchType = ST_WORD_RANGE_NEW3;
	m_strKeyword = "하";
	OnRefreshList();
}

void CCustomerPage1::OnTimer(UINT nIDEvent)
{
	KillTimer(nIDEvent);

	if(m_nCNo != 0)
	{
		CString strTel;
		m_lcTel.ResetContent();
		CMkCommand pCmd(m_pMkDb, "select_customertel");
		CMkRecordset pRs(m_pMkDb);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), LF->GetCurBranchInfo()->nCompanyCode);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nCNo);

		if(!pRs.Execute(&pCmd)) return;
		while(!pRs.IsEOF()) {
			CString strTel;
			pRs.GetFieldValue(0, strTel);
			m_lcTel.AddString(LF->GetDashPhoneNumber(strTel));
			pRs.MoveNext();
		}

		pRs.Close();
	}
	CMyFormView::OnTimer(nIDEvent);
}

BOOL CCustomerPage1::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{	
		if(pMsg->hwnd == m_ctrlData.GetSafeHwnd()) {
			OnBnClickedButtonSearch();
			return TRUE;
		}
		else if(pMsg->hwnd == m_CompanyEdit.GetSafeHwnd()) {
			m_DepartEdit.SetFocus();
			m_DepartEdit.SetSel(0xFFFF);
			return TRUE;
		}
		else if(pMsg->hwnd == m_DepartEdit.GetSafeHwnd()) {
			m_SNameEdit.SetFocus();
			m_SNameEdit.SetSel(0xFFFF);
			return TRUE;
		}
		else if(pMsg->hwnd == m_SNameEdit.GetSafeHwnd()) {
			m_TelEdit.SetFocus();
			m_TelEdit.SetSel(0xFFFF);
			return TRUE;
		}
		else if(pMsg->hwnd == m_TelEdit.GetSafeHwnd()) {
			m_DongEdit.SetFocus();
			m_DongEdit.SetSel(0xFFFF);
			return TRUE;
		}
		else if(pMsg->hwnd == m_DongEdit.GetSafeHwnd()) {
			m_CreditCheck.SetFocus();
			return TRUE;
		}
		else if(pMsg->hwnd == m_CreditCheck.GetSafeHwnd()) {
			m_DiscountEdit.SetFocus();
			m_DiscountEdit.SetSel(0xFFFF);
			return TRUE;
		}
		else if(pMsg->hwnd == m_DiscountEdit.GetSafeHwnd()) {
			m_LocateEdit.SetFocus();
			m_LocateEdit.SetSel(0xFFFF);
			return TRUE;
		}
		else if(pMsg->hwnd == m_LocateEdit.GetSafeHwnd()) {
			m_TelAddEdit.SetFocus();
			m_TelAddEdit.SetSel(0xFFFF);
			return TRUE;
		}
		else if(pMsg->hwnd == m_TelAddEdit.GetSafeHwnd()) {
			OnBnClickedButtonTeladd();
			return TRUE;
		}
	}

	return CMyFormView::PreTranslateMessage(pMsg);
}

void CCustomerPage1::OnBnClickedTeamSearchBtn()
{
	CString strSearch;
	m_TeamSearchCombo.GetWindowText(strSearch);
	m_nSearchType = ST_TEAM_NO;
	m_strKeyword.Format(strSearch == "일반" ? "0" : strSearch);
	OnRefreshList();
}

//드래그 상태에서 마우스업
void CCustomerPage1::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bDragMode) // In Drag&Drop mode ?
	{
		::ReleaseCapture();
		
		CPoint pt(point);
		ClientToScreen(&pt);
		SetCursor(m_hcArrow);

		
		m_lcData.ScreenToClient(&pt);
		CXTPGridRow *pRow = m_lcData.HitTest(pt);

		if(!pRow)
			return;

		int nHoverItem = pRow->GetIndex();
		int nSelItem = m_lcData.GetNextItem(-1, LVNI_SELECTED);

		if(m_lcData.GetItemText(nSelItem, 0) == "" || m_lcData.GetItemText(nHoverItem, 0) == "")
		{
			MessageBox("번호가 있는 항목을 선택해주세요", "확인", MB_ICONINFORMATION);
			return;			
		}

		if(nHoverItem == nSelItem)
		{
			MessageBox("합치려는 고객이 같습니다", "확인", MB_ICONINFORMATION);
			return;
		}

		if(nHoverItem != nSelItem) {
			CSumCnoDlg dlg;
			dlg.m_strCNo1 = CString("고객번호 ") + m_lcData.GetItemText(nSelItem, 0);
			dlg.m_strCNo2 = CString("고객번호 ") + m_lcData.GetItemText(nHoverItem, 0);
			dlg.m_strCNo3 = CString("고객번호 ") +  m_lcData.GetItemText(nHoverItem, 0);
			if(IDOK == dlg.DoModal())
			{
				
				long nSrcCNo = (long)m_lcData.GetItemData(nSelItem);
				long nDstCNo = (long)m_lcData.GetItemData(nHoverItem);
				CString sDeleteEtc = "고객통합[고객창] 삭제";
				CMkCommand pCmd(m_pMkDb, "Integrated_customer_alone_2");
				pCmd.AddParameter(typeLong, typeInput, sizeof(long), LF->GetCurBranchInfo()->nCompanyCode);		//nCompany
				pCmd.AddParameter(typeLong, typeInput, sizeof(long), nSrcCNo);
				pCmd.AddParameter(typeLong, typeInput, sizeof(long), nDstCNo);
				pCmd.AddParameter(typeLong , typeInput, sizeof(long), m_ui.nWNo);
				pCmd.AddParameter(typeLong , typeInput, sizeof(long), m_ui.nCompany);						
				pCmd.AddParameter(typeString, typeInput, sDeleteEtc.GetLength(), sDeleteEtc);

				pCmd.Execute();
				OnRefreshList();
			}
		}

		m_bDragMode = FALSE;
	}

	CMyFormView::OnLButtonUp(nFlags, point);
}

//아이템 클릭
void CCustomerPage1::OnReportItemClick(NMHDR*  pNotifyStruct, LRESULT* /*result*/) 
{
	//	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	CXTPListCtrlRecord2* pRecord = static_cast<CXTPListCtrlRecord2*>(m_lcData.GetFirstSelectedRecord());

	if(pRecord == NULL)
		return;
	CString strTel;

	m_strID = m_lcData.GetItemText(pRecord , kClientNumber);
	m_sCompany = m_lcData.GetItemText(pRecord , kCompany);
	m_sDepart = m_lcData.GetItemText(pRecord , kDepart);
	m_sName = m_lcData.GetItemText(pRecord, kName);
	m_sTel1 = m_lcData.GetItemText(pRecord, kPhone1);
	m_stredtID = m_lcData.GetItemText(pRecord, kUserID);
	m_sDong = m_lcData.GetItemText(pRecord, kDong);
	m_sLocation = m_lcData.GetItemText(pRecord, kLocation);
	m_bCredit = (m_lcData.GetItemText(pRecord , kCredit) == "신용") ? TRUE : FALSE;
	m_nDiscount =   _ttoi(m_lcData.GetItemText(pRecord , kDiscount));
	m_nCNo = static_cast<long>(m_lcData.GetItemData(pRecord));
	m_strMemo = m_lcData.GetItemText(pRecord , kMemo);


	UpdateData(FALSE);

	//고객전화번호 검색타이머
	//키패드를 움직인 후 0.5초가 지난후에 전화번호리스트를 불러들인다.
	KillTimer(0);
	SetTimer(0, 500, NULL);

	//*pResult = 0;
}



//드래그앤드랍 시작
void CCustomerPage1::OnReportBeginDrag(NMHDR*  pNotifyStruct, LRESULT* /*result*/) 
{
	m_bDragMode = TRUE;
	m_pSourceRecord = m_lcData.GetFirstSelectedRecord();
	SetCursor(m_hcMoveHold);
	SetCapture();
}

void CCustomerPage1::OnEnChangeEditSearch()
{
	CString strSearch;
	m_edtSearch.GetWindowText(strSearch);

	strSearch.Replace("-", "");
	strSearch.MakeLower();
 
	CXTPGridRecords *pRecords = m_lcData.GetRecords();

	for(int i = 0; i < pRecords->GetCount(); i++) {
		CXTPGridRecord *pRecord = pRecords->GetAt(i);

		CString str1 = pRecord->GetItem(1)->GetCaption(NULL);
		CString str2 = pRecord->GetItem(2)->GetCaption(NULL);
		CString str3 = pRecord->GetItem(3)->GetCaption(NULL);
		CString str4 = pRecord->GetItem(4)->GetCaption(NULL);

		try{
			str1.Replace("-", ""); str1.MakeLower();
			str2.Replace("-", ""); str2.MakeLower();
			str3.Replace("-", ""); str3.MakeLower();
			str4.Replace("-", ""); str4.MakeLower();
		}
		catch (CException *){

		}
		

		if(str1.Find(strSearch) >= 0 ||
			str2.Find(strSearch) >= 0 ||
			str3.Find(strSearch) >= 0 ||
			str4.Find(strSearch) >= 0)
			pRecord->SetVisible(TRUE);
		else
			pRecord->SetVisible(FALSE);
	}

	m_lcData.Populate();
}
