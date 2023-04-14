
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

#define CHECK_HANDLE(hWnd, msg) g_bana_log->Print("üũ��: %s\n", msg);\
	if(hWnd == NULL)\
	throw msg;

BOOL CInsungCallPass::CallPass(CMkDatabase *pMkDb, CInsungCallPassInfo &info)
{
	try
	{
		CDisplayBarThreadText bar(pMkDb->GetDisplayBarThread(), 
			"���н����Դϴ�.\n���콺/Ű���带 ������ ���ʽÿ�.", TRUE, 0);

		int nCount;
		HWND hRcpDlg, hTop, hRcpPageBtn, hRcpBtn, hMDIClient, hRcpState;
		HWND hRcpNewBtn, hCID, hPlaceGroup, hCustomer, hSDong;

		hTop = FindOutWindow("FNWND380", 0, 0, -1, "*", "�μ���");
		CHECK_HANDLE(hTop, "�μ����α׷� ã�� ����(������ �α��ιٶ�!)");

		hRcpPageBtn = FindOutControl(hTop, 1);
		CHECK_HANDLE(hRcpPageBtn, "������ ã�� ����");

		hRcpBtn = FindOutControl(hRcpPageBtn, LAST_CHILD, 0, TRUE);
		CHECK_HANDLE(hRcpBtn, "������� ��ư ã�� ����");
		SendButtonClick(hRcpBtn);

		hMDIClient = FindOutControl(hTop, 2);
		CHECK_HANDLE(hMDIClient, "MDI Client ã�� ����");

		hRcpState = FindOutControl(hMDIClient, 1);
		CHECK_HANDLE(hRcpState, "������Ȳ ã�� ����");

		hRcpNewBtn = FindOutControl(hRcpState, "����", 7, NULL, &nCount);
		CHECK_HANDLE(hRcpNewBtn, "�ű� ��� ��ư ã�� ����");
		SendButtonClick(hRcpNewBtn);

		hRcpDlg = FindOutWindow("FNWNS380", 0, 0, -1, "*", "�ű�", TRUE);
		CHECK_HANDLE(hRcpDlg, "�ű�â ã�� ����");
		::SetForegroundWindow(hRcpDlg);
		::SetWindowPos(hRcpDlg, HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);

		hCID = FindOutControl(hRcpDlg, 9);
		CHECK_HANDLE(hCID, "CID�ڽ� ã�� ����");
		::SetFocus(hCID);

		SendKeyToHandle(hCID, info.strCID);
		SendKey(VK_RETURN);

		Sleep(500);
		if((hCustomer = FindOutWindow("FNWNS380", 0, 0, -1, "*", "���˻�LIST", TRUE)) != NULL)
		{
			CDisplayBarThreadText bar(pMkDb->GetDisplayBarThread(), 
				"���˻�LIST�� �����Ͽ� �ֽñ� �ٶ��ϴ�.(10�ʰ���� ������ҵ�)\n������ ����ϸ� ������ �� �� �ֽ��ϴ�.", TRUE, 0);

			if(!CloseWaitWindow(hCustomer, 10000))
				return FALSE;
		}

		hPlaceGroup = FindOutControl(hRcpDlg, "&Dby", 2, NULL, &nCount);
		CHECK_HANDLE(hPlaceGroup, "PlaceGroup ã�� ����");

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
		if((hSDong = FindOutWindow("FNWNS380", 0, 0, -1, "*", "���˻�", TRUE)) != NULL)
		{
			CDisplayBarThreadText bar(pMkDb->GetDisplayBarThread(), 
				"��������� �����Ͽ� �ֽñ� �ٶ��ϴ�.(5�ʰ���� ������ҵ�)\n������ ����ϸ� ������ �� �� �ֽ��ϴ�.", TRUE, 0);

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
		strMsg.Format("���н��߿� ������ �߻��߽��ϴ�.\n��������Ʈ�� ���ǹٶ��ϴ�.\n[%s]", szMsg);
		MessageBox(NULL, strMsg, "Ȯ��", MB_ICONINFORMATION);
		return FALSE;
	}
}
