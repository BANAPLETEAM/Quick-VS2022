// ConsignDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ConsignDlg.h"

#include "ConsignModiDlg.h"

#define  DEST_FOCUS 1000001
// CConsignDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CConsignDlg, CMyDialog)
CConsignDlg::CConsignDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CConsignDlg::IDD, pParent)
{

	m_pStartPoi = NULL;
	m_pDestPoi = NULL;
	m_sDest = "";
	m_nCharge = FALSE;
	m_sTerminal = "";
}

CConsignDlg::~CConsignDlg()
{
}

void CConsignDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DEST_EDIT, m_edtDest);
	DDX_Text(pDX, IDC_DEST_EDIT, m_sDest);
	DDX_Control(pDX, IDC_TERMINAL_EDIT, m_edtTerminal);
	DDX_Text(pDX, IDC_TERMINAL_EDIT, m_sTerminal);
	DDX_Control(pDX, IDC_ETC_EDIT, m_edtEtc);
	DDX_Control(pDX, IDC_CUSTOM1, m_Data);
}


BEGIN_MESSAGE_MAP(CConsignDlg, CMyDialog)
	ON_BN_CLICKED(ID_SEND_OK, OnBnClickedSendOk)
	ON_BN_CLICKED(IDC_NEW_BTN, OnBnClickedNewBtn)
	ON_BN_CLICKED(IDC_MODIFY_BTN, OnBnClickedModifyBtn)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_NOTIFY(NM_CLICK, IDC_CUSTOM1, OnReportItemClick)
	ON_NOTIFY(NM_DBLCLK, IDC_CUSTOM1, OnReportItemDblClick)
	//ON_NOTIFY(NM_DBLCLK, IDC_CUSTOM1, OnReportItemDblClick)
	//ON_NOTIFY(LVN_ITEMCHANGED, IDC_CUSTOM1, OnReportItemDblClick)
	ON_NOTIFY(XTP_NM_GRID_SELCHANGED, IDC_CUSTOM1, OnReportItemChange)

	ON_WM_TIMER()
END_MESSAGE_MAP()


// CConsignDlg 메시지 처리기입니다.

BOOL CConsignDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_Data.AddColumn(new CXTPGridColumn(0, "터미날,역", 90))->SetAlignment(DT_LEFT);
	m_Data.AddColumn(new CXTPGridColumn(1, "Km", 45))->SetAlignment(DT_RIGHT);
	m_Data.AddColumn(new CXTPGridColumn(2, "운송차량", 75))->SetAlignment(DT_CENTER);
	m_Data.AddColumn(new CXTPGridColumn(3, "세부정보", 80))->SetAlignment(DT_LEFT);
	m_Data.AddColumn(new CXTPGridColumn(4, "도착지", 80))->SetAlignment(DT_LEFT);
	m_Data.AddColumn(new CXTPGridColumn(5, "금액", 55))->SetAlignment(DT_RIGHT);
	m_Data.AddColumn(new CXTPGridColumn(6, "전화번호", 80))->SetAlignment(DT_LEFT);
	m_Data.AddColumn(new CXTPGridColumn(7, "첫차", 60))->SetAlignment(DT_LEFT);
	m_Data.AddColumn(new CXTPGridColumn(8, "막차", 60))->SetAlignment(DT_LEFT);
	m_Data.AddColumn(new CXTPGridColumn(9, "배차간격", 80))->SetAlignment(DT_LEFT);
	m_Data.AllowEdit(TRUE);
	m_Data.Populate();

	m_edtDest.SetWindowText(m_sDest);
	m_edtDest.SetFocus();

	SetTimer(DEST_FOCUS,700,NULL);
	
	return TRUE;
}

void CConsignDlg::RefreshListTerminal()
{
	m_Data.DeleteAllItems();
	UpdateData();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_consign_terminal");
	pCmd.AddParameter(m_sTerminal);
	if(!pRs.Execute(&pCmd)) return;

	int nItem =0;
	while(!pRs.IsEOF())
	{
		CString	sTerminalName, sWayEtc, sDest, sStart,sEnd, sTel, sInterval, sEtc, sKm;
		long nID, nTranWay, nCharge,nTerminalPOI, nKm;

		pRs.GetFieldValue("nID", nID);
		pRs.GetFieldValue("sTerminalName", sTerminalName);
		pRs.GetFieldValue("nTranWay", nTranWay);
		pRs.GetFieldValue("sWayEtc", sWayEtc);
		pRs.GetFieldValue("sDest", sDest);
		pRs.GetFieldValue("nCharge", nCharge);
		pRs.GetFieldValue("sTel", sTel);
		pRs.GetFieldValue("sStart", sStart);
		pRs.GetFieldValue("sEnd", sEnd);
		pRs.GetFieldValue("sInterval", sInterval);
		pRs.GetFieldValue("sEtc", sEtc);
		pRs.GetFieldValue("nTerminalPOI", nTerminalPOI);

		if(nTerminalPOI > 0 && m_pStartPoi != NULL)
		{			
			nKm = GetDistance(nTerminalPOI);
			sKm.Format("%d", nKm);
		}
		else
			sKm = "N/A";

		CConsignRecord* record = new CConsignRecord(sTerminalName, sKm, nTranWay, sWayEtc, sDest, LF->GetMyNumberFormat(nCharge), sTel, sStart, sEnd, sInterval);
		m_Data.AddRecord(record);
		m_Data.SetItemLong(record, nID);
		m_Data.SetItemLong2(record, nCharge);
		m_Data.SetItemDataText(record, sEtc);
		if(nItem == 0)
			m_Data.SetSelectedRow(0);
		nItem++;

		pRs.MoveNext();
	}
	m_Data.Populate();
}

void CConsignDlg::RefreshListArea()
{

	m_Data.DeleteAllItems();
	UpdateData();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_consign_area");
	pCmd.AddParameter(m_sDest);
	if(!pRs.Execute(&pCmd)) return;

	int nItem =0;
	while(!pRs.IsEOF())
	{
		CString	sTerminalName, sWayEtc, sDest, sStart,sEnd, sTel, sInterval, sEtc,sKm = "";
		long nID, nTranWay, nCharge, nKm, nTerminalPOI;

		pRs.GetFieldValue("nID", nID);
		pRs.GetFieldValue("sTerminalName", sTerminalName);
		pRs.GetFieldValue("nTranWay", nTranWay);
		pRs.GetFieldValue("sWayEtc", sWayEtc);
		pRs.GetFieldValue("sDest", sDest);
		pRs.GetFieldValue("nCharge", nCharge);
		pRs.GetFieldValue("sTel", sTel);
		pRs.GetFieldValue("sStart", sStart);
		pRs.GetFieldValue("sEnd", sEnd);
		pRs.GetFieldValue("sInterval", sInterval);
		pRs.GetFieldValue("sEtc", sEtc);
		pRs.GetFieldValue("nTerminalPOI", nTerminalPOI);

		if(nTerminalPOI > 0 && m_pStartPoi != NULL)
		{			
			nKm = GetDistance(nTerminalPOI);
			sKm.Format("%d", nKm);
		}
		else
			sKm = "N/A";

		CConsignRecord* record = new CConsignRecord(sTerminalName, sKm, nTranWay, sWayEtc, sDest, LF->GetMyNumberFormat(nCharge), sTel, sStart, sEnd, sInterval);
		m_Data.AddRecord(record);
		m_Data.SetItemLong(record, nID);
		m_Data.SetItemLong2(record, nCharge);
		m_Data.SetItemDataText(record, sEtc);

		pRs.MoveNext();
		if(nItem == 0)
			m_Data.SetSelectedRow(0);
		nItem++;
	}
	pRs.Close();
	m_Data.Populate();


}

long CConsignDlg::GetDistance(long nPOIID)
{

	if(nPOIID == 0)
		return 0;

	if(m_pStartPoi == NULL)
		return 0;

	CPOIUnit *pTerminal = m_poiNew.GetPOI(nPOIID);

	long nKm = (long)m_pStartPoi->GetDistanceMeter(pTerminal) / 1000;
	return (nKm < 0 ) ?  0 : nKm;
}

void CConsignDlg::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * result)
{
	if(m_Data.GetItemCount() <= 0)
		return;

	CConsignRecord* pRecord = (CConsignRecord*)m_Data.GetFirstSelectedRecord();
	m_edtEtc.SetWindowText(m_Data.GetItemDataText(pRecord));
}

void CConsignDlg::OnReportItemChange(NMHDR * pNotifyStruct, LRESULT * result)
{
	CConsignRecord* pRecord = (CConsignRecord*)m_Data.GetFirstSelectedRecord();
	m_nCharge = m_Data.GetItemLong2(pRecord);
}

void CConsignDlg::OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * result)
{
	if(m_Data.GetItemCount() <= 0)
		return;

	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*)pNotifyStruct;
	CConsignRecord* pRecord = (CConsignRecord*)m_Data.GetFirstSelectedRecord();
	m_nCharge = m_Data.GetItemLong2(pRecord);
	OnOK();
}

void CConsignDlg::OnBnClickedSendOk()
{
	if(m_Data.GetItemCount() <= 0)
		return;

	CConsignRecord* pRecord = (CConsignRecord*)m_Data.GetFirstSelectedRecord();
	m_nCharge = m_Data.GetItemLong2(pRecord);
	OnOK();
}

void CConsignDlg::OnBnClickedNewBtn()
{
	CConsignModiDlg dlg;
	dlg.m_nMod = 0;
	dlg.DoModal();
}

void CConsignDlg::OnBnClickedModifyBtn()
{
	if(m_Data.GetItemCount() <= 0)
		return;

	CConsignRecord* pRecord = (CConsignRecord*)m_Data.GetFirstSelectedRecord();

	CConsignModiDlg dlg;
	dlg.m_nMod = m_Data.GetItemLong(pRecord);
	dlg.DoModal();
}

void CConsignDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnCancel();
}

BOOL CConsignDlg::PreTranslateMessage(MSG* pMsg)
{

	if(pMsg->message == WM_KEYDOWN)
	{
	
		
		if(pMsg->wParam == VK_RETURN )		
		{
			switch(::GetDlgCtrlID(pMsg->hwnd))
			{
			case IDC_DEST_EDIT:
				{
					RefreshListArea();
					return FALSE;
				}
				break;
			case IDC_TERMINAL_EDIT:
				{
					RefreshListTerminal();
					return FALSE;
				}
				break;
			case IDC_CUSTOM1:
				{
					OnBnClickedSendOk();
					return FALSE;
				}
				break;
			}
		}
		if(pMsg->wParam == VK_DOWN )		
		{
			switch(::GetDlgCtrlID(pMsg->hwnd))
			{
			case IDC_DEST_EDIT:
				{
					m_Data.SetFocus();
					m_Data.SetSelectedRow(0);
					
					return FALSE;
				}
				break;
			}
		}
	}

	return CMyDialog::PreTranslateMessage(pMsg);
}

void CConsignDlg::OnTimer(UINT nIDEvent)
{
	
	if(nIDEvent == DEST_FOCUS )
	{

		m_edtDest.SetFocus();
		KillTimer(DEST_FOCUS);
	}

	CMyDialog::OnTimer(nIDEvent);
}
