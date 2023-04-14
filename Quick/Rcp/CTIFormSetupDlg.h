#pragma once

#include "MyCheckBtn.h"

// CCTIFormSetupDlg 대화 상자입니다.

class CCTIFormSetupDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CCTIFormSetupDlg)

public:
	CCTIFormSetupDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCTIFormSetupDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CTI_FORM_SETUP_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnBnClickedConnectBtn();
	afx_msg void OnBnClickedAutoTransferCheck();
	afx_msg void OnBnClickedQueueRcpPopupCheck();
	afx_msg void OnBnClickedRingMusicCheck();
	afx_msg void OnBnClickedOpenRingMusic();
	afx_msg void OnEnChangeAddressEdit();
	afx_msg void OnEnChangeAddressEdit2();
	afx_msg void OnEnChangeLineEdit();

	BOOL LoadCTIInfoReg(CString strUserID = "");
	void SaveCTIInfoReg(CString strUserID = "");

	DECLARE_MESSAGE_MAP()

public:
	CFlatEdit2 m_edtAddress;
	CFlatEdit2 m_edtAddress2;
	CFlatEdit2 m_edtKeyPhoneID;
	CFlatEdit2 m_edtAutoTransfer;
	CFlatEdit2 m_edtAutoTransfer2;
	CFlatEdit2 m_edtAutoHangupElapsedMin;
	CMyCheckBtn m_chkUseCTI;
	CMyCheckBtn m_chkAutoBlocking;
	CMyCheckBtn m_chkHotCID;
	CMyCheckBtn m_chkAutoTransfer;
	CMyCheckBtn m_chkEnableDBRefresh;
	CMyCheckBtn m_chkAutoHangup;
	BOOL m_bReconnect;
	CMyCheckBtn m_chkQueueRcpPopup;
	CComboBox m_cmbRcpPopupSecond;
	CMyCheckBtn m_chkRingColor;
	CMyCheckBtn m_chkRingMusic;
	CButton m_btnRingMusic;
	CEdit m_edtRingMusicPath;
	CMyCheckBtn m_chkNotCalllistPickup;
};
