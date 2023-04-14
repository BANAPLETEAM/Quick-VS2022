#pragma once


// CSmartCallEventReqLogDlg ��ȭ �����Դϴ�.

class CSmartCallEventReqLogDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSmartCallEventReqLogDlg)

public:
	CSmartCallEventReqLogDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSmartCallEventReqLogDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SMART_CALL_EVENT_REQ_LOG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
