// CTIFormSetupDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Resource.h"
#include "CTIFormSetupDlg.h"
#include "RcpPageCTIForm.h"

// CCTIFormSetupDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCTIFormSetupDlg, CMyDialog)
CCTIFormSetupDlg::CCTIFormSetupDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CCTIFormSetupDlg::IDD, pParent)
{
	m_bReconnect = FALSE;
} 

CCTIFormSetupDlg::~CCTIFormSetupDlg()
{
}

void CCTIFormSetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ADDRESS_EDIT, m_edtAddress);
	DDX_Control(pDX, IDC_ADDRESS_EDIT2, m_edtAddress2);
	DDX_Control(pDX, IDC_KEY_PHONE_ID_EDIT, m_edtKeyPhoneID);
	DDX_Control(pDX, IDC_AUTO_TRANSFER_EDIT, m_edtAutoTransfer);
	DDX_Control(pDX, IDC_AUTO_TRANSFER_EDIT2, m_edtAutoTransfer2);
	DDX_Control(pDX, IDC_USE_CTI_CHECK, m_chkUseCTI);
	DDX_Control(pDX, IDC_AUTO_BLOCKING_CHECK, m_chkAutoBlocking);
	DDX_Control(pDX, IDC_HOT_CID_CHECK, m_chkHotCID);
	DDX_Control(pDX, IDC_AUTO_TRANSFER_CHECK, m_chkAutoTransfer);
	DDX_Control(pDX, IDC_ENABLE_DB_REFRESH_CHECK, m_chkEnableDBRefresh);
	DDX_Control(pDX, IDC_AUTO_HANGUP_CHECK, m_chkAutoHangup);
	DDX_Control(pDX, IDC_AUTO_HANGUP_ELAPSED_MIN_EDIT, m_edtAutoHangupElapsedMin);
	DDX_Control(pDX, IDC_QUEUE_RCP_POPUP_CHECK, m_chkQueueRcpPopup);
	DDX_Control(pDX, IDC_RCP_POPUP_SECOND_COMBO, m_cmbRcpPopupSecond);
	DDX_Control(pDX, IDC_RING_COLOR_CHECK, m_chkRingColor);
	DDX_Control(pDX, IDC_RING_MUSIC_CHECK, m_chkRingMusic);
	DDX_Control(pDX, IDC_RING_MUSIC_EDIT, m_edtRingMusicPath);
	DDX_Control(pDX, IDC_OPEN_RING_MUSIC_BUTTON, m_btnRingMusic);
	DDX_Control(pDX, IDC_NOT_CALLLIST_PICKUP_CHECK, m_chkNotCalllistPickup);
}


BEGIN_MESSAGE_MAP(CCTIFormSetupDlg, CMyDialog)
	ON_BN_CLICKED(IDC_CONNECT_BTN, &CCTIFormSetupDlg::OnBnClickedConnectBtn)
	ON_BN_CLICKED(IDC_QUEUE_RCP_POPUP_CHECK, OnBnClickedQueueRcpPopupCheck)
	ON_BN_CLICKED(IDC_RING_MUSIC_CHECK, OnBnClickedRingMusicCheck)
	ON_BN_CLICKED(IDC_OPEN_RING_MUSIC_BUTTON,  OnBnClickedOpenRingMusic)
	ON_EN_CHANGE(IDC_ADDRESS_EDIT, OnEnChangeAddressEdit)
	ON_EN_CHANGE(IDC_ADDRESS_EDIT2, OnEnChangeAddressEdit2)
	ON_EN_CHANGE(IDC_KEY_PHONE_ID_EDIT, OnEnChangeLineEdit)
END_MESSAGE_MAP()


// CCTIFormSetupDlg 메시지 처리기입니다.

BOOL CCTIFormSetupDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

#ifdef _SYSMANAGER
	m_chkHotCID.ShowWindow(SW_SHOW);
	m_chkAutoBlocking.ShowWindow(SW_SHOW);
#endif

	CString strTemp;
	for (int i = 0 ; i < 16 ; i++)
	{
		strTemp.Format("%d초", i);
		m_cmbRcpPopupSecond.AddString(strTemp);
	}

	LoadCTIInfoReg(m_ui.strID);
	if(m_edtAddress.GetWindowTextLength() == 0)
		LoadCTIInfoReg();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CCTIFormSetupDlg::OnOK()
{
	SaveCTIInfoReg();
	SaveCTIInfoReg(m_ui.strID);
	CMyDialog::OnOK();
}

void CCTIFormSetupDlg::OnBnClickedConnectBtn()
{
	m_bReconnect = TRUE;
	OnOK();
}

void CCTIFormSetupDlg::OnBnClickedQueueRcpPopupCheck()
{
	m_cmbRcpPopupSecond.EnableWindow(m_chkQueueRcpPopup.GetCheck());
}

void CCTIFormSetupDlg::OnBnClickedRingMusicCheck()
{
	m_btnRingMusic.EnableWindow(m_chkRingMusic.GetCheck());
	m_edtRingMusicPath.EnableWindow(m_chkRingMusic.GetCheck());
}

void CCTIFormSetupDlg::OnBnClickedOpenRingMusic()
{
	CString strPathName = "";
	CFileDialog dlg(TRUE, "*.wav", NULL, OFN_ALLOWMULTISELECT | OFN_FILEMUSTEXIST | OFN_LONGNAMES | OFN_PATHMUSTEXIST, "Wav Files (*.wav)|*.wav||", this);

	if(dlg.DoModal() == IDOK)
	{
		strPathName = dlg.GetPathName();
		if(strPathName.GetLength() == 0)
			MessageBox("파일이름이 없거나 선택이 되지 않았습니다.");
		else if(!(strPathName.Right(3).MakeUpper() == "wav" || strPathName.Right(3).MakeUpper() == "WAV"))
			MessageBox("파일형식이 잘못되었습니다.");
		else
			m_edtRingMusicPath.SetWindowText(strPathName);
	}
}

BOOL CCTIFormSetupDlg::LoadCTIInfoReg(CString strUserID)
{
	CString strKey = CString("TelMonitor") + (strUserID.IsEmpty() ? "" : "\\" + strUserID);

	m_edtAddress.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtAddress.SetUserOption(RGB(0, 0, 255), RGB(220, 200, 255), "서버주소", FALSE, FALSE);
	m_edtAddress2.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtAddress2.SetUserOption(RGB(0, 0, 255), RGB(220, 200, 255), "서버주소2", FALSE, FALSE);
	m_edtKeyPhoneID.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtKeyPhoneID.SetUserOption(RGB(0, 0, 255), RGB(220, 200, 255), "키폰ID", FALSE, FALSE);
	m_edtAutoTransfer.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtAutoTransfer.SetUserOption(RGB(0, 0, 0), RGB(255, 255, 255), "자동착신1", FALSE, FALSE);
	m_edtAutoTransfer2.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtAutoTransfer2.SetUserOption(RGB(0, 0, 0), RGB(255, 255, 255), "자동착신2", FALSE, FALSE);

	CString strIP, strIP2, strKeyPhoneID, strAutoTransfer, strAutoTransfer2, strRingMusicPath;
	strIP = AfxGetApp()->GetProfileString(strKey, "ServerIP", "");
	strIP2 = AfxGetApp()->GetProfileString(strKey, "ServerIP2", "");
	strKeyPhoneID = AfxGetApp()->GetProfileString(strKey, "KeyPhoneID", "");
	strAutoTransfer = AfxGetApp()->GetProfileString(strKey, "AutoTransfer1", "");
	strAutoTransfer2 = AfxGetApp()->GetProfileString(strKey, "AutoTransfer2", "");
	m_chkUseCTI.SetCheck(AfxGetApp()->GetProfileInt(strKey, "Enable", 1));
	m_chkHotCID.SetCheck(AfxGetApp()->GetProfileInt(strKey, "HotCID", 0));
	m_chkAutoBlocking.SetCheck(AfxGetApp()->GetProfileInt(strKey, "AutoBlocking", 0));
	m_chkAutoTransfer.SetCheck(AfxGetApp()->GetProfileInt(strKey, "AutoTransfer", 0));
	m_chkEnableDBRefresh.SetCheck(AfxGetApp()->GetProfileInt(strKey, "EnableDBRefresh", 0));
	m_chkQueueRcpPopup.SetCheck(AfxGetApp()->GetProfileInt(strKey, "QueueRcpPopup", 0));	
	m_cmbRcpPopupSecond.SetCurSel(AfxGetApp()->GetProfileInt(strKey, "RcpPopupSecond", 0));
	m_cmbRcpPopupSecond.EnableWindow(m_chkQueueRcpPopup.GetCheck());
	m_chkRingColor.SetCheck(AfxGetApp()->GetProfileInt(strKey, "RingColor", 0));
	m_chkRingMusic.SetCheck(AfxGetApp()->GetProfileInt(strKey, "RingMusic", 0));
	strRingMusicPath = AfxGetApp()->GetProfileString(strKey, "RingMusicPath", "");
	m_chkNotCalllistPickup.SetCheck(AfxGetApp()->GetProfileInt(strKey, "NotCalllistPickup", 0));

	if(strIP.IsEmpty())
		CRcpPageCTIForm::LoadTelClientInfo(strIP, strKeyPhoneID);

	m_edtAddress.SetWindowText(strIP);
	m_edtAddress2.SetWindowText(strIP2);
	m_edtKeyPhoneID.SetWindowText(strKeyPhoneID);
	m_edtAutoTransfer.SetWindowText(strAutoTransfer);
	m_edtAutoTransfer2.SetWindowText(strAutoTransfer2);
	m_edtRingMusicPath.SetWindowText(strRingMusicPath);

	if(m_ui.nWNo == 0)
	{
		char buffer[10];
		m_chkAutoHangup.ShowWindow(SW_SHOW);
		m_chkAutoHangup.SetCheck(m_ci.m_nAutoHangupElapsedMin > 0);
		m_edtAutoHangupElapsedMin.ShowWindow(SW_SHOW);
		m_edtAutoHangupElapsedMin.SetWindowText(ltoa(m_ci.m_nAutoHangupElapsedMin, buffer, 10));
		GetDlgItem(IDC_AUTO_HANGUP_STATIC)->ShowWindow(SW_SHOW);
	}

	CBranchInfo *pBI = LF->GetBranchInfo(m_ui.nCompany);

	if (pBI->bIPPBXType == FALSE)
	{
		m_chkQueueRcpPopup.SetCheck(0);
		m_chkQueueRcpPopup.ShowWindow(SW_HIDE);
		m_cmbRcpPopupSecond.ShowWindow(SW_HIDE);
	}

	m_btnRingMusic.EnableWindow(m_chkRingMusic.GetCheck());
	m_edtRingMusicPath.EnableWindow(m_chkRingMusic.GetCheck());

	return TRUE;
}

void CCTIFormSetupDlg::SaveCTIInfoReg(CString strUserID)
{
	CString strKey = CString("TelMonitor") + (strUserID.IsEmpty() ? "" : "\\" + strUserID);

	CString strIP, strIP2, strKeyPhoneID, strAutoTransfer, strAutoTransfer2, strRingMusicPath;
	int nPhoneType = 0, nRcpPopupSecond = 0;
	m_edtAddress.GetWindowText(strIP);
	m_edtAddress2.GetWindowText(strIP2);
	m_edtKeyPhoneID.GetWindowText(strKeyPhoneID);
	nRcpPopupSecond = m_cmbRcpPopupSecond.GetCurSel();
	m_edtAutoTransfer.GetWindowText(strAutoTransfer);
	m_edtAutoTransfer2.GetWindowText(strAutoTransfer2);
	m_edtRingMusicPath.GetWindowText(strRingMusicPath);

	strAutoTransfer.Remove('-');
	strAutoTransfer.Remove(' ');
	strAutoTransfer2.Remove('-');
	strAutoTransfer2.Remove(' ');

	AfxGetApp()->WriteProfileString(strKey, "ServerIP", strIP);
	AfxGetApp()->WriteProfileString(strKey, "ServerIP2", strIP2);
	AfxGetApp()->WriteProfileString(strKey, "KeyPhoneID", strKeyPhoneID);
	AfxGetApp()->WriteProfileString(strKey, "AutoTransfer1", strAutoTransfer);
	AfxGetApp()->WriteProfileString(strKey, "AutoTransfer2", strAutoTransfer2);
	AfxGetApp()->WriteProfileInt(strKey, "Enable", m_chkUseCTI.GetCheck());
	AfxGetApp()->WriteProfileInt(strKey, "HotCID", m_chkHotCID.GetCheck());
	AfxGetApp()->WriteProfileInt(strKey, "AutoBlocking", m_chkAutoBlocking.GetCheck());
	AfxGetApp()->WriteProfileInt(strKey, "AutoTransfer", m_chkAutoTransfer.GetCheck());
	AfxGetApp()->WriteProfileInt(strKey, "EnableDBRefresh", m_chkEnableDBRefresh.GetCheck());
	AfxGetApp()->WriteProfileInt(strKey, "QueueRcpPopup", m_chkQueueRcpPopup.GetCheck());
	AfxGetApp()->WriteProfileInt(strKey, "RcpPopupSecond", nRcpPopupSecond);
	AfxGetApp()->WriteProfileInt(strKey, "RingColor", m_chkRingColor.GetCheck());
	AfxGetApp()->WriteProfileInt(strKey, "RingMusic", m_chkRingMusic.GetCheck());
	AfxGetApp()->WriteProfileString(strKey, "RingMusicPath", strRingMusicPath);
	AfxGetApp()->WriteProfileInt(strKey, "NotCalllistPickup", m_chkNotCalllistPickup.GetCheck());

	if(m_ui.nWNo == 0)
	{
		CString strElapsedMin;
		BOOL bAutoHangup = m_chkAutoHangup.GetCheck();
		m_edtAutoHangupElapsedMin.GetWindowText(strElapsedMin);
		int nElapsedMin = atol(strElapsedMin);

		if(!bAutoHangup)
			nElapsedMin = 0;

		if(m_ci.m_nAutoHangupElapsedMin != nElapsedMin)
		{
			m_ci.m_nAutoHangupElapsedMin = nElapsedMin;
			CMkCommand pCmd(m_pMkDb, "update_auto_hangup_state");
			pCmd.AddParameter(m_ci.m_nCompanyCode);
			pCmd.AddParameter(nElapsedMin);
			pCmd.Execute();
		}
	}
}

void CCTIFormSetupDlg::OnEnChangeAddressEdit()
{
	CString strText;
	m_edtAddress.GetWindowText(strText);

	if(strText.Replace(",", ".") > 0)
	{
		MessageBox("서버 IP에 콤마(,)는 사용할 수 없어 마침표(.)로 변경됩니다.", "확인", MB_ICONINFORMATION);
		m_edtAddress.SetWindowText(strText);
	}
}

void CCTIFormSetupDlg::OnEnChangeAddressEdit2()
{
	CString strText;
	m_edtAddress2.GetWindowText(strText);

	if(strText.Replace(",", ".") > 0)
	{
		MessageBox("보조서버 IP에 콤마(,)는 사용할 수 없어 마침표(.)로 변경됩니다.", "확인", MB_ICONINFORMATION);
		m_edtAddress2.SetWindowText(strText);
	}
}

void CCTIFormSetupDlg::OnEnChangeLineEdit()
{
	CString strText;
	m_edtKeyPhoneID.GetWindowText(strText);

	if(strText.Replace(".", ",") > 0)
	{
		MessageBox("키폰내선ID에 마침표(.)는 사용할 수 없어 콤마(,)로 변경됩니다.", "확인", MB_ICONINFORMATION);
		m_edtKeyPhoneID.SetWindowText(strText);
	}
}