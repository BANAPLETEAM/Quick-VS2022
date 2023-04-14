#pragma once


// CBillDlg 대화 상자입니다.

class CBillDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CBillDlg)

public:
	CBillDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CBillDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_BILL_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
