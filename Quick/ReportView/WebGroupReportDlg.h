#pragma once


// CWebGroupReportDlg ��ȭ �����Դϴ�.

class CWebGroupReportDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CWebGroupReportDlg)

public:
	CWebGroupReportDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CWebGroupReportDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_WEB_GROUP_REPORT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);

	CXTPTabControl m_wndTabControl;

	long m_nCount;

	CStringArray m_strGNo;
	CStringArray m_strID;
	CStringArray m_strTitle;
};
