#pragma once


// CCardPayLogDlg ��ȭ �����Դϴ�.

class CCardPayLogDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CCardPayLogDlg)

public:
	CCardPayLogDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CCardPayLogDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CARD_PAY_LOG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

	long m_nTNo;

	CXTPListCtrl2 m_lstReport;
	virtual BOOL OnInitDialog();

	void RefreshList();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
