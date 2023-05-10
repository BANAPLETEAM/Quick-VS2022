#pragma once


// CBillDlg ��ȭ �����Դϴ�.

class CBillDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CBillDlg)

public:
	CBillDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CBillDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_BILL_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
	
	CListCtrl m_BillList;
	CImageList m_imgList;

	CDateTimeCtrl m_DateDT;

public:
	LONG m_nCompanyCode;
	COleDateTime m_dtDate;
	
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();

	void RefreshList();
	afx_msg void OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkBillList(NMHDR *pNMHDR, LRESULT *pResult);
};
