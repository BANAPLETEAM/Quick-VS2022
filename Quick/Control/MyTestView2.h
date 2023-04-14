#pragma once


// CMyTestView2 ���Դϴ�.
#include "MyXTPReportView.h"
#include "MyTestView1.h"






class CMyTestView2 : public CK2ReportView
{
	DECLARE_DYNCREATE(CMyTestView2)

protected:
	CMyTestView2();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CMyTestView2();

public:
	virtual void OnDraw(CDC* pDC);      // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
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


