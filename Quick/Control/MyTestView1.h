#pragma once


// CMyTestView 뷰입니다.
#include "MyXTPReportView.h"


class CGroupView1PaintManager 	: public CXTPGridPaintManager
{
	friend class CXTPGridControl;
public:

	CGroupView1PaintManager()
	{	
		for(int i = 0; i < 20; i++)
			m_bSelect[i] = 0;
	}	
	virtual ~CGroupView1PaintManager(){}

	BOOL m_bSelect[20];
	void SetSelectCol(BOOL bSelectCol[20])
	{
		for(int i =0; i < 20; i++)
			m_bSelect[i] = bSelectCol[i];
	}

public:
	virtual void DrawItemCaption(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pMetrics)
	{
		int nCol = pDrawArgs->pColumn->GetIndex();
		int nRow = pDrawArgs->pRow->GetIndex();
		CDC *pDC = pDrawArgs->pDC;	

		CDataBox *pData = (CDataBox*)pDrawArgs->pRow->GetControl();
		long nGNo = pData->GetItemDataLong2(nRow);		
		long nCNo = pData->GetItemDataLong(nRow);		
		CRect rcItem = pDrawArgs->rcItem;
		CString strText = pMetrics->strText;

		COLORREF BODYTEXT = RGB(0, 0, 0);
		COLORREF GROUPOWNERCOLOR = RGB(0, 200, 0);

		COLORREF rectRegular = RGB(255, 255, 255);
		COLORREF rectAllRow = RGB(236,249,245);
		COLORREF rectSelect = RGB(229,195,246);	
 

		if(m_cg.GetGroupData(nGNo)->nGroupOwner == nCNo)			
			pDC->SetTextColor(GROUPOWNERCOLOR);				
		else
			pDC->SetTextColor(BODYTEXT);		

	


		if(nCol > 1)
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
		

		if(strText.GetLength() > 0)
			pDC->DrawText(strText, rcItem, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

	}	
};


class CMyTestView1 : public CK2ReportView
{
	DECLARE_DYNCREATE(CMyTestView1)

protected:
	CMyTestView1();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CMyTestView1();

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
	

public:
	BOOL m_bSelectCol[20];
	CGroupView1PaintManager * m_pPaintManager;	
	void Refresh();
	afx_msg void OnReportStartItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);	
	void SetGNo(long nGNo){	m_nGNo = nGNo;}
	void SetChild(BOOL bChild){m_bChild = bChild;}
	virtual void OnInitialUpdate();
	void ReportDblClick();
};


