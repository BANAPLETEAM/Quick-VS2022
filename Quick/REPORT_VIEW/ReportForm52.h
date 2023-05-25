#pragma once

//y#include "ReportForm17.h"

// CReportForm52 폼 뷰입니다.

typedef map<long, int> GNO_MAP;



class CMyGroupReport52 : public CDataBox
{
public:
	CMyGroupReport52()
	{
		

	};   // 표준 생성자입니다.
	virtual ~CMyGroupReport52(){};	

	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics)
	{

		int nCol = pDrawArgs->pColumn->GetIndent();
		CString strColName = pDrawArgs->pColumn->GetCaption();
		COleDateTime dtNow(COleDateTime::GetCurrentTime());
		CXTPGridColumn *pCol = pDrawArgs->pColumn;
		CMyXTPGridRecord *pRecord = (CMyXTPGridRecord *)pDrawArgs->pRow->GetRecord();
		CString sState = "";
		if(pRecord && pCol)
		{
			if(strColName.Compare("상태") == 0)
			{
				sState = pRecord->GetItem(5)->GetCaption(pCol);
				if(sState.Compare("입금완료") == 0)
				{
					pItemMetrics->clrForeground = RGB(0, 0, 255);				
					pItemMetrics->pFont = &pDrawArgs->pControl->GetPaintManager()->m_fontBoldText;
				}
				else if(sState.Compare("부분입금") == 0)
					pItemMetrics->clrForeground = RGB(255, 0, 0);
			}

			if(strColName.Compare("총합계") == 0 || strColName.Compare("신용금액") == 0)
				pItemMetrics->pFont = &pDrawArgs->pControl->GetPaintManager()->m_fontBoldText;
				
			if(strColName.Compare("미수금") == 0 || strColName.Compare("경과") == 0 ) 
				pItemMetrics->clrForeground = RGB(255, 0, 0);
			if( strColName.Compare("수금일") == 0 )
			{
				CString strTemp ;
				COleDateTime dtTemp;
				strTemp = pRecord->GetItem(15)->GetCaption(pCol);

				if(strTemp.GetLength() == 5)
				{
					dtTemp.SetDateTime(dtNow.GetYear(), atol(strTemp.Left(2)), atol(strTemp.Right(2)),0,0,0) ;
					if(dtNow > dtTemp)
						pItemMetrics->clrForeground = RGB(255, 0, 0);
				}
				

			}

			if(strColName.Compare("재수금일") == 0 || strColName.Compare("수금액") == 0)
				pItemMetrics->clrForeground = RGB(0, 0, 255);
		}
		
	}

};

class CReportForm52 : public CMyFormView
{
	DECLARE_DYNCREATE(CReportForm52)

protected:
	CReportForm52();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CReportForm52();

public:
	enum { IDD = IDD_REPORT52 };
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

	afx_msg void OnBnClickedBillPage();
	afx_msg void OnBnClickedBillExcel();
	afx_msg void OnBnClickedBill();
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
	afx_msg void OnPayIncome();
	afx_msg void OnPayCancel();
	afx_msg void OnPayEnd();
	afx_msg void OnReportDelete();
	afx_msg void OnPayView();
	afx_msg void OnBnClickedWebViewBtn();
	afx_msg void OnBnClickedWebTaxViewBtn();
	afx_msg void OnBnClickedLogiTest1Btn();
	afx_msg void OnBnClickedLogiTest2Btn();

	BOOL IsTimeValid(COleDateTime dt);
	void IncomeWork(int nType);
	void OnAfterReport();
	void OnUnBill();	
	void ReportWebView(long nReportNo , long nGNo, COleDateTime dtFrom, COleDateTime dtTo,CString strGNoList);
	void ReportBillPageView(long nCompany, long nGroupReportID, long nType);
	void RefreshList();
	void InitColumn();
	void RefreshOrderList();
	CString GetGNoList();
	void OnMakeGroupReport();
	void ChildInput(CGroupRecord* pOriginalRecord);
	void LogiTest(int nType);

	CMyGroupReport52 m_lstOrder;
	CGroupList m_lstGroup;
	GNO_MAP m_mapGNoList;
	
	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;
	CDateTimeCtrl m_dtFromCtl;
	CDateTimeCtrl m_dtToCtl;

	CDateButton m_btnDate;
	
	CComboBox		m_cmbSearhType;
	CFlatEdit2 m_edtSearch;
	CFlatEdit2 m_edtSearchOrder;
	
	BOOL m_bDragMode;
	CString m_sSelectGNo;

	long m_nCalculateCount;
	long m_nCalculateSum;
	long m_nCalculateTrans;

	CButton m_btnLogiTest1;
	CButton m_btnLogiTest2;
	
	
};


