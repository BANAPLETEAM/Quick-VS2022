
#include "StdAfx.h"
#include "InsungCallPass.h"



CInsungCallPass::CInsungCallPass(void)
{
}

CInsungCallPass::~CInsungCallPass(void)
{
}

void CInsungCallPass::ToInsungCarType(int &nCarType)
{
	switch(nCarType)
	{
	case CAR_DAMA:
		nCarType = 1;
		break;
	case CAR_LABO:
		nCarType = 3;
		break;
	case CAR_VAN:
		nCarType = 2;
		break;
	case CAR_TRUCK:
		nCarType = 4;
		break;
	case CAR_SUBWAY:
		nCarType = 5;
		break;
	default:
		nCarType = 0;
		break;
	}
}

#define CHECK_HANDLE(hWnd, msg) g_bana_log->Print("체크중: %s\n", msg);\
	if(hWnd == NULL)\
	throw msg;

BOOL CInsungCallPass::CallPass(CMkDatabase *pMkDb, CInsungCallPassInfo &info)
{
	try
	{
		CDisplayBarThreadText bar(pMkDb->GetDisplayBarThread(), 
			"콜패스중입니다.\n마우스/키보드를 누르지 마십시오.", TRUE, 0);

		int nCount;
		HWND hRcpDlg, hTop, hRcpPageBtn, hRcpBtn, hMDIClient, hRcpState;
		HWND hRcpNewBtn, hCID, hPlaceGroup, hCustomer, hSDong;

		hTop = FindOutWindow("FNWND380", 0, 0, -1, "*", "인성퀵");
		CHECK_HANDLE(hTop, "인성프로그램 찾기 실패(실행후 로그인바람!)");

		hRcpPageBtn = FindOutControl(hTop, 1);
		CHECK_HANDLE(hRcpPageBtn, "메인탭 찾기 실패");

		hRcpBtn = FindOutControl(hRcpPageBtn, LAST_CHILD, 0, TRUE);
		CHECK_HANDLE(hRcpBtn, "접수등록 버튼 찾기 실패");
		SendButtonClick(hRcpBtn);

		hMDIClient = FindOutControl(hTop, 2);
		CHECK_HANDLE(hMDIClient, "MDI Client 찾기 실패");

		hRcpState = FindOutControl(hMDIClient, 1);
		CHECK_HANDLE(hRcpState, "접수현황 찾기 실패");

		hRcpNewBtn = FindOutControl(hRcpState, "접수", 7, NULL, &nCount);
		CHECK_HANDLE(hRcpNewBtn, "신규 등록 버튼 찾기 실패");
		SendButtonClick(hRcpNewBtn);

		hRcpDlg = FindOutWindow("FNWNS380", 0, 0, -1, "*", "신규", TRUE);
		CHECK_HANDLE(hRcpDlg, "신규창 찾기 실패");
		::SetForegroundWindow(hRcpDlg);
		::SetWindowPos(hRcpDlg, HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);

		hCID = FindOutControl(hRcpDlg, 9);
		CHECK_HANDLE(hCID, "CID박스 찾기 실패");
		::SetFocus(hCID);

		SendKeyToHandle(hCID, info.strCID);
		SendKey(VK_RETURN);

		Sleep(500);
		if((hCustomer = FindOutWindow("FNWNS380", 0, 0, -1, "*", "고객검색LIST", TRUE)) != NULL)
		{
			CDisplayBarThreadText bar(pMkDb->GetDisplayBarThread(), 
				"고객검색LIST를 선택하여 주시기 바랍니다.(10초경과시 진행취소됨)\n선택을 취소하면 오동작 될 수 있습니다.", TRUE, 0);

			if(!CloseWaitWindow(hCustomer, 10000))
				return FALSE;
		}

		hPlaceGroup = FindOutControl(hRcpDlg, "&Dby", 2, NULL, &nCount);
		CHECK_HANDLE(hPlaceGroup, "PlaceGroup 찾기 실패");

		Sleep(600);
		SetForegroundHwnd(hRcpDlg);
		TypingMessage(info.strSCompany);
		SendKey(VK_TAB);
		TypingMessage(info.strSDepart);
		SendKey(VK_TAB);
		TypingMessage(info.strSManager);
		SendKey(VK_TAB);
		TypingMessage(info.strSPhone);
		SendKey(VK_TAB);
		TypingMessage(info.strSDong);
		SendKey(VK_RETURN);

		Sleep(500);
		if((hSDong = FindOutWindow("FNWNS380", 0, 0, -1, "*", "동검색", TRUE)) != NULL)
		{
			CDisplayBarThreadText bar(pMkDb->GetDisplayBarThread(), 
				"출발지동을 선택하여 주시기 바랍니다.(5초경과시 진행취소됨)\n선택을 취소하면 오동작 될 수 있습니다.", TRUE, 0);

			if(!CloseWaitWindow(hSDong, 5000))
				return FALSE;
		}

		SendKeyShift(TRUE);
		SendKey(VK_TAB);
		SendKeyShift(FALSE);

		TypingMessage(info.strSDetail);
		SendKey(VK_TAB);

		TypingMessage(info.strDCompany);
		SendKey(VK_TAB);
		TypingMessage(info.strDDepart);
		SendKey(VK_TAB);
		TypingMessage(info.strDManager);
		SendKey(VK_TAB);
		TypingMessage(info.strDPhone);
		SendKey(VK_TAB);
		TypingMessage(info.strDDong);
		SendKey(VK_TAB);
		TypingMessage(info.strDDetail);
		SendKey(VK_TAB, 7);

		TypingMessage(info.strEtc);
		SendKey(VK_TAB, 2);
		SendKey(VK_SPACE);
		SendKey(VK_TAB, 3);

		SendKey(VK_RIGHT, info.nPayType);
		SendKey(VK_TAB);
		SendKey(VK_RIGHT, info.nCarType);
		SendKey(VK_TAB, 3);
		SendKey(VK_RIGHT, info.nWayType);
		SendKey(VK_TAB, 2);
		TypingMessage(info.nCharge);
		SendKey(VK_TAB, 3);

		if(info.nTransCharge)
			TypingMessage(info.nTransCharge);

		SendKey(VK_TAB, 2);
		SetForegroundHwnd(NULL);
		Sleep(500);

		return TRUE;
	}
	catch(char *szMsg)
	{
		CString strMsg;
		strMsg.Format("콜패스중에 오류가 발생했습니다.\n로지소프트로 문의바랍니다.\n[%s]", szMsg);
		MessageBox(NULL, strMsg, "확인", MB_ICONINFORMATION);
		return FALSE;
	}
}
