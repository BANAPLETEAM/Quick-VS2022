#pragma once

//y#include "ReportForm17.h"

// CReportForm51 폼 뷰입니다.

typedef map<long, int> GNO_MAP;



class CMyGroupReport51 : public CDataBox
{
public:
	CMyGroupReport51()
	{
		

	};   // 표준 생성자입니다.
	virtual ~CMyGroupReport51(){};	

	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics)
	{

		int nCol = pDrawArgs->pColumn->GetIndent();
		CString strColName = pDrawArgs->pColumn->GetCaption();
		CMyXTPGridRecord *pRecord = (CMyXTPGridRecord *)pDrawArgs->pRow->GetRecord();
		if(pRecord)
		{
			long nPayType = pRecord->GetItemData();

			if(nPayType == 2 && strColName.Compare("지불") == 0)
				pItemMetrics->clrForeground = RGB(255, 0, 0);
		}
		
	}

};

class CReportForm51 : public CMyFormView
{
	DECLARE_DYNCREATE(CReportForm51)

protected:
	CReportForm51();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CReportForm51();

public:
	enum { IDD = IDD_REPORT51 };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();

	afx_msg void OnBnClickedRefreshBtn2();
	afx_msg void OnEnChangeSearchEdit();	
	afx_msg void OnGroupReportItemDbClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnGroupReportClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);	
	afx_msg void OnReportBeginDrag(NMHDR * /*pNotifyStruct*/, LRESULT * /*result*/);
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnEnChangeSearchOrderEdit();
	afx_msg void OnOrderReportClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnOrderReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnViewExcel();
	afx_msg void OnBnClickedDeptWebViewBtn();
	afx_msg void OnBnClickedMainWebViewBtn();

	void OnAfterReport();
	void OnUnBill();

	void RefreshList();
	void InitColumn();
	void RefreshOrderList();
	CString GetGNoList();
	void ChildInput(CGroupRecord* pOriginalRecord);
	void OnMakeGroupReport();

	CMyGroupReport51 m_lstOrder;
	CGroupList m_lstGroup;
	GNO_MAP m_mapGNoList;

	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;
	CDateTimeCtrl m_dtFromCtl;
	CDateTimeCtrl m_dtToCtl;

	CDateButton m_btnDate;
	
	CButton		m_chkCredit;
	CFlatEdit2 m_edtSearch;
	CFlatEdit2 m_edtSearchOrder;
	
	BOOL m_bDragMode;
	CString m_sSelectGNo;

	long m_nCalculateCount;
	long m_nCalculateSum;
	long m_nCalculateTrans;
	
	
	
};


