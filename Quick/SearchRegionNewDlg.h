#pragma once


// CSearchRegionNewDlg 대화 상자입니다.

class CSearchRegionNewDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSearchRegionNewDlg)

public:
	CSearchRegionNewDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSearchRegionNewDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SEARCH_REGION_NEW_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedSearchBtn();
	afx_msg void OnBnClickedOk();

	DECLARE_MESSAGE_MAP()

public:
	void RefreshList();
	void SelectUp();
	void SelectDown();

	CFlatEdit2 m_edtSearch;
	CXTPListCtrl2 m_List;

	CString m_strDisplayDong;
	CString m_strSearch;
	CString m_strLi;

	int m_nDongID;

	BOOL m_bAloneItemAutoClosed;
	BOOL m_bExpandLiData;

	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
