#pragma once


// CSmartCallBoardDlg 대화 상자입니다.

class CSmartCallBoardDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSmartCallBoardDlg)

public:
	CSmartCallBoardDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSmartCallBoardDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SMART_CALL_BOARD_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
