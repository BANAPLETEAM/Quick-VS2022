#pragma once

struct RIDER_ATTEND_INFO
{
	int		nRow;	
	CString strCompanyCode;
};


typedef map<CString, RIDER_ATTEND_INFO> RIDER_ATTEND;


class CStaffPage4 : public CMyFormView
{
	DECLARE_DYNCREATE(CStaffPage4)

public:
	CStaffPage4();   // 표준 생성자입니다.
	virtual ~CStaffPage4();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_STAFF_PAGE4 };

public:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedShowByPayBtn();
	afx_msg void OnBnClickedDateBtn();
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnViewExcel();
	afx_msg void OnWorkStop();
	afx_msg void OnWorkOk();
	afx_msg void OnMenuMsg();
	afx_msg void OnBnClickedIncreseColBtn();
	afx_msg void OnLvnDeleteallitemsListReport(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListReport(NMHDR *pNMHDR, LRESULT *pResult);

	DECLARE_MESSAGE_MAP()

public:
	void CreateHeader();
	void SetRiderInfo();
	void SetRiderState();
	void DeleteColumn();
	void RefreshList();
	void MonthInit();

public:
	CXTPListCtrl2 m_XTPList;
	CStatic m_stcInfo;
	CDateButton m_DateBtn;
	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;
	CDateTimeCtrl m_FromDT;
	CDateTimeCtrl m_ToDT;

	CButton m_chkNotWork;
	CButton m_btnRefresh;
	CButton m_btnIncreaseCol;

private:
	CStringArray m_RecentDay;
	CStringArray m_RiderServiceState;
	int m_nLastCompanyCount;
	RIDER_ATTEND m_RiderInfo;
};
