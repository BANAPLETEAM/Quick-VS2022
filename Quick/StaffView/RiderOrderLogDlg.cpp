// RiderOrderLogDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "RiderOrderLogDlg.h"
	#include "MakeHtmlTable.h"
#include "WeatherDlg.h"

static LOGFONT lfSmallEdit = {11,0,0,0,FW_BOLD,0,0,0,HANGUL_CHARSET,0,0,0,0,"굴림"};
// CRiderOrderLogDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CRiderOrderLogDlg, CMyDialog)
CRiderOrderLogDlg::CRiderOrderLogDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CRiderOrderLogDlg::IDD, pParent)
{
}

CRiderOrderLogDlg::~CRiderOrderLogDlg()
{
}

void CRiderOrderLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT_LIST, m_wndReport);

	DDX_Control(pDX, IDC_RIDER_NAME_STC, m_stcRiderName);
	DDX_Control(pDX, IDC_RNO_STC, m_stcRNo);
	DDX_Control(pDX, IDC_ATTENDANCE_STC, m_stcAttendance);
	DDX_Control(pDX, IDC_ABSENCE_STC, m_stcAbsence);
	DDX_Control(pDX, IDC_TYPEA_STC, m_stcTypeA);
	DDX_Control(pDX, IDC_TYPEB_STC, m_stcTypeB);
	DDX_Control(pDX, IDC_TYPEC_STC, m_stcTypeC);
	DDX_Control(pDX, IDC_TYPED_STC, m_stcTypeD);
	DDX_Control(pDX, IDC_CASH_STC, m_stcCash);
	DDX_Control(pDX, IDC_CREDIT_STC, m_stcCredit);
	DDX_Control(pDX, IDC_REMITTANCE_STC, m_stcRemittance);
	DDX_Control(pDX, IDC_TOTAL_STC, m_stcTotal);

	DDX_Control(pDX, IDC_RIDER_NAME_EDT, m_RiderNameEdt);
	DDX_Control(pDX, IDC_RNO_EDT, m_RnoEdt);
	DDX_Control(pDX, IDC_ATTENDANCE_EDT, m_AttendanceEdt);
	DDX_Control(pDX, IDC_ABSENCE_EDT, m_AbsenceEdt);
	DDX_Control(pDX, IDC_TYPEA_EDT, m_TypeAEdt);
	DDX_Control(pDX, IDC_TYPEB_EDT, m_TypeBEdt);
	DDX_Control(pDX, IDC_TYPEC_EDT, m_TypeCEdt);
	DDX_Control(pDX, IDC_TYPED_EDT, m_TypeDEdt);
	DDX_Control(pDX, IDC_CASH_EDT, m_CashEdt);
	DDX_Control(pDX, IDC_CREDIT_EDT, m_CreditEdt);
	DDX_Control(pDX, IDC_REMITTANCE_EDT, m_RemittanceEdt);
	DDX_Control(pDX, IDC_TOTAL_EDT, m_TotalEdt);
	DDX_Control(pDX, IDC_MONTH_COMBO, m_MonthCmb);
	DDX_Control(pDX, IDC_REFRESH_BTN, m_btnRefresh);
	DDX_Control(pDX, IDC_WEATHER_BTN, m_btnWeather);
}


BEGIN_MESSAGE_MAP(CRiderOrderLogDlg, CMyDialog)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_BN_CLICKED(IDC_WEATHER_BTN, OnBnClickedWeatherBtn)
	ON_NOTIFY (UDM_TOOLTIP_DISPLAY, NULL, NotifyDisplayTooltip)
END_MESSAGE_MAP()

void CRiderOrderLogDlg::MakeTooltipData()
{
	m_mapRider.clear();

	CString sDate;
	long index = m_MonthCmb.GetCurSel();
	
	m_MonthCmb.GetLBText(index, sDate);
    

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_rider_log_detail_1");

	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nRiderCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nRNo);
	pCmd.AddParameter(typeString, typeInput, sDate.GetLength(), sDate);

	if(!pRs.Execute(&pCmd)) return ;

//	long nCompany, nState, nChargeSum, nPayType, nChargeType;
	COleDateTime dt1;
	CString sSDong, sDDong;

	long nCount = 0;

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		ST_RIDER_ORDER data;

		pRs.GetFieldValue("nCompany", data.nCompany);
		pRs.GetFieldValue("dt1", data.dt1);
		pRs.GetFieldValue("nState", data.nState);
		pRs.GetFieldValue("sSDong", data.strSDong);
		pRs.GetFieldValue("sDDong", data.strDDong);
		pRs.GetFieldValue("nChargeSum", data.nChargeSum);
		pRs.GetFieldValue("nPayType", data.nPayType);
		pRs.GetFieldValue("nChargeType", data.nChargeType);
		
		m_mapRider[data.dt1] = data;
		//m_mapRider.insert(m_mapRider::value_type(dt1, data));

		//CString sChargeType;

		//if(nChargeType == 0)	sChargeType = "A타입";
		//else if(nChargeType == 1)	sChargeType = "B타입";
		//else if(nChargeType == 2)	sChargeType = "C타입";
		//else if(nChargeType == 3)	sChargeType = "D타입";
		//else	"알수없음";

		pRs.MoveNext();
	}

}

void CRiderOrderLogDlg::NotifyDisplayTooltip(NMHDR * pNMHDR, LRESULT * result)
{
	*result = 0;
	NM_PPTOOLTIP_DISPLAY * pNotify = (NM_PPTOOLTIP_DISPLAY*)pNMHDR;

	if (NULL == pNotify->hwndTool)
	{
		//Order to update a tooltip for a current Tooltip Help
		//He has not a handle of the window
		//If you want change tooltip's parameter than make it's here
	}
	else
	{
		//Order to update a tooltip for a specified window as tooltip's tool

		//Gets a ID of the window if needed
		UINT nID = CWnd::FromHandle(pNotify->hwndTool)->GetDlgCtrlID();

		//Change a tooltip's parameters for a current window (control)
		BOOL bOutside = FALSE;
		CPoint pt = *pNotify->pt;
		CRect rect, rcCtrl, rcCol;
		if (IDC_REPORT_LIST == nID)
		{
			m_wndReport.GetWindowRect(&rcCtrl);
			pt -= rcCtrl.TopLeft();
			CXTPGridRow *pRow = m_wndReport.HitTest(pt);
			if(pRow)
			{
				CXTPGridColumn *pCol = NULL;
				pRow->HitTest(pt, &rcCol, &pCol);

				if(pCol->GetItemIndex() == 3 || pCol->GetItemIndex() == 4)
				{
					CMakeHtmlTable htable;

					CXTPGridColumn *pColumn = NULL;
					CString sDate = ((CXTPGridRecordItemText*)pRow->GetRecord()->GetItem(0))->GetCaption(pColumn);
					CString sAbsence = ((CXTPGridRecordItemText*)pRow->GetRecord()->GetItem(2))->GetCaption(pColumn);

					if(sAbsence == "결 근")
						return; 

					htable.AddCol("상태");
					htable.AddCol("회사명");
					htable.AddCol("출발동");
					htable.AddCol("도착동");
					htable.AddCol("접수시간");
					htable.AddCol("요금");
					htable.AddCol("입금방식");
					htable.AddCol("요금타입");
					htable.AddRow();
					
					if(MakeHtmlTable(&htable, sDate))
					{
						CString strTitle;
						strTitle.Format("상세내역");
						htable.SetTitle(strTitle);
						htable.SetTableBorder(1);
						pNotify->ti->sTooltip = htable.GetHtmlTable();
						pt = *pNotify->pt;
						pt.x += 5;
						pt.y += 20;
						*pNotify->pt = pt;
					}
				}

			}

		} //if
	} //if
} //End NotifyDisplayTooltip

BOOL CRiderOrderLogDlg::MakeHtmlTable(CMakeHtmlTable *pTable, CString sDate)
{
	//CMkRecordset pRs(m_pMkDb);
	//CMkCommand pCmd(m_pMkDb, "select_rider_log_detail");

	//pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nRiderCompany);
	//pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nRNo);
	//pCmd.AddParameter(typeString, typeInput, sDate.GetLength(), sDate);

	//if(!pRs.Execute(&pCmd)) return FALSE;

	//long nCompany, nState, nChargeSum, nPayType, nChargeType;
	//COleDateTime dt1;
	//CString sSDong, sDDong;

	RIDER_ORDER_MAP::iterator pos;

	COleDateTime dtFrom(_ttoi(sDate.Left(4)), _ttoi(sDate.Mid(5,2)), _ttoi(sDate.Right(2)), 0, 0, 0);
	COleDateTimeSpan span(1, 0, 0, 0);
	COleDateTime dtTo = dtFrom + span;
	
	long nCount = 0;
//수정해야함
	for(pos = m_mapRider.begin(); pos != m_mapRider.end(); pos++)
	{
		COleDateTime dt = pos->first;

		if(pos->first > dtFrom && pos->first < dtTo)
        {
			CString sChargeType;

			if(pos->second.nChargeType == 0)	sChargeType = "A타입";
			else if(pos->second.nChargeType == 1)	sChargeType = "B타입";
			else if(pos->second.nChargeType == 2)	sChargeType = "C타입";
			else if(pos->second.nChargeType == 3)	sChargeType = "D타입";
			else	"알수없음";

			pTable->AddImageList(GetImageNumber(pos->second.nState), "");
			pTable->AddCol(CString(m_ci.GetName(pos->second.nCompany)) + "/" + 
				CString(m_ci.GetBranchName(pos->second.nCompany)));
			pTable->AddCol(pos->second.strSDong);
			pTable->AddCol(pos->second.strDDong);
			pTable->AddCol(pos->second.dt1.Format("%H:%M"));
			pTable->AddCol(::GetMyNumberFormat(pos->second.nChargeSum));
			pTable->AddCol(::GetPayTypeFromLong(pos->second.nPayType));
			pTable->AddCol(sChargeType);
			pTable->AddRow();

			nCount++;
		}
	}

	if(nCount>0)
		return TRUE;
	else
		return FALSE;
}

void CRiderOrderLogDlg::OnBnClickedRefreshBtn()
{
	MakeTooltipData();
	RefreshList();
}

void CRiderOrderLogDlg::RefreshList()
{
    m_wndReport.DeleteAllItems();

	long index = m_MonthCmb.GetCurSel();
	CString sCmb;
	m_MonthCmb.GetLBText(index, sCmb);
	sCmb.Replace(" 내역", "");

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_riderOrderLog");

	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nRiderCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nRNo);
	pCmd.AddParameter(typeString, typeInput, sCmb.GetLength(), sCmb);

	if(!pRs.Execute(&pCmd)) return;

	CString sDate;
	COleDateTime dtStart, dtEnd; 
	CString sStart, sDest;
	long nTypeOrderCountA, nTypeOrderChargeA, nTypeOrderCountB, nTypeOrderChargeB; 
	long nTypeOrderCountC, nTypeOrderChargeC, nTypeOrderCountD, nTypeOrderChargeD;
	long nTypeCashCount, nTypeCashCharge, nTypeCreditCount, nTypeCreditCharge, nTypeRemittanceCount, nTypeRemittanceCharge;

	long nTypeOrderTotalCountA, nTypeOrderTotalChargeA, nTypeOrderTotalCountB, nTypeOrderTotalChargeB;
	long nTypeOrderTotalCountC, nTypeOrderTotalChargeC, nTypeOrderTotalCountD, nTypeOrderTotalChargeD;
	long nTypeCashTotalCount, nTypeCashTotalCharge, nTypeCreditTotalCount, nTypeCreditTotalCharge, nTypeRemittanceTotalCount, nTypeRemittanceTotalCharge;

	long nTotalCount, nTotalCharge;

	nTypeOrderTotalCountA = nTypeOrderTotalChargeA = nTypeOrderTotalCountB = nTypeOrderTotalChargeB =
	nTypeOrderTotalCountC = nTypeOrderTotalChargeC = nTypeOrderTotalCountD = nTypeOrderTotalChargeD =
	nTypeCashTotalCount = nTypeCashTotalCharge = nTypeCreditTotalCount = nTypeCreditTotalCharge = 
	nTypeRemittanceTotalCount = nTypeRemittanceTotalCharge = nTotalCount = nTotalCharge = 0;

	long nAttendance = 0;
	long nAbsence = 0;
	CString sWeather;

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		long nTypeOrderTotalCountH, nTypeOrderTotalChargeH, nTypeCashTotalCountH, nTypeCashTotalChargeH; 
		nTypeOrderTotalCountH = nTypeOrderTotalChargeH = nTypeCashTotalCountH = nTypeCashTotalChargeH = 0;

		pRs.GetFieldValue("sDate", sDate);
		pRs.GetFieldValue("dtStart", dtStart);
		pRs.GetFieldValue("dtEnd", dtEnd);
		pRs.GetFieldValue("sStart", sStart);
		pRs.GetFieldValue("sDest", sDest);
		pRs.GetFieldValue("nTypeOrderCountA", nTypeOrderCountA);
		pRs.GetFieldValue("nTypeOrderChargeA", nTypeOrderChargeA);
		pRs.GetFieldValue("nTypeOrderCountB", nTypeOrderCountB);
		pRs.GetFieldValue("nTypeOrderChargeB", nTypeOrderChargeB);
		pRs.GetFieldValue("nTypeOrderCountC", nTypeOrderCountC);
		pRs.GetFieldValue("nTypeOrderChargeC", nTypeOrderChargeC);
		pRs.GetFieldValue("nTypeOrderCountD", nTypeOrderCountD);
		pRs.GetFieldValue("nTypeOrderChargeD", nTypeOrderChargeD);
		pRs.GetFieldValue("nTypeCashCount", nTypeCashCount);
		pRs.GetFieldValue("nTypeCashCharge", nTypeCashCharge);
		pRs.GetFieldValue("nTypeCreditCount", nTypeCreditCount);
		pRs.GetFieldValue("nTypeCreditCharge", nTypeCreditCharge);
		pRs.GetFieldValue("nTypeRemittanceCount", nTypeRemittanceCount);
		pRs.GetFieldValue("nTypeRemittanceCharge", nTypeRemittanceCharge);
		pRs.GetFieldValue("sWeather", sWeather);

		nTypeOrderTotalCountH += nTypeOrderCountA + nTypeOrderCountB + nTypeOrderCountC + nTypeOrderCountD; //가로
		nTypeOrderTotalChargeH += nTypeOrderChargeA + nTypeOrderChargeB + nTypeOrderChargeC + nTypeOrderChargeD;//가로
		nTypeCashTotalCountH += nTypeCashCount + nTypeCreditCount + nTypeRemittanceCount;//가로
		nTypeCashTotalChargeH += nTypeCashCharge + nTypeCreditCharge + nTypeRemittanceCharge;//가로

		nTypeOrderTotalCountA += nTypeOrderCountA;
		nTypeOrderTotalCountB += nTypeOrderCountB;
		nTypeOrderTotalCountC += nTypeOrderCountC;
		nTypeOrderTotalCountD += nTypeOrderCountD;

		nTypeOrderTotalChargeA += nTypeOrderChargeA;
		nTypeOrderTotalChargeB += nTypeOrderChargeB;
		nTypeOrderTotalChargeC += nTypeOrderChargeC;
		nTypeOrderTotalChargeD += nTypeOrderChargeD;

		nTypeCashTotalCount += nTypeCashCount;
		nTypeCashTotalCharge += nTypeCashCharge;
		nTypeCreditTotalCount += nTypeCreditCount;
		nTypeCreditTotalCharge += nTypeCreditCharge;
		nTypeRemittanceTotalCount += nTypeRemittanceCount;
		nTypeRemittanceTotalCharge += nTypeRemittanceCharge;

		if(nTypeOrderTotalCountH == 0)
		{
			m_wndReport.AddRecord(new CRiderRecord(sDate.Left(4) + "-" + sDate.Mid(4, 2) + "-" + sDate.Right(2),
								sWeather, "결 근", "----------------------------", "----------------------------", "----------", FALSE));

			nAbsence++;
		}
		else
		{
			CString s0, s1, s2, s3, s4, s5;
			CString sFormat, sFormat1, sFormat2;

			//대문자 Z는 \r\n 대신에 들어 있는거

			s0 = sDate.Left(4) + "-" + sDate.Mid(4, 2) + "-" + sDate.Right(2);
			s1 = sWeather;

			s2 = "시작:" + ::GetMyNumberFormat(dtStart.GetHour()) + ":" + ::GetMyNumberFormat(dtStart.GetMinute()) + " (" + sStart + ")Z" +
				"완료:" + ::GetMyNumberFormat(dtEnd.GetHour()) + ":" + ::GetMyNumberFormat(dtEnd.GetMinute()) + " (" + sDest + ")";

			sFormat1 = "A(" + ::GetMyNumberFormat(nTypeOrderCountA) + "건/" + ::GetMyNumberFormat(nTypeOrderChargeA) + "원)";
            GetEmptyString(sFormat1);
			sFormat1 += "B(" + ::GetMyNumberFormat(nTypeOrderCountB) + "건/" + ::GetMyNumberFormat(nTypeOrderChargeB) + "원)Z";

			sFormat2 = "C(" + ::GetMyNumberFormat(nTypeOrderCountC) + "건/" + ::GetMyNumberFormat(nTypeOrderChargeC) + "원)";
			GetEmptyString(sFormat2);
			sFormat2 += "D(" + ::GetMyNumberFormat(nTypeOrderCountD) + "건/" + ::GetMyNumberFormat(nTypeOrderChargeD) + "원)";

			s3 = sFormat1 + sFormat2;

			s4 = "현금(" + ::GetMyNumberFormat(nTypeCashCount) + "건/" + ::GetMyNumberFormat(nTypeCashCharge) + "원)Z" +
				"신용(" + ::GetMyNumberFormat(nTypeCreditCount) + "건/" + ::GetMyNumberFormat(nTypeCreditCharge) + "원),  " +
				"송금(" + ::GetMyNumberFormat(nTypeRemittanceCount) + "건/" + ::GetMyNumberFormat(nTypeRemittanceCharge) + "원)";

			s5 = "총 " + ::GetMyNumberFormat(nTypeOrderTotalCountH) + "건Z" +
				::GetMyNumberFormat(nTypeOrderTotalChargeH) + "원";

			m_wndReport.AddRecord(new CRiderRecord(s0, s1, s2, s3, s4, s5, TRUE));

			nAttendance++;
		}
			
		pRs.MoveNext();		
	}

	m_wndReport.Populate();

	char buffer[20];

	m_RiderNameEdt.SetWindowText(m_strRName);
	m_RnoEdt.SetWindowText(itoa(m_nRNo, buffer, 10));
	m_AttendanceEdt.SetWindowText(itoa(nAttendance, buffer, 10));
	m_AbsenceEdt.SetWindowText(itoa(nAbsence, buffer, 10));
	m_TypeAEdt.SetWindowText(::GetMyNumberFormat(nTypeOrderTotalCountA) + "건 (" + ::GetMyNumberFormat(nTypeOrderTotalChargeA) + "원)");
	m_TypeBEdt.SetWindowText(::GetMyNumberFormat(nTypeOrderTotalCountB) + "건 (" + ::GetMyNumberFormat(nTypeOrderTotalChargeB) + "원)");
	m_TypeCEdt.SetWindowText(::GetMyNumberFormat(nTypeOrderTotalCountC) + "건 (" + ::GetMyNumberFormat(nTypeOrderTotalChargeC) + "원)");
	m_TypeDEdt.SetWindowText(::GetMyNumberFormat(nTypeOrderTotalCountD) + "건 (" + ::GetMyNumberFormat(nTypeOrderTotalChargeD) + "원)");
	m_CashEdt.SetWindowText(::GetMyNumberFormat(nTypeCashTotalCount) + "건 (" + ::GetMyNumberFormat(nTypeCashTotalCharge) + "원)");
	m_CreditEdt.SetWindowText(::GetMyNumberFormat(nTypeCreditTotalCount) + "건 (" + ::GetMyNumberFormat(nTypeCreditTotalCharge) + "원)");
	m_RemittanceEdt.SetWindowText(::GetMyNumberFormat(nTypeRemittanceTotalCount) + "건 (" + ::GetMyNumberFormat(nTypeRemittanceTotalCharge) + "원)");
	m_TotalEdt.SetWindowText(::GetMyNumberFormat(nTypeCashTotalCount + nTypeCreditTotalCount + nTypeRemittanceTotalCount) + 
			"건 (" + ::GetMyNumberFormat(nTypeCashTotalCharge + nTypeCreditTotalCharge + nTypeRemittanceTotalCharge) + "원)");



}

void CRiderOrderLogDlg::GetEmptyString(CString &sFormat)
{
	//20자 째부터  B;D가 나옴
	long nLen = sFormat.GetLength();

	for(int i=nLen; i<20; i++)
	{
		sFormat += " ";
	}

}

BOOL CRiderOrderLogDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	SetForegroundWindow();

	char buffer[20];

	COleDateTime dtCurrent = COleDateTime::GetCurrentTime();

	m_MonthCmb.InsertString(0, "최근한달");
	
	for(int i=0; i<3; i++)
	{
        CString str = CString(itoa(dtCurrent.GetYear(), buffer, 10)) + "-";
		
		if(dtCurrent.GetMonth() < 10)
			str += "0" + CString(itoa(dtCurrent.GetMonth(), buffer, 10));
		else
			str += CString(itoa(dtCurrent.GetMonth(), buffer, 10));

		m_MonthCmb.InsertString(i+1, str);

		COleDateTimeSpan span(dtCurrent.GetDay() , 0, 0, 0);
		dtCurrent = dtCurrent - span;
	}

	m_MonthCmb.SetCurSel(0);

	CXTPGridColumn * pCol0 = m_wndReport.AddColumn(new CXTPGridColumn(0,_T("날짜"), 55, TRUE));
	CXTPGridColumn * pCol1 = m_wndReport.AddColumn(new CXTPGridColumn(1,_T("날씨"),40, TRUE));
	CXTPGridColumn * pCol2 = m_wndReport.AddColumn(new CXTPGridColumn(2,_T("근무시간"), 100, TRUE));
	CXTPGridColumn * pCol3 = m_wndReport.AddColumn(new CXTPGridColumn(3,_T("A,B,C,D 오더별 내역"), 150, TRUE));
	CXTPGridColumn * pCol4 = m_wndReport.AddColumn(new CXTPGridColumn(4,_T("현금,신용,송금"), 150, TRUE));
	CXTPGridColumn * pCol5 = m_wndReport.AddColumn(new CXTPGridColumn(5,_T("총 합계"), 60, TRUE));

	//pCol0->SetAlignment(DT_LEFT);
	//pCol1->SetAlignment(DT_LEFT);
	//pCol2->SetAlignment(DT_LEFT);
	//pCol3->SetAlignment(DT_LEFT);
	//pCol4->SetAlignment(DT_LEFT);
	pCol5->SetAlignment(DT_VCENTER);

	m_wndReport.SetPaintManager(new CPaintManager);
	m_wndReport.GetPaintManager()->m_strNoItems = "표시할 대상이 존재하지 않음";
	//m_wndReport.GetPaintManager()->m_nRowHeight = 20;
	
    m_wndReport.GetReportHeader()->AllowColumnRemove(FALSE);
	m_wndReport.GetReportHeader()->AllowColumnResize(TRUE);
	m_wndReport.GetReportHeader()->AllowColumnSort(TRUE);
	m_wndReport.GetReportHeader()->SetAutoColumnSizing(TRUE);
	m_wndReport.AllowEdit(FALSE);
	m_wndReport.FocusSubItems(TRUE);
	m_wndReport.GetPaintManager()->SetGridStyle(TRUE, xtpGridSolid);
	m_wndReport.SetGridColor(RGB(180, 180, 200));
	m_wndReport.GetPaintManager()->SetTextFont(lfSmallEdit);

	m_wndReport.Populate();

	m_RiderNameEdt.SetFont(m_FontManager.GetFont("굴림", 13, FW_BOLD));
	m_RnoEdt.SetFont(m_FontManager.GetFont("굴림", 13, FW_BOLD));
	m_AttendanceEdt.SetFont(m_FontManager.GetFont("굴림", 13, FW_BOLD));
	m_AbsenceEdt.SetFont(m_FontManager.GetFont("굴림", 13, FW_BOLD));
	m_TypeAEdt.SetFont(m_FontManager.GetFont("굴림", 13, FW_BOLD));
	m_TypeBEdt.SetFont(m_FontManager.GetFont("굴림", 13, FW_BOLD));
	m_TypeCEdt.SetFont(m_FontManager.GetFont("굴림", 13, FW_BOLD));
	m_TypeDEdt.SetFont(m_FontManager.GetFont("굴림", 13, FW_BOLD));
	m_CashEdt.SetFont(m_FontManager.GetFont("굴림", 13, FW_BOLD));
	m_CreditEdt.SetFont(m_FontManager.GetFont("굴림", 13, FW_BOLD));
	m_RemittanceEdt.SetFont(m_FontManager.GetFont("굴림", 13, FW_BOLD));
	m_TotalEdt.SetFont(m_FontManager.GetFont("굴림", 13, FW_BOLD));

	m_tooltip.Create(this, FALSE);
	m_tooltip.SetBehaviour(PPTOOLTIP_MULTIPLE_SHOW);
	m_tooltip.SetNotify();
	m_tooltip.SetImageList(IDB_LIST, 16, 18, 14, RGB(0,255,255));
	m_tooltip.SetTransparency(30);

	m_tooltip.SetDelayTime(PPTOOLTIP_TIME_INITIAL, 100);
	m_tooltip.SetDelayTime(PPTOOLTIP_TIME_AUTOPOP, 50000);
	m_tooltip.SetDelayTime(PPTOOLTIP_TIME_FADEIN, 10);
	m_tooltip.SetDelayTime(PPTOOLTIP_TIME_FADEOUT, 10);

	m_tooltip.AddTool(&m_wndReport, "");

	MakeTooltipData();
	RefreshList();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CRiderOrderLogDlg::OnBnClickedWeatherBtn()
{
	CWeatherDlg dlg;
	dlg.DoModal();
}

BOOL CRiderOrderLogDlg::PreTranslateMessage(MSG* pMsg)
{
	m_tooltip.RelayEvent(pMsg);

	return CMyDialog::PreTranslateMessage(pMsg);
}
