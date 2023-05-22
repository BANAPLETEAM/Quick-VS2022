// CustomerPage12.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "CustomerPage12.h"
#include "RcpDlg.h"

// CCustomerPage12 

IMPLEMENT_DYNCREATE(CCustomerPage12, CMyFormView)

CCustomerPage12::CCustomerPage12()
	: CMyFormView(CCustomerPage12::IDD)
	, m_strData(_T(""))
{
	m_nCNo = 0;
}

CCustomerPage12::~CCustomerPage12()
{ 
}

void CCustomerPage12::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATA_EDIT, m_edtData);
	DDX_Text(pDX, IDC_DATA_EDIT, m_strData);
	DDX_Control(pDX, IDC_REPOR_LIST, m_Report);

	for(int i=0; i<STATIC_COUNT; i++)
	{
		DDX_Control(pDX, IDC_STATIC_SIMPLE0+i, m_MyStc[i]);

		if(i<EDIT_COUNT)
			DDX_Control(pDX, IDC_EDIT_SIMPLE0+i, m_EditStc[i]);
	}

	DDX_Control(pDX, IDC_SIMPLE_STATIC83, m_stcBtn[0]);
	DDX_Control(pDX, IDC_SIMPLE_STATIC84, m_stcBtn[1]);
	DDX_Control(pDX, IDC_SIMPLE_STATIC85, m_stcBtn[2]);
	DDX_Control(pDX, IDC_SIMPLE_STATIC86, m_stcBtn[3]);
	DDX_Control(pDX, IDC_SIMPLE_STATIC87, m_stcBtn[4]);
	DDX_Control(pDX, IDC_SIMPLE_STATIC95, m_stcBtn[5]);
	DDX_Control(pDX, IDC_TEL_LIST, m_lstTel);
	DDX_Control(pDX, IDC_SEARCH_STATIC, m_stcSearch);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_dtFromCtl);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_dtToCtl);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_dtTo);
	DDX_Control(pDX, IDC_DATE_BTN, m_DateBtn);
}

BEGIN_MESSAGE_MAP(CCustomerPage12, CMyFormView)
	ON_BN_CLICKED(IDC_SEARCH_BTN, OnBnClickedSearchBtn)
	ON_NOTIFY(XTP_NM_GRID_SELCHANGED, IDC_REPOR_LIST, OnReportItemChange)
	ON_NOTIFY(NM_CLICK, IDC_REPOR_LIST, OnReportItemClick)
	ON_WM_PAINT()
	ON_EN_CHANGE(IDC_DATA_EDIT, OnEnChangeDataEdit)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_MAKE_CUSTOMER, OnMakeCustomer)
	ON_COMMAND(ID_DELETE_CUSTOMER, OnDeleteCustomer)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_SEARCH_ALL_BTN, OnBnClickedSearchAllBtn)
END_MESSAGE_MAP()


// CCustomerPage12 진단입니다.

#ifdef _DEBUG
void CCustomerPage12::AssertValid() const
{
	CMyFormView::AssertValid();
}

void CCustomerPage12::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif //_DEBUG

void CCustomerPage12::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	SetText();
	SetTimer(0, 500, NULL);

}

void CCustomerPage12::OnReportItemChange(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;
	
	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	SetText();
	SetTimer(0, 500, NULL);
}

void CCustomerPage12::OnBnClickedSearchBtn()
{
	UINT nType;

	UpdateData(TRUE);
	m_edtData.GetWindowText(m_strData);

	if(m_strData.IsEmpty()) return;
	if(!CRcpDlg::MakeSearchQuery(m_strData, m_strKeyword, &nType)) return;
	m_nSearchType = nType;

	RefreshList();
}

void CCustomerPage12::RefreshList()
{
	DeleteListAllItems();
	if(m_strKeyword.IsEmpty()) return;

	CMkCommand pCmd(m_pMkDb, "search_customer_delete");
	CMkRecordset pRs(m_pMkDb);

	if(m_nSearchType == ST_COMPANY) m_nSearchType++;
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nSearchType);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), GetCurBranchInfo()->nCustomerTable);
	pCmd.AddParameter(typeString, typeInput, m_strKeyword.GetLength(), m_strKeyword);
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_ci.m_bSearchFourNumberWithUID);


	if(!pRs.Execute(&pCmd)) return ;

	ShowData(&pRs);
}

void CCustomerPage12::ShowData(CMkRecordset *pRs)
{
	char buffer[10];

	long nWNo;
	CString strDeleteEtc;

	for(int i=0; i<pRs->GetRecordCount(); i++)
	{	
		ST_CUSTOMER_INFO *pc = new ST_CUSTOMER_INFO;

		pRs->GetFieldValue("nCNo", pc->nCNo);
		pRs->GetFieldValue("nID", pc->nID);
		pRs->GetFieldValue("sCompany", pc->strCompany);
		pRs->GetFieldValue("sDepart", pc->strDepart);
		pRs->GetFieldValue("sName", pc->strName);
		pRs->GetFieldValue("sTel1", pc->strTel1);
		pRs->GetFieldValue("sDong", pc->strDong);
		pRs->GetFieldValue("sLocation", pc->strLocation);
		pRs->GetFieldValue("bCredit", pc->bCredit);
		pRs->GetFieldValue("nDiscount", pc->nDiscount);
		pRs->GetFieldValue("nGNo", pc->nGNo);
		pRs->GetFieldValue("nTeamNo", pc->nTeamNo);
		pRs->GetFieldValue("nAllocGroup", pc->nAllocGroup);
		pRs->GetFieldValue("nCouponCharge", pc->nCouponCharge);
		pRs->GetFieldValue("sMemo", pc->strMemo);
		//pRs->GetFieldValue("sMobile", pc->strMobile);
		pRs->GetFieldValue("nPosX", pc->nPosX);
		pRs->GetFieldValue("nPosY", pc->nPosY);
		pRs->GetFieldValue("nDongID", pc->nDongID);
		pRs->GetFieldValue("sAddress", pc->strAddress);
		pRs->GetFieldValue("nNodeID", pc->nNodeID);
		pRs->GetFieldValue("nType", pc->nCustomerType);
		pRs->GetFieldValue("sEMail", pc->strEMail);
		pRs->GetFieldValue("dtRegister", pc->dtRegister);
		pRs->GetFieldValue("dtLastUse", pc->dtLastUse);
		pRs->GetFieldValue("nUseCount", pc->nUseCount);
		pRs->GetFieldValue("nCancelCount", pc->nCancelCount);
		pRs->GetFieldValue("sRiderMemo", pc->strRiderMemo);

		pRs->GetFieldValue("sUserID", pc->strUserID);
		pRs->GetFieldValue("nSendStateChangeSMS", pc->nSendStateChangeSMS);
		pRs->GetFieldValue("bPreventPosUpdate", pc->bPreventPosUpdate);
		pRs->GetFieldValue("bCreditAfterDiscount", pc->bCreditAfterDiscount);
		pRs->GetFieldValue("sLoginID", pc->strLoginID);
		pRs->GetFieldValue("sLoginPW", pc->strLoginPW);
		pRs->GetFieldValue("bUseHomepage", pc->bUseHomepage);
		pRs->GetFieldValue("nCustomerGrade", pc->nCustomerGrade);
		pRs->GetFieldValue("nPriceGrade", pc->nPriceGrade);

		pRs->GetFieldValue("nReportStartDay", pc->nReportStartDay);
		pRs->GetFieldValue("nReportEndDay", pc->nReportEndDay);
		pRs->GetFieldValue("nIssueTaxBillDay", pc->nIssueTaxBillDay);
		pRs->GetFieldValue("nUncollectedAmount", pc->nUnCollectedAmount);
		//		pRs->GetFieldValue("dtPRDate", dtPRDate);

		pRs->GetFieldValue("nDiscountType", pc->nDiscountType);
		pRs->GetFieldValue("nMileageType", pc->nMileageType);
		pRs->GetFieldValue("nMileageValue", pc->nMileageValue);
		pRs->GetFieldValue("nCouponType", pc->nCouponType);
		pRs->GetFieldValue("bGroupOwner", pc->bGroupOwner);
		pRs->GetFieldValue("nMileageBalance", pc->nMileageBalance);
		pRs->GetFieldValue("nWNo", nWNo);
		pRs->GetFieldValue("sDeleteEtc", strDeleteEtc);

		m_Report.InsertItem(i, itoa(i+1, buffer, 10));
		m_Report.SetItemText(i, 1, pc->bCredit ? "신용" : "");
		m_Report.SetItemText(i, 2, pc->strCompany);
		m_Report.SetItemText(i, 3, pc->strDepart);
		m_Report.SetItemText(i, 4, pc->strName);
		m_Report.SetItemText(i, 5, pc->strUserID);
		m_Report.SetItemText(i, 6, GetDashPhoneNumber(pc->strTel1));
		m_Report.SetItemText(i, 7, pc->strDong);
		m_Report.SetItemText(i, 8, m_cg.GetGroupData(pc->nGNo)->strFullName);
		m_Report.SetItemText(i, 9, pc->strLocation);
		m_Report.SetItemText(i, 10, itoa(nWNo, buffer, 10));
		m_Report.SetItemText(i, 11, strDeleteEtc);
		m_Report.SetItemData(i, (DWORD_PTR)pc);

		pRs->MoveNext();
	}

	m_Report.Populate();

}

void CCustomerPage12::DeleteListAllItems()
{
	for(int nItem = 0; nItem < m_Report.GetRecords()->GetCount(); nItem++)
	{
		CXTPGridRecord *pRecord = m_Report.GetRecords()->GetAt(nItem);

		if(m_Report.GetItemText(pRecord, 0) != "지명")
		{
			ST_CUSTOMER_INFO *pCusInfo = (ST_CUSTOMER_INFO*)m_Report.GetItemData(pRecord);
			if(pCusInfo)
				delete pCusInfo;
		}
	}

	m_Report.DeleteAllItems();
}
void CCustomerPage12::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	m_DateBtn.InitDateButton(&m_dtFromCtl, &m_dtToCtl);
	m_DateBtn.OnMenuMonth();

	DeleteListAllItems();

	m_Report.InsertColumn(0,"번호",LVCFMT_LEFT,50);
	m_Report.InsertColumn(1,"신용",LVCFMT_LEFT,40);
	m_Report.InsertColumn(2,"상호",LVCFMT_LEFT,135);
	m_Report.InsertColumn(3,"부서",LVCFMT_LEFT,95);
	m_Report.InsertColumn(4,"담당",LVCFMT_LEFT,75);
	m_Report.InsertColumn(5,"아이디",LVCFMT_LEFT,60);
	m_Report.InsertColumn(6,"전화번호",LVCFMT_LEFT,100);
	m_Report.InsertColumn(7,"기준동",LVCFMT_LEFT,70);
	m_Report.InsertColumn(8,"그룹명",LVCFMT_LEFT,95);
	m_Report.InsertColumn(9,"위치",LVCFMT_LEFT,200);
	m_Report.InsertColumn(10,"접수자",LVCFMT_LEFT,60);
	m_Report.InsertColumn(11,"삭제위치",LVCFMT_LEFT, 100);

	for(int i=0; i<EDIT_COUNT; i++)
	{
		m_EditStc[i].SetMyFont("맑은 고딕", 17, FW_NORMAL);
		m_EditStc[i].SetUserOption(RGB(0, 0, 255), RGB(255, 255, 255), "");
	}
	
	m_Report.Populate();

	SetResize(IDC_REPOR_LIST, sizingRightBottom);
}

void CCustomerPage12::OnPaint()
{
	CPaintDC dc(this); // device context for painting
}

void CCustomerPage12::SetText()
{
	CXTPGridRow *pRow= m_Report.GetSelectedRows()->GetAt(0);

	if(pRow == NULL) return;

	CXTPGridRecord *pRecord = pRow->GetRecord();
	ST_CUSTOMER_INFO *pc = (ST_CUSTOMER_INFO*)m_Report.GetItemData(pRecord);

	if(pc == NULL) return;

	char buffer[20];

	m_nCNo = pc->nCNo;

	long nItem = 0;
	m_EditStc[nItem++].SetWindowText(pc->nCustomerType == 0 ? "거래처" : "일반고객"); //타입
	m_EditStc[nItem++].SetWindowText(ltoa(pc->nID, buffer, 10)); //고객코드
	m_EditStc[nItem++].SetWindowText(m_cg.GetGroupData(pc->nGNo)->strTotalName);  //그룹명
	m_EditStc[nItem++].SetWindowText(GetPrice(pc->nPriceGrade)); //가격등급
	m_EditStc[nItem++].SetWindowText((CString)ltoa(pc->nIssueTaxBillDay , buffer, 10) + "일"); //계산서발행일
	m_EditStc[nItem++].SetWindowText(pc->strUserID); //고객아이디
	m_EditStc[nItem++].SetWindowText(::GetGrade(pc->nCustomerGrade)); //고객등급
	m_EditStc[nItem++].SetWindowText(ltoa(pc->nUseCount, buffer, 10)); //이용횟수
	m_EditStc[nItem++].SetWindowText(GetDiscountType(pc->nDiscountType)); //할인타입
	m_EditStc[nItem++].SetWindowText(ltoa(pc->nDiscount, buffer, 10)); //할인액
	m_EditStc[nItem++].SetWindowText(pc->strCompany); //상호
	m_EditStc[nItem++].SetWindowText(pc->dtRegister.Format("%y-%m-%d %H:%M")); //최초이용
	m_EditStc[nItem++].SetWindowText(pc->dtLastUse.Format("%y-%m-%d %H:%M")); //최종
	m_EditStc[nItem++].SetWindowText(GetDiscountType(pc->nCouponType)); // 쿠폰타입
	m_EditStc[nItem++].SetWindowText(ltoa(pc->nCouponCharge, buffer, 10)); // 쿠폰타입할인
	m_EditStc[nItem++].SetWindowText(pc->strDepart); // 부서
	m_EditStc[nItem++].SetWindowText(""); // 홍보일
	m_EditStc[nItem++].SetWindowText(pc->nTeamNo == 0 ? "일반" : ltoa(pc->nTeamNo, buffer, 10)); // 기사
	m_EditStc[nItem++].SetWindowText("마일리지"); //
	m_EditStc[nItem++].SetWindowText(pc->strName); // 담당
	m_EditStc[nItem++].SetWindowText(pc->nReportStartDay == 0 ? "정산안함" : ltoa(pc->nReportStartDay, buffer, 10)); // 정산일1번
	m_EditStc[nItem++].SetWindowText(pc->nReportEndDay == 0 ? "정산안함" : ltoa(pc->nReportEndDay, buffer, 10)); // 정산일2번
	m_EditStc[nItem++].SetWindowText(GetDashPhoneNumber(pc->strTel1)); // 대표전화
	m_EditStc[nItem++].SetWindowText(pc->strLoginID); // 로그인아이디
	m_EditStc[nItem++].SetWindowText(pc->strLoginPW); // 로그인패스
	m_EditStc[nItem++].SetWindowText("1일"); // 입금예정
	m_EditStc[nItem++].SetWindowText("1일"); // 입금예정
	//m_EditStc[nItem++].SetWindowText(GetDashPhoneNumber(pc->strMobile)); // 휴대폰
	m_EditStc[nItem++].SetWindowText(GetDashPhoneNumber(pc->strEMail)); // 이메일
	m_EditStc[nItem++].SetWindowText(pc->strLocation); // 위치정보
	m_EditStc[nItem++].SetWindowText(pc->strMemo); // 메모
	m_EditStc[nItem++].SetWindowText(pc->strRiderMemo); // 기사메모 
	m_EditStc[nItem++].SetWindowText(m_poiNew.GetPOI(pc->nDongID)->GetRegionName()); // 기준동
	//m_EditStc[nItem++].SetWindowText(m_poi.GetDisplayName(pc->nDongID) + " " + pc->strAddress); // 주소
	m_EditStc[nItem++].SetWindowText(pc->nDongID == 0 ? "" : m_poiNew.GetPOI(pc->nDongID)->GetDong()); // PDA표시등
	m_EditStc[nItem++].SetWindowText("배차1그룹"); // 배차그룹 

	//중간에 자질구리한 주소 뺌
} 


BOOL CCustomerPage12::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{	
		if(pMsg->hwnd == m_edtData.GetSafeHwnd()) {
				OnBnClickedSearchBtn();
			
			return TRUE;
		}
	}

	return CMyFormView::PreTranslateMessage(pMsg);
}

void CCustomerPage12::OnEnChangeDataEdit()
{
	CString sData; m_edtData.GetWindowText(sData);
	SearchListData(sData);
}

void CCustomerPage12::SearchListData(CString sSearchData)
{
	CXTPGridRows *pRows = m_Report.GetRows();
	CXTPGridRecords *pRecords = m_Report.GetRecords();
	CXTPGridColumn *pColumn = NULL;

	CString sCompany, sDepart, sName, sUserID, sTel1, sDong, sLocation;

	for(int i=0; i<m_Report.GetRecords()->GetCount(); i++)
	{
		CXTPGridRow *pRow = pRows->GetAt(i);
		CXTPGridRecord *pRecord = pRecords->GetAt(i);

		sCompany = ((CXTPGridRecordItemText*)m_Report.GetRecords()->GetAt(i)->GetItem(1))->GetCaption(pColumn);
		sDepart = ((CXTPGridRecordItemText*)m_Report.GetRecords()->GetAt(i)->GetItem(2))->GetCaption(pColumn);
		sName = ((CXTPGridRecordItemText*)m_Report.GetRecords()->GetAt(i)->GetItem(3))->GetCaption(pColumn);
		sUserID = ((CXTPGridRecordItemText*)m_Report.GetRecords()->GetAt(i)->GetItem(4))->GetCaption(pColumn);
		sTel1 = ((CXTPGridRecordItemText*)m_Report.GetRecords()->GetAt(i)->GetItem(5))->GetCaption(pColumn);
		sDong = ((CXTPGridRecordItemText*)m_Report.GetRecords()->GetAt(i)->GetItem(6))->GetCaption(pColumn);
		sLocation = ((CXTPGridRecordItemText*)m_Report.GetRecords()->GetAt(i)->GetItem(8))->GetCaption(pColumn);


		if((sCompany.Find(sSearchData) >= 0) ||
			(sDepart.Find(sSearchData) >= 0) ||
			(sName.Find(sSearchData) >= 0) ||
			(sUserID.Find(sSearchData) >= 0) ||
			(sTel1.Find(sSearchData) >= 0) ||
			(sDong.Find(sSearchData) >= 0) ||
			(sLocation.Find(sSearchData) >= 0) )
			pRecord->SetVisible(TRUE);
		else
			pRecord->SetVisible(FALSE);
	}

	m_Report.Populate();
}

void CCustomerPage12::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_Report.GetWindowRect(&rect);

	if(rect.PtInRect(point))
	{
		CMenu rMenu;
		rMenu.LoadMenu(IDR_CONTEXT_MENU);
		CMenu *pRMenu=rMenu.GetSubMenu(17);
		pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}
}

void CCustomerPage12::OnMakeCustomer()
{
	CXTPGridRow *pRow = m_Report.GetSelectedRows()->GetAt(0);

	if(pRow == NULL)
		return;

	CXTPGridRecord *pRecord = pRow->GetRecord();

	CString sMsg = "";
	CString sCompany = ((CXTPGridRecordItemText*)pRecord->GetItem(2))->GetCaption(NULL);

	sMsg.Format("[%s]고객을 복구 하시겠습니까?", sCompany);

	if(MessageBox(sMsg, "확인", MB_OKCANCEL) != IDOK)
	return;

	ST_CUSTOMER_INFO *pc = (ST_CUSTOMER_INFO*)m_Report.GetItemData(pRecord);

	CMkCommand pCmd(m_pMkDb, "delete_customer_to_customer");
	pCmd.AddParameter(pc->nCNo);
	
	if(pCmd.Execute())
	{
		delete pc;
		pRecord->RemoveAll();

		m_Report.GetRecords()->RemoveRecord(pRecord);
		m_Report.GetRows()->RemoveRow(pRow);
		m_Report.Populate();
	}
}

void CCustomerPage12::OnDeleteCustomer()
{
	CXTPGridRow *pRow = m_Report.GetSelectedRows()->GetAt(0);

	if(pRow == NULL)
		return;

	CXTPGridRecord *pRecord = pRow->GetRecord();

	CString sMsg = "";
	CString sCompany = ((CXTPGridRecordItemText*)pRecord->GetItem(2))->GetCaption(NULL);

	sMsg.Format("[%s]고객을 완전히 하시겠습니까?", sCompany);

	if(MessageBox(sMsg, "확인", MB_OKCANCEL) != IDOK)
		return;

	ST_CUSTOMER_INFO *pc = (ST_CUSTOMER_INFO*)m_Report.GetItemData(pRecord);

	CMkCommand pCmd(m_pMkDb, "delete_customer_complete");
	pCmd.AddParameter(pc->nCNo);

	if(pCmd.Execute())
	{
		delete pc;
		m_Report.GetRecords()->RemoveRecord(pRecord);
		m_Report.GetRows()->RemoveRow(pRow);
		m_Report.Populate();
	}

}
void CCustomerPage12::OnTimer(UINT nIDEvent)
{
	if(0 == nIDEvent)
	{
		KillTimer(nIDEvent);

		if(m_nCNo != 0) 
		{
			CString strTel;
			m_lstTel.ResetContent();
			CMkCommand pCmd(m_pMkDb, "select_customertel_delete");
			CMkRecordset pRs(m_pMkDb);
			pCmd.AddParameter(typeLong, typeInput, sizeof(long), GetCurBranchInfo()->nCompanyCode);
			pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nCNo);

			pRs.Execute(&pCmd);
			while(!pRs.IsEOF()) {
				CString strTel;
				pRs.GetFieldValue(0, strTel);
				m_lstTel.AddString(GetDashPhoneNumber(strTel));
				pRs.MoveNext();
			}
			pRs.Close();
		}
	}

	CMyFormView::OnTimer(nIDEvent);
}

void CCustomerPage12::OnBnClickedSearchAllBtn()
{
	UpdateData(TRUE);
	DeleteListAllItems();
	
	CMkCommand pCmd(m_pMkDb, "search_customer_delete_all");
	CMkRecordset pRs(m_pMkDb);

	if(m_nSearchType == ST_COMPANY) m_nSearchType++;
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), GetCurBranchInfo()->nCustomerTable);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), GetCurBranchInfo()->bIntegrated);
	pCmd.AddParameter(m_dtFrom);
	pCmd.AddParameter(m_dtTo);

	if(!pRs.Execute(&pCmd)) return ;

	ShowData(&pRs);
}
