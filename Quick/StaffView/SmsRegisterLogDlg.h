#pragma once


// CSmsRegisterLogDlg ��ȭ �����Դϴ�.

class CSmsRegisterLogDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSmsRegisterLogDlg)

public:
	CSmsRegisterLogDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSmsRegisterLogDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SMS_REGISTER_LOG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

	CXTPListCtrl2 m_lstLogList;

public:
	virtual BOOL OnInitDialog();
	void RefreshLogList();

	long m_nCompany;
	long m_nTelNo;
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
