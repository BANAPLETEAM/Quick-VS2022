#pragma once


// CSmartCallBoardDlg ��ȭ �����Դϴ�.

class CSmartCallBoardDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSmartCallBoardDlg)

public:
	CSmartCallBoardDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSmartCallBoardDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SMART_CALL_BOARD_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void RefreshList();
	CString GetOrderInsertType(long nOrderInsertType);
	CXTPListCtrl2 m_lstReport;
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnBnClickedInsertBtn();
	void InsertBoard(CXTPGridRecord *pRecord);
	BOOL m_bEventBoard;
	long m_nCompany;
	long m_nBoardIndex;
	afx_msg void OnBnClickedCloseBtn();
	afx_msg void OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * result);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnDelete();
	afx_msg void OnLog();
	CXTPGridRecord* GetFirstSelectRecord();
};
