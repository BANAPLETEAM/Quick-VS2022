
#pragma once
#include "XTPListCtrl2.h"


#define TAKEROW 0
#define TAKETOTALROW 1
#define TAKEALLTOTALROW 2
#define GIVEROW 3
#define GIVETOTALROW 4
#define GIVEALLTOTALROW 5

#define LINE_ROW 0
#define GROUP_NAME_ROW 1

#define TRANSFER_DATE_COL 13
#define TRANSFER_STATE_COL 14
#define TRANSFER_ETC_COL 15


using namespace std;


class CMyXTPListCtrl_1 : public CXTPListCtrl2
{
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);
};

class CXTPListCtrl3 : public CXTPListCtrl2
{
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);
};

class CXTPListCtrl4 : public CXTPListCtrl2
{
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);
};

class CXTPListCtrl5 : public CXTPListCtrl2
{
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);
};

class CXTPListCtrl6 : public CXTPListCtrl2
{
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);
};

class CXTPListCtrl7 : public CXTPListCtrl2
{
public:
	//CFont *m_fontBig;
	//CFont *m_fontSmall;
	CXTPListCtrl7::CXTPListCtrl7()
	{
		//m_fontBig = m_FontManager.GetFont("∏º¿∫ ∞ÌµÒ", 18, FW_BOLD);;
		//m_fontSmall = m_FontManager.GetFont("∏º¿∫ ∞ÌµÒ", 16, FW_BOLD);;
	}

	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);
};

class CXTPListCtrl8 : public CXTPListCtrl2
{
public:
	CXTPListCtrl8::CXTPListCtrl8()
	{
		m_nRow = -1;
		m_nCol = -1;
	}

	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);
	
public:
	long m_nRow;
	long m_nCol;
	void SetSelectCol(long nRow, long nCol) {m_nRow = nRow; m_nCol = nCol;};
	long GetSelRow(){return m_nRow;};
	long GetSelCol(){return m_nCol;};
};


class CXTPListCtrl9 : public CXTPListCtrl2
{
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);
};

class CXTPListCtrl10 : public CXTPListCtrl2
{
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics); 

public:
	CString m_strSearchData;
	static CFont m_fontBold;
};

class CXTPListCtrl11 : public CXTPListCtrl2
{
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);	
};

class CXTPListCtrl13 : public CXTPListCtrl2
{
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);
};

class CXTPListCtrl15 : public CXTPListCtrl2
{
	virtual	void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);
};

class CXTPListCtrl16 : public CXTPListCtrl2
{
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);
};

class CXTPListCtrl17 : public CXTPListCtrl2
{
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);
};


class CMyXTPListCtrl_IF3 : public CXTPListCtrl2
{
public:
	CMyXTPListCtrl_IF3() {} 
	~CMyXTPListCtrl_IF3() {}

	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);
};

class CXTPListCtrl18 : public CXTPListCtrl2
{
public:
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);
	CString m_strSearchData;
};

class CXTPListCtrl19 : public CXTPListCtrl2
{
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS *pDrawArgs, XTP_GRIDRECORDITEM_METRICS *pItemMetrics);
};

class CXTPListCtrl20 : public CXTPListCtrl2
{
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS *pDrawArgs, XTP_GRIDRECORDITEM_METRICS *pItemMetrics);
};

class CGroupList24 : public CXTPGridControl
{
public:
	void SetSelected(long nGNo, BOOL bSelect);	
};


class CXTPListCtrl21 : public CXTPListCtrl2
{
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS *pDrawArgs, XTP_GRIDRECORDITEM_METRICS *pItemMetrics);
};

class CXTPListCtrl22 : public CXTPListCtrl2
{
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS *pDrawArgs, XTP_GRIDRECORDITEM_METRICS *pItemMetrics);
};

class CXTPListCtrl23 : public CXTPListCtrl2
{
	virtual void GetItemMetrics (XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);
};

class CXTPListCtrl24 : public CXTPListCtrl2
{
	virtual void GetItemMetrics (XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);
};

class CXTPListCtrl25 : public CXTPListCtrl2
{
	virtual void GetItemMetrics (XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);
};


class CXTPListCtrl26 : public CXTPListCtrl2
{
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);

public:
	long m_nRow;
	long m_nCol;
	void SetSelectCol(long nRow, long nCol) {m_nRow = nRow; m_nCol = nCol;};
	long GetSelRow(){return m_nRow;};
	long GetSelCol(){return m_nCol;};
};

class CXTPListCtrl27 : public CXTPListCtrl2
{
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);
};

class CXTPListCtrl28 : public CXTPListCtrl2
{
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);
};

class CXTPListCtrl29 : public CXTPListCtrl2
{
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);
};

class CXTPListCtrl30 : public CXTPListCtrl2
{
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);
};

class CXTPListCtrl31 : public CXTPListCtrl2
{
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);
};

class CXTPListCtrl32 : public CXTPListCtrl2
{
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);
};

class CXTPListCtrl34 : public CXTPListCtrl2
{
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);
};

class CXTPListCtrl35 : public CXTPListCtrl2
{
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);
};

class CXTPListCtrl36 : public CXTPListCtrl2
{
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);
};

class CXTPListCtrl37 : public CXTPListCtrl2
{
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);
};

class CXTPListCtrl38 : public CXTPListCtrl2
{
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);
};

class CXTPListCtrl39 : public CXTPListCtrl2
{
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);
};

class CXTPListCtrl40 : public CXTPListCtrl2
{
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);
};

class CXTPListCtrl41 : public CXTPListCtrl2
{
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);
};

class CXTPListCtrl42 : public CXTPListCtrl2
{
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);
};

class CXTPListCtrl43 : public CXTPListCtrl2
{
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);
};

class CXTPListCtrl44 : public CXTPListCtrl2
{
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);
};

class CXTPListCtrl45 : public CXTPListCtrl2
{
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);
}; 

class CXTPListCtrl46 : public CXTPListCtrl2
{
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);
}; 

class CXTPListCtrl47 : public CXTPListCtrl2
{
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);
};

class CXTPListCtrl48 : public CXTPListCtrl2
{
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);
};

class CXTPListCtrl49 : public CXTPListCtrl2
{
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);
};

class CXTPListCtrl50 : public CXTPListCtrl2
{
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);
};


class CXTPListCtrl55 : public CXTPListCtrl2
{
public:
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics)
	{
		long nType = GetItemLong(pDrawArgs->pRow->GetRecord());

		if(nType == 1)
			pItemMetrics->clrBackground = RGB(245, 200, 190);
		else if(nType == 2)
			pItemMetrics->clrBackground = RGB(200, 190, 245);

	}
};


class CCustomerGroupList : public CXTPListCtrl2
{
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);
};

class CGroupListReport24 : public CXTPListCtrl2
{
public:
	void SetGroupData(long nGNo, GROUP_REPORT st, BOOL bSumReport = FALSE);	
}; 

class CGroupList1 : public CXTPGridControl //æÍ¿« ø¯∑°¿Ã∏ß¿Ã CGroupList ¡ﬂ∫πµ«º≠ 1¿ª ∫Ÿ¿”
{
public:
	void SetSelected(long nGNo, BOOL bSelect);
};

class CGroupListReport : public CXTPGridControl
{
public:
	void SetGroupData(long nGNo, GROUP_REPORT st, BOOL bSumReport = FALSE);
};


class CXTPGridControl12 : public CXTPGridControl
{
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);
};

class CGroupList : public CXTPListCtrl2
{
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS *pDrawArgs, XTP_GRIDRECORDITEM_METRICS *pMetrics);
};

class CGroupList2 : public CXTPListCtrl2
{	
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS *pDrawArgs, XTP_GRIDRECORDITEM_METRICS *pItemMetrics);
};

class CustomerList :public CXTPListCtrl2
{
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS *pDrawArgs, XTP_GRIDRECORDITEM_METRICS *pMetrics);
};

class CMembers : public CXTPListCtrl2
{
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS *pDrawArgs, XTP_GRIDRECORDITEM_METRICS *pMetrics);

public:
	long m_nGNo;
	void SetGNo(long nGNo){m_nGNo = nGNo;}
};

class ChargeList : public CXTPListCtrl2
{
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS *pDrawArgs, XTP_GRIDRECORDITEM_METRICS *pMetrics);

public:
	long m_nChargeType;
	long m_nCarType;
	long m_nOGNo;

public :
	ChargeList::ChargeList()
	{
		m_nCarType = -1;
		m_nChargeType = -1;
		m_nOGNo = 0;
	}
};

class CMyMileageReport : public CXTPListCtrl2
{
public:
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);

	MAP_CUSTOMER_DATA m_mapData;
	MAP_ROW_DATA m_mapRow;
	void SetData(MAP_CUSTOMER_DATA &data){m_mapData = data;}
	void SetIndex(MAP_ROW_DATA &data){m_mapRow = data;}	
};