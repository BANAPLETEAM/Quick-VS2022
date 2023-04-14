#include "StdAfx.h"
#include "resource.h"
#include "MyCallMessage.h"
#include "RcpPageCTIForm.h"

CMyCallMessage::CMyCallMessage(CRcpPageCTIForm *pDlg)
{
	m_pDlg = pDlg;
}

CMyCallMessage::~CMyCallMessage(void)
{
}

LRESULT CMyCallMessage::SendMessage(UINT nMsg)
{
	if(m_pDlg)	
		return m_pDlg->SendMessage(WM_MY_CALL_MESSAGE, (WPARAM)this, (LPARAM)nMsg);
	else 
		return 0;
}

void CMyCallMessage::CallChange(int nType, char* szPhoneNumber, char* szKeyPhoneID, char* szDID)
{
	m_nType = nType;
	m_szPhoneNumber = szPhoneNumber;
	m_szKeyPhoneID = szKeyPhoneID;
	m_szDID = szDID;
	SendMessage(CALL_CHANGE);
}

void CMyCallMessage::SetCallNumber(char *szPhoneNumber)
{
	m_szPhoneNumber = szPhoneNumber;
	SendMessage(SET_CALL_NUMBER);
}

void CMyCallMessage::SetCallList(int nType, char* szPhoneNumber, char* szKeyPhoneID,
				 char* szDID, char* szOperator, char* szCustomer,
				 COleDateTime dtCur,
				 BOOL bRedraw)
{
	m_nType = nType;
	m_szPhoneNumber = szPhoneNumber;
	m_szKeyPhoneID = szKeyPhoneID;
	m_szDID = szDID;
	m_szOperator = szOperator;
	m_szCustomer = szCustomer;
	m_dtCur = dtCur;
	m_bRedraw = bRedraw;
	SendMessage(SET_CALL_LIST);
}

void CMyCallMessage::CustomerInfo(char* szPhoneNumber, char* strCName, char* sDesc)
{
	m_szPhoneNumber = szPhoneNumber;
	m_szCustomer = strCName;
	m_szDesc = sDesc;
	SendMessage(CUSTOMER_INFO);
}

void CMyCallMessage::RefreshQueueState()
{
	SendMessage(REFRESH_QUEUE);
}

LRESULT CMyCallMessage::Process(UINT nMsg)
{
	if(nMsg == SET_CALL_NUMBER)
	{
		//m_pDlg->SetCallNumber(m_szPhoneNumber);
	}
	else if(nMsg == CALL_CHANGE)
	{
		if(m_nType == PH_ANSWER)
		{
			m_pDlg->SearchRecvCID((char*)m_szPhoneNumber);
			m_pDlg->PopupRcpDlg((char*)m_szPhoneNumber, (char*)m_szKeyPhoneID, (char*)m_szDID);
		}
		else if(m_nType == PH_OUT_BOUND_CALL)
		{
			m_pDlg->SearchRecvCID((char*)m_szPhoneNumber);
		}
		else
		{
			m_pDlg->ClearRecvCIDFilter();
		}
	}
	else if(nMsg == SET_CALL_LIST)
	{
		m_pDlg->SetCallList(m_nType, m_szPhoneNumber, m_szKeyPhoneID, m_szDID, m_szOperator, m_szCustomer, m_dtCur, m_bRedraw);
		m_pDlg->SetOPState(m_nType, m_szPhoneNumber, m_szKeyPhoneID, m_szDID, m_szOperator, m_szCustomer, m_dtCur, m_bRedraw);
	}
	else if(nMsg == CUSTOMER_INFO)
	{
		CString strCustomer = m_szCustomer;
		CString strDepart = m_szDesc;
		if(strDepart.GetLength() > 1)
			strCustomer = strCustomer + "/" + strDepart;
		else
			strCustomer = strCustomer;

		m_pDlg->AddPhoneCustomer(m_szPhoneNumber, strCustomer);
		m_pDlg->SetLastRefresh();
		m_pDlg->m_wndReport.RedrawControl();
	}
	else if(nMsg == REFRESH_QUEUE)
	{
		m_pDlg->RefreshQueueState();
	}
	else if(nMsg == INTERNAL_CALL_POPUP)
	{
		/*CString strSend = m_szKeyPhoneID;
		CString strSendOP = m_szOperator;
		if(strSendOP.GetLength() > 1)
			strSend = strSendOP + "(" + strSend + ")";

		//m_pDlg->CheckInternalCall(strSend, m_szPhoneNumber);
		m_pDlg->PostMessage(WM_INTERNAL_CALL, (WPARAM)new CString(strSend), (LPARAM)m_szPhoneNumber);*/
	}

	return 0;
}

void CMyCallMessage::InternalCallPopup(char* szPhoneNumber, char* szOperator, char* szKeyPhoneID)
{
	m_szPhoneNumber = szPhoneNumber;
	m_szOperator = szOperator;
	m_szKeyPhoneID = szKeyPhoneID;
	SendMessage(INTERNAL_CALL_POPUP);
}