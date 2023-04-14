// MyMkMessenger.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "MyMkMessenger.h"
#include "RiderMapDlg.h"
#include "AllocateBoardDlg.h"
#include "QueryChargeDlg.h"
#include "RcpCopyData.h"
#include <Mmsystem.h>
#include "POIData.h"
#include "RcpView.h"
#include "MainFrm.h"
#include "NotifierContainer.h"

#pragma comment(lib, "winmm.lib")


#define PST_SERVER_RIDER_POS_MSG		370		//기사위치메시지 메신저 연동
#define PST_SERVER_RIDER_CONN_STATE_MSG      368            //기사 NETWORKSTATE 메신져 연동

// CMyMkMessenger

IMPLEMENT_DYNAMIC(CMyMkMessenger, CMkMessenger)
CMyMkMessenger::CMyMkMessenger(CWnd *pParent) : CMkMessenger(pParent)
{
}

CMyMkMessenger::~CMyMkMessenger()
{
}


BEGIN_MESSAGE_MAP(CMyMkMessenger, CMkMessenger)
END_MESSAGE_MAP()



// CMyMkMessenger 메시지 처리기입니다.

BOOL CMyMkMessenger::OnRecvOKProtocol(QPACKET *p)
{
	if(p->nSubType == PST_SERVER_RIDER_POS_MSG)
	{
		OnServerRiderPosMsg(p->data);
	}
	else if(p->nSubType == PST_EDIT_ORDER)
	{
		OnRecvEditOrderState(p->data);
	}
	else if(p->nSubType == PST_SERVER_WORK_REPORT_MSG)
	{
		OnRiderWorkReportMsg(p->data);
	}
	else if(p->nSubType == PST_SERVER_RIDER_CONN_STATE_MSG)
	{
		OnRiderConnState(p->data);
	}

	return TRUE;
}


BOOL CMyMkMessenger::OnRecvUserProtocol(long nCompany, long nMNo, BOOL bIntercall, 
									  char *szCompanyName, char *szName, char *szMsg)
{
	BOOL bHandled = TRUE;

	if(CheckString(szMsg, "$$%QUERYCHARGE"))
	{
		OnQueryCharge(nCompany, nMNo, szCompanyName, szName, szMsg);
	}
	if(CheckString(szMsg, "$$%GROUP_CHAT"))
	{
		OnGroupChat(nCompany, nMNo, szCompanyName, szName, szMsg);
	}
	else if(CheckString(szMsg, "$$%RESPONSECHARGE")) 
	{
		bHandled = OnResponseCharge(szMsg);
	}
	else if(CheckString(szMsg, "$$%RCPCOPYDATA"))
	{
		OnRcpCopyData(szName, szMsg);
	}
	else if(CheckString(szMsg, "$$%QUERYINTERCALLCHARGE"))
	{
		OnQueryCharge(nCompany, nMNo, szCompanyName, szName, szMsg);
	}
	else if(CheckString(szMsg, "$$%INTERCALL_RECEIPT"))
	{
		
		OnInterCallReceipt(szMsg);
	}
	return bHandled;
}
void CMyMkMessenger::OnInterCallReceipt(char *szMsg)
{	
	CString strTitle, strMsg;
	char szINS[30];
	char cno[12], cname[30], szStart[30], szDest[30];
	if(STRTOK2("^&",szMsg,0, szINS,  cno, cname, szStart, szDest, VL_END)) 
	{
		strTitle.Format("인터넷 접수 (%s)", strlen(cname) > 0 ? cname : "알수없음");
		strMsg.Format("%s->%s(%s) 접수확인바람", szStart, szDest, cno);
		

		NOTIFIER_ITEM *pNItem = new NOTIFIER_ITEM;
		pNItem->type = NFI_RESERVE;
		pNItem->strIdentity = cno;
		pNItem->strCName = strlen(cname) > 0 ? cname : "알수없음";

		CStartbarNotifier *pNotifier = new CStartbarNotifier;
		pNotifier->Create(m_pnfc);
		pNotifier->DefaultSetting();
		pNotifier->Initailze(strTitle, strMsg, 0, 300000, 0, 2);
		pNotifier->SetItemData((void*)pNItem);
		m_pnfc->AddNotifier(pNotifier);


		MyPlaySound();
	}
}

void CMyMkMessenger::OnGroupChat(long nCompany, long nMNo, char *szCompanyName, char *szName, char *szMsg)
{
	char szTemp[30];
	char szText[1024];

	if(STRTOK2("^&", szMsg, 0, szTemp, szText, VL_END))
	{
		AfxGetMainWnd()->PostMessage(WM_USER+890, (WPARAM)szName, LPARAM(szText));
	}
}

void CMyMkMessenger::OnQueryCharge(long nCompany, long nMNo, char *szCompanyName, char *szName, char *szMsg)
{
	CString strTitle;
	char szINS[30];
	char szUniqueID[10], szCName[50], szStart[200];
	char szStartDong[200], szDest[200], szDestDong[200];

	if(STRTOK2("^&", szMsg, 0, szINS, szUniqueID, szCName, szStart, szStartDong, 
		szDest, szDestDong, VL_END))
	{ 
		CString sStartDong = IsNumeric(szStartDong) == TRUE ? m_poiNew.GetPOI(atoi(szStartDong))->GetDong() : szStartDong;
		CString sDestDong = IsNumeric(szDestDong) == TRUE ? m_poiNew.GetPOI(atoi(szDestDong))->GetDong() : szDestDong;
		CString sStartDisplay = IsNumeric(szStartDong) == TRUE ? m_poiNew.GetPOI(atoi(szStartDong))->GetRegionName() : szStartDong;
		CString sDestDisplay = IsNumeric(szDestDong) == TRUE ? m_poiNew.GetPOI(atoi(szDestDong))->GetRegionName() : szDestDong;
 
		CQueryChargeDlg *pDlg = new CQueryChargeDlg;
		pDlg->m_strCustomer = szCName;
		pDlg->m_strStart = szStart;
		pDlg->m_strStartDong = sStartDisplay;
		pDlg->m_strDest = szDest;
		pDlg->m_strDestDong = sDestDisplay;
		pDlg->m_strOP.Format("- %s(%d)님으로 부터의 요금문의", szName, nMNo);
		pDlg->m_nMNo = nMNo;

		NOTIFIER_ITEM *pNItem = new NOTIFIER_ITEM;
		pNItem->type = nMNo > 30000 ? NFI_QUERY_CHARGE_INTERCALL : NFI_QUERY_CHARGE;
		pNItem->strCName = CString("요금문의(") + szCName + ")";
		pNItem->strMsg = sStartDong + "->" + sDestDong;
		pNItem->strCompanyName = szCompanyName;
		pNItem->strName = szName;
		pNItem->nCompanyCode = nCompany;
		pNItem->nMNo = nMNo;
		pNItem->nClientType = 0;
		pNItem->pVoid = (void*)pDlg;
		pNItem->strUniqueID = szUniqueID;

		strTitle.Format("메시지(%s):", pNItem->strCName.GetLength() > 0 ? 
			pNItem->strCName : "알수없음");

		CStartbarNotifier *pNotifier = new CStartbarNotifier;
		pNotifier->Create(m_pnfc);
		pNotifier->DefaultSetting();
		pNotifier->Initailze(CString("요금문의(") + szCName + ")", CString(sStartDong) + "->" + sDestDong, 0, 300000, 0, 2);
		pNotifier->SetItemData((void*)pNItem);
		m_pnfc->AddNotifier(pNotifier);
		MyPlaySound();
	}
}

BOOL CMyMkMessenger::OnResponseCharge(char *szMsg)
{
	char szINS[20], szUniqueID[20], szCharge[20], szEtc[255], szSave[10] = {0,};

	BOOL bSuccess = FALSE;
	if(CheckString(szMsg, "$$%RESPONSECHARGE2"))
	{
		bSuccess = STRTOK2("^&", szMsg, 0, szINS, szUniqueID, szCharge, szEtc, szSave, VL_END);
	}
	else
	{
		bSuccess = STRTOK2("^&", szMsg, 0, szINS, szUniqueID, szCharge, szEtc, VL_END);
	}

	if(bSuccess)
	{
		AfxGetMainWnd()->PostMessage(WM_USER+887, atol(szUniqueID), atol(szCharge));
		MyPlaySound();

		if(strlen(szEtc) > 0)
		{
			strcpy(szMsg, szEtc);
			return FALSE;
		}
	}

	return TRUE;
}

void CMyMkMessenger::OnRcpCopyData(char *szName, char *szMsg)
{
	CRcpCopyData *pRcpCopyData = new CRcpCopyData;
	pRcpCopyData->PacketToMap(szMsg);
	pRcpCopyData->InsertData("SEND_OP", szName);
	AfxGetMainWnd()->PostMessage(WM_USER+888, (WPARAM)pRcpCopyData, (LPARAM)0);
}


void CMyMkMessenger::OnServerRiderPosMsg(char *pData)
{
#ifdef _QUICK
	char szShareCode1[10], szCompanyCode[10], szRNo[10], szDtConn[10];
	char szConnDongID[10], szPosName[50], szPosX[20], szPosY[20];
	char szGpsUsage[10], szGugun[50], szDong[50];
	char szDongPosX[20], szDongPosY[20], szRealPosX[20], szRealPosY[20];
	char szName[50], szCarType[10], szDeviceType[50], szDeviceName[50], szVersion[50], szOS[50];
	char szPhone[30], szCity[30];
	char szTruckType[20] = {0, };
	char szTon[20] = {0, };
	CString strDeviceType, strDeviceName;
	long nPos;

	if(nPos = STRTOK(pData, 0, 
		szShareCode1, 
		szCompanyCode, 
		szRNo,  
		szDtConn, 
		szConnDongID,  
		szPosName, 
		szPosX,  
		szPosY,  
		szGpsUsage,  
		szGugun, 
		szDong,  
		szDongPosX,  
		szDongPosY,  
		szRealPosX,  
		szRealPosY,  
		szGpsUsage,
		szName,  
		szCarType, 
		szDeviceType,
		szDeviceName, 
		szOS, 
		szVersion,
		szPhone,
		szCity,
		VL_END))
	{
		CRealTimeRiderPos pos;
		pos.nPosX = atol(szDongPosX);
		pos.nPosY = atol(szDongPosY);

		STRTOK(pData, nPos, szTruckType, szTon, VL_END);
		LU->GpsPosRevision(pos.nPosX, pos.nPosY, atol(szDeviceType), szDeviceName, szVersion);

		if(AfxGetMainWnd())
		{
			pos.nCompany = atol(szCompanyCode);
			pos.nRNo = atol(szRNo);
			pos.strName = szName;
			pos.bUseGps = atol(szGpsUsage);
			pos.cartype.nCarType = atol(szCarType);
			pos.cartype.nTruckType = atol(szTruckType);
			pos.cartype.strTon = (atof(szTon) == 0) ? "" : szTon;
			pos.strPosName = szPosName;
			pos.strDeviceName = szDeviceName;
			pos.strOS = szOS;
			pos.strVersion = szVersion;
			pos.strPhone = szPhone;
			pos.strCity = szCity;

			if(LU->GetRiderMapDlg())
				LU->GetRiderMapDlg()->SetRiderPosRealTime(pos);

			if(LU->GetAllocateBoardDlg())
				LU->GetAllocateBoardDlg()->SetRiderPosRealTime(pos);

			LU->AddRiderPos(pos);

			for(int i = 0; i < m_arrRecvRiderPosWnd.GetCount(); i++)
			{
				CWnd *pWnd = (CWnd*)m_arrRecvRiderPosWnd.GetAt(i);
				if(pWnd->GetSafeHwnd())
					pWnd->PostMessage(WM_REFRESH_RIDER_POS, pos.nCompany, pos.nRNo);
			}
		}

		//g_bana_log->Print("* %s %s %s %s %s %s %s\n", szRNo, szName, szDongPosX, szDongPosY, szPosName, szDtConn, szGpsUsage);
	}
#endif
}

void CMyMkMessenger::OnRecvEditOrderState(char *pData)
{
	char szTNo[20], szTickCount[20], szState[20], szWName[512];

	if(STRTOK(pData, 0, szTNo, szTickCount, szState, szWName, VL_END))
	{
		if(AfxGetMainWnd())
		{
			((CMainFrame*)AfxGetMainWnd())->OnRecvEditOrderState(
						atol(szTNo), atol(szTickCount), atol(szState), szWName);
		}
	}
}

void CMyMkMessenger::SendEditOrderState(long nTNo, int nState)
{
	char data[1024], szTNo[20], szState[20];
	STRCPY(data, ltoa(nTNo, szTNo, 10), ltoa(nState, szState, 10), "", "", VL_END);
	GetDatabase()->GetSocket()->SendData(PT_REQUEST, PST_EDIT_ORDER, data);
}

void CMyMkMessenger::OnRiderWorkReportMsg(char *pData)
{
#ifdef _QUICK

	BOOL bRecv = AfxGetApp()->GetProfileInt("RcpPage", "RecvAttendMsg", 1);

	char szShareCode1[20], szCompanyCode[20], szRNo[20], szState[20];

	if(STRTOK(pData, 0, szShareCode1, szCompanyCode, szRNo, szState, VL_END))
	{
		if(AfxGetMainWnd())
		{
			if(LU->GetAllocateBoardDlg())
			{
				LU->GetAllocateBoardDlg()->SetRiderWorkReport(
					atol(szCompanyCode), atol(szRNo), atol(szState));
			} 

			if(bRecv == FALSE)
				return;

			NOTIFIER_ITEM *pNItem = new NOTIFIER_ITEM;
			pNItem->type = NFI_ALLOC_MESSAGE;
			pNItem->strCName = "";
			pNItem->strMsg.Format("%s번 기사님 %s보고 하였습니다.", szRNo, 
						atol(szState) == 1 ? "출근" : "퇴근");

			g_bana_log->Print(pNItem->strMsg  + "\r\n");

			PlaySound(MAKEINTRESOURCE(IDR_ALLOCATE_WAV), 
				AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);

			CStartbarNotifier *pNotifier = new CStartbarNotifier;
			pNotifier->Create(m_pnfc);
			pNotifier->SetSkin(IDB_SKIN_ATTEND_NOTICE);
			pNotifier->SetTextFont("돋움", 110,TN_TEXT_NORMAL,TN_TEXT_UNDERLINE);
			pNotifier->SetTitleTextColor(RGB(120, 170, 0));
			pNotifier->SetTextColor(RGB(120, 170, 0),RGB(0,0,200));
			pNotifier->SetTextRect(CRect(94,6, 295, 20));
			pNotifier->Initailze("", pNItem->strMsg, 0, 10000, 0, 2);
			pNotifier->SetItemData((void*)pNItem);
			m_pnfc->AddNotifier(pNotifier);
		}		
	}
#endif
}

void CMyMkMessenger::OnRiderConnState(char *pData)
{
#ifdef _QUICK

	char szRealShareCode1[10];
	char szCompanyCode[10];
	char szRNo[10];
	char szState[10];

	if(STRTOK(pData, 0, 
		szRealShareCode1, 
		szCompanyCode, 
		szRNo,  
		szState, VL_END))
	{
		if(AfxGetMainWnd())
		{
			if(LU->GetRiderMapDlg())
			{
				LU->GetRiderMapDlg()->SetRiderConnState(
					atol(szCompanyCode), atol(szRNo), atol(szState));
			}

			if(LU->GetAllocateBoardDlg())
			{
				LU->GetAllocateBoardDlg()->SetRiderConnState(
					atol(szCompanyCode), atol(szRNo), atol(szState));
			}
		}
	}	
#endif 
}

void CMyMkMessenger::AddRecvRiderPosWnd(CWnd *pWnd)
{
	for(int i = 0; i < m_arrRecvRiderPosWnd.GetCount(); i++)
	{
		if(m_arrRecvRiderPosWnd.GetAt(i) == pWnd)
			return;
	}
	m_arrRecvRiderPosWnd.Add(pWnd);
}

void CMyMkMessenger::DeleteRiderPosWnd(CWnd *pWnd)
{
	for(int i = 0; i < m_arrRecvRiderPosWnd.GetCount(); i++)
	{
		if(m_arrRecvRiderPosWnd.GetAt(i) == pWnd)
		{
			m_arrRecvRiderPosWnd.RemoveAt(i);
			return;
		}
	}
}

void CMyMkMessenger::CopyRecvRiderPosArray(CMyMkMessenger *pMsg)
{
	for(int i = 0; i < m_arrRecvRiderPosWnd.GetCount(); i++)
		pMsg->AddRecvRiderPosWnd((CWnd*)m_arrRecvRiderPosWnd.GetAt(i));
}