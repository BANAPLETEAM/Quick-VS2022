// ReportForm5.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ReportForm5.h"


enum { INT_COMPANY = 0, SHARED_COMPANY = 1};

// CReportForm5 대화 상자입니다.

IMPLEMENT_DYNCREATE(CReportForm5, CMyFormView)
CReportForm5::CReportForm5()
	: CMyFormView(CReportForm5::IDD)
{
	COleDateTimeSpan span(30, 0,0,0);
	m_dtFrom= COleDateTime::GetCurrentTime() - span;
	m_dtTo = COleDateTime::GetCurrentTime();
	m_strProcessRate = "50";

	m_bCash = TRUE;
	m_bCredit = TRUE;
	m_bOnline = TRUE;
}

CReportForm5::~CReportForm5()
{
}

void CReportForm5::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_REPORT, m_List);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_FROM, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TO, m_dtTo);
	DDX_Control(pDX, IDC_DATETIMEPICKER_FROM, m_FromDT);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TO, m_ToDT);
	DDX_Control(pDX, IDC_SHOW_BTN, m_ShowBtn);
	DDX_Control(pDX, IDC_DATE_BTN, m_DateBtn);
	DDX_Control(pDX, IDC_PERIOD_STATIC, m_PeriodStatic);
	DDX_Text(pDX, IDC_CALLPAY_EDIT1, m_strProcessRate);
	DDX_Text(pDX, IDC_CALLPAY_EDIT2, m_strOperateRate);
	DDX_Text(pDX, IDC_FEE_EDIT, m_strFee);
	DDX_Control(pDX, IDC_CALLPAY_EDIT1, m_ProcessRateEdit);
	DDX_Control(pDX, IDC_CALLPAY_EDIT2, m_OperateRateEdit);
	DDX_Control(pDX, IDC_FIRST_SHARE_CHECK, m_FirstShareCheck);
	DDX_Control(pDX, IDC_SECOND_SHARE_CHECK, m_SecondShareCheck);
	DDX_Control(pDX, IDC_THIRD_SHARE_CHECK, m_ThirdShareCheck);
	DDX_Control(pDX, IDC_CALLCENTER_CHECK, m_CallcenterCheck);
	DDX_Control(pDX, IDC_FEE_EDIT, m_FeeEdit);
	DDX_Control(pDX, IDC_STATIC1, m_Static1);
	DDX_Control(pDX, IDC_STATIC2, m_Static2);
	DDX_Control(pDX, IDC_STATIC3, m_Static3);
	DDX_Control(pDX, IDC_STATIC4, m_Static4);

	DDX_Control(pDX, IDC_CASH_CHECK, m_CashCheck);
	DDX_Control(pDX, IDC_CREDIT_CHECK, m_CreditCheck);
	DDX_Control(pDX, IDC_ONLINE_CHECK, m_OnlineCheck);

	DDX_Check(pDX, IDC_CASH_CHECK, m_bCash);
	DDX_Check(pDX, IDC_CREDIT_CHECK, m_bCredit);
	DDX_Check(pDX, IDC_ONLINE_CHECK, m_bOnline);
}

BEGIN_MESSAGE_MAP(CReportForm5, CMyFormView)
	ON_BN_CLICKED(IDC_SHOW_BTN, OnBnClickedShowBtn)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CReportForm5 메시지 처리기입니다.

void CReportForm5::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	m_DateBtn.InitDateButton(&m_FromDT, &m_ToDT);
	m_DateBtn.OnMenuYesterday();

	CImageList ImageList; 
	ImageList.Create(1,17,ILC_COLOR,1,1); 
	m_List.SetImageList(&ImageList,LVSIL_SMALL); 
	m_List.ModifyStyle(0, LVS_SHOWSELALWAYS | LVS_NOSORTHEADER);
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_FLATSB | LVS_EX_GRIDLINES);

	/*
	m_List.InsertColumn(0,"번호",LVCFMT_CENTER,50);
	m_List.InsertColumn(1,"분류",LVCFMT_CENTER,40);
	m_List.InsertColumn(2,"콜소속",LVCFMT_CENTER, 60);
	m_List.InsertColumn(3,"주문일시",LVCFMT_LEFT,80);
	m_List.InsertColumn(4,"출발지",LVCFMT_LEFT,80);
	m_List.InsertColumn(5,"도착지",LVCFMT_LEFT,80);
	m_List.InsertColumn(6,"기사소속", LVCFMT_CENTER,80);
	m_List.InsertColumn(7,"기사",LVCFMT_CENTER,45);
	m_List.InsertColumn(8,"운행료",LVCFMT_RIGHT,55);
	m_List.InsertColumn(9,"할인비",LVCFMT_RIGHT,75);
	m_List.InsertColumn(10,"콜비",LVCFMT_RIGHT,70);
	m_List.InsertColumn(11,"접수비",LVCFMT_RIGHT,70);	
	m_List.InsertColumn(12,"처리비",LVCFMT_RIGHT,50);
	m_List.InsertColumn(13,"운영비",LVCFMT_RIGHT,65);
	m_List.InsertColumn(14,"상태",LVCFMT_CENTER, 40);
	m_List.InsertColumn(15,"레벨",LVCFMT_CENTER, 40);
	m_List.InsertColumn(16,"지불",LVCFMT_CENTER, 40);*/

	m_List.InsertColumn(0,"번호",LVCFMT_CENTER,40);
	m_List.InsertColumn(1,"분류",LVCFMT_CENTER,40);
	m_List.InsertColumn(2,"콜소속",LVCFMT_CENTER, 60);
	m_List.InsertColumn(3,"주문일시",LVCFMT_LEFT,75);
	m_List.InsertColumn(4,"접수번호",LVCFMT_LEFT, 60);
	m_List.InsertColumn(5,"고객명",LVCFMT_LEFT,90);
	m_List.InsertColumn(6,"출발지",LVCFMT_LEFT,80);
	m_List.InsertColumn(7,"도착지",LVCFMT_LEFT,80);
	m_List.InsertColumn(8,"기사소속", LVCFMT_CENTER,80);
	m_List.InsertColumn(9,"기사",LVCFMT_CENTER,45);
	m_List.InsertColumn(10,"운행료",LVCFMT_RIGHT,55);
	m_List.InsertColumn(11,"할인",LVCFMT_RIGHT,55);
	m_List.InsertColumn(12,"할인비",LVCFMT_RIGHT,75);
	m_List.InsertColumn(13,"콜비",LVCFMT_RIGHT,70);
	m_List.InsertColumn(14,"접수비",LVCFMT_RIGHT,70);	
	m_List.InsertColumn(15,"처리비",LVCFMT_RIGHT,50);
	m_List.InsertColumn(16,"운영비",LVCFMT_RIGHT,65);
	m_List.InsertColumn(17,"상태",LVCFMT_CENTER, 40);
	m_List.InsertColumn(18,"레벨",LVCFMT_CENTER, 40);
	m_List.InsertColumn(19,"지불",LVCFMT_CENTER, 40);
	m_List.InsertColumn(20,"직접수금",LVCFMT_CENTER, 60);
	m_List.InsertColumn(21,"탁송",LVCFMT_CENTER, 40);


	m_toolTip.Create(this);
	CStringArray saInfo;

	saInfo.Add("☆ '처리콜비' 입력박스 입니다.");
	saInfo.Add("   100 미만으로 입력하시면 %로 인식되며,");
	saInfo.Add("   100 이상으로 입력하면 원으로 인식됨");
	saInfo.Add("   [접수비 = 입금액 - 처리비 - 운영비]");
	saInfo.Add("");
	saInfo.Add("☆ 콜비 구분");
	saInfo.Add("접수비/처리비/운영비 3가지 구분됨");
	saInfo.Add("접수비: 콜을 접수받은 회원사가 받는 콜비");
	saInfo.Add("처리비: 콜을 처리한 기사의 소속회원사가 받는 콜비");
	saInfo.Add("운영비: 콜센터 분리운영시 콜센터가 받는 콜비");
	saInfo.Add("");
	saInfo.Add("(ex1) 처리=30, 운영=200 입력후 입금액이 1600원인 경우");
	saInfo.Add(" -> 운영=200원, 처리=(1600-200)*30/100=420원, 접수=1600-620=980원");
	saInfo.Add("(ex2) 처리=40, 운영=10 입력후 입금액이 2000원인 경우");
	saInfo.Add(" -> 운영=2000*10/100=200원, 처리=2000*40/100=800원, 접수=1000원");
	saInfo.Add("(ex3) 처리=500, 운영=100 입력후 입금액이 1600원인 경우");
	saInfo.Add(" -> 운영=100원, 처리=500원, 접수=1000원");
	saInfo.Add("");
	saInfo.Add("");
	m_toolTip.AddControlInfo(IDC_CALLPAY_EDIT, saInfo);
	saInfo.RemoveAll();
	saInfo.Add("☆ '운영콜비' 입력박스 입니다.");
	saInfo.Add("   100 미만으로 입력하시면 %로 인식되며,");
	saInfo.Add("   100 이상으로 입력하면 원으로 인식됨");
	saInfo.Add("   [접수비 = 입금액 - 처리비 - 운영비]");
	saInfo.Add("");
	saInfo.Add("☆ 콜비 구분");
	saInfo.Add("접수비/처리비/운영비 3가지 구분됨");
	saInfo.Add("접수비: 콜을 접수받은 회원사가 받는 콜비");
	saInfo.Add("처리비: 콜을 처리한 기사의 소속회원사가 받는 콜비");
	saInfo.Add("운영비: 콜센터 분리운영시 콜센터가 받는 콜비");
	saInfo.Add("");
	saInfo.Add("(ex1) 처리=30, 운영=200 입력후 입금액이 1600원인 경우");
	saInfo.Add(" -> 운영=200원, 처리=(1600-200)*30/100=420원, 접수=1600-620=980원");
	saInfo.Add("(ex2) 처리=40, 운영=10 입력후 입금액이 2000원인 경우");
	saInfo.Add(" -> 운영=2000*10/100=200원, 처리=2000*40/100=800원, 접수=1000원");
	saInfo.Add("(ex3) 처리=500, 운영=100 입력후 입금액이 1600원인 경우");
	saInfo.Add(" -> 운영=100원, 처리=500원, 접수=1000원");
	saInfo.Add("");
	saInfo.Add("");
	m_toolTip.AddControlInfo(IDC_CALLPAY_EDIT2, saInfo);
	SetTimer(0, 100, NULL);

	m_strProcessRate.Format("%d", AfxGetApp()->GetProfileInt("Share", "ProcessShareRate", 50));
	m_strOperateRate.Format("%d", AfxGetApp()->GetProfileInt("Share", "OperateShareRate", 0));
	m_strFee.Format("%d", AfxGetApp()->GetProfileInt("Share", "Fee", 20));

	m_ProcessRateEdit.SetWindowText(m_strProcessRate);
	m_OperateRateEdit.SetWindowText(m_strOperateRate);
	m_FeeEdit.SetWindowText(m_strFee);

	m_FirstShareCheck.SetCheck(AfxGetApp()->GetProfileInt("Share", "1stShare", 1));
	m_SecondShareCheck.SetCheck(AfxGetApp()->GetProfileInt("Share", "2stShare", 1));
	m_ThirdShareCheck.SetCheck(AfxGetApp()->GetProfileInt("Share", "3rdShare", 1));
	m_CallcenterCheck.SetCheck(AfxGetApp()->GetProfileInt("Share", "CallCenter", 0));

	SetResize(IDC_LIST_REPORT, sizingRightBottom);

	m_List.Populate();

}


#define SET_COLOR_LIST(ppp, x, y, z) 	COLOR_STRUCT *ppp = new COLOR_STRUCT;\
										ppp->crBk = RGB(x,y,z);\
										ppp->crText = RGB(0,0,0);\
										m_List.SetItemData(nItem, (DWORD_PTR)ppp);

/*
void CReportForm5::RefreshList()
{
	if(LF->GetCurBranchInfo()->bIntegrated) {
		MessageBox("지점간 정산은 통합보기를 지원하지 않습니다.", "확인", MB_ICONINFORMATION);
		return;
	}

	CWaitCursor wait;;

	UpdateData(TRUE);
	m_List.DeleteAllItems();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_interchange_order");
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), LF->GetCurBranchInfo()->nDOrderTable);
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), LASTBRANCH(1, LF->GetCurBranchInfo()->nDOrderTable));
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtFrom);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtTo);
	if(!pRs.Execute(&pCmd)) 
		return;

	const char *szAPayMask[] = {"선불", "착불", "신용", "송금"};

	int nItem = 0;
	long nTNo, nCompany, nRiderCompany;
	COleDateTime dt1;
	CString strCName, strStart, strDest;
	int nRNo, nState;
	long nCharge;
	long nTotalFee = 0, nTotalConFee = 0;
	BOOL bTake, bLastTake = TRUE;
	char buffer[20];
	int nNumber = 1;
	long nDeposit;

	for(int i = 0; i < 10; i++) {
		m_nTakeFee[i] = 0;
		m_nGiveFee[i] = 0;
		m_nTakeDeposit[i] = 0;
		m_nGiveDeposit[i] = 0;
		m_nTakeCount[i] = 0;
		m_nGiveCount[i] = 0;
	}

	while(!pRs.IsEOF())
	{	
		pRs.GetFieldValue("nTNo", nTNo);
		pRs.GetFieldValue("dt1", dt1);
		pRs.GetFieldValue("sCName", strCName);
		pRs.GetFieldValue("sStart", strStart);
		pRs.GetFieldValue("sDest", strDest);
		pRs.GetFieldValue("nRNo", nRNo);
		pRs.GetFieldValue("nRiderCompany", nRiderCompany);
		pRs.GetFieldValue("nCharge", nCharge);
		pRs.GetFieldValue("nState", nState);
		pRs.GetFieldValue("nCompany", nCompany);
		pRs.GetFieldValue("nDeposit", nDeposit);
		pRs.GetFieldValue("bTake", bTake);

		if(bTake != bLastTake) {
			nNumber = 1;
			if(nItem != 0) {
				nItem++;
				m_List.InsertItem(nItem, "");
			}
		}

		if(bTake) {
  			m_nTakeFee[nCompany % 10] += nCharge;
			m_nTakeDeposit[nCompany % 10] += nDeposit;
			m_nTakeCount[nCompany % 10]++;
		}
		else {
			m_nGiveFee[nRiderCompany % 10] += nCharge;
			m_nGiveDeposit[nRiderCompany % 10] += nDeposit;
			m_nGiveCount[nRiderCompany % 10]++;
		}

		m_List.InsertItem(nItem, ltoa(nNumber++, buffer, 10));
		m_List.SetItemText(nItem, 1, bTake ? "받음" : "넘김");
		m_List.SetItemText(nItem, 2, m_ci.GetName(nCompany));
		m_List.SetItemText(nItem, 3, dt1.Format("%m-%d %H:%M"));
		m_List.SetItemText(nItem, 4, strCName);
		m_List.SetItemText(nItem, 5, strStart);
		m_List.SetItemText(nItem, 6, strDest);
		m_List.SetItemText(nItem, 7, m_ShareCompanyMap[nRiderCompany].szName);
		m_List.SetItemText(nItem, 8, ltoa(nRNo, buffer, 10));
		m_List.SetItemText(nItem, 9, LF->GetMyNumberFormat(nCharge));
		m_List.SetItemText(nItem, 10, LF->GetMyNumberFormat(nDeposit));
		m_List.SetItemText(nItem, 11, LF->GetStateString(nState));
		bLastTake = bTake;
		nItem++;

		pRs.MoveNext();
	}


	if(nItem == 0) return;
	m_List.InsertItem(nItem++, "");

	m_List.InsertItem(nItem, "");
	SET_COLOR_LIST(p1, 255, 200, 200);
	m_List.SetItemText(nItem, 3, "받은오더");
	m_List.SetItemText(nItem, 7, "건 수");
	m_List.SetItemText(nItem, 9, "운행료");
	m_List.SetItemText(nItem++, 10, "입금액");
	
	for(int i = 0; i < 10; i++) {
		if(m_nTakeCount[i] > 0) {
			m_List.InsertItem(nItem, "");
			SET_COLOR_LIST(p2, 255, 200, 200);
			m_List.SetItemText(nItem, 4, m_ShareCompanyMap[i].szName);
			m_List.SetItemText(nItem, 7, ltoa(m_nTakeCount[i], buffer, 10));
			m_List.SetItemText(nItem, 9, LF->GetMyNumberFormat(m_nTakeFee[i]));
			m_List.SetItemText(nItem++, 10, LF->GetMyNumberFormat(m_nTakeDeposit[i]));
		}
	}
	
	m_List.InsertItem(nItem, "");
	SET_COLOR_LIST(p3, 255, 255, 200);
	m_List.SetItemText(nItem, 3, "넘긴오더");
	m_List.SetItemText(nItem, 7, "건 수");
	m_List.SetItemText(nItem, 9, "운행료");
	m_List.SetItemText(nItem++, 10, "입금액");
	
	for(int i = 0; i < 10; i++) {
		if(m_nGiveCount[i] > 0) {
			m_List.InsertItem(nItem, "");
			SET_COLOR_LIST(p4, 255, 255, 200);
			m_List.SetItemText(nItem, 4, m_ShareCompanyMap[i].szName);
			m_List.SetItemText(nItem, 7, ltoa(m_nGiveCount[i], buffer, 10));
			m_List.SetItemText(nItem, 9, LF->GetMyNumberFormat(m_nGiveFee[i]));
			m_List.SetItemText(nItem++, 10, LF->GetMyNumberFormat(m_nGiveDeposit[i]));

		}
	}
	
	m_List.InsertItem(nItem, "");
	SET_COLOR_LIST(p4, 200, 200, 255);
	m_List.SetItemText(nItem, 3, "받음-넘김");
	m_List.SetItemText(nItem, 7, "건 수");
	m_List.SetItemText(nItem, 9, "운행료");
	m_List.SetItemText(nItem++, 10, "입금정산");

	for(int i = 0; i < 10; i++) {
		if(m_nTakeCount[i] > 0 || m_nGiveCount[i] > 0) {
			int nTotalFee = m_nTakeFee[i] - m_nGiveFee[i];
			nTotalFee = nTotalFee - nTotalFee % 100;
			nTotalFee = - nTotalFee;

			int nTotalDeposit = m_nTakeDeposit[i] - m_nGiveDeposit[i];
			nTotalDeposit = nTotalDeposit - nTotalDeposit % 100;
			nTotalDeposit = - nTotalDeposit;



			m_List.InsertItem(nItem, "");
			SET_COLOR_LIST(p4, 200, 200, 255);
			m_List.SetItemText(nItem, 4, CString(m_ShareCompanyMap[i].szName));
			m_List.SetItemText(nItem, 7, ltoa(m_nTakeCount[i] - m_nGiveCount[i], buffer, 10));
			m_List.SetItemText(nItem, 9, LF->GetMyNumberFormat(ltoa(nTotalFee, buffer, 10)));
			m_List.SetItemText(nItem++, 10, LF->GetMyNumberFormat(ltoa(nTotalDeposit , buffer, 10)));
		}
	}


	pRs.Close();
}
*/

void CReportForm5::RefreshList()
{
	CMyFormView::RefreshList();

	const char *szAPayMask[] = {"선불", "착불", "신용", "송금", "직접수금"};

	if(m_CallcenterCheck.GetCheck()) {
		RefreshCallcenter();
		return;
	}

	int nItem = 0;
	long nTNo, nCompany, nRiderCompany;
	COleDateTime dt1;
	CString strCName, strStart, strDest;
	int nRNo, nState;
	long nCharge, nAPay;
	long nTotalFee = 0, nTotalConFee = 0;
	BOOL bTake,bCreditAfterDiscount, bLastTake = FALSE;
	char buffer[20];
	int nNumber = 1;
	ICM::iterator it;
	CWaitCursor wait;;
	int nShareCode1, nShareCode2, nShareCode3;
	int nCurShareCode1, nCurShareCode2, nCurShareCode3;
	BOOL bShowShare1, bShowShare2, bShowShare3;
	int nShareLevel, nDis;
	long nDeposit, nDisCount, nTotal, nDisCharge, nChargeTrans;
	nDeposit = nDisCount =  nTotal =  nDisCharge =0;
	CString sDisCount = "";

	UpdateData(TRUE);
	
	int nProcessRate = atol(m_strProcessRate);
	int nOperateRate = atol(m_strOperateRate);
	bShowShare1 = m_FirstShareCheck.GetCheck() > 0 ? TRUE : FALSE;
	bShowShare2 = m_SecondShareCheck.GetCheck() > 0 ? TRUE : FALSE;
	bShowShare3 = m_ThirdShareCheck.GetCheck() > 0 ? TRUE : FALSE;

	m_List.DeleteAllItems();
	if(LF->GetCurBranchInfo()->bIntegrated) {
		MessageBox("지점간 정산은 통합보기를 지원하지 않습니다.", 
				"확인", MB_ICONINFORMATION);
		return;
	}
	CBranchInfo *pCurBi = NULL;
	int i = 0;
	for(i = 0; i < m_ba.GetCount(); i++) {
		pCurBi = m_ba.GetAt(i);
		if(pCurBi->nCompanyCode == LF->GetCurBranchInfo()->nDOrderTable) {
			nShareCode1 = pCurBi->nShareCode1 == 0 ? -1 : pCurBi->nShareCode1;
			nShareCode2 = pCurBi->nShareCode2 == 0 ? -1 : pCurBi->nShareCode2;
			nShareCode3 = pCurBi->nShareCode3 == 0 ? -1 : pCurBi->nShareCode3;
			
			break;
		}
	}

	if(i == m_ba.GetCount()) {
		MessageBox("회원사 공유코드 정보 획득실패!!\n"\
				"로지소프트로 문의바랍니다.", 
				"확인", MB_ICONINFORMATION);
		return;
	}

	MakeSharedCompanyList();
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_interchange_shared_order7");
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), LF->GetCurBranchInfo()->nDOrderTable);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtFrom);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtTo);
	if(!pRs.Execute(&pCmd)) 
		return;

	while(!pRs.IsEOF())
	{	
		pRs.GetFieldValue("nTNo", nTNo);
		pRs.GetFieldValue("dt1", dt1);
		pRs.GetFieldValue("sCName", strCName);
		pRs.GetFieldValue("sStart", strStart);
		pRs.GetFieldValue("sDest", strDest);
		pRs.GetFieldValue("nRNo", nRNo);
		pRs.GetFieldValue("nRiderCompany", nRiderCompany);
		pRs.GetFieldValue("nTotal", nCharge);
		pRs.GetFieldValue("nState", nState);
		pRs.GetFieldValue("nCompany", nCompany);
		pRs.GetFieldValue("nAPay", nAPay);
		pRs.GetFieldValue("bTake", bTake);
		pRs.GetFieldValue("nShareCode1", nCurShareCode1);
		pRs.GetFieldValue("nShareCode2", nCurShareCode2);
		pRs.GetFieldValue("nShareCode3", nCurShareCode3);
		pRs.GetFieldValue("sDisCount", sDisCount);			
		pRs.GetFieldValue("bCreditAfterDiscount", bCreditAfterDiscount);		
		pRs.GetFieldValue("cDis", nDis);		
		pRs.GetFieldValue("nChargeTrans", nChargeTrans);		
		
		if(sDisCount.Left(1) == "-") 
		{
			sDisCount.Replace("-","");
			nDisCount = atol(sDisCount) * -1;
		}
		else{
			nDisCount = atol(sDisCount);
		}	

		if(nDisCount == 0){					
				nDeposit = nCharge * atol(m_strFee) / 100;		
				nDisCharge = nCharge;
		}
		else
		{
			if(!bTake)
			{
				if(pCurBi->bCreditAfterDiscount && bCreditAfterDiscount && nDisCount != 0 )
				{				
					if(nDisCount > -100 && nDisCount < 100 )  //  할인율계산  날자적용 해주어야 함...
						nDisCharge =  nCharge + (nCharge * nDisCount) / 100;				
					else  // 금액계산
						nDisCharge = nCharge + nDisCount;				
				}
				else
				{	
					nDisCharge =  nCharge;				
				}
				nDeposit = nDisCharge * atol(m_strFee) / 100;
			}
			else
			{
				if(bCreditAfterDiscount && nDisCount != 0 )
				{				
					if(nDisCount > -100 && nDisCount < 100 )  //  할인율계산  날자적용 해주어야 함...
						nDisCharge =  nCharge + (nCharge * nDisCount) / 100;				
					else  // 금액계산
						nDisCharge = nCharge + nDisCount;				
				}
				else
				{	
					nDisCharge =  nCharge;				
				}
				nDeposit = nDisCharge * atol(m_strFee) / 100;

			}
		}


		if(!(nAPay <= 1 && m_bCash ||
			nAPay == 2 && m_bCredit ||
			nAPay == 3 && m_bOnline))
		{
			pRs.MoveNext();
			continue;
		}

		nShareLevel = FilterLevel(nCompany, nRiderCompany);
		if(!((bShowShare1 && nShareLevel == 1) ||
			(bShowShare2 && nShareLevel == 2) ||
			(bShowShare3 && nShareLevel == 3)))
		{
			pRs.MoveNext();
			continue;
		}


		if(bTake != bLastTake) {
			nNumber = 1;
			if(nItem != 0) {
				nItem++;
				m_List.InsertItem(nItem, "");
			}
		}

		it = m_icm.find(nCompany);
		if(it == m_icm.end()) {
			m_icm[nCompany].nGiveCount = 0;
			m_icm[nCompany].nGiveDeposit = 0;
			m_icm[nCompany].nGiveFee = 0;
			m_icm[nCompany].nTakeCount = 0;
			m_icm[nCompany].nTakeDeposit = 0;
			m_icm[nCompany].nTakeFee = 0;
			m_icm[nCompany].nTakeRcpShare = 0;
			m_icm[nCompany].nTakeProcessShare = 0;
			m_icm[nCompany].nTakeOperateShare = 0;
			m_icm[nCompany].nGiveRcpShare = 0;
			m_icm[nCompany].nGiveProcessShare = 0;
			m_icm[nCompany].nGiveOperateShare = 0;
		}

		it = m_icm.find(nRiderCompany);
		if(it == m_icm.end()) {
			m_icm[nRiderCompany].nGiveCount = 0;
			m_icm[nRiderCompany].nGiveDeposit = 0;
			m_icm[nRiderCompany].nGiveFee = 0;
			m_icm[nRiderCompany].nTakeCount = 0;
			m_icm[nRiderCompany].nTakeDeposit = 0;
			m_icm[nRiderCompany].nTakeFee = 0;
			m_icm[nRiderCompany].nTakeRcpShare = 0;
			m_icm[nRiderCompany].nTakeProcessShare = 0;
			m_icm[nRiderCompany].nTakeOperateShare = 0;
			m_icm[nRiderCompany].nGiveRcpShare = 0;
			m_icm[nRiderCompany].nGiveProcessShare = 0;
			m_icm[nRiderCompany].nGiveOperateShare = 0;
		}
	
		int nOperateShare = nOperateRate >= 100 ? 
					nOperateRate : (nDeposit * nOperateRate / 100);
		int nProcessShare = nProcessRate >= 100 ?
					nProcessRate : ((nDeposit - nOperateShare) * nProcessRate / 100);
		int nRcpShare = nDeposit - (nOperateShare + nProcessShare);

		if(bTake) { //받은경우
  			m_icm[nCompany].nTakeFee += nDisCharge;//nCharge;
			m_icm[nCompany].nTakeDeposit += nDeposit;
			m_icm[nCompany].nTakeCount++;

			//오더를 받은 경우에 처리비를 받고, 접수비와 운영비를 준다.
			m_icm[nCompany].nTakeRcpShare += nRcpShare;
			m_icm[nCompany].nTakeProcessShare += nProcessShare;
			m_icm[nCompany].nTakeOperateShare += nOperateShare;
		}
		else { //준경우
  			m_icm[nRiderCompany].nGiveFee += nDisCharge;//nCharge;
			m_icm[nRiderCompany].nGiveDeposit += nDeposit;
			m_icm[nRiderCompany].nGiveCount++;

			//오더를 넘긴경우에 접수비와 운영비를 받고, 처리비를 준다.
			m_icm[nRiderCompany].nGiveRcpShare += nRcpShare;
			m_icm[nRiderCompany].nGiveProcessShare += nProcessShare;
			m_icm[nRiderCompany].nGiveOperateShare += nOperateShare;
		}
/*
		m_List.InsertItem(nItem, ltoa(nNumber++, buffer, 10));
		m_List.SetItemText(nItem, 1, bTake ? "받음" : "넘김");
		m_List.SetItemText(nItem, 2, m_icm[nCompany].szCompany);
		m_List.SetItemText(nItem, 3, dt1.Format("%m-%d %H:%M"));
		m_List.SetItemText(nItem, 4, strStart);
		m_List.SetItemText(nItem, 5, strDest);
		m_List.SetItemText(nItem, 6, m_icm[nRiderCompany].szCompany);
		m_List.SetItemText(nItem, 7, ltoa(nRNo, buffer, 10));
		m_List.SetItemText(nItem, 8, LF->GetMyNumberFormat(nCharge));
		m_List.SetItemText(nItem, 9, LF->GetMyNumberFormat(nDisCharge));
		m_List.SetItemText(nItem, 10, LF->GetMyNumberFormat(nDeposit));
		m_List.SetItemText(nItem, 11, LF->GetMyNumberFormat(nRcpShare));
		m_List.SetItemText(nItem, 12, LF->GetMyNumberFormat(nProcessShare));
		m_List.SetItemText(nItem, 13, LF->GetMyNumberFormat(nOperateShare));
		m_List.SetItemText(nItem, 14, LF->GetStateString(nState));
		m_List.SetItemText(nItem, 15, CString(ltoa(nShareLevel, buffer, 10)) + "차" );
		m_List.SetItemText(nItem, 16, szAPayMask[nAPay]);

		*/
		m_List.InsertItem(nItem, ltoa(nNumber++, buffer, 10));
		m_List.SetItemText(nItem, 1, bTake ? "받음" : "넘김");
		m_List.SetItemText(nItem, 2, m_icm[nCompany].szCompany);
		m_List.SetItemText(nItem, 3, dt1.Format("%m-%d %H:%M"));
		m_List.SetItemText(nItem, 4, itoa(nTNo,buffer,10));
		m_List.SetItemText(nItem, 5, strCName);
		m_List.SetItemText(nItem, 6, strStart);
		m_List.SetItemText(nItem, 7, strDest);
		m_List.SetItemText(nItem, 8, m_icm[nRiderCompany].szCompany);
		m_List.SetItemText(nItem, 9, ltoa(nRNo, buffer, 10));
		m_List.SetItemText(nItem, 10, LF->GetMyNumberFormat(nCharge));

		if(pCurBi->bCreditAfterDiscount && bCreditAfterDiscount && nDisCount != 0 )
			m_List.SetItemText(nItem, 11,  (atoi(sDisCount) >= 100) ? "-" +LF->GetMyNumberFormat(sDisCount) :"-" +sDisCount +"%" );
		else
			m_List.SetItemText(nItem, 11, "");

		m_List.SetItemText(nItem, 12, LF->GetMyNumberFormat(nDisCharge));
		m_List.SetItemText(nItem, 13, LF->GetMyNumberFormat(nDeposit));
		m_List.SetItemText(nItem, 14, LF->GetMyNumberFormat(nRcpShare));
		m_List.SetItemText(nItem, 15, LF->GetMyNumberFormat(nProcessShare));
		m_List.SetItemText(nItem, 16, LF->GetMyNumberFormat(nOperateShare));
		m_List.SetItemText(nItem, 17, LF->GetStateString(nState));
		m_List.SetItemText(nItem, 18, CString(ltoa(nShareLevel, buffer, 10)) + "차" );
		m_List.SetItemText(nItem, 19, szAPayMask[nAPay]);
		m_List.SetItemText(nItem, 20, nAPay == 4 ? LF->GetMyNumberFormat(nCharge) : "");
		m_List.SetItemText(nItem, 21, LF->GetMyNumberFormat(nChargeTrans));
		
		bLastTake = bTake;
		nItem++;

		pRs.MoveNext();
	}


	if(nItem == 0) return;
	m_List.InsertItem(nItem++, "");

	m_List.InsertItem(nItem, "");
	SET_COLOR_LIST(p1, 255, 255, 200);
	m_List.SetItemText(nItem, 5, "◁넘긴콜");
	m_List.SetItemText(nItem, 8, "건 수");
	m_List.SetItemText(nItem, 12, "운행(할인)");
	m_List.SetItemText(nItem, 13, "콜비");
	m_List.SetItemText(nItem++, 14, "접수합계");
	//m_List.SetItemText(nItem++, 13, "운영합계");

	for(it = m_icm.begin() ; it != m_icm.end(); it++)
	{
		int nCompany = (*it).first;
		INTERCHANGE_INFO ii = (*it).second;
		if(ii.nGiveCount > 0) {
			m_List.InsertItem(nItem, "");
			SET_COLOR_LIST(p2, 255, 255, 200);
			m_List.SetItemText(nItem, 6, m_icm[nCompany].szCompany);
			m_List.SetItemText(nItem, 8, ltoa(ii.nGiveCount, buffer, 10));
			m_List.SetItemText(nItem, 12, LF->GetMyNumberFormat(ii.nGiveFee));
			m_List.SetItemText(nItem, 13, LF->GetMyNumberFormat(ii.nGiveDeposit));
			m_List.SetItemText(nItem++, 14, LF->GetMyNumberFormat(ii.nGiveRcpShare));
		}
	}
	
	m_List.InsertItem(nItem, "");
	SET_COLOR_LIST(p3, 255, 200, 200);
	m_List.SetItemText(nItem, 5, "▷받은콜");
	m_List.SetItemText(nItem, 8, "건 수");
	m_List.SetItemText(nItem, 12, "운행(할인)");
	m_List.SetItemText(nItem, 13, "콜비");
	m_List.SetItemText(nItem, 14, "접수합계");
	m_List.SetItemText(nItem++, 16, "운영합계");
	
	for(it = m_icm.begin() ; it != m_icm.end(); it++)
	{
		int nCompany = (*it).first;
		INTERCHANGE_INFO ii = (*it).second;
		if(ii.nTakeCount > 0) {
			m_List.InsertItem(nItem, "");
			SET_COLOR_LIST(p4, 255, 200, 200);
			m_List.SetItemText(nItem, 6, m_icm[nCompany].szCompany);
			m_List.SetItemText(nItem, 8, ltoa(ii.nTakeCount, buffer, 10));
			m_List.SetItemText(nItem, 12, LF->GetMyNumberFormat(ii.nTakeFee));
			m_List.SetItemText(nItem, 13, LF->GetMyNumberFormat(ii.nTakeDeposit));
			m_List.SetItemText(nItem, 14, LF->GetMyNumberFormat(ii.nTakeRcpShare));
			m_List.SetItemText(nItem++, 16, LF->GetMyNumberFormat(- ii.nTakeOperateShare));
		}
	}
	
	m_List.InsertItem(nItem, "");
	SET_COLOR_LIST(p4, 200, 200, 255);
	m_List.SetItemText(nItem, 5, "넘김-받음");
	m_List.SetItemText(nItem, 8, "건 수");
	m_List.SetItemText(nItem, 12, "운행(할인)");
	m_List.SetItemText(nItem, 13, "수수료");
	m_List.SetItemText(nItem, 14, "수금-송금");
	m_List.SetItemText(nItem, 16, "운영합계");
	nItem++;

	for(it = m_icm.begin() ; it != m_icm.end(); it++)
	{
		int nCompany = (*it).first;
		INTERCHANGE_INFO ii = (*it).second;
		if(ii.nTakeCount > 0 || ii.nGiveCount > 0) {
			int nTotalFee = ii.nTakeFee - ii.nGiveFee;
			nTotalFee = nTotalFee - nTotalFee % 100;
			nTotalFee = - nTotalFee;

			int nTotalDeposit = ii.nTakeDeposit - ii.nGiveDeposit;
			nTotalDeposit = nTotalDeposit - nTotalDeposit % 100;
			nTotalDeposit = - nTotalDeposit;

			m_List.InsertItem(nItem, "");
			SET_COLOR_LIST(p4, 200, 200, 255);
			m_List.SetItemText(nItem, 6, m_icm[nCompany].szCompany);
			m_List.SetItemText(nItem, 8, ltoa(ii.nGiveCount - ii.nTakeCount, buffer, 10));
			m_List.SetItemText(nItem, 12, LF->GetMyNumberFormat(ltoa(nTotalFee, buffer, 10)));
			m_List.SetItemText(nItem, 13, LF->GetMyNumberFormat(ltoa(nTotalDeposit , buffer, 10)));
			m_List.SetItemText(nItem, 14, LF->GetMyNumberFormat(ii.nGiveRcpShare - ii.nTakeRcpShare));
			m_List.SetItemText(nItem++, 16, LF->GetMyNumberFormat(- ii.nTakeOperateShare));
		}
	}
	
	AfxGetApp()->WriteProfileInt("Share", "ProcessShareRate", atol(m_strProcessRate));
	AfxGetApp()->WriteProfileInt("Share", "OperateShareRate", atol(m_strOperateRate));
	AfxGetApp()->WriteProfileInt("Share", "1stShare", m_FirstShareCheck.GetCheck() ? 1 : 0);
	AfxGetApp()->WriteProfileInt("Share", "2stShare", m_SecondShareCheck.GetCheck() ? 1 : 0);
	AfxGetApp()->WriteProfileInt("Share", "3rdShare", m_ThirdShareCheck.GetCheck() ? 1 : 0);
	AfxGetApp()->WriteProfileInt("Share", "Callcenter", m_CallcenterCheck.GetCheck() ? 1 : 0);
	AfxGetApp()->WriteProfileInt("Share", "Fee", atol(m_strFee));
	pRs.Close();

	m_List.Populate();
}

void CReportForm5::OnBnClickedShowBtn()
{
	RefreshList();
}

void CReportForm5::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_List.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(2);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}

void CReportForm5::OnViewExcel()
{
	if(!LF->POWER_CHECK(3900, "엑셀변환", TRUE))
		return;

	LF->AddSecurityLog(LF->GetCurBranchInfo()->nDOrderTable, 305, m_ui.nWNo, m_List.GetItemCount());  
	CMyExcel::ToExcel(&m_List);
}


void CReportForm5::MakeSharedCompanyList()
{
	m_icm.clear();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_all_company");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), LF->GetCurBranchInfo()->nDOrderTable);
	
	if(pRs.Execute(&pCmd)) {
		int nID;
		CString strName, strTel, strBranchName;
		while(!pRs.IsEOF()) {
			pRs.GetFieldValue("nID", nID);
			pRs.GetFieldValue("sName", strName);
			pRs.GetFieldValue("sBranchName", strBranchName);

			strcpy(m_icm[nID].szCompany, strBranchName + "/" + strName);
			pRs.MoveNext();
		}
		pRs.Close();
	}	
}

void CReportForm5::OnTimer(UINT nIDEvent)
{

	CRect rc;
	CWnd *pWnd = GetFocus();
	if(pWnd->GetSafeHwnd() != NULL)
	{
		pWnd->GetWindowRect(rc);
		ScreenToClient(&rc);
		m_toolTip.ShowToolTip(CPoint(rc.left, rc.top + 1));
	}

	CMyFormView::OnTimer(nIDEvent);
}

void CReportForm5::RefreshCallcenter()
{
	const char *szAPayMask[] = {"선불", "착불", "신용", "송금"};

	int nItem = 0;
	long nTNo, nCompany, nRiderCompany;
	COleDateTime dt1;
	CString strCName, strStart, strDest, sDisCount;
	int nRNo, nState;
	long nCharge;
	long nTotalFee = 0, nTotalConFee = 0;
	BOOL  bLastTake = FALSE, bFirst = FALSE;
	char buffer[20];
	int nNumber = 1;
	long nDeposit;
	ICM::iterator it;
	CWaitCursor wait;;
	int nShareCode1, nShareCode2, nShareCode3;
	int nCurShareCode1, nCurShareCode2, nCurShareCode3;
	BOOL bShowShare1, bShowShare2, bShowShare3, bMyCall, bCreditAfterDiscount;
	int nShareLevel;
	int nRcpTotal = 0, nProcessTotal = 0;
	int nRcpCount = 0, nProcessCount = 0;
	int nOperateTotal = 0;
	long nAPay,  nDisCount, nTotal, nDisCharge, nDis, nChargeTrans;
	nAPay = nTotal = nDisCount = nDisCharge = 0;
	UpdateData(TRUE);

	int nProcessRate = atol(m_strProcessRate);
	int nOperateRate = atol(m_strOperateRate);
	int nRcpRate = 100 - ((nProcessRate >= 100 ? 0 : nProcessRate) + (nOperateRate >= 100 ? 0: nOperateRate));
	
	bShowShare1 = m_FirstShareCheck.GetCheck() > 0 ? TRUE : FALSE;
	bShowShare2 = m_SecondShareCheck.GetCheck() > 0 ? TRUE : FALSE;
	bShowShare3 = m_ThirdShareCheck.GetCheck() > 0 ? TRUE : FALSE;

	m_List.DeleteAllItems();
	if(LF->GetCurBranchInfo()->bIntegrated) {
		MessageBox("지점간 정산은 통합보기를 지원하지 않습니다.", 
				"확인", MB_ICONINFORMATION);
		return;
	}
	CBranchInfo *pCurBi = NULL;
	int i = 0;
	for(i = 0; i < m_ba.GetCount(); i++) {
		pCurBi = m_ba.GetAt(i);
		if(pCurBi->nCompanyCode == LF->GetCurBranchInfo()->nDOrderTable) {
			nShareCode1 = pCurBi->nShareCode1 == 0 ? -1 : pCurBi->nShareCode1;
			nShareCode2 = pCurBi->nShareCode2 == 0 ? -1 : pCurBi->nShareCode2;
			nShareCode3 = pCurBi->nShareCode3 == 0 ? -1 : pCurBi->nShareCode3;
			break;
		}
	}

	if(i == m_ba.GetCount()) {
		MessageBox("회원사 공유코드 정보 획득실패!!\n"\
				"로지소프트로 문의바랍니다.", 
				"확인", MB_ICONINFORMATION);
		return;
	}


	MakeSharedCompanyList();
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_callcenter_report6");
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), LF->GetCurBranchInfo()->nDOrderTable);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtFrom);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtTo);
	if(!pRs.Execute(&pCmd)) 
		return;

	while(!pRs.IsEOF())
	{			
		pRs.GetFieldValue("nTNo", nTNo);
		pRs.GetFieldValue("dt1", dt1);
		pRs.GetFieldValue("sCName", strCName);
		pRs.GetFieldValue("sStart", strStart);
		pRs.GetFieldValue("sDest", strDest);
		pRs.GetFieldValue("nRNo", nRNo);
		pRs.GetFieldValue("nRiderCompany", nRiderCompany);
		pRs.GetFieldValue("nTotal", nCharge);		
		pRs.GetFieldValue("nState", nState);
		pRs.GetFieldValue("nCompany", nCompany);
		pRs.GetFieldValue("nShareCode1", nCurShareCode1);
		pRs.GetFieldValue("nShareCode2", nCurShareCode2);
		pRs.GetFieldValue("nShareCode3", nCurShareCode3);
		pRs.GetFieldValue("bMyCall", bMyCall);
		pRs.GetFieldValue("nAPay", nAPay);
		pRs.GetFieldValue("sDisCount", sDisCount);
		pRs.GetFieldValue("bCreditAfterDiscount", bCreditAfterDiscount);		
		pRs.GetFieldValue("cDis", nDis);
		pRs.GetFieldValue("nChargeTrans", nChargeTrans);
		
		if(sDisCount.Left(1) == "-") 
		{
			sDisCount.Replace("-","");
			nDisCount = atol(sDisCount) * -1;
		}
		else{
			nDisCount = atol(sDisCount);
		}	

		if(nDisCount == 0){					
				nDeposit = nCharge * atol(m_strFee) / 100;		
				nDisCharge = nCharge;
		}
		else
		{
			if(bMyCall)
			{
				if(pCurBi->bCreditAfterDiscount && bCreditAfterDiscount && nDisCount != 0 )
				{				
					if(nDisCount > -100 && nDisCount < 100 )  //  할인율계산  날자적용 해주어야 함...
						nDisCharge =  nCharge + (nCharge * nDisCount) / 100;				
					else  // 금액계산
						nDisCharge = nCharge + nDisCount;				
				}
				else
				{	
					nDisCharge =  nCharge;				
				}
				nDeposit = nDisCharge * atol(m_strFee) / 100;
			}
			else
			{
				if(bCreditAfterDiscount && nDisCount != 0 )
				{				
					if(nDisCount > -100 && nDisCount < 100 )  //  할인율계산  날자적용 해주어야 함...
						nDisCharge =  nCharge + (nCharge * nDisCount) / 100;				
					else  // 금액계산
						nDisCharge = nCharge + nDisCount;				
				}
				else
				{	
					nDisCharge =  nCharge;				
				}
				nDeposit = nDisCharge * atol(m_strFee) / 100;

			}
		}
	

		if(!((nAPay <= 1 || nAPay == 4) && m_bCash ||
			nAPay == 2 && m_bCredit ||
			nAPay == 3 && m_bOnline))
		{
			pRs.MoveNext();
			continue;
		}

		nShareLevel = FilterLevel(nCompany, nRiderCompany);
		if(!((bShowShare1 && nShareLevel == 1) ||
			(bShowShare2 && nShareLevel == 2) ||
			(bShowShare3 && nShareLevel == 3)))
		{
			pRs.MoveNext();
			continue;
		}

		if(!bMyCall && !bFirst && m_List.GetItemCount() > 0) {
			m_List.InsertItem(nItem++, "");
			bFirst = TRUE;
		}

		m_List.InsertItem(nItem, ltoa(nNumber++, buffer, 10));
		m_List.SetItemText(nItem, 1, bMyCall ? "접수" : "처리");
		m_List.SetItemText(nItem, 2, m_icm[nCompany].szCompany);
		m_List.SetItemText(nItem, 3, dt1.Format("%m-%d %H:%M"));
		
		m_List.SetItemText(nItem, 4, itoa(nTNo,buffer,10));
		m_List.SetItemText(nItem, 5, strCName);

		m_List.SetItemText(nItem, 6, strStart);
		m_List.SetItemText(nItem, 7, strDest);
		m_List.SetItemText(nItem, 8, m_icm[nRiderCompany].szCompany);
		m_List.SetItemText(nItem, 9, ltoa(nRNo, buffer, 10));
		m_List.SetItemText(nItem, 10, LF->GetMyNumberFormat(nCharge));
		
		if(pCurBi->bCreditAfterDiscount && bCreditAfterDiscount && nDisCount != 0 )
			m_List.SetItemText(nItem, 11, "-" + (atoi(sDisCount) >= 100) ? LF->GetMyNumberFormat(sDisCount) :sDisCount +"%" );
		else
			m_List.SetItemText(nItem, 11, "");

		m_List.SetItemText(nItem, 12, LF->GetMyNumberFormat(nDisCharge));
		m_List.SetItemText(nItem, 13, LF->GetMyNumberFormat(nDeposit));

		if(bMyCall) {
			nRcpCount++;
			int nOperateShare = nOperateRate >= 100 ? 
						nOperateRate : (nDeposit * nOperateRate / 100);
			int nOffset = (nOperateRate >= 100) ? nOperateRate : 0;
			int nRcpShare = (nDeposit - nOffset) * nRcpRate / 100;
			nRcpTotal += nRcpShare;
			nOperateTotal += nOperateShare;
			m_List.SetItemText(nItem, 13, LF->GetMyNumberFormat(nRcpShare));
			if(nOperateShare > 0)
				m_List.SetItemText(nItem, 15, LF->GetMyNumberFormat(nOperateShare));
		}
		else {
			nProcessCount++;

			int nOperateShare = nOperateRate >= 100 ? 
						nOperateRate : (nDeposit * nOperateRate / 100);
			int nOffset = (nOperateRate >= 100) ? nOperateRate : 0;
			int nProcessShare = (nDeposit - nOffset) * nProcessRate / 100;
			nProcessTotal += nProcessShare;
			m_List.SetItemText(nItem, 14, LF->GetMyNumberFormat(nProcessShare));
		}

		m_List.SetItemText(nItem, 16, LF->GetStateString(nState));
		m_List.SetItemText(nItem, 17, CString(ltoa(nShareLevel, buffer, 10)) + "차" );
		m_List.SetItemText(nItem, 18, szAPayMask[nAPay]);
		nItem++;

		pRs.MoveNext();
	}

	m_List.InsertItem(nItem++, "");
	m_List.InsertItem(nItem, "");
	SET_COLOR_LIST(p4, 200, 200, 255);
	m_List.SetItemText(nItem, 8, "접수총액");
	m_List.SetItemText(nItem, 9, CString(ltoa(100 - nProcessRate, buffer, 10)) + "%");
	m_List.SetItemText(nItem, 10, CString(ltoa(nRcpCount, buffer, 10)) + "건");
	m_List.SetItemText(nItem++, 12, LF->GetMyNumberFormat(nRcpTotal) + "원");

	m_List.InsertItem(nItem, "");
	SET_COLOR_LIST(p3, 200, 200, 255);
	m_List.SetItemText(nItem, 8, "처리총액");
	m_List.SetItemText(nItem, 9, CString(ltoa(nProcessRate, buffer, 10)) + "%");
	m_List.SetItemText(nItem, 10, CString(ltoa(nProcessCount, buffer, 10)) + "건");
	m_List.SetItemText(nItem++, 12, LF->GetMyNumberFormat(nProcessTotal) + "원");

	m_List.InsertItem(nItem, "");
	SET_COLOR_LIST(p5, 200, 200, 255);
	m_List.SetItemText(nItem, 8, "운영총액");
	m_List.SetItemText(nItem++, 12, LF->GetMyNumberFormat(nOperateTotal) + "원");

	m_List.InsertItem(nItem, "");
	SET_COLOR_LIST(p2, 255, 200, 200);
	m_List.SetItemText(nItem, 8, "총합계");
	m_List.SetItemText(nItem, 10, CString(ltoa(nRcpCount + nProcessCount, buffer, 10)) + "건");
	m_List.SetItemText(nItem++, 12, LF->GetMyNumberFormat(nRcpTotal + nProcessTotal + nOperateTotal) + "원");

	AfxGetApp()->WriteProfileInt("Share", "ProcessShareRate", atol(m_strProcessRate));
	AfxGetApp()->WriteProfileInt("Share", "OperateShareRate", atol(m_strOperateRate));
	AfxGetApp()->WriteProfileInt("Share", "1stShare", m_FirstShareCheck.GetCheck() ? 1 : 0);
	AfxGetApp()->WriteProfileInt("Share", "2stShare", m_SecondShareCheck.GetCheck() ? 1 : 0);
	AfxGetApp()->WriteProfileInt("Share", "3rdShare", m_ThirdShareCheck.GetCheck() ? 1 : 0);
	AfxGetApp()->WriteProfileInt("Share", "Callcenter", m_CallcenterCheck.GetCheck() ? 1 : 0);
	AfxGetApp()->WriteProfileInt("Share", "Fee", atol(m_strFee));
}


int CReportForm5::FilterLevel(int nCompany, int nRiderCompany)
{
	static BOOL bNotMatch = FALSE;

	for(int i = 1; i <= 5; i++)
		if(m_ci.GetShareCode(nCompany, i) == m_ci.GetShareCode(nRiderCompany, i))
			return i;

	if(!bNotMatch)
	{
		CString strMsg;
		strMsg.Format("공유코드가 일치하지 않는 회원사가 존재함 C:%d, R:%d", 
				nCompany, nRiderCompany);
		MessageBox(strMsg);
		bNotMatch = TRUE;
	}
	return 1;
}





