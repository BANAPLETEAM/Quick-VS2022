// ShareReportRateDlg3.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ShareReportRateDlg3.h"

// CShareReportRateDlg3

IMPLEMENT_DYNCREATE(CShareReportRateDlg3, CMyFormView)

CShareReportRateDlg3::CShareReportRateDlg3()
	: CMyFormView(CShareReportRateDlg3::IDD)
{
	COleDateTimeSpan span(30, 0,0,0);
	m_dtFrom= COleDateTime::GetCurrentTime() - span;
	m_dtTo = COleDateTime::GetCurrentTime();
}

CShareReportRateDlg3::~CShareReportRateDlg3()
{

}

void CShareReportRateDlg3::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_REPORT, m_List);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_FROM, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TO, m_dtTo);
	DDX_Control(pDX, IDC_DATETIMEPICKER_FROM, m_FromDT);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TO, m_ToDT);
	DDX_Control(pDX, IDC_DATE_BTN, m_DateBtn);
	DDX_Control(pDX, IDC_REPORT_INT_CHECK, m_ReportIntCheck);
}

BEGIN_MESSAGE_MAP(CShareReportRateDlg3, CMyFormView)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_BN_CLICKED(IDC_SHOW_BTN, OnBnClickedShowBtn)
	ON_WM_MOUSEACTIVATE()
END_MESSAGE_MAP()


// CShareReportRateDlg3 진단입니다.

#ifdef _DEBUG
void CShareReportRateDlg3::AssertValid() const
{
	CMyFormView::AssertValid();
}

void CShareReportRateDlg3::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif //_DEBUG


// CShareReportRateDlg3 메시지 처리기입니다.

void CShareReportRateDlg3::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	m_DateBtn.InitDateButton(&m_FromDT, &m_ToDT);
	m_DateBtn.OnMenuYesterday();

	CImageList ImageList; 
	ImageList.Create(1,17,ILC_COLOR,1,1); 
	m_List.SetImageList(&ImageList,LVSIL_SMALL); 
	m_List.ModifyStyle(0, LVS_SHOWSELALWAYS | LVS_NOSORTHEADER);
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_FLATSB | LVS_EX_GRIDLINES);


	m_List.InsertColumn(0,"타입",LVCFMT_LEFT,70);
	m_List.InsertColumn(1,"회사명",LVCFMT_LEFT,110);
	m_List.InsertColumn(2,"지사명",LVCFMT_LEFT,90);
	m_List.InsertColumn(3,"건수",LVCFMT_RIGHT,50);
	m_List.InsertColumn(4,"운행료",LVCFMT_RIGHT,80);
	m_List.InsertColumn(5,"입금액",LVCFMT_RIGHT,70);
	m_List.InsertColumn(6,"접수비",LVCFMT_RIGHT,70);
	m_List.InsertColumn(7,"처리비",LVCFMT_RIGHT,50);
	m_List.InsertColumn(8,"운영비",LVCFMT_RIGHT,60);
	m_List.InsertColumn(9,"정산비율",LVCFMT_CENTER,60);

	m_ReportIntCheck.SetCheck(1);

}

void CShareReportRateDlg3::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_List.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(2);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}

void CShareReportRateDlg3::OnViewExcel()
{
	if(!POWER_CHECK(1900, "엑셀변환", TRUE))
		return;

	AddSecurityLog(GetCurBranchInfo()->nDOrderTable, 1203, m_List.GetItemCount());  
	CMyExcel::ToExcel(m_List);
}


#define SET_COLOR_LIST(ppp, x, y, z) 	COLOR_STRUCT *ppp = new COLOR_STRUCT;\
										ppp->crBk = RGB(x,y,z);\
										ppp->crText = RGB(0,0,0);\
										m_List.SetItemData(nItem, (DWORD_PTR)ppp);


void CShareReportRateDlg3::RefreshList()
{
	UpdateData(TRUE);
	m_List.DeleteAllItems();

	char buffer[20];
	int nItem = 0;

	INTERCHANGE_INFO2 gtii;
	ZeroMemory(&gtii, sizeof(gtii));


	ICM2 icm;
	long  nCompany, nRiderCompany;//nTNo,
	COleDateTime dt1;
	CString strCName, strStart, strDest;
	//int  nState;//nRNo,
	long nCharge;
	long nTotalFee = 0, nTotalConFee = 0;
	BOOL bTake, bLastTake = FALSE;
	int nNumber = 1;
	long nDeposit;
	ICM2::iterator it;

	//CWaitCursor wait;
	//int nShareCode1, nShareCode2, nShareCode3, nShareCode4, nShareCode5;
	//int nShareCode6, nShareCode7, nShareCode8, nShareCode9, nShareCode10;
	//int nCurShareCode1, nCurShareCode2, nCurShareCode3, nCurShareCode4, nCurShareCode5;
	//int nCurShareCode6, nCurShareCode7, nCurShareCode8, nCurShareCode9, nCurShareCode10;
	CString strCompany, strRiderCompany, strBranchName, strRiderBranchName;
	long nCount;
	COleDateTime dtLog;

	int nMyCompany = m_nDOrderTable;
//	StatusText(0, "정산중입니다....");

	ICM2 icmTotal;
/*
	for(int i = 0; i < m_ba.GetCount(); i++) {
		CBranchInfo *pCurBi = m_ba.GetAt(i);
		if(pCurBi->nCompanyCode == nMyCompany) {
			nShareCode1 = pCurBi->nShareCode1 == 0 ? -1 : pCurBi->nShareCode1;
			nShareCode2 = pCurBi->nShareCode2 == 0 ? -1 : pCurBi->nShareCode2;
			nShareCode3 = pCurBi->nShareCode3 == 0 ? -1 : pCurBi->nShareCode3;
			nShareCode4 = pCurBi->nShareCode4 == 0 ? -1 : pCurBi->nShareCode4;
			nShareCode5 = pCurBi->nShareCode5 == 0 ? -1 : pCurBi->nShareCode5;
			break;
		}
	}


	if(i == m_ba.GetCount()) {
		MessageBox("회원사 공유코드 정보 획득실패!!\n"\
			"로지소프트로 문의바랍니다.", 
			"확인", MB_ICONINFORMATION);
		return;
	}
*/
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_soa_report_1");
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), m_ci.m_nCompanyCode);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtFrom);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtTo);
	pCmd.AddParameter(typeBool, typeInput, sizeof(LONG), 1);


	if(!pRs.Execute(&pCmd)) 
	{
		MessageBox("재시도 하시기 바랍니다.", "통신오류", MB_ICONINFORMATION);
		return;
	}

	while(!pRs.IsEOF())
	{	
		long nOrderShare1, nRiderShare1;
/*
		long nOrderShare1, nOrderShare2, nOrderShare3, nOrderShare4, nOrderShare5;
		long nOrderShare6, nOrderShare7, nOrderShare8, nOrderShare9, nOrderShare10;
		long nRiderShare1, nRiderShare2, nRiderShare3, nRiderShare4, nRiderShare5;
		long nRiderShare6, nRiderShare7, nRiderShare8, nRiderShare9, nRiderShare10;
*/
		long nRcpDeposit, nRcpRate;

		pRs.GetFieldValue("nRiderCompany", nRiderCompany);
		pRs.GetFieldValue("nCharge", nCharge);
		pRs.GetFieldValue("nCompany", nCompany);
		pRs.GetFieldValue("nDeposit", nDeposit);
		pRs.GetFieldValue("nCount", nCount);
		pRs.GetFieldValue("bTake", bTake);
		pRs.GetFieldValue("sName", strCompany);
		pRs.GetFieldValue("sBranchName", strBranchName);
		pRs.GetFieldValue("sRiderName", strRiderCompany);
		pRs.GetFieldValue("sRiderBranchName", strRiderBranchName);

		pRs.GetFieldValue("nOrderShare1", nOrderShare1);
/*
		pRs.GetFieldValue("nOrderShare2", nOrderShare2);
		pRs.GetFieldValue("nOrderShare3", nOrderShare3);
		pRs.GetFieldValue("nOrderShare4", nOrderShare4);
		pRs.GetFieldValue("nOrderShare5", nOrderShare5);
		pRs.GetFieldValue("nOrderShare6", nOrderShare6);
		pRs.GetFieldValue("nOrderShare7", nOrderShare7);
		pRs.GetFieldValue("nOrderShare8", nOrderShare8);
		pRs.GetFieldValue("nOrderShare9", nOrderShare9);
		pRs.GetFieldValue("nOrderShare10", nOrderShare10);
*/
		pRs.GetFieldValue("nRiderShare1", nRiderShare1);
/*
		pRs.GetFieldValue("nRiderShare2", nRiderShare2);
		pRs.GetFieldValue("nRiderShare3", nRiderShare3);
		pRs.GetFieldValue("nRiderShare4", nRiderShare4);
		pRs.GetFieldValue("nRiderShare5", nRiderShare5);
		pRs.GetFieldValue("nRiderShare6", nRiderShare6);
		pRs.GetFieldValue("nRiderShare7", nRiderShare7);
		pRs.GetFieldValue("nRiderShare8", nRiderShare8);
		pRs.GetFieldValue("nRiderShare9", nRiderShare9);
		pRs.GetFieldValue("nRiderShare10", nRiderShare10);
*/
		pRs.GetFieldValue("nRcpDeposit", nRcpDeposit);
		pRs.GetFieldValue("nRcpRate", nRcpRate);


		if(bTake != bLastTake) {
			nNumber = 1;
			if(nItem != 0) {
				nItem++;
				m_List.InsertItem(nItem, "");
			}
		}

		it = icm.find(nCompany);
		if(it == icm.end()) {
			ZeroMemory(&icm[nCompany], sizeof(INTERCHANGE_INFO2));
			strcpy(icm[nCompany].szCompany, strCompany);
			strcpy(icm[nCompany].szBranchName, strBranchName);
			icm[nCompany].nShareCode1 = nOrderShare1;
			icm[nCompany].nRcpRate = nRcpRate;
		}

		it = icm.find(nRiderCompany);
		if(it == icm.end()) {
			ZeroMemory(&icm[nRiderCompany], sizeof(INTERCHANGE_INFO2));
			strcpy(icm[nRiderCompany].szCompany, strRiderCompany);
			strcpy(icm[nRiderCompany].szBranchName, strRiderBranchName);
			icm[nRiderCompany].nShareCode1 = nRiderShare1;
			icm[nRiderCompany].nRcpRate = nRcpRate;
		}


		if(bTake) { //받은경우
			icm[nCompany].nTakeFee += nCharge;
			icm[nCompany].nTakeDeposit += nDeposit;
			icm[nCompany].nTakeCount += nCount;

			//오더를 받은 경우에 처리비를 받고, 접수비와 운영비를 준다.
			icm[nCompany].nTakeRcpShare += nRcpDeposit;
//			icm[nCompany].nTakeProcessShare += nProcessShare;
//			icm[nCompany].nTakeOperateShare += nOperateShare;
		}
		else { //준경우
			icm[nRiderCompany].nGiveFee += nCharge;
			icm[nRiderCompany].nGiveDeposit += nDeposit;
			icm[nRiderCompany].nGiveCount += nCount;

			//오더를 넘긴경우에 접수비와 운영비를 받고, 처리비를 준다.
			icm[nRiderCompany].nGiveRcpShare += nRcpDeposit;
//			icm[nRiderCompany].nGiveProcessShare += nProcessShare;
//			icm[nRiderCompany].nGiveOperateShare += nOperateShare;
		}


		nNumber++;
		bLastTake = bTake;
		pRs.MoveNext();
	}


	INTERCHANGE_INFO2 tii;
	ZeroMemory(&tii, sizeof(tii));


	//1차통합정산인 경우에 1차코드에 따라서 group by 한 후에 맵을 재 복사한다.
	if(m_ReportIntCheck.GetCheck())
	{
		ICM2 icm2;
		for(it = icm.begin() ; it != icm.end(); it++)
		{	
			int nCompany = (*it).first;
			int nShareCode1 = (*it).second.nShareCode1;
			INTERCHANGE_INFO2 ii = (*it).second;
			if(ii.nGiveCount > 0) {
				icm2[nShareCode1].nGiveCount += ii.nGiveCount;
				icm2[nShareCode1].nGiveFee += ii.nGiveFee;
				icm2[nShareCode1].nGiveDeposit += ii.nGiveDeposit;
				icm2[nShareCode1].nGiveRcpShare += ii.nGiveRcpShare;
				icm2[nShareCode1].nGiveOperateShare += ii.nGiveOperateShare;
				icm2[nShareCode1].nRcpRate = ii.nRcpRate;
				if(strlen(icm2[nShareCode1].szCompany) == 0)
					strcpy(icm2[nShareCode1].szCompany, (*it).second.szCompany);
			}

			if(ii.nTakeCount > 0)
			{
				icm2[nShareCode1].nTakeCount += ii.nTakeCount;
				icm2[nShareCode1].nTakeFee += ii.nTakeFee;
				icm2[nShareCode1].nTakeDeposit += ii.nTakeDeposit;
				icm2[nShareCode1].nTakeRcpShare += ii.nTakeRcpShare;
				icm2[nShareCode1].nTakeOperateShare += ii.nTakeOperateShare;
				icm2[nShareCode1].nRcpRate = ii.nRcpRate;
				if(strlen(icm2[nShareCode1].szCompany) == 0)
					strcpy(icm2[nShareCode1].szCompany, (*it).second.szCompany);
			}
		}

		icm.erase(icm.begin(), icm.end());
		icm.insert(icm2.begin(), icm2.end());
	}


	m_List.InsertItem(nItem, "");
	SET_COLOR_LIST(p1, 255, 255, 200);
	m_List.SetItemText(nItem, 0, "◁넘긴콜");
	m_List.SetItemText(nItem, 3, "건 수");
	m_List.SetItemText(nItem, 4, "운행료");
	m_List.SetItemText(nItem, 5, "입금액");
	m_List.SetItemText(nItem++, 6, "접수합계");
	//m_List.SetItemText(nItem++, 12, "운영합계"); //넘긴콜은 운영합계가 없다.


	for(it = icm.begin() ; it != icm.end(); it++)
	{
		int nCompany = (*it).first;
		INTERCHANGE_INFO2 ii = (*it).second;
		if(ii.nGiveCount > 0) {
			m_List.InsertItem(nItem, "");
			SET_COLOR_LIST(p2, 255, 255, 200);
			m_List.SetItemText(nItem, 1, icm[nCompany].szCompany);
			m_List.SetItemText(nItem, 2, icm[nCompany].szBranchName);
			m_List.SetItemText(nItem, 3, ltoa(ii.nGiveCount, buffer, 10));
			m_List.SetItemText(nItem, 4, GetMyNumberFormat(ii.nGiveFee));
			m_List.SetItemText(nItem, 5, GetMyNumberFormat(ii.nGiveDeposit));
			m_List.SetItemText(nItem, 6, GetMyNumberFormat(ii.nGiveRcpShare));
			m_List.SetItemText(nItem++, 9, GetShareReportRateString(ii.nRcpRate));
			tii.nGiveCount += ii.nGiveCount;
			tii.nGiveFee += ii.nGiveFee;
			tii.nGiveDeposit += ii.nGiveDeposit;
			tii.nGiveRcpShare += ii.nGiveRcpShare;
		}
	}

	if(tii.nGiveCount > 0)
	{
		m_List.InsertItem(nItem, "");
		SET_COLOR_LIST(p3, 255, 255, 200);
		m_List.SetItemText(nItem, 1, "*합계");
		m_List.SetItemText(nItem, 3, ltoa(tii.nGiveCount, buffer, 10));
		m_List.SetItemText(nItem, 4, GetMyNumberFormat(tii.nGiveFee));
		m_List.SetItemText(nItem, 5, GetMyNumberFormat(tii.nGiveDeposit));
		m_List.SetItemText(nItem++, 6, GetMyNumberFormat(tii.nGiveRcpShare));
		gtii.nGiveCount += tii.nGiveCount;
		gtii.nGiveFee += tii.nGiveFee;
		gtii.nGiveDeposit += tii.nGiveDeposit;
		gtii.nGiveRcpShare += tii.nGiveRcpShare;
	}


	m_List.InsertItem(nItem, "");
	SET_COLOR_LIST(p4, 255, 200, 200);
	m_List.SetItemText(nItem, 0, "▷받은콜");
	m_List.SetItemText(nItem, 3, "건 수");
	m_List.SetItemText(nItem, 4, "운행료");
	m_List.SetItemText(nItem, 5, "입금액");
	m_List.SetItemText(nItem, 6, "접수합계");
	m_List.SetItemText(nItem++, 8, "운영합계");

	for(it = icm.begin() ; it != icm.end(); it++)
	{
		int nCompany = (*it).first;
		INTERCHANGE_INFO2 ii = (*it).second;
		if(ii.nTakeCount > 0) {
			m_List.InsertItem(nItem, "");
			SET_COLOR_LIST(p5, 255, 200, 200);
			m_List.SetItemText(nItem, 1, icm[nCompany].szCompany);
			m_List.SetItemText(nItem, 2, icm[nCompany].szBranchName);
			m_List.SetItemText(nItem, 3, ltoa(ii.nTakeCount, buffer, 10));
			m_List.SetItemText(nItem, 4, GetMyNumberFormat(ii.nTakeFee));
			m_List.SetItemText(nItem, 5, GetMyNumberFormat(ii.nTakeDeposit));
			m_List.SetItemText(nItem, 6, GetMyNumberFormat(ii.nTakeRcpShare));
			m_List.SetItemText(nItem, 8, GetMyNumberFormat(- ii.nTakeOperateShare));
			m_List.SetItemText(nItem++, 9, GetShareReportRateString(ii.nRcpRate));
			tii.nTakeCount += ii.nTakeCount;
			tii.nTakeFee += ii.nTakeFee;
			tii.nTakeDeposit += ii.nTakeDeposit;
			tii.nTakeRcpShare += ii.nTakeRcpShare;
			tii.nTakeOperateShare += ii.nTakeOperateShare;
		}
	}


	if(tii.nTakeCount > 0)
	{
		m_List.InsertItem(nItem, "");
		SET_COLOR_LIST(p6, 255, 200, 200);
		m_List.SetItemText(nItem, 1, "*합계");
		m_List.SetItemText(nItem, 3, ltoa(tii.nTakeCount, buffer, 10));
		m_List.SetItemText(nItem, 4, GetMyNumberFormat(tii.nTakeFee));
		m_List.SetItemText(nItem, 5, GetMyNumberFormat(tii.nTakeDeposit));
		m_List.SetItemText(nItem, 6, GetMyNumberFormat(tii.nTakeRcpShare));
		m_List.SetItemText(nItem++, 8, GetMyNumberFormat(- tii.nTakeOperateShare));
		gtii.nTakeCount += tii.nTakeCount;
		gtii.nTakeFee += tii.nTakeFee;
		gtii.nTakeDeposit += tii.nTakeDeposit;
		gtii.nTakeRcpShare += tii.nTakeRcpShare;
		gtii.nTakeOperateShare += tii.nTakeOperateShare;
	}


	m_List.InsertItem(nItem, "");
	SET_COLOR_LIST(p7, 200, 200, 255);
	m_List.SetItemText(nItem, 0, "넘김-받음");
	m_List.SetItemText(nItem, 3, "건 수");
	m_List.SetItemText(nItem, 4, "운행료");
	m_List.SetItemText(nItem, 5, "입금정산");
	m_List.SetItemText(nItem, 6, "수금-송금");
	m_List.SetItemText(nItem++, 8, "운영합계");

	for(it = icm.begin() ; it != icm.end(); it++)
	{
		int nCompany = (*it).first;
		INTERCHANGE_INFO2 ii = (*it).second;
		if(ii.nTakeCount > 0 || ii.nGiveCount > 0) {
			int nTotalFee = ii.nTakeFee - ii.nGiveFee;
			nTotalFee = nTotalFee - nTotalFee % 100;
			nTotalFee = - nTotalFee;

			int nTotalDeposit = ii.nTakeDeposit - ii.nGiveDeposit;
			nTotalDeposit = nTotalDeposit - nTotalDeposit % 100;
			nTotalDeposit = - nTotalDeposit;

			m_List.InsertItem(nItem, "");
			SET_COLOR_LIST(p8, 200, 200, 255);
			m_List.SetItemText(nItem, 1, icm[nCompany].szCompany);
			m_List.SetItemText(nItem, 2, icm[nCompany].szBranchName);
			m_List.SetItemText(nItem, 3, ltoa(ii.nGiveCount - ii.nTakeCount, buffer, 10));
			m_List.SetItemText(nItem, 4, GetMyNumberFormat(ltoa(nTotalFee, buffer, 10)));
			m_List.SetItemText(nItem, 5, GetMyNumberFormat(ltoa(nTotalDeposit , buffer, 10)));
			m_List.SetItemText(nItem, 6, GetMyNumberFormat(ii.nGiveRcpShare - ii.nTakeRcpShare));
			m_List.SetItemText(nItem, 8, GetMyNumberFormat(- ii.nTakeOperateShare));
			m_List.SetItemText(nItem++, 9, GetShareReportRateString(ii.nRcpRate));

			icmTotal[nCompany].nTakeCount += ii.nTakeCount;
			icmTotal[nCompany].nTakeDeposit += ii.nTakeDeposit;
			icmTotal[nCompany].nTakeFee += ii.nTakeFee;
			icmTotal[nCompany].nTakeOperateShare += ii.nTakeOperateShare;
			icmTotal[nCompany].nTakeProcessShare += ii.nTakeProcessShare;
			icmTotal[nCompany].nTakeRcpShare += ii.nTakeRcpShare;
			icmTotal[nCompany].nGiveCount += ii.nGiveCount;
			icmTotal[nCompany].nGiveDeposit += ii.nGiveDeposit;
			icmTotal[nCompany].nGiveFee += ii.nGiveFee;
			icmTotal[nCompany].nGiveOperateShare += ii.nGiveOperateShare;
			icmTotal[nCompany].nGiveProcessShare += ii.nGiveProcessShare;
			icmTotal[nCompany].nGiveRcpShare += ii.nGiveRcpShare;
			strcpy(icmTotal[nCompany].szCompany, ii.szCompany);
		}
	}

	if(tii.nTakeCount > 0 || tii.nGiveCount > 0)
	{
		m_List.InsertItem(nItem, "");
		SET_COLOR_LIST(p9, 200, 200, 255);
		m_List.SetItemText(nItem, 1, "*합계");
		m_List.SetItemText(nItem, 3, ltoa(tii.nGiveCount - tii.nTakeCount, buffer, 10));
		m_List.SetItemText(nItem, 4, GetMyNumberFormat(tii.nGiveFee - tii.nTakeFee));
		m_List.SetItemText(nItem, 5, GetMyNumberFormat(tii.nGiveDeposit - tii.nTakeDeposit));
		m_List.SetItemText(nItem, 6, GetMyNumberFormat(tii.nGiveRcpShare - tii.nTakeRcpShare));
		m_List.SetItemText(nItem++, 8, GetMyNumberFormat(- tii.nTakeOperateShare));
	}

	pRs.Close();


//	StatusText(0, "정산이 완료되었습니다.");

}

void CShareReportRateDlg3::OnBnClickedShowBtn()
{
	RefreshList();
}


CString CShareReportRateDlg3::GetShareReportRateString(long nRcpRate)
{
	CString strRate;
	if(nRcpRate == 30)
		strRate = "무정산";
	else
		strRate.Format("%d : %d", nRcpRate, 0);

	return strRate;
}

int CShareReportRateDlg3::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	return 0;
	return CMyFormView::OnMouseActivate(pDesktopWnd, nHitTest, message);
}
