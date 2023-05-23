
// CallCountDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "CallCountDlg.h"
#include "MainFrm.h" 

// CCallCountDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCallCountDlg, CMyDialog)
CCallCountDlg::CCallCountDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(CCallCountDlg::IDD, pParent)
{
}

CCallCountDlg::~CCallCountDlg()
{
}

void CCallCountDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_EXCEL_OUT_BUTTON, m_btnExcelOut);
	DDX_Control(pDX, IDC_REFRESH_BTN, m_btnRefresh);
	DDX_Control(pDX, IDC_OK_BTN, m_btnOk);
	DDX_Control(pDX, IDC_CANCEL_BTN, m_btnCancel);

	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_FROM, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TO, m_dtTo);
	DDX_Control(pDX, IDC_DATETIMEPICKER_FROM, m_FromDT);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TO, m_ToDT);
	DDX_Control(pDX, IDC_DATE_BTN, m_btnDate);
	DDX_Control(pDX, IDC_MAIN_COMBO, m_cmbMain);
	DDX_Control(pDX, IDC_BRANCH_EDIT, m_edtBranch);
	DDX_Control(pDX, IDC_OPEN_BRNACH_BTN, m_btnOpenBranch);
	DDX_Control(pDX, IDC_NO_SHOW_ZERO_CHECK, m_chkNoShowZero);
}


BEGIN_MESSAGE_MAP(CCallCountDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_BN_CLICKED(IDC_EXCEL_OUT_BUTTON, OnBnClickedExcelOutButton)
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_WM_CONTEXTMENU()
	ON_BN_CLICKED(IDC_CANCEL_BTN, OnBnClickedCancelBtn)
	ON_BN_CLICKED(IDC_OK_BTN, OnBnClickedOkBtn)
	ON_BN_CLICKED(IDC_OPEN_BRNACH_BTN, OnBnClickedOpenBranchBtn)
	ON_BN_CLICKED(IDC_NO_SHOW_ZERO_CHECK, &CCallCountDlg::OnBnClickedNoShowZeroCheck)
END_MESSAGE_MAP()


// CCallCountDlg 메시지 처리기입니다.

void CCallCountDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();
}

BOOL CCallCountDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	BOOL bChk = AfxGetApp()->GetProfileInt("CallCountDlg", "NoZero", 0);
	m_chkNoShowZero.SetCheck(bChk);

	m_btnDate.InitDateButton(&m_FromDT, &m_ToDT);
	m_btnDate.OnMenuToday();

	m_cBranchCombo.InitBranchCombo(&m_cmbMain, &m_edtBranch, &m_btnOpenBranch);

	CImageList m_ImageList; 
	m_ImageList.Create(1,17,ILC_COLOR,1,1); 
	m_List.SetImageList(&m_ImageList,LVSIL_SMALL); 

	m_List.ModifyStyle(0, LVS_SHOWSELALWAYS);
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_FLATSB | 
		LVS_EX_GRIDLINES | LVS_EX_SUBITEMIMAGES);

	m_List.InsertColumn(0,"No.",LVCFMT_LEFT,30);
	m_List.InsertColumn(1,"지사명",LVCFMT_LEFT,90);
	m_List.InsertColumn(2,"전화",LVCFMT_LEFT, 85);
	m_List.InsertColumn(3,"총건수",LVCFMT_RIGHT, 55);
	m_List.InsertColumn(4,"완료수",LVCFMT_RIGHT, 55);
	
	m_List.InsertColumn(5,"취소수",LVCFMT_RIGHT, 50);
	m_List.InsertColumn(6,"취소율",LVCFMT_RIGHT, 50);
	m_List.InsertColumn(7,"문의(콜)",LVCFMT_RIGHT, 55);
	m_List.InsertColumn(8,"기사부족",LVCFMT_RIGHT, 65);
	m_List.InsertColumn(9,"총입금",LVCFMT_RIGHT, 65);
	m_List.InsertColumn(10,"금액",LVCFMT_RIGHT, 75);
	m_List.InsertColumn(11,"총기사",LVCFMT_RIGHT, 50);
	m_List.InsertColumn(12,"출근",LVCFMT_RIGHT, 40);
	m_List.InsertColumn(13,"운행",LVCFMT_RIGHT, 40);
	m_List.InsertColumn(14,"운행률",LVCFMT_RIGHT, 55);

	OnBnClickedRefreshBtn();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CCallCountDlg::OnBnClickedRefreshBtn()
{
	//CWaitCursor wait;
	int nItem = 0;
	char buffer[10];

	UpdateData(TRUE);

	if((m_ei.dtTodayBound - COleDateTimeSpan(0, 3, 0, 0)) > m_dtFrom)
	{
		if(!LF->POWER_CHECK(1501, "콜카운트 이전날짜 조회", TRUE))
			return;
	}

	m_List.DeleteAllItems();

	CBranchInfo *pBi = NULL;
	int nTankType = 0;
	int nCount = (int)m_ba.GetCount();
	if(nCount < 2)
	{
		pBi = m_ba.GetAt(0);
		nTankType = pBi->nTankType;
	}
	else
	{
		for(int i= 0; i < m_ba.GetCount(); i++)
		{
			pBi = m_ba.GetAt(i);
			if(!pBi->bIntegrated && pBi->nCompanyCode == m_ci.m_nCompanyCode)
			{
				nTankType = pBi->nTankType;
				break;
			}
		}
	}

	long nCompany = 0;
	BOOL bIntegrated = FALSE;
	CString sTemp = "", sInqueryCount = "";

	m_cBranchCombo.GetVirtualCode(nCompany, bIntegrated, sTemp);

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_call_count_2021");
	//pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ci.m_nCompanyCode);
	//pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_ba.GetCount() < 2 ? FALSE : TRUE);
	pCmd.AddParameter(nCompany);
	pCmd.AddParameter(bIntegrated);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtFrom);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtTo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long),nTankType );

	if(pRs.Execute(&pCmd))
	{
		long nTotalCountT = 0;
		long nCompleteCountT = 0;
		long nCancelCountT = 0;
		long nCancelCount7T = 0, nInqueryCountT = 0;
		long nTotalRiderT = 0, nAttendRiderT = 0, nOrderRiderT = 0;
		LONGLONG nTotalDepositT = 0, nTotalChargeT = 0;

		BOOL bNoShowZero = m_chkNoShowZero.GetCheck();

		while(!pRs.IsEOF())
		{
			CString strBranchName, strPhone;
			long nTotalCount, nCompleteCount, nInqueryCount;
			long nCancelCount, nCancelCount7;
			long nTotalRider, nAttendRider, nOrderRider;

			CString strTotalDeposit, strTotalCharge;
			LONGLONG nTotalDeposit, nTotalCharge;

			pRs.GetFieldValue("sBranchName", strBranchName);
			pRs.GetFieldValue("sTel", strPhone);
			pRs.GetFieldValue("nTotalCount", nTotalCount);
			pRs.GetFieldValue("nCompleteCount", nCompleteCount);
			pRs.GetFieldValue("nCancelCount", nCancelCount);
			pRs.GetFieldValue("nCancelCount7", nCancelCount7); 
			pRs.GetFieldValue("sTotalDeposit", strTotalDeposit); nTotalDeposit = _atoi64(strTotalDeposit);
			pRs.GetFieldValue("sTotalCharge", strTotalCharge); nTotalCharge = _atoi64(strTotalCharge);
		
			pRs.GetFieldValue("nTotalRider", nTotalRider);
			pRs.GetFieldValue("nAttendRider", nAttendRider);
			pRs.GetFieldValue("nOrderRider", nOrderRider);
			pRs.GetFieldValue("nInqueryCount", nInqueryCount);

			float nCancelRate = 0, nOrderRiderRate = 0.0;
			if(nTotalCount > 0)
				nCancelRate = (float)nCancelCount * 100 / (float)nTotalCount;

			if(nTotalRider > 0) 
				nOrderRiderRate = (float)nOrderRider * 100.0 / (float)nTotalRider;

			sInqueryCount = LF->GetMyNumberFormat(nInqueryCount) +  "(" + LF->GetMyNumberFormat(nTotalCount + nInqueryCount) + ")";

			m_List.InsertItem(nItem, ltoa(nItem, buffer, 10));
			m_List.SetItemText(nItem, 1, strBranchName);
			m_List.SetItemText(nItem, 2, LF->GetDashPhoneNumber(strPhone));
			m_List.SetItemText(nItem, 3, ltoa(nTotalCount, buffer, 10));
			m_List.SetItemText(nItem, 4, ltoa(nCompleteCount, buffer, 10));
			m_List.SetItemText(nItem, 5, ltoa(nCancelCount, buffer, 10));

			CString sTemp = ""; sTemp.Format("%.1f", nCancelRate);
			m_List.SetItemText(nItem, 6, sTemp + "%");
			m_List.SetItemText(nItem, 7, sInqueryCount);
			m_List.SetItemText(nItem, 8, itoa(nCancelCount7, buffer, 10));

			m_List.SetItemText(nItem, 9, LF->GetMyNumberFormat(strTotalDeposit));

			m_List.SetItemText(nItem, 10, LF->GetMyNumberFormat(strTotalCharge));
			m_List.SetItemText(nItem, 11, LF->GetMyNumberFormat(nTotalRider));
			m_List.SetItemText(nItem, 12, LF->GetMyNumberFormat(nAttendRider));
			m_List.SetItemText(nItem, 13, LF->GetMyNumberFormat(nOrderRider));
			sTemp.Format("%.1f", nOrderRiderRate);
			m_List.SetItemText(nItem, 14, sTemp+ "%");		

			nTotalCountT += nTotalCount;
			nCompleteCountT += nCompleteCount;
			nCancelCountT += nCancelCount;
			nCancelCount7T += nCancelCount7;
			nInqueryCountT += nInqueryCount;
			nTotalDepositT += nTotalDeposit;
			nTotalChargeT += nTotalCharge;

			nTotalRiderT += nTotalRider;
			nAttendRiderT += nAttendRider;
			nOrderRiderT += nOrderRider;

			nItem++;
			pRs.MoveNext();
		}

		if(nItem > 0)
		{ 
			float nCancelRateT = 0;
			float nOrderRiderRateT = 0.0; 
			if(nTotalCountT > 0)
				nCancelRateT = (float)nCancelCountT * 100 / (float)nTotalCountT;

			if(nTotalRiderT > 0)
				nOrderRiderRateT = (float)nOrderRiderT * 100.0 / (float)nTotalRiderT ;

			m_List.InsertItem(nItem++, "");
			m_List.InsertItem(nItem, "");
			m_List.SetItemText(nItem, 1, "합계");
			m_List.SetItemText(nItem, 2, "");
			m_List.SetItemText(nItem, 3, ltoa(nTotalCountT, buffer, 10));
			m_List.SetItemText(nItem, 4, ltoa(nCompleteCountT, buffer, 10));
			m_List.SetItemText(nItem, 5, ltoa(nCancelCountT, buffer, 10));

			CString sTemp = ""; sTemp.Format("%.1f", nCancelRateT);
			m_List.SetItemText(nItem, 6, sTemp + "%"); 
			m_List.SetItemText(nItem, 7, ltoa(nCancelCount7T, buffer, 10));
			m_List.SetItemText(nItem, 8, LF->GetMyNumberFormat(nInqueryCountT));
			CString strTempDeposit, strTempCharge;
			strTempDeposit.Format("%lld", nTotalDepositT);
			strTempCharge.Format("%lld", nTotalChargeT);
			m_List.SetItemText(nItem, 9, LF->GetMyNumberFormat(strTempDeposit));
			m_List.SetItemText(nItem, 10, LF->GetMyNumberFormat(strTempCharge));

			m_List.SetItemText(nItem, 11, LF->GetMyNumberFormat(nTotalRiderT));
			m_List.SetItemText(nItem, 12, LF->GetMyNumberFormat(nAttendRiderT));
			m_List.SetItemText(nItem, 13, LF->GetMyNumberFormat(nOrderRiderT));

			sTemp.Format("%.1f", nOrderRiderRateT);
			m_List.SetItemText(nItem, 14, sTemp + "%" );
		}
	}

	m_List.Populate();

	ListFilter();
}

void CCallCountDlg::ListFilter()
{
	BOOL bNoShowZero = m_chkNoShowZero.GetCheck();

	CXTPGridRecords* pRecords = m_List.GetRecords();

	for(int i=0; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord* pRecord = pRecords->GetAt(i);

		CString sCount = pRecord->GetItem(3)->GetCaption(NULL);

		if((sCount == "0") && (bNoShowZero == TRUE))
			pRecord->SetVisible(FALSE);
		else
			pRecord->SetVisible(TRUE);
	}

	m_List.Populate();	
}


void CCallCountDlg::OnViewExcel()
{
	if(!LF->POWER_CHECK(1900, "상황 엑셀변환", TRUE))
		return;

	/* 김과장 작업
	AddSecurityLogEx(LF->GetCurBranchInfo()->nCompanyCode,
		701, m_List.GetItemCount());  */

	CMyExcel::ToExcel(&m_List);
}	

void CCallCountDlg::OnBnClickedExcelOutButton()
{
	if(!LF->POWER_CHECK(1900, "상황 엑셀변환", TRUE))
		return;

	/*AddSecurityLogEx(LF->GetCurBranchInfo()->nCompanyCode,
		701, m_List.GetItemCount());  */
	CMyExcel::ToExcel(&m_List);
}

void CCallCountDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	rect = NULL;
	m_List.GetWindowRect(&rect);

	if(rect.PtInRect(point))
	{
		CMenu rMenu;
		rMenu.LoadMenu(IDR_CONTEXT_MENU);
		CMenu *pRMenu=rMenu.GetSubMenu(2);
		pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
	}


}

void CCallCountDlg::OnBnClickedCancelBtn()
{
	OnOK();
}

void CCallCountDlg::OnBnClickedOkBtn()
{
	OnCancel();
}

void CCallCountDlg::OnBnClickedOpenBranchBtn()
{
	if(m_ba.GetCount() <= ONE)
		return;

	m_cBranchCombo.OpenBranchDlg();
}


void CCallCountDlg::OnBnClickedNoShowZeroCheck()
{
	AfxGetApp()->WriteProfileInt("CallCountDlg", "NoZero", m_chkNoShowZero.GetCheck());
	ListFilter();
}