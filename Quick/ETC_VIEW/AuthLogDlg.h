#pragma once

// CAuthLogDlg ��ȭ �����Դϴ�.

class CAuthLogDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CAuthLogDlg)

public:
	CAuthLogDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CAuthLogDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_AUTH_LOG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	void Refresh();
	CString ReturnType(int nType);
	void OnCustomdrawList (NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedRefreshBtn();

	CDateTimeCtrl m_dtFrom;
	CDateTimeCtrl m_dtTo;
	COleDateTime m_From;
	COleDateTime m_To;
	CDateButton m_DateBtn;
	CXTPListCtrl2 m_List;
	CButton m_RefreshBtn;
	HBRUSH m_WhiteBrush;
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
