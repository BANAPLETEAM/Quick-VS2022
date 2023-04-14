#pragma once

// CMyMkMessenger
#include "MkMessenger.h"

#define PST_SERVER_WORK_REPORT_MSG		375		//기사 출/퇴근보고 메세지
#define	PST_EDIT_ORDER					376		//수정모드

enum { EOS_GET_STATE = 0, EOS_EDITING = 1, EOS_END_EDIT = 2, EOS_CANCEL_EDIT = 3};

class CMyMkMessenger : public CMkMessenger
{
	DECLARE_DYNAMIC(CMyMkMessenger)

public:
	CMyMkMessenger(CWnd *pParent);
	virtual ~CMyMkMessenger();

public:
	virtual BOOL OnRecvOKProtocol(QPACKET *p);
	virtual BOOL OnRecvUserProtocol(long nCompany, long nMNo, BOOL bIntercall, 
			char *szCompanyName, char *szName, char *szMsg);

protected:
	DECLARE_MESSAGE_MAP()

	void OnServerRiderPosMsg(char *pData);
	void OnGroupChat(long nCompany, long nMNo, char *szCompanyName, char *szName, char *szMsg);
	void OnQueryCharge(long nCompany, long nMNo, char *szCompanyName, char *szName, char *szMsg);
	BOOL OnResponseCharge(char *szMsg);
	void OnRcpCopyData(char *szName, char *szMsg);
	void OnRecvEditOrderState(char *pData);
	void OnRiderWorkReportMsg(char *pData);
	void OnRiderConnState(char *pData);
	void OnInterCallReceipt(char *szMsg);

	CPtrArray m_arrRecvRiderPosWnd;
public:
	void SendEditOrderState(long nTNo, int State);
	void AddRecvRiderPosWnd(CWnd *pWnd);
	void DeleteRiderPosWnd(CWnd *pWnd);
	void CopyRecvRiderPosArray(CMyMkMessenger *pMsg);
};


