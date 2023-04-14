
#pragma once



#define TAB_FORM_HEIGHT 150
#define TAB_FORM_HEIGHT_BIG	500
#define CALL_TO_RIDER 30
#define CALL_TO_CUSTOMER 40


typedef map<CRcpDlg*, CRcpDlg*> RCP_DLG_MAP;
typedef map<CString,COleDateTime> RECV_PHONE_LIST_MAP;


typedef struct {
	int nState;
	long nTNo;
	CString strCName;
	CString strStart;
	CString strDest;
	COleDateTime dt0;
	COleDateTime dt1;
	BOOL bDoc;
	int nKDelivery;
	int nRNo;
	COleDateTime dt2;
	COleDateTime dt3;
	long nTotal;
	long nAPay;
	CString strEtc;
	COleDateTime dtFinal;
	CString strDName;
	long nCompany;
	BOOL bInternet;
	long nRiderCompany;
	long nAllocGroup;
	long nCNo;
	long nWNo;
	CString strRName;
	CString strManager;
} ORDER_INFO;

typedef enum { RT_TODAY = 0, RT_PREDATE, RT_CID_CALL, RT_TODAY_SHARE} REFRESH_TYPE;

class CRcpFormTabControl : public CXTPTabControl
{
protected:
	virtual void OnItemClick(CXTPTabManagerItem* pItem);
};
