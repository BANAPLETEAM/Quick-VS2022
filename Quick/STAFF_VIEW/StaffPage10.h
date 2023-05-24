#pragma once


// CStaffPage10 대화 상자입니다.


class CStaffPage10 : public CMyFormView
{
	DECLARE_DYNCREATE(CStaffPage10)

public:
	CFont m_font;
	CStaffPage10();   // 표준 생성자입니다.
	virtual ~CStaffPage10();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_STAFF_PAGE10};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate();

	afx_msg void OnBnClickedRegisterButton();
	afx_msg void OnViewExcel();
	afx_msg void OnViewExcel2();
	afx_msg void OnBnClickedDeleteButton();
	afx_msg void OnBnClickedModifyButton();
	afx_msg void OnBnClickedRefreshListButton();
	afx_msg void OnNMDblclkOtherriderList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkMyriderList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);

	void OnDelayAllocate();
	void OnDelayAllocateLog();

	DECLARE_MESSAGE_MAP()

public:
	void InitControl();
	void RefreshList();

public:
	CXTPListCtrl2 m_MyList;
	CXTPListCtrl2 m_OtherList;

	CXTPGridControl m_wndReport;

	CButton m_RegisterBtn;
	CButton m_DeleteBtn;
	CButton m_RefreshListBtn;

	afx_msg void OnNMClickMyriderList(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnCustomdrawOtherList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawMyList(NMHDR *pNMHDR, LRESULT *pResult);


	//
	long m_nOtherCompanyCol;

	void OtherDriverList();
	afx_msg void OnEnChangeEdit1();
	CEdit m_edtOtherRider;
	CEdit m_edtMyRider;
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnBnClickedRegisterButton2();
};
