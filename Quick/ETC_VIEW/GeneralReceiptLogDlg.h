#pragma once

// CGeneralReceiptLogDlg ��ȭ �����Դϴ�.

class CGeneralReceiptLogDlg : public CMyDialog
{ 
	DECLARE_DYNAMIC(CGeneralReceiptLogDlg)

public:
	CGeneralReceiptLogDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CGeneralReceiptLogDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_GENERAL_RECEIPT_LOG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
	
	
public:
	CXTPListCtrl2 m_lstReport;
	afx_msg void OnBnClickedRefresh();
	virtual BOOL OnInitDialog();
	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void RefreshList();
};
