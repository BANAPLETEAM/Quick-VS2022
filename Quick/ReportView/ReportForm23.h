#pragma once

class CGraph;
#define MAX_DAY 100

typedef struct{
	long nDay[MAX_DAY];
}ARRAY_STRUCT;

typedef map <long, ARRAY_STRUCT> DRAW_MAP;

// CReportForm23 폼 뷰입니다.

class CReportForm23 : public CMyFormView
{
	DECLARE_DYNCREATE(CReportForm23)

protected:
	CReportForm23();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CReportForm23();

public:
	enum { IDD = IDD_REPORT23 };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnEnChangeSearchEdit();
	afx_msg void OnReportItemDbClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportItemSelChanged(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	virtual void OnInitialUpdate();
	void InitColumn();
	void RefreshList();
	void DrawGraph(DRAW_MAP *pMap, long nGNo);
	void MakeData(long nGNo);	
	long GetColumnLocation(CString sDate);

	CXTPListCtrl25 m_Report;

	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;
	CDateTimeCtrl m_dtFromCtl;
	CDateTimeCtrl m_dtToCtl;
	CDateButton m_DateBtn;

	BOOL m_bGraphComplete;
	CGraph *m_Graph;

	CFlatEdit2 m_edtSearch;

	CStatic m_stcDraw;
	
	
};


