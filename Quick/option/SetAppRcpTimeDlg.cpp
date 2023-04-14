// CSetAppRcpTimeDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "SetAppRcpTimeDlg.h"
#include "SetAppRcpTimeDlg.h"


// CSetAppRcpTimeDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSetAppRcpTimeDlg, CMyDialog)

CSetAppRcpTimeDlg::CSetAppRcpTimeDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CSetAppRcpTimeDlg::IDD, pParent)
{
	m_bMonday = TRUE;
	m_bTuesday = TRUE;
	m_bWednesday = TRUE;
	m_bThursday = TRUE;
	m_bFriday = TRUE;
	m_bSaturday = TRUE;
	m_bSunday = TRUE;

	m_nStartMonday = 0;
	m_nStartTuesday = 0;
	m_nStartWednesday = 0;
	m_nStartThursday = 0;
	m_nStartFriday = 0;
	m_nStartSaturday = 0;
	m_nStartSunday = 0;

	m_nEndMonday = 0;
	m_nEndTuesday = 0;
	m_nEndWednesday = 0;
	m_nEndThursday = 0;
	m_nEndFriday = 0;
	m_nEndSaturday = 0;
	m_nEndSunday = 0;


}

CSetAppRcpTimeDlg::~CSetAppRcpTimeDlg()
{
}

void CSetAppRcpTimeDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_MONDAY_CHECK, m_bMonday);
	DDX_Check(pDX, IDC_TUESDAY_CHECK, m_bTuesday);
	DDX_Check(pDX, IDC_WEDNESDAY_CHECK, m_bWednesday);
	DDX_Check(pDX, IDC_THURSDAY_CHECK, m_bThursday);
	DDX_Check(pDX, IDC_FRIDAY_CHECK, m_bFriday);
	DDX_Check(pDX, IDC_SATURDAY_CHECK, m_bSaturday);
	DDX_Check(pDX, IDC_SUNDAY_CHECK, m_bSunday);

	DDX_Control(pDX, IDC_START_MONDAY_COMBO, m_cmbStartMonday);
	DDX_Control(pDX, IDC_START_TUESDAY_COMBO, m_cmbStartTuesday);
	DDX_Control(pDX, IDC_START_WEDNESDAY_COMBO, m_cmbStartWednesday);
	DDX_Control(pDX, IDC_START_THURSDAY_COMBO, m_cmbStartThursday);
	DDX_Control(pDX, IDC_START_FRIDAY_COMBO, m_cmbStartFriday);
	DDX_Control(pDX, IDC_START_SATURDAY_COMBO, m_cmbStartSaturday);
	DDX_Control(pDX, IDC_START_SUNDAY_COMBO, m_cmbStartSunday);

	DDX_Control(pDX, IDC_END_MONDAY_COMBO, m_cmbEndMonday);
	DDX_Control(pDX, IDC_END_TUESDAY_COMBO, m_cmbEndTuesday);
	DDX_Control(pDX, IDC_END_WEDNESDAY_COMBO, m_cmbEndWednesday);
	DDX_Control(pDX, IDC_END_THURSDAY_COMBO, m_cmbEndThursday);
	DDX_Control(pDX, IDC_END_FRIDAY_COMBO, m_cmbEndFriday);
	DDX_Control(pDX, IDC_END_SATURDAY_COMBO, m_cmbEndSaturday);
	DDX_Control(pDX, IDC_END_SUNDAY_COMBO, m_cmbEndSunday);

	DDX_CBIndex(pDX, IDC_START_MONDAY_COMBO, m_nStartMonday);
	DDX_CBIndex(pDX, IDC_START_TUESDAY_COMBO, m_nStartTuesday);
	DDX_CBIndex(pDX, IDC_START_WEDNESDAY_COMBO, m_nStartWednesday);
	DDX_CBIndex(pDX, IDC_START_THURSDAY_COMBO, m_nStartThursday);
	DDX_CBIndex(pDX, IDC_START_FRIDAY_COMBO, m_nStartFriday);
	DDX_CBIndex(pDX, IDC_START_SATURDAY_COMBO, m_nStartSaturday);
	DDX_CBIndex(pDX, IDC_START_SUNDAY_COMBO, m_nStartSunday);

	DDX_CBIndex(pDX, IDC_END_MONDAY_COMBO, m_nEndMonday);
	DDX_CBIndex(pDX, IDC_END_TUESDAY_COMBO, m_nEndTuesday);
	DDX_CBIndex(pDX, IDC_END_WEDNESDAY_COMBO, m_nEndWednesday);
	DDX_CBIndex(pDX, IDC_END_THURSDAY_COMBO, m_nEndThursday);
	DDX_CBIndex(pDX, IDC_END_FRIDAY_COMBO, m_nEndFriday);
	DDX_CBIndex(pDX, IDC_END_SATURDAY_COMBO, m_nEndSaturday);
	DDX_CBIndex(pDX, IDC_END_SUNDAY_COMBO, m_nEndSunday);

}


BEGIN_MESSAGE_MAP(CSetAppRcpTimeDlg, CMyDialog)
	ON_BN_CLICKED(IDC_SAVE_BTN, &CSetAppRcpTimeDlg::OnBnClickedSaveBtn)
	ON_BN_CLICKED(IDC_CLOSE_BTN, &CSetAppRcpTimeDlg::OnBnClickedCloseBtn)
END_MESSAGE_MAP()


void CSetAppRcpTimeDlg::RefreshDlg()
{
	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_app_rcp_time_info");
	cmd.AddParameter(m_nCompany);

	if(!rs.Execute(&cmd))
		return;

	if(rs.GetRecordCount() <= 0)
		return;
	rs.GetFieldValue("bMonday", m_bMonday);
	rs.GetFieldValue("bTuesday", m_bTuesday);
	rs.GetFieldValue("bWednesday", m_bWednesday);
	rs.GetFieldValue("bThursday", m_bThursday);
	rs.GetFieldValue("bFriday", m_bFriday);
	rs.GetFieldValue("bSaturday", m_bSaturday);
	rs.GetFieldValue("bSunday", m_bSunday);

	rs.GetFieldValue("nStartMonday", m_nStartMonday);
	rs.GetFieldValue("nStartTuesday", m_nStartTuesday);
	rs.GetFieldValue("nStartWednesday", m_nStartWednesday);
	rs.GetFieldValue("nStartThursday", m_nStartThursday);
	rs.GetFieldValue("nStartFriday", m_nStartFriday);
	rs.GetFieldValue("nStartSaturday", m_nStartSaturday);
	rs.GetFieldValue("nStartSunday", m_nStartSunday);

	rs.GetFieldValue("nEndMonday", m_nEndMonday);
	rs.GetFieldValue("nEndTuesday", m_nEndTuesday);
	rs.GetFieldValue("nEndWednesday", m_nEndWednesday);
	rs.GetFieldValue("nEndThursday", m_nEndThursday);
	rs.GetFieldValue("nEndFriday", m_nEndFriday);
	rs.GetFieldValue("nEndSaturday", m_nEndSaturday);
	rs.GetFieldValue("nEndSunday", m_nEndSunday);

	UpdateData(FALSE);
}


BOOL CSetAppRcpTimeDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CenterWindow();
	RefreshDlg();	

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CSetAppRcpTimeDlg::OnBnClickedSaveBtn()
{
	UpdateData(TRUE);

	CMkCommand cmd(m_pMkDb, "update_app_rcp_time_info");
	cmd.AddParameter(m_nCompany);

	cmd.AddParameter(m_bMonday);
	cmd.AddParameter(m_bTuesday);
	cmd.AddParameter(m_bWednesday);
	cmd.AddParameter(m_bThursday);
	cmd.AddParameter(m_bFriday);
	cmd.AddParameter(m_bSaturday);
	cmd.AddParameter(m_bSunday);

	cmd.AddParameter(m_nStartMonday);
	cmd.AddParameter(m_nStartTuesday);
	cmd.AddParameter(m_nStartWednesday);
	cmd.AddParameter(m_nStartThursday);
	cmd.AddParameter(m_nStartFriday);
	cmd.AddParameter(m_nStartSaturday);
	cmd.AddParameter(m_nStartSunday);

	cmd.AddParameter(m_nEndMonday);
	cmd.AddParameter(m_nEndTuesday);
	cmd.AddParameter(m_nEndWednesday);
	cmd.AddParameter(m_nEndThursday);
	cmd.AddParameter(m_nEndFriday);
	cmd.AddParameter(m_nEndSaturday);
	cmd.AddParameter(m_nEndSunday);

	if(cmd.Execute())
	{
		MessageBox("저장되었습니다", "확인", MB_ICONINFORMATION);
		OnOK();
	}

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CSetAppRcpTimeDlg::OnBnClickedCloseBtn()
{
	OnCancel();
}

BOOL CSetAppRcpTimeDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->hwnd == m_cmbStartMonday.GetSafeHwnd() || pMsg->hwnd == m_cmbStartTuesday.GetSafeHwnd() || pMsg->hwnd == m_cmbStartWednesday.GetSafeHwnd() || pMsg->hwnd == m_cmbStartThursday.GetSafeHwnd() ||
			pMsg->hwnd == m_cmbStartFriday.GetSafeHwnd() || pMsg->hwnd == m_cmbStartSaturday.GetSafeHwnd() || pMsg->hwnd == m_cmbStartSunday.GetSafeHwnd() ||
			pMsg->hwnd == m_cmbEndMonday.GetSafeHwnd() || pMsg->hwnd == m_cmbEndTuesday.GetSafeHwnd() || pMsg->hwnd == m_cmbEndWednesday.GetSafeHwnd() || pMsg->hwnd == m_cmbEndThursday.GetSafeHwnd() ||
			pMsg->hwnd == m_cmbEndFriday.GetSafeHwnd() || pMsg->hwnd == m_cmbEndSaturday.GetSafeHwnd() || pMsg->hwnd == m_cmbEndSunday.GetSafeHwnd())
		{
			int nVirtKey = (int) pMsg->wParam;
			if(nVirtKey >= VK_NUMPAD0 && nVirtKey <= VK_NUMPAD9)
			{
				CComboBox *pCombo = (CComboBox*)FromHandle(pMsg->hwnd);
				if(pCombo)
				{
					CString strKey;
					switch (nVirtKey)
					{
					case VK_NUMPAD0 :
						strKey = "0";	break;
					case VK_NUMPAD1 :
						strKey = "1";	break;
					case VK_NUMPAD2 :
						strKey = "2";	break;
					case VK_NUMPAD3 :
						strKey = "3";	break;
					case VK_NUMPAD4 :
						strKey = "4";	break;
					case VK_NUMPAD5 :
						strKey = "5";	break;
					case VK_NUMPAD6 :
						strKey = "6";	break;
					case VK_NUMPAD7 :
						strKey = "7";	break;
					case VK_NUMPAD8 :
						strKey = "8";	break;
					case VK_NUMPAD9 :
						strKey = "9"; 	break;
					default:
						strKey = "0";	break;
					}

					KeyDownSearchComboBox(pCombo, strKey);
					return TRUE;
				}
			}
			else if(isalpha(nVirtKey) || isdigit(nVirtKey))
			{
				CComboBox *pCombo = (CComboBox*)FromHandle(pMsg->hwnd);
				if(pCombo)
				{
					char szKey = nVirtKey;
					CString strKey;
					strKey.Format("%c", szKey);
					KeyDownSearchComboBox(pCombo, strKey);
					return TRUE;
				}
			}
		}
	}

	return CMyDialog::PreTranslateMessage(pMsg);
}

void CSetAppRcpTimeDlg::KeyDownSearchComboBox(CComboBox *pCombo, CString strText)
{
	CString strSearch, strCombo;
	pCombo->GetWindowText(strCombo);
	strSearch = strCombo + strText;

	if (pCombo->SelectString(-1, strSearch) == CB_ERR)
		pCombo->SelectString(-1, strText);

	/*
	int nLength = strSearch.GetLength();

	// Currently selected range
	DWORD dwCurSel = pCombo->GetEditSel();
	WORD dStart = LOWORD(dwCurSel);
	WORD dEnd   = HIWORD(dwCurSel);

	if (pCombo->SelectString(-1, strSearch) == CB_ERR)
	{
		SetWindowText(strSearch);       // No text selected, so restore what was there before
		if (dwCurSel != CB_ERR)
		{
			pCombo->SetEditSel(dStart, dEnd);   //restore cursor postion
		}
	}


	// Set the text selection as the additional text that we have added
	if (dEnd < nLength && dwCurSel != CB_ERR)
		pCombo->SetEditSel(dStart, dEnd);
	else
		pCombo->SetEditSel(nLength, -1);
	*/
}