#pragma once

// CGeneralReceiptLogDlg 대화 상자입니다.

class CGeneralReceiptLogDlg : public CMyDialog
{ 
	DECLARE_DYNAMIC(CGeneralReceiptLogDlg)

public:
	CGeneralReceiptLogDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CGeneralReceiptLogDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_GENERAL_RECEIPT_LOG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	
	
public:
	CXTPListCtrl2 m_lstReport;
	afx_msg void OnBnClickedRefresh();
	virtual BOOL OnInitDialog();
	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void RefreshList();
};
