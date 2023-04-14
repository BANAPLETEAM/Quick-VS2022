#pragma once


// CSetAppRcpTimeDlg 대화 상자입니다.

class CSetAppRcpTimeDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSetAppRcpTimeDlg)

public:
	CSetAppRcpTimeDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSetAppRcpTimeDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SET_APP_RCP_TIME_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	afx_msg BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSaveBtn();

	virtual BOOL OnInitDialog();
	void RefreshDlg();

	BOOL m_bMonday;
	BOOL m_bTuesday;
	BOOL m_bWednesday;
	BOOL m_bThursday;
	BOOL m_bFriday;
	BOOL m_bSaturday;
	BOOL m_bSunday;

	CComboBox m_cmbStartMonday;
	CComboBox m_cmbStartTuesday;
	CComboBox m_cmbStartWednesday;
	CComboBox m_cmbStartThursday;
	CComboBox m_cmbStartFriday;
	CComboBox m_cmbStartSaturday;
	CComboBox m_cmbStartSunday;

	CComboBox m_cmbEndMonday;
	CComboBox m_cmbEndTuesday;
	CComboBox m_cmbEndWednesday;
	CComboBox m_cmbEndThursday;
	CComboBox m_cmbEndFriday;
	CComboBox m_cmbEndSaturday;
	CComboBox m_cmbEndSunday;

	int m_nStartMonday;
	int m_nStartTuesday;
	int m_nStartWednesday;
	int m_nStartThursday;
	int m_nStartFriday;
	int m_nStartSaturday;
	int m_nStartSunday;

	int m_nEndMonday;
	int m_nEndTuesday;
	int m_nEndWednesday;
	int m_nEndThursday;
	int m_nEndFriday;
	int m_nEndSaturday;
	int m_nEndSunday;

	long m_nCompany;
	afx_msg void OnBnClickedCloseBtn();

	void KeyDownSearchComboBox(CComboBox *pCombo, CString strText);
};
