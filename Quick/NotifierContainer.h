#pragma once


#include "StartbarNotifier.h"
#include <list>

typedef std::list<CStartbarNotifier*> LIST_NOTIFIER;

typedef struct _NotifierItem {
	UINT type;
	CString strIdentity;
	CString strCName;
	CString strMsg;
	CString strCompanyName;
	CString strName;
	int nCompanyCode;
	int nMNo;
	int nClientType;
	void *pVoid;
	CString strUniqueID;
	int nSendType;
} NOTIFIER_ITEM;

enum { NFI_RECV_MESSAGE = 0,
	   NFI_SEND_MESSAGE, 
	   NFI_RESERVE,
       NFI_ALLOC_MESSAGE,
	   NFI_RECV_MESSAGE2,
	   NFI_RECV_MESSAGE_INTERCALL,
	   NFI_QUERY_CHARGE,
	   NFI_QUERY_CHARGE_INTERCALL};


class CNotifierContainer : public CWnd
{
public:
	DECLARE_DYNAMIC(CNotifierContainer)

	CNotifierContainer(void);
	virtual ~CNotifierContainer(void);

	void AddNotifier(CStartbarNotifier *pNotifier);
	void RemoveNotifier(CStartbarNotifier *pNotifier);
	int Create(CWnd *pWndParent);

	LONG OnNotifierClicked(WPARAM wParam, LPARAM lParam);
	LONG OnNotifierHide(WPARAM wParam, LPARAM lParam);

	LONG GetNotifierCount() { return (LONG)m_listNotifier.size();}

protected:
	DECLARE_MESSAGE_MAP()

protected:
	LIST_NOTIFIER m_listNotifier;
	CRITICAL_SECTION m_csNotifier;

	CWnd *m_pWndParent;
	
};
