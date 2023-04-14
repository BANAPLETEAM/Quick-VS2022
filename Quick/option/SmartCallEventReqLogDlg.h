#pragma once


// CSmartCallEventReqLogDlg 대화 상자입니다.

class CSmartCallEventReqLogDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSmartCallEventReqLogDlg)

public:
	CSmartCallEventReqLogDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSmartCallEventReqLogDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SMART_CALL_EVENT_REQ_LOG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCloseBtn();
	afx_msg void OnBnClickedExcelBtn();

	CXTPListCtrl2 m_lstReport;
	afx_msg void OnBnClickedRefreshBtn();
	long m_nBoardID;

	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;
	CDateTimeCtrl m_dtpFrom;
	CDateTimeCtrl m_dtpTo;
	CDateButton m_btnData;
};
