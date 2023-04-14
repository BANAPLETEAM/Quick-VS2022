#pragma once


class CStateRecordItem : public CXTPGridRecordItemText
{
public:
	CStateRecordItem::CStateRecordItem()
	{
		m_bApply = TRUE;
		m_nTNo = 0;
	}
public:
	CStateRecordItem(CString strDummy):CXTPGridRecordItemText(strDummy)
	{
		m_bApply = TRUE;
		m_nTNo = 0;
	}

public:
	CBranchInfo *pBi;
	long m_nDay;
	long m_nTNo;
	BOOL m_bApply;
	COleDateTime m_dt1;
};

class CMyPaintManager : public CXTPGridPaintManager
{
public:
	CMyPaintManager();
	virtual ~CMyPaintManager(void);
public:
	int GetRowHeight(CDC* /*pDC*/, CXTPGridRow* pRow);
	virtual void DrawItemCaption(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pMetrics);
};
