#pragma once


// CChangeHistoryNameDlg ��ȭ �����Դϴ�.

class CChangeHistoryNameDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CChangeHistoryNameDlg)

public:
	CChangeHistoryNameDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CChangeHistoryNameDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CHANGE_HISTORY_NAME_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()


	afx_msg void OnBnClickedOkBtn();
	afx_msg void OnBnClickedCancelBtn();
public:
	CString m_sChargeName;
	CString m_sChargeEtc;
};
