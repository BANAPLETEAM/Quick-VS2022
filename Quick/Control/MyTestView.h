#pragma once


// CMyTestView 뷰입니다.
#include "MyXTPReportView.h"


class CGroupViewPaintManager 	: public CXTPGridThemeResource
{
	friend class CXTPGridControl;
public:

	CGroupViewPaintManager()
	{	
		for(int i = 0; i < 10; i++)
			m_bSelect[i] = 0;
	}	
	virtual ~CGroupViewPaintManager(){}

	BOOL m_bSelect[10];
	void SetSelectCol(BOOL bSelectCol[10])
	{
		for(int i =0; i < 10; i++)
			m_bSelect[i] = bSelectCol[i];
	}

public:
	virtual void DrawItemCaption(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pMetrics)
	{
		int nCol = pDrawArgs->pColumn->GetIndex();
		int nRow = pDrawArgs->pRow->GetIndex();
		CDC *pDC = pDrawArgs->pDC;	

		CXTPListCtrl2 *pData = (CXTPListCtrl2*)pDrawArgs->pRow->GetControl();
		long nGNo = pData->GetItemLong2(nRow);		
		long nCNo = pData->GetItemLong(nRow);		
		CRect rcItem = pDrawArgs->rcItem;
		CString strText = pMetrics->strText;

		COLORREF BODYTEXT = RGB(0, 0, 0);
		COLORREF GROUPOWNERCOLOR = RGB(0, 200, 0);

		COLORREF rectRegular = RGB(255, 255, 255);
		COLORREF rectAllRow = RGB(236,249,245);
		COLORREF rectSelect = RGB(229,195,246);	


		if(nCol > 5)
		{					
			if(m_bSelect[nCol])
			{				
				CBrush brush(rectSelect);
				pDC->FillRect(rcItem,&brush);				
				//)>FillSolidRect(rcItem,RGB(229,195,246));		 // 선택아이콘없어짐 중요	
			}			
			else
			{
				CBrush brush(rectAllRow);				
				pDC->FillRect(rcItem,&brush);				
			}			
		}		 
		if(m_cg.GetGroupData(nGNo)->nGroupOwner == nCNo)			
			pDC->SetTextColor(GROUPOWNERCOLOR);				
		else
			pDC->SetTextColor(BODYTEXT);

		if(strText.GetLength() > 0)
			pDC->DrawText(strText, rcItem, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

	}	
};


class CMyTestView : public CK2ReportView
{
	DECLARE_DYNCREATE(CMyTestView)

protected:
	CMyTestView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CMyTestView();

public:
	virtual void OnDraw(CDC* pDC);      // 이 뷰를 그리기 위해 재정의되었습니다.
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()

	
	long m_nGNo;	
	BOOL m_bChild;
	CWnd *m_pParentWnd;	

public:
	afx_msg void OnReportBeginDrag(NMHDR * /*pNotifyStruct*/, LRESULT * /*result*/);
	BOOL m_bSelectCol[10];
	CGroupViewPaintManager * m_pPaintManager;	
	void Refresh();
	afx_msg void OnReportStartItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);	
	void SetGNo(long nGNo){	m_nGNo = nGNo;}
	void SetChild(BOOL bChild){m_bChild = bChild;}
	virtual void OnInitialUpdate();
	void ReportDblClick();
	void SetWnd(CWnd *pWnd);
};


