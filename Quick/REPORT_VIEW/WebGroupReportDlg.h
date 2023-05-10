#pragma once


// CWebGroupReportDlg 대화 상자입니다.

class CWebGroupReportDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CWebGroupReportDlg)

public:
	CWebGroupReportDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CWebGroupReportDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_WEB_GROUP_REPORT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
