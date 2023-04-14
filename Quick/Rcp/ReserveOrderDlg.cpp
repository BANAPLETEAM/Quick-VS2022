// ReserveOrderDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ReserveOrderDlg.h"
#include "RcpDlg.h"
#include "CustomMyAfxMessgagebox.h"

// CReserveOrderDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CReserveOrderDlg, CMyDialog)

CReserveOrderDlg::CReserveOrderDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CReserveOrderDlg::IDD, pParent)
{
	m_nKeyDownCount = 0;
	m_bChangeRiderForReserve = -1;
}

CReserveOrderDlg::~CReserveOrderDlg()
{
}

void CReserveOrderDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RESERVE_CHK, m_chkReserve);
	DDX_Control(pDX, IDC_RESERVE_DATE_DTP, m_dtpDate);
	DDX_Control(pDX, IDC_RESERVE_TIME_DTP, m_dtpTime);
	DDX_Control(pDX, IDC_RELEASE_MIN_COMBO, m_cmbReleaseMin);
	DDX_Control(pDX, IDC_RELEASE_STATE_COMBO, m_cmbReleaseState);
	DDX_Control(pDX, IDC_ADD_TIME_COMBO, m_cmbAddTime);
	DDX_Control(pDX, IDC_INFO_STATIC, m_stcInfo);
}


BEGIN_MESSAGE_MAP(CReserveOrderDlg, CMyDialog)
	ON_BN_CLICKED(IDC_OK_BTN, &CReserveOrderDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CReserveOrderDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_RESERVE_CHK, &CReserveOrderDlg::OnBnClickedReserve)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_RESERVE_DATE_DTP, &CReserveOrderDlg::OnDtnDatetimechangeReserveDateDtp)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_RESERVE_TIME_DTP, &CReserveOrderDlg::OnDtnDatetimechangeReserveTimeDtp)
	ON_CBN_SELCHANGE(IDC_RELEASE_MIN_COMBO, &CReserveOrderDlg::OnDisplayReserveInfo)
	ON_CBN_EDITCHANGE(IDC_RELEASE_MIN_COMBO, &CReserveOrderDlg::OnDisplayReserveInfo)
	ON_CBN_SELCHANGE(IDC_RELEASE_STATE_COMBO, &CReserveOrderDlg::OnDisplayReserveInfo)
	ON_CBN_SELCHANGE(IDC_ADD_TIME_COMBO, &CReserveOrderDlg::OnCbnSelchangeAddTimeCombo)
	ON_NOTIFY(NM_SETFOCUS, IDC_RESERVE_TIME_DTP, &CReserveOrderDlg::OnNMSetfocusReserveTimeDtp)
END_MESSAGE_MAP()


// CReserveOrderDlg 메시지 처리기입니다.

BOOL CReserveOrderDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	InitControl();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CReserveOrderDlg::InitControl()
{
	char buffer[10];
	m_chkReserve.SetCheck(FALSE);
	m_dtpDate.SetTime(COleDateTime::GetCurrentTime());
	m_dtpDate.SetFormat("yyyy-MM-dd");
	m_dtpDate.SetFont(m_FontManager.GetFont("맑은 고딕", 16, FW_NORMAL));

	m_dtpDate.SetTime(COleDateTime::GetCurrentTime());
	m_dtpTime.SetTime(COleDateTime::GetCurrentTime());
	m_dtpTime.SetFormat("HH:mm");
	m_dtpTime.SetFont(m_FontManager.GetFont("맑은 고딕", 16, FW_NORMAL));

	m_cmbReleaseMin.SetWindowText(ltoa(AfxGetApp()->GetProfileInt("RcpDlg", "ReleaseMin", 0), buffer, 10));
	m_cmbReleaseState.SetCurSel(AfxGetApp()->GetProfileInt("RcpDlg", "ReserveAfterWait", 0));
	m_cmbReleaseMin.SetCurSel(-1);
	m_cmbAddTime.SetCurSel(0);
	m_stcInfo.SetTextColor(RGB(255, 100, 100));
	m_stcInfo.SetWindowText("");
}

void CReserveOrderDlg::Hide()
{
	((CRcpDlg*)GetParent())->HideReserveBehindControl(FALSE);
	this->ShowWindow(SW_HIDE);
}

void CReserveOrderDlg::OnBnClickedOk()
{
	Hide();
}

void CReserveOrderDlg::OnBnClickedCancel()
{
	Hide();
}

void CReserveOrderDlg::OnDisplayReserveInfo()
{
	COleDateTime dtReserve = GetReserveTime();
	COleDateTime dtCur = COleDateTime::GetCurrentTime();

	if(IsReserve())
	{
		CString strMsg;
		COleDateTimeSpan dtSpan = dtReserve - dtCur;
		COleDateTime dtReserveDay(dtReserve.GetYear(), dtReserve.GetMonth(), dtReserve.GetDay(), 0, 0, 0);
		COleDateTime dtCurDay(dtCur.GetYear(), dtCur.GetMonth(), dtCur.GetDay(), 0, 0, 0);
		COleDateTimeSpan dtSpanDay = dtReserveDay - dtCurDay;
		long nDayGap = dtSpanDay.GetTotalDays();

		if(dtSpan.GetTotalMinutes() < 5 && dtSpan.GetTotalMinutes() > -5)
			strMsg.Format("예약시각이 현재시각 입니다.");
		else if(nDayGap == -1)
			strMsg.Format("예약시각이 어제 입니다.");
		else if(nDayGap < -1)
			strMsg.Format("예약시각이 %d일 전입니다.", -nDayGap);
		else if(dtReserve < dtCur)
			strMsg.Format("예약시각이 현재시각 이전입니다.");
		else if(nDayGap == 1)
			strMsg.Format("예약시각이 내일입니다.");
		else if(nDayGap > 1)
			strMsg.Format("예약시각이 %d일 후입니다.", nDayGap);
		else if(dtSpan.GetTotalMinutes() < 60)
			strMsg.Format("예약시각이 %0.0f분 후입니다.", dtSpan.GetTotalMinutes());
		else
			strMsg.Format("예약시각이 %0.0f시간%d분 후입니다.", dtSpan.GetTotalHours(), dtSpan.GetMinutes());

		m_stcInfo.SetWindowText(strMsg);

		AfxGetApp()->WriteProfileInt("RcpDlg", "ReleaseMin", GetReleaseMin());
		AfxGetApp()->WriteProfileInt("RcpDlg", "ReserveAfterWait", m_cmbReleaseState.GetCurSel());
	}
	
	if(m_pRcpDlg)
		m_pRcpDlg->DisplayReserveInfo();
}

void CReserveOrderDlg::OnDtnDatetimechangeReserveDateDtp(NMHDR *pNMHDR, LRESULT *pResult)
{
	SetReserveSate(TRUE);
	OnDisplayReserveInfo();
	*pResult = 0;
}

void CReserveOrderDlg::OnDtnDatetimechangeReserveTimeDtp(NMHDR *pNMHDR, LRESULT *pResult)
{
	SetReserveSate(TRUE);
	OnDisplayReserveInfo();
	*pResult = 0;
}

void CReserveOrderDlg::OnCbnSelchangeAddTimeCombo()
{
	int nCurSel = m_cmbAddTime.GetCurSel();

	if(nCurSel > 0)
	{
		SetReserveSate(TRUE);
		long nAddMin = m_cmbAddTime.GetItemData(nCurSel);
		COleDateTime dt = m_dtBase + COleDateTimeSpan(0, 0, nAddMin, 0);
		SetReserveTime(dt);
		OnDisplayReserveInfo();
		m_cmbAddTime.SetCurSel(0);
		Hide();
	}
}

void CReserveOrderDlg::SetReserve(BOOL bReserve)
{
	m_chkReserve.SetCheck(bReserve);
}

void CReserveOrderDlg::SetReserveSate(BOOL bReserve)
{
	if(bReserve && m_chkReserve.GetCheck())
		return ;

	m_chkReserve.SetCheck(bReserve);

	MakerAfxMsgBox();

	if(!m_chkReserve.GetCheck())
	{
		Hide();
		m_pRcpDlg->DisplayReserveInfo();
	}
	else
		OnDisplayReserveInfo();
}

void CReserveOrderDlg::SetReserveTime(COleDateTime dtTime)
{
	m_dtpDate.SetTime(dtTime);
	m_dtpTime.SetTime(dtTime);
}

void CReserveOrderDlg::SetReserveTime(COleDateTime dtDate, COleDateTime dtTime)
{
	m_dtpDate.SetTime(dtDate);
	m_dtpTime.SetTime(dtTime);
}

void CReserveOrderDlg::SetReleaseMin(long nMin)
{
	CString strMin;
	strMin.Format("%d", nMin);
	m_cmbReleaseMin.SetWindowText(strMin);
}

void CReserveOrderDlg::SetReleaseState(BOOL bWait)
{
	m_cmbReleaseState.SetCurSel(bWait);
}

void CReserveOrderDlg::SetReleaseStateDB(long nStateType)
{
	m_cmbReleaseState.SetCurSel((nStateType == 2) ? 1 : 0);
}

BOOL CReserveOrderDlg::IsReserve()
{
	return m_chkReserve.GetCheck();
}

COleDateTime CReserveOrderDlg::GetReserveTime()
{
	COleDateTime dtDate, dtTime;
	m_dtpDate.GetTime(dtDate);
	m_dtpTime.GetTime(dtTime);

	COleDateTime dt(COleDateTime::GetCurrentTime());
	if(m_chkReserve.GetCheck() )
		dt.SetDateTime(dtDate.GetYear(), dtDate.GetMonth(), dtDate.GetDay(), 
						dtTime.GetHour(), dtTime.GetMinute(), 0);
	return dt;
}

long CReserveOrderDlg::GetReleaseMin()
{
	CString strReleaseMin;
	int nIndex = m_cmbReleaseMin.GetCurSel();

	if(nIndex >= 0)
		m_cmbReleaseMin.GetLBText(nIndex, strReleaseMin);
	else
		m_cmbReleaseMin.GetWindowText(strReleaseMin);

	return atol(strReleaseMin);
}

BOOL CReserveOrderDlg::IsReleaseAfterWait()
{
	return m_cmbReleaseState.GetCurSel();
}

long CReserveOrderDlg::GetReleaseStateDB()
{ 
	long nIndex = m_cmbReleaseState.GetCurSel();

	if(nIndex > 1)
		return 0;

	return nIndex + 1;
}

CString CReserveOrderDlg::GetReserveTimeString()
{
	COleDateTime dtDate, dtTime;
	m_dtpDate.GetTime(dtDate);
	m_dtpTime.GetTime(dtTime);

	CString strFormat;
	strFormat.Format("[%02d-%02d %02d:%02d]", 
				dtDate.GetMonth(), dtDate.GetDay(),
				dtTime.GetHour(), dtTime.GetMinute());

	return strFormat;
}

void CReserveOrderDlg::OnBnClickedReserve()
{
	MakerAfxMsgBox();

	if(!m_chkReserve.GetCheck())
	{
		Hide();
		m_pRcpDlg->DisplayReserveInfo();
	}
	else
		OnDisplayReserveInfo();
}

BOOL CReserveOrderDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN )
	{
		if(pMsg->wParam == VK_RETURN)
		{
			COMBOBOXINFO info = { sizeof(COMBOBOXINFO) };
			m_cmbReleaseMin.GetComboBoxInfo(&info);
			if(info.hwndItem == pMsg->hwnd ||
				::GetDlgCtrlID(pMsg->hwnd) == IDC_RESERVE_TIME_DTP)
			{
				Hide();
				return TRUE;
			}
		}
	}
	else if(pMsg->message == WM_KEYUP)
	{
		if(::GetDlgCtrlID(pMsg->hwnd) == IDC_RESERVE_TIME_DT)
		{
			if(pMsg->wParam >= VK_NUMPAD0 && pMsg->wParam <= VK_NUMPAD9 ||
				pMsg->wParam >= 0x30 && pMsg->wParam <= 0x39) 
			{
				if(++m_nKeyDownCount == 2)
				{
					m_dtpTime.PostMessage(WM_KEYDOWN, VK_RIGHT);
					return FALSE;
				}
			}
			else
				m_nKeyDownCount = 0;
		}
	}

	return CMyDialog::PreTranslateMessage(pMsg);
}

void CReserveOrderDlg::MakeAddTime()
{
	m_cmbAddTime.ResetContent();
	m_cmbAddTime.AddString("빠른입력");

	COleDateTime dt = COleDateTime::GetCurrentTime() + COleDateTimeSpan(0, 0, 30, 0);
	if(dt.GetMinute() <= 15)
		dt.SetDateTime(dt.GetYear(), dt.GetMonth(), dt.GetDay(), dt.GetHour(), 0, 0);
	else if(dt.GetMinute() <= 45)
		dt.SetDateTime(dt.GetYear(), dt.GetMonth(), dt.GetDay(), dt.GetHour(), 30, 0);
	else 
		dt.SetDateTime(dt.GetYear(), dt.GetMonth(), dt.GetDay(), dt.GetHour() + 1, 0, 0);

	m_dtBase = dt;
	COleDateTime dtEnd(dt.GetYear(), dt.GetMonth(), dt.GetDay(), 21, 0, 0);
	long nAddMin = 0;
	CString strHead;
	COleDateTime dtCur = dt;

	while(dtCur <= dtEnd)
	{
		dtCur = dt + COleDateTimeSpan(0, 0, nAddMin, 0);
		CString strHead = dtCur.GetHour() < 12 ? "오전 " : "오후 ";
		int nSel = m_cmbAddTime.AddString(strHead + (dtCur.GetMinute() == 0 ? dtCur.Format("%I시") : dtCur.Format("%I시반")));
		m_cmbAddTime.SetItemData(nSel, nAddMin);
		nAddMin += 30;
	}

	COleDateTime dtTor = dt + COleDateTimeSpan(1, 0, 0, 0);	
	COleDateTime dtTorEnd;
	dtTor.SetDateTime(dtTor.GetYear(), dtTor.GetMonth(), dtTor.GetDay(), 7, 0, 0);
	dtTorEnd.SetDateTime(dtTor.GetYear(), dtTor.GetMonth(), dtTor.GetDay(), 9, 0, 0);

	COleDateTimeSpan span = dtTor - dt;
	nAddMin = span.GetTotalMinutes();
	dtCur = dtTor;

	while(dtCur <= dtTorEnd)
	{
		dtCur = dt + COleDateTimeSpan(0, 0, nAddMin, 0);

		int nSel = m_cmbAddTime.AddString("내일오전 " + (dtCur.GetMinute() == 0 ? dtCur.Format("%I시") : dtCur.Format("%I시반")));
		m_cmbAddTime.SetItemData(nSel, nAddMin);
		nAddMin += 30;
	}

	m_cmbAddTime.SetCurSel(0);
}

void CReserveOrderDlg::MakerAfxMsgBox()
{
	if(m_pRcpDlg->m_nState != STATE_RESERVED && m_pRcpDlg->m_nState != STATE_OK_ONLY_MAN)
	{
		m_bChangeRiderForReserve = 0;
		return ;
	}

	CString strRider = "", strMessage = "";
	CString strDescription = "";
	char buffer[10];
	strRider = m_pRcpDlg->m_strRiderName + "/" + CString(itoa(m_pRcpDlg->m_nRNo, buffer, 10));

	if(IsReserve() && strRider.GetLength() > 0 && strRider.Compare("0") > 0)
	{
		CString strCombText;
		m_cmbReleaseState.GetLBText(m_cmbReleaseState.GetCurSel(), strCombText);
		strMessage.Format("알림 : %s 번 기사님이 예약과 함께 배차 적용되어 있습니다.", strRider);
		strDescription.Format("해지될때 현재 기사님에게 개별배차\n\n해지될때 %s로 변경\n(해당오더에 기사정보초기화)", strCombText);
	
		CCustomMyAfxMessgagebox dlg;
		dlg.SetTitle(strMessage);
		dlg.SetSecondDesc(strDescription);
		dlg.SetCustomMode();
		long nRet = dlg.DoModal();

		if(nRet == IDOK)
			m_bChangeRiderForReserve = dlg.m_nType;
	}
}

void CReserveOrderDlg::OnNMSetfocusReserveTimeDtp(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_nKeyDownCount = 0;
	*pResult = 0;
}