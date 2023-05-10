#pragma once

#define ALONE 0
#define ALL_GROUP 1
#define ACTIVE_GROUP 2
#define UN_ACTIVE_GROUP 3
#define CASH_GROUP 4
#define CREDIT_GROUP 5

#define MAX_TAB_COUNT 7

class CReport24TabControl : public CXTPTabControl
{
protected:
	virtual void OnItemClick(CXTPTabManagerItem* pItem);
};


class CGroupSearchDlg;

class CReportForm24 : public CMyFormView
{
	DECLARE_DYNCREATE(CReportForm24)

protected:
	CReportForm24();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CReportForm24();

public:
	enum { IDD = IDD_REPORT24  };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

	CGroupSearchDlg *m_pGroupSearchDlg;

	CReport24TabControl m_wndTabControl;
	CGroupList24 m_List;
	CDataBox	m_LogList;

	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnGroupReportItemDbClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnGroupReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedFullScreenBtn();
	afx_msg void OnEnSetfocusSearchEdit();
	afx_msg void OnEnChangeSearchEdit();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnBnClickedRefreshChooseBtn();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnReportBeginDrag(NMHDR * /*pNotifyStruct*/, LRESULT * /*result*/);
	afx_msg void OnPaint();
	
	void DeleteAllList();
	void MoveControl();
	void SetData(CString sGNo);
	void RefreshList();
	void PreRefreshList(BOOL bAll);
	void MakeListTree(long nGNo, VEC_CUSTOMER_GROUP::iterator it);
	void CallChildReport(CXTPGridRecord *pRecord);
	void OpenSearchDlg();
	BOOL CheckCharValid(CString sData);
	void GetSearchDay(long &nCount);
	void SearchFilter();
	void UpdateCount();
	void SetExcelData(COleSafeArray &sa, GROUP_REPORT st, BOOL bSumRecord, long &nItem, long nCol);

	CButton m_RefreshBtn;
	CButton m_AllSeeBtn;
	CButton m_DeleteAllBtn;
	CButton m_DeletePartBtn;

	CStatic m_TipStc;
	CStatic m_stcDraw;
	CStatic m_stcLine;

	CFlatEdit2 m_edtSearch;

	CRect m_rcLst;
	CRect m_rcLstReport;
	CRect m_rcBtn;
	CRect m_rcLogReport;

	BOOL m_bDragMode;
	BOOL m_bFullScreen;
	
	CString m_strNotIncomeMonth[6];
	//void UpdateCount(CPaintDC *pDC);

	long m_nUnBillCollection;
	long m_nBillCollection;
	long m_nCashCount;
	long m_nCreditCount;
	long m_nCreditCharge;
	long m_nCashCharge;
};


