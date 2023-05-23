#pragma once
#include "afxwin.h"
#include "MakeRcpPower.h"
#include "MyCheckBtn.h"

// CLogonDlg 대화 상자입니다.

class CLogonDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CLogonDlg)

public:
	CLogonDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CLogonDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_LOGON_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedCloseBtn();
	afx_msg void OnBnClickedOkBtn();
	afx_msg void OnBnClickedCancelBtn();
	afx_msg void OnStnClickedBackStatic();
	afx_msg void OnBnClickedHpauthButton();
	afx_msg void OnBnClickedRemoteBtn();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

public:
	CBitmapButton m_CloseBtn;
	CBitmapButton m_OkBtn;
	CBitmapButton m_CancelBtn;
	CBitmapButton m_HpAuthBtn;
	CBitmapButton	m_RemoteBtn;
	CBitmapButton m_MDacBtn;
	CStatic m_BackStatic;
	CStatic m_stcMent;
	CStatic m_stcMent2;
	CStatic m_stcVersion;
	CFlatEdit2 m_edtID;
	CFlatEdit2 m_edtPW;
	CMyCheckBtn m_chkSaveID;

public:
	CString m_strID;
	CString m_strPW;
	BOOL m_bAuth;
	CString m_sPreID;

	CString GetLogiSessionKey();
	void RefreshOnlyLoadGroup();
	void RefreshUserDongPos();	
	void CheckSaveID();
	void SaveID();
	void SetVersionInfo();
	void RefreshMent();
	void MakeLineGroupMap();
	void UpdateRegionInfo();
	void SetPayTypeOrder(CBranchInfo* pBi, CString strPayTypeOrder);
	void SetCarTypeOrder(CBranchInfo* pBi, CString strCarTypeOrder);
	void LoadConsignShare(CBranchInfo *pBi);
	void GetRsData(CMkRecordset *pRs, CBranchInfo *pBi);
};