#pragma once


typedef struct {
	CString strKeyPhoneID;
	CString strOperator;
	int nState;
    CString strCurPhone;
	COleDateTime dtLastTime;
	CString strCustomer;
	COleDateTime dtLastAnswer;
	BOOL bARSLine;
} OP_STATE_INFO;

typedef map<CString, OP_STATE_INFO*> OP_STATE_MAP;



class COPStateRecordItem : public CXTPGridRecordItemText
{
public:
	COPStateRecordItem(CString strDummy):CXTPGridRecordItemText(strDummy)
	{
	}

public:
	OP_STATE_INFO *pOPState;
};


class COPStatePaintManager : public CXTPGridPaintManager
{
	friend class CXTPGridControl;

public:
	COPStatePaintManager();
	virtual ~COPStatePaintManager();


public:
	virtual void DrawItemCaption(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pMetrics);

	void DrawTextLine(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, CString strText,
						CRect rcItem, int nFlag, int& nCharCounter, int& nHyperlikCounter);

	int DrawString(int* pnCurrDrawPos, CDC* pDC, CString strDraw, CRect rcDraw, UINT nFormat, UINT nAlign = DT_LEFT);

	int DrawLink(int* pnCurrDrawPos, XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, CXTPGridHyperlink* pHyperlink,
						CString strText, CRect rcLink, int nFlag);

	virtual int GetRowHeight(CDC* pDC, CXTPGridRow* pRow);

public:
	BOOL m_bShowLastPhoneNumber;
	OP_STATE_MAP m_mapOPState;
	CFont *m_pfntNormal;
	CFont *m_pfntSmall;
};
