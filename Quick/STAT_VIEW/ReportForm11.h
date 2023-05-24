#pragma once

class CGraph;

static const char *dayofweek[] = {"일", "월", "화", "수", "목", "금", "토", "평균"};

typedef struct {
	UINT nData;
	COleDateTime dt;
	int nDayOfWeek;
} GRAPH_DATA;

class CReportFormRecord_RealTime11 : public CXTPGridRecord
{
public:

	CReportFormRecord_RealTime11::CReportFormRecord_RealTime11(CString sDate, CString sCount, 
		CString sCash, CString sCredit, CString sOnline, CString sMile, CString sCard, 
		CString sChargeSum, 
		CString sDeposit, CString sChargeDriving,CString sRiderDeposit, 
		CString sExcepotionDeposit, CString sMyRider, CString sOtherRider, CString sTruckCount,
		CString sTrans
		)
	{
		AddItem(new CXTPGridRecordItemText(sDate));
		AddItem(new CXTPGridRecordItemText(sCount));
		AddItem(new CXTPGridRecordItemText(sCash));
		AddItem(new CXTPGridRecordItemText(sCredit));
		AddItem(new CXTPGridRecordItemText(sOnline));
		AddItem(new CXTPGridRecordItemText(sMile));
		AddItem(new CXTPGridRecordItemText(sCard));
		AddItem(new CXTPGridRecordItemText(sChargeSum));
		AddItem(new CXTPGridRecordItemText(sDeposit));
		AddItem(new CXTPGridRecordItemText(sChargeDriving));
		AddItem(new CXTPGridRecordItemText(sRiderDeposit));
		AddItem(new CXTPGridRecordItemText(sExcepotionDeposit)); 
		AddItem(new CXTPGridRecordItemText(sMyRider));
		AddItem(new CXTPGridRecordItemText(sOtherRider));
		AddItem(new CXTPGridRecordItemText(sTruckCount));
		AddItem(new CXTPGridRecordItemText(sTrans));
	}
};
class CReportFormRecord11 : public CXTPGridRecord
{
protected:

	class CXTPGridRecordItemFormatNumber : public CXTPGridRecordItemNumber
	{
	public:
		CXTPGridRecordItemFormatNumber(long nAmount) : CXTPGridRecordItemNumber(nAmount)
		{
			m_strCaption = LF->GetMyNumberFormat(nAmount);
		}
	};


	class CXTPGridRecordItemPercentNumber : public CXTPGridRecordItemNumber
	{
	public:
		CXTPGridRecordItemPercentNumber(long nAmount) : CXTPGridRecordItemNumber(nAmount)
		{
			m_strCaption = LF->GetMyNumberFormat(nAmount) + "%";
		}
	};

	class CXTPGridRecordItemMyDate : public CXTPGridRecordItemDateTime
	{
	public:
		CXTPGridRecordItemMyDate(COleDateTime dtDateTime)
			: CXTPGridRecordItemDateTime(dtDateTime)
		{
			m_strFormatString = dtDateTime.Format("%Y-%m-%d") + "(" + dayofweek[dtDateTime.GetDayOfWeek() - 1] + ")";
		}
	};

public:
	CReportFormRecord11::CReportFormRecord11(COleDateTime dt, long nTotal, long nComplete, long nCancel, LONGLONG nCash,
						LONGLONG nCredit, long nTotalDeposit, long nGive, long nTake, long nMileageCharge, long nChargeCompany, long nMileage, BOOL bTotal);
	CReportFormRecord11::CReportFormRecord11();

};

// CReportForm11 폼 뷰입니다.

class CReportForm11 : public CMyFormView
{
	DECLARE_DYNCREATE(CReportForm11)

protected:
	CReportForm11();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CReportForm11();

public:
	enum { IDD = IDD_REPORT11 };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CGraph* m_Graph;
	BOOL m_bGraphComplete;
	
	CDateTimeCtrl m_dtFrom;
	CDateTimeCtrl m_dtTo;
	COleDateTime m_From;
	COleDateTime m_To;

	CDateButton m_DateBtn;
	CButton m_RefreshBtn;
	CMyStatic m_PeriodStatic;
	CButton m_chkIntegrteInquery;

	void RefreshList();
	void SetHeader(BOOL bIntegated);
	void RefreshListRealtime();
	void DrawGraph(GRAPH_DATA *pGraphData, UINT nMaxTotal, int nCount);
	CXTPGridControl m_wndReport;
	virtual void OnInitialUpdate();
	afx_msg void OnPaint();
	CStatic m_GraphStc;
	afx_msg void OnBnClickedButtonRiderFetch();
	afx_msg void OnViewExcel();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint point);
	CButton m_HorizontalChk;
	afx_msg void OnBnClickedHorizontalChk();
	afx_msg void OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);

	void Move(bool bWidth);
	CRect m_RcList;
	CRect m_RcStc;
	afx_msg void OnBnClickedIntegrateInqueryCheck();
};


