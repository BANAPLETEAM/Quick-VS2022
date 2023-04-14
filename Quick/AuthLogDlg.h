#pragma once

// CAuthLogDlg 대화 상자입니다.

class CAuthLogDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CAuthLogDlg)

public:
	CAuthLogDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CAuthLogDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_AUTH_LOG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
