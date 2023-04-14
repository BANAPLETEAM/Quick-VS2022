#pragma once



typedef map<pair<long, long>, ST_WCOUNT> MAP_WCOUNT;

// CRcpPageWCountForm 폼 뷰입니다.

class CXTPChartButtonControl : public CXTPChartControl
{

protected:
	DECLARE_MESSAGE_MAP()

private:
	CWnd *m_pMsgWnd;
	CButton m_btnClick;

public:
	afx_msg void OnClick();
	void MakeButton(CWnd *pMsgWnd);
};

class CRcpPageWCountForm : public CMyFormView
{
	DECLARE_DYNCREATE(CRcpPageWCountForm)

protected:
	CRcpPageWCountForm();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CRcpPageWCountForm();

public:
	enum { IDD = IDD_RCP_PAGE_W_COUNT_FORM };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:

	long m_nAllCount;
	long m_nHourCount;

	COleDateTime m_dtLastRefresh;
	CXTPChartButtonControl m_chtWNo;
	virtual void OnInitialUpdate();

	void RefreshChart();
	void FillData();
	void ChangeDatePer();
	void OnSize(UINT nType, int cx, int cy);

	MAP_WCOUNT m_mapWCount;
	afx_msg void OnBnClickedRefreshButton();
	afx_msg LONG OnChartRefresh(WPARAM wParam, LPARAM lParam);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	CString GetGraphLabel(long nType);
	long GetGraphItem(ST_WCOUNT *st, long nType);
	void RefreshRankList();

	void AddGraphData(vector <ST_WCOUNT> *vec, long nType, long nGroup);
	void CRcpPageWCountForm::GetPreRank(COleDateTime dtRefresh);

	CXTPGridControl m_lstReport;

};


