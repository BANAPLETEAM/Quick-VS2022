#include "stdafx.h"
#include "IPass.h"
#include "RcpDlg.h"
#include "RcpPlaceInfo.h"

CIPass::CIPass(CRcpDlg *pRcpDlg)
{
	m_pRcpDlg = pRcpDlg;
}


CIPass::~CIPass()
{
}

void CIPass::GetAllWindowsFromProcessID(DWORD dwProcessID, std::vector <HWND> &vhWnds)
{
	// find all hWnds (vhWnds) associated with a process id (dwProcessID)
	HWND hCurWnd = NULL;
	do
	{
		hCurWnd = ::FindWindowEx(NULL, hCurWnd, NULL, NULL);
		DWORD dwProcessIDFind = 0;
		GetWindowThreadProcessId(hCurWnd, &dwProcessIDFind);
		if (dwProcessIDFind == dwProcessID)	{
			vhWnds.push_back(hCurWnd);  // add the found hCurWnd to the vector			
		}
	} while (hCurWnd != NULL);
}


HWND CIPass::FindExe()
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshot)
	{
		PROCESSENTRY32 ProcessEntry32;
		BOOL bProcessFound;
		ProcessEntry32.dwSize = sizeof(PROCESSENTRY32);
		bProcessFound = Process32First(hSnapshot, &ProcessEntry32);
		while (bProcessFound)
		{
			CString strProg(ProcessEntry32.szExeFile);

			if (strProg == "IsQuick.exe")
			{
				std::vector <HWND> vecHwnd;
				GetAllWindowsFromProcessID(ProcessEntry32.th32ProcessID, vecHwnd);

				for (int i = 0; i < vecHwnd.size(); i++)
				{
					CWnd *pWnd = CWnd::FromHandle(vecHwnd.at(i));

					CString s; pWnd->GetWindowText(s);

					if (s.Find("�μ� �� ����") >= 0)
					{
						return vecHwnd.at(i);
					}
				}
			}

			bProcessFound = Process32Next(hSnapshot, &ProcessEntry32);
		}
		CloseHandle(hSnapshot);
	}

	return 0;
}

BOOL CIPass::ClickRcpDlg()
{
	HWND hwndMain = FindExe();
	//HWND hwndMain1 = ::FindWindow(NULL, "�μ� �� ���� [�ùٷ�] / [(��)�ùٷμ���-(��)�ùٷμ���]");

	if (!hwndMain) {
		return FALSE;
	}
	
	CWnd *pWnd = CWnd::FromHandle(hwndMain);


	CWnd *pChildWnd = pWnd->GetWindow(GW_CHILD);
	while (pChildWnd != NULL && pChildWnd->GetSafeHwnd()) {
		CWnd *pChildSubWnd = pChildWnd->GetWindow(GW_CHILD);
		while (pChildSubWnd != NULL && pChildSubWnd->GetSafeHwnd()) {
			CString strCaption;
			pChildSubWnd->GetWindowText(strCaption);

			if (strCaption == "������Ȳ") {
				CWnd *pWndRcpView = GetSubWnd(pChildSubWnd, 23);
				CWnd *pRcpBtn = GetSubWnd(pWndRcpView, 5);

				if(pRcpBtn == NULL) {
					pWndRcpView = GetSubWnd(pChildSubWnd, 22);
					pRcpBtn = GetSubWnd(pWndRcpView, 5);

				}

				if(pRcpBtn) {
					::SendMessage(pRcpBtn->GetSafeHwnd(), WM_LBUTTONDOWN, 0, 0);
					::SendMessage(pRcpBtn->GetSafeHwnd(), WM_LBUTTONUP, 0, 0);
					return TRUE;
				}
				return FALSE;				
			}
			pChildSubWnd = pChildSubWnd->GetWindow(GW_HWNDNEXT);
		}

		pChildWnd = pChildWnd->GetWindow(GW_HWNDNEXT);
	}

	return FALSE;
}

CWnd* CIPass::GetRcpWnd()
{
	HWND hwndMain = ::FindWindow(NULL, "��������(�ű�) ");
	return CWnd::FromHandle(hwndMain);
}

void CIPass::PassData()
{
	try {
		CString strTemp;
		long nS = GetTickCount();
		CWnd *pRcpWnd = GetRcpWnd();
		CWnd *pRcpDataMain = GetSubWnd(pRcpWnd, 1);
		CWnd *pRcpDataWnd = GetSubWnd(pRcpDataMain, 1);

		CWnd *pChargeWnd = GetSubWnd(pRcpDataWnd, 0);
		pChargeWnd = GetSubWnd(pChargeWnd, 2);

		CWnd *pOptionWnd = GetSubWnd(pRcpDataWnd, 0);
		pOptionWnd = GetSubWnd(pOptionWnd, 3);

		CWnd *pPerson = GetSubWnd(pRcpDataWnd, 1);

		CWnd *pChildOrder = GetSubWnd(pPerson, 2);
		CWnd *pChildStart = GetSubWnd(pPerson, 1);
		CWnd *pChildDest = GetSubWnd(pPerson, 0);

		InsertOrderData(pChildOrder);
		InsertStartData(pChildStart);
		InsertDestData(pChildDest);
		InsertChargeData(pChargeWnd);
		InsertOptionData(pOptionWnd);

		CWnd *pOptionOrderMemo = GetSubWnd(pRcpDataWnd, 0);
		pOptionOrderMemo = GetSubWnd(pOptionOrderMemo, 0);
		pOptionOrderMemo = GetSubWnd(pOptionOrderMemo, 0);
		pOptionOrderMemo = GetSubWnd(pOptionOrderMemo, 1);
		::SendMessage(pOptionOrderMemo->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)::GetStringFromEdit(&m_pRcpDlg->m_edtIntercallEtc));

		CWnd *pRcpDataTitle = GetSubWnd(pRcpDataMain, 3);
		pRcpDataTitle = GetSubWnd(pRcpDataTitle, 3);
		pRcpDataTitle = GetSubWnd(pRcpDataTitle, 0);
		strTemp = m_pRcpDlg->m_strCID;
		strTemp.Replace("-", "");
		::SendMessage(pRcpDataTitle->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)strTemp);
		

		long nS1 = GetTickCount();
		long nS2 = 0;
	}
	catch(int){

	}
}

CWnd* CIPass::GetSubWnd(CWnd *pWnd, long nIndex)
{
	if(!pWnd)
		return NULL;

	CWnd *pChildWnd = pWnd->GetWindow(GW_CHILD);
	long nCount = 0;

	while (pChildWnd != NULL && pChildWnd->GetSafeHwnd()) {
		if (nCount++ == nIndex) {
			return pChildWnd;
		}

		pChildWnd = pChildWnd->GetWindow(GW_HWNDNEXT);
	}

	return NULL;
}

long CIPass::GetPayTypeI()
{
	//����,���� ���� ��� �ſ�����
	if(m_pRcpDlg->GetPayTypeNew() == PAY_PRE)	 return 10;
	if(m_pRcpDlg->GetPayTypeNew() == PAY_AFTER)  return 100;
	
	return 150;

	// 10 ����, 100����. 150�ſ� //200�۱� // 250���� // 300 ī��
	/*
	if(m_pRcpDlg->GetPayTypeNew() == PAY_PRE)	 return 10;
	if(m_pRcpDlg->GetPayTypeNew() == PAY_AFTER)  return 100;
	if(m_pRcpDlg->GetPayTypeNew() == PAY_CREDIT) return 150;
	if(m_pRcpDlg->GetPayTypeNew() == PAY_ONLINE) return 200;
	if(m_pRcpDlg->GetPayTypeNew() == PAY_DIRECT) return 250;
	if(m_pRcpDlg->GetPayTypeNew() == PAY_CARD)	 return 300;

	return 10;
	*/
}

long CIPass::GetCarTypeI()
{
	if(m_pRcpDlg->GetCarTypeNew() == CAR_AUTO)	  return 10;
	if(m_pRcpDlg->GetCarTypeNew() == CAR_BIGBIKE) return 10;
	if(m_pRcpDlg->GetCarTypeNew() == CAR_DAMA)	  return 100;
	if(m_pRcpDlg->GetCarTypeNew() == CAR_LABO)	  return 200;
	if(m_pRcpDlg->GetCarTypeNew() == CAR_VAN)     return 150;
	if(m_pRcpDlg->GetCarTypeNew() == CAR_6VAN)    return 150;
	if(m_pRcpDlg->GetCarTypeNew() == CAR_TRUCK)   return 250;
	if(m_pRcpDlg->GetCarTypeNew() == CAR_1_4_TON) return 250;
	if(m_pRcpDlg->GetCarTypeNew() == CAR_2_5_TON) return 250;
	if(m_pRcpDlg->GetCarTypeNew() == CAR_3_5_TON) return 250;
	if(m_pRcpDlg->GetCarTypeNew() == CAR_5_TON)   return 250;
	if(m_pRcpDlg->GetCarTypeNew() == CAR_11_TON)  return 250;
	if(m_pRcpDlg->GetCarTypeNew() == CAR_18_TON)  return 250;
	if(m_pRcpDlg->GetCarTypeNew() == CAR_25_TON)  return 250;
	if(m_pRcpDlg->GetCarTypeNew() == CAR_SUBWAY)  return 300;

	return 10;
}

long CIPass::GetRunTypeI()
{
	if(m_pRcpDlg->GetWayTypeNew() == WAY_TWO)	  return 80;
	if(m_pRcpDlg->GetWayTypeNew() == WAY_SEVERAL)	  return 120;
	if(m_pRcpDlg->GetRunTypeNew() == RUN_FAST)	  return 170;
	if(m_pRcpDlg->GetRunTypeNew() == RUN_VERY_FAST)	  return 170;

	return 10;
}

void CIPass::InsertOptionData(CWnd *pWnd)
{
	CWnd *pChildWnd = pWnd->GetWindow(GW_CHILD);
	long nCount = 0;

	while (pChildWnd != NULL && pChildWnd->GetSafeHwnd())
	{
		CWnd *pTemp;
		if(nCount == 2)
		{
			// 10 ����, 100�ٸ�. 150�� //200�� // 250Ʈ�� // 300 ����ö
			::SendMessage(pChildWnd->GetSafeHwnd(), WM_LBUTTONDOWN, 0, MAKELPARAM(GetCarTypeI(), 10));
			::SendMessage(pChildWnd->GetSafeHwnd(), WM_LBUTTONUP, 0, MAKELPARAM(GetCarTypeI(), 10)); //CarTyper
		}
		else if(nCount == 3)
		{
			// 10 ����, 100����. 150�ſ� //200�۱� // 250���� // 300 ī��
			::SendMessage(pChildWnd->GetSafeHwnd(), WM_LBUTTONDOWN, 0, MAKELPARAM(GetPayTypeI(), 10));
			::SendMessage(pChildWnd->GetSafeHwnd(), WM_LBUTTONUP, 0, MAKELPARAM(GetPayTypeI(), 10)); //PayType
		}
		else if(nCount == 8)
		{
			::SendMessage(pChildWnd->GetSafeHwnd(), WM_LBUTTONDOWN, 0, 0);
			::SendMessage(pChildWnd->GetSafeHwnd(), WM_LBUTTONUP, 0, 0); //����üũ
		}
		else if(nCount == 13)
		{
			//10�� 80 �պ� 120 ���� 170 ���
			::SendMessage(pChildWnd->GetSafeHwnd(), WM_LBUTTONDOWN, 0, MAKELPARAM(GetRunTypeI(), 10));
			::SendMessage(pChildWnd->GetSafeHwnd(), WM_LBUTTONUP, 0, MAKELPARAM(GetRunTypeI(), 10)); //GetRunTypeI
		}
		else if(nCount == 28)
		{
			pTemp = GetSubWnd(pChildWnd, 1);

			CString strTemp = ::GetStringFromEdit(m_pRcpDlg->m_EDT_ETC.pEdit);

			int nStart = strTemp.Find("{��ü�δ��");
			int nEnd = strTemp.Find("}", nStart);

			if(nEnd > nStart)
			{
				CString strDelete = strTemp.Mid(nStart, nEnd - nStart + 1);
				strTemp.Replace(strDelete, "");
			}

			::SendMessage(pTemp->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)strTemp); //����
		}
		else if(nCount == 30)
		{
			pTemp = GetSubWnd(pChildWnd, 0);
			::SendMessage(pTemp->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)m_pRcpDlg->m_pOrder->GetPhone()); // SMS
		}

		pChildWnd = pChildWnd->GetWindow(GW_HWNDNEXT);
		nCount++;
	}

	/*
	CWnd *pSmsPhone = GetSubWnd(pWnd, 30);
	pSmsPhone = GetSubWnd(pSmsPhone, 0);
	::SendMessage(pSmsPhone->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)m_pRcpDlg->m_pOrder->GetPhone()); // SMS

	CWnd *pEtc = GetSubWnd(pWnd, 28);
	pEtc = GetSubWnd(pEtc, 1);
	::SendMessage(pEtc->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)::GetStringFromEdit(m_pRcpDlg->m_EDT_ETC.pEdit)); //����
	

	CWnd *pShare = GetSubWnd(pWnd, 8); //����üũ
	::SendMessage(pShare->GetSafeHwnd(), WM_LBUTTONDOWN, 0, 0);
	::SendMessage(pShare->GetSafeHwnd(), WM_LBUTTONUP, 0, 0);


	// 10 ����, 100����. 150�ſ� //200�۱� // 250���� // 300 ī��
	CWnd *pPayType = GetSubWnd(pWnd, 3);
	::SendMessage(pPayType->GetSafeHwnd(), WM_LBUTTONDOWN, 0, MAKELPARAM(GetPayTypeI(), 10));
	::SendMessage(pPayType->GetSafeHwnd(), WM_LBUTTONUP, 0, MAKELPARAM(GetPayTypeI(), 10));

	// 10 ����, 100�ٸ�. 150�� //200�� // 250Ʈ�� // 300 ����ö
	CWnd *pCarType = GetSubWnd(pWnd, 2);
	::SendMessage(pCarType->GetSafeHwnd(), WM_LBUTTONDOWN, 0, MAKELPARAM(GetCarTypeI(), 10));
	::SendMessage(pCarType->GetSafeHwnd(), WM_LBUTTONUP, 0, MAKELPARAM(GetCarTypeI(), 10));

	//10�� 80 �պ� 120 ���� 170 ���
	CWnd *pRunType = GetSubWnd(pWnd, 13);
	::SendMessage(pRunType->GetSafeHwnd(), WM_LBUTTONDOWN, 0, MAKELPARAM(GetRunTypeI(), 10));
	::SendMessage(pRunType->GetSafeHwnd(), WM_LBUTTONUP, 0, MAKELPARAM(GetRunTypeI(), 10));
	*/
}

void CIPass::InsertOrderData(CWnd *pWnd)
{
	CWnd *pChildWnd = pWnd->GetWindow(GW_CHILD);
	long nCount = 0;

	while (pChildWnd != NULL && pChildWnd->GetSafeHwnd()) 
	{
		CWnd *pTemp = NULL;
		if(nCount == 4)
		{
			pTemp = GetSubWnd(pChildWnd, 0);
			::SendMessage(pTemp->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)m_pRcpDlg->m_pOrder->GetCompany()); //�Ƿ�����
		}
		else if(nCount == 7)
		{
			pTemp = GetSubWnd(pChildWnd, 0);
			::SendMessage(pTemp->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)m_pRcpDlg->m_pOrder->GetDepart()); //�Ƿ����μ�
		}
		else if(nCount == 8)
		{
			pTemp = GetSubWnd(pChildWnd, 0);
			pTemp = GetSubWnd(pTemp, 0);
			::SendMessage(pTemp->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)m_pRcpDlg->m_pOrder->GetPhone()); // �Ƿ�����ȭ1
		}
		else if(nCount == 12)
		{
			pTemp = GetSubWnd(pChildWnd, 1);
			::SendMessage(pTemp->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)m_pRcpDlg->m_pOrder->GetMemo()); // �Ƿ�������
		}
		else if(nCount == 13)
		{
			pTemp = GetSubWnd(pChildWnd, 1);
			CString strTemp = m_pRcpDlg->m_pOrder->GetAddress() + " " + m_pRcpDlg->m_pOrder->GetDetail();
			::SendMessage(pTemp->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)strTemp); // �Ƿ�����ġ
		}
		else if(nCount == 19)
		{
			pTemp = GetSubWnd(pChildWnd, 0);
			::SendMessage(pTemp->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)m_pRcpDlg->m_pOrder->GetManager()); // �Ƿ������
		}
		else if(nCount == 22)
		{
			pTemp = GetSubWnd(pChildWnd, 0);
			::SendMessage(pTemp->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)m_pRcpDlg->m_pOrder->GetPhone(TRUE));//  "�Ƿ�����ȭ2"
		}
		else if(nCount == 24)
		{
			pTemp = GetSubWnd(pChildWnd, 0);
			::SendMessage(pTemp->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)m_pRcpDlg->m_pOrder->GetDisplayDong()); //�Ƿ�������
		}

		pChildWnd = pChildWnd->GetWindow(GW_HWNDNEXT);
		nCount++;
	}

	/*
	// �ڵ�� ��
	CWnd *pName = GetSubWnd(pWnd, 4);
	pName = GetSubWnd(pName, 0);
	::SendMessage(pName->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)m_pRcpDlg->m_pOrder->GetCompany()); //�Ƿ�����

	CWnd *pDong = GetSubWnd(pWnd, 24);
	pDong = GetSubWnd(pDong, 0);
	::SendMessage(pDong->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)m_pRcpDlg->m_pOrder->GetDisplayDong()); //�Ƿ�������
	
	CWnd *pPhone1 = GetSubWnd(pWnd, 8);
	pPhone1 = GetSubWnd(pPhone1, 0);
	pPhone1 = GetSubWnd(pPhone1, 0);
	::SendMessage(pPhone1->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)m_pRcpDlg->m_pOrder->GetPhone()); // �Ƿ�����ȭ1

	CWnd *pPhone2 = GetSubWnd(pWnd, 22);
	pPhone2 = GetSubWnd(pPhone2, 0);
	::SendMessage(pPhone2->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)m_pRcpDlg->m_pOrder->GetPhone(TRUE));//  "�Ƿ�����ȭ2"

	CWnd *pDepart = GetSubWnd(pWnd, 7);
	pDepart = GetSubWnd(pDepart, 0);
	::SendMessage(pDepart->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)m_pRcpDlg->m_pOrder->GetDepart()); //�Ƿ����μ�

	CWnd *pManager = GetSubWnd(pWnd, 19);
	pManager = GetSubWnd(pManager, 0);
	::SendMessage(pManager->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)m_pRcpDlg->m_pOrder->GetManager()); // �Ƿ������

	CWnd *pLocation = GetSubWnd(pWnd, 13);
	pLocation = GetSubWnd(pLocation, 1);
	::SendMessage(pLocation->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)m_pRcpDlg->m_pOrder->GetDetail()); // �Ƿ�����ġ

	CWnd *pEtc = GetSubWnd(pWnd, 12);
	pEtc = GetSubWnd(pEtc, 1);
	::SendMessage(pEtc->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)m_pRcpDlg->m_pOrder->GetMemo()); // �Ƿ�������
	*/
}

void CIPass::InsertStartData(CWnd *pWnd)
{
	CWnd *pChildWnd = pWnd->GetWindow(GW_CHILD);
	long nCount = 0;

	while (pChildWnd != NULL && pChildWnd->GetSafeHwnd())
	{
		CWnd *pTemp = NULL;

		if(nCount == 3)
		{
			pTemp = GetSubWnd(pChildWnd, 1);
			CString strTemp = m_pRcpDlg->m_pStart->GetAddress() + " " + m_pRcpDlg->m_pStart->GetDetail();
			::SendMessage(pTemp->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)strTemp); //�������ġ
		}
		else if(nCount == 8)
		{
			pTemp = GetSubWnd(pChildWnd, 0);
			::SendMessage(pTemp->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)m_pRcpDlg->m_pStart->GetPhone(TRUE)); //�������ȭ2
		}
		else if(nCount == 11)
		{
			pTemp = GetSubWnd(pChildWnd, 0);
			::SendMessage(pTemp->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)m_pRcpDlg->m_pStart->GetManager()); //��������
		}
		else if(nCount == 13)
		{
			pTemp = GetSubWnd(pChildWnd, 0);
			::SendMessage(pTemp->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)m_pRcpDlg->m_pStart->GetDepart()); //������μ�
		}
		else if(nCount == 15)
		{
			pTemp = GetSubWnd(pChildWnd, 0);
			::SendMessage(pTemp->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)m_pRcpDlg->m_pStart->GetDisplayDong()); // ���������
		}
		else if(nCount == 17)
		{
			pTemp = GetSubWnd(pChildWnd, 0);
			::SendMessage(pTemp->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)m_pRcpDlg->m_pStart->GetCompany()); // �������
		}
		else if(nCount == 23)
		{
			pTemp = GetSubWnd(pChildWnd, 0);
			::SendMessage(pTemp->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)m_pRcpDlg->m_pStart->GetPhone()); //�������ȭ1
		}
	
		pChildWnd = pChildWnd->GetWindow(GW_HWNDNEXT);
		nCount++;
	}
	/*
	// �ڵ�� �����
	CWnd *pName = GetSubWnd(pWnd, 17);
	pName = GetSubWnd(pName, 0);
	::SendMessage(pName->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)m_pRcpDlg->m_pStart->GetCompany()); // �������

	CWnd *pDong = GetSubWnd(pWnd, 15);
	pDong = GetSubWnd(pDong, 0);
	::SendMessage(pDong->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)m_pRcpDlg->m_pStart->GetDisplayDong()); // ���������

	CWnd *pPhone1 = GetSubWnd(pWnd, 23);
	pPhone1 = GetSubWnd(pPhone1, 0);
	::SendMessage(pPhone1->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)m_pRcpDlg->m_pStart->GetPhone()); //�������ȭ1

	CWnd *pPhone2 = GetSubWnd(pWnd, 8);
	pPhone2 = GetSubWnd(pPhone2, 0);
	::SendMessage(pPhone2->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)m_pRcpDlg->m_pStart->GetPhone(TRUE)); //�������ȭ2

	CWnd *pDepart = GetSubWnd(pWnd, 13);
	pDepart = GetSubWnd(pDepart, 0);
	::SendMessage(pDepart->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)m_pRcpDlg->m_pStart->GetDepart()); //������μ�

	CWnd *pManager = GetSubWnd(pWnd, 11);
	pManager = GetSubWnd(pManager, 0);
	::SendMessage(pManager->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)m_pRcpDlg->m_pStart->GetManager()); //��������

	CWnd *pLocation = GetSubWnd(pWnd, 3);
	pLocation = GetSubWnd(pLocation, 1);
	::SendMessage(pLocation->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)m_pRcpDlg->m_pStart->GetDetail()); //�������ġ
	*/
}

void CIPass::InsertDestData(CWnd *pWnd)
{
	CWnd *pChildWnd = pWnd->GetWindow(GW_CHILD);
	long nCount = 0;

	while (pChildWnd != NULL && pChildWnd->GetSafeHwnd())
	{
		CWnd *pTemp = NULL;

		if(nCount == 4)
		{
			pTemp = GetSubWnd(pChildWnd, 1);

			CString strTemp = m_pRcpDlg->m_pDest->GetAddress() + " " + m_pRcpDlg->m_pDest->GetDetail();
			::SendMessage(pTemp->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)strTemp); //��������ġ
		}
		else if(nCount == 10)
		{
			pTemp = GetSubWnd(pChildWnd, 0);
			::SendMessage(pTemp->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)m_pRcpDlg->m_pDest->GetPhone(TRUE)); //��������ȭ2
		}
		else if(nCount == 12)
		{
			pTemp = GetSubWnd(pChildWnd, 0);
			::SendMessage(pTemp->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)m_pRcpDlg->m_pDest->GetManager()); //���������
		}
		else if(nCount == 14)
		{
			pTemp = GetSubWnd(pChildWnd, 0);
			::SendMessage(pTemp->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)m_pRcpDlg->m_pDest->GetDepart()); //�������μ�
		}
		else if(nCount == 16)
		{	
			pTemp = GetSubWnd(pChildWnd, 0);
			::SendMessage(pTemp->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)m_pRcpDlg->m_pDest->GetDisplayDong()); //����������
		}
		else if(nCount == 18)
		{	
			pTemp = GetSubWnd(pChildWnd, 0);
			::SendMessage(pTemp->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)m_pRcpDlg->m_pDest->GetCompany()); //��������
		}
		else if(nCount == 24)
		{	
			pTemp = GetSubWnd(pChildWnd, 0);
			::SendMessage(pTemp->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)m_pRcpDlg->m_pDest->GetPhone()); //��������ȭ1
		}

		pChildWnd = pChildWnd->GetWindow(GW_HWNDNEXT);
		nCount++;
	}

	/*
	// �ڵ�� ������
	CWnd *pName = GetSubWnd(pWnd, 18);
	pName = GetSubWnd(pName, 0);
	::SendMessage(pName->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)m_pRcpDlg->m_pDest->GetCompany()); //��������

	CWnd *pDong = GetSubWnd(pWnd, 16);
	pDong = GetSubWnd(pDong, 0);
	::SendMessage(pDong->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)m_pRcpDlg->m_pDest->GetDisplayDong()); //����������

	CWnd *pPhone1 = GetSubWnd(pWnd, 24);
	pPhone1 = GetSubWnd(pPhone1, 0);
	::SendMessage(pPhone1->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)m_pRcpDlg->m_pDest->GetPhone()); //��������ȭ1

	CWnd *pPhone2 = GetSubWnd(pWnd, 10);
	pPhone2 = GetSubWnd(pPhone2, 0);
	::SendMessage(pPhone2->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)m_pRcpDlg->m_pDest->GetPhone(TRUE)); //��������ȭ2

	CWnd *pDepart = GetSubWnd(pWnd, 14);
	pDepart = GetSubWnd(pDepart, 0);
	::SendMessage(pDepart->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)m_pRcpDlg->m_pDest->GetDepart()); //�������μ�

	CWnd *pManager = GetSubWnd(pWnd, 12);
	pManager = GetSubWnd(pManager, 0);
	::SendMessage(pManager->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)m_pRcpDlg->m_pDest->GetManager()); //���������

	CWnd *pLocation = GetSubWnd(pWnd, 4);
	pLocation = GetSubWnd(pLocation, 1);
	::SendMessage(pLocation->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)m_pRcpDlg->m_pDest->GetDetail()); //��������ġ
	*/
}

void CIPass::InsertChargeData(CWnd *pWnd)
{	
	CWnd *pDefault = GetSubWnd(pWnd, 17);
	pDefault = GetSubWnd(pDefault, 0);
	AddCharge(pDefault, ::RemoveComma(::GetStringFromEdit(m_pRcpDlg->m_EDT_CHARGE_BASIC.pEdit)));//�⺻���

	CWnd *pAdd = GetSubWnd(pWnd, 2);
	pAdd = GetSubWnd(pAdd, 0);
	long nAdd = atoi(::RemoveComma(::GetStringFromEdit(m_pRcpDlg->m_EDT_CHARGE_ADD.pEdit)));	
	AddCharge(pAdd, ::GetStringFromLong(nAdd));//�߰�

	CWnd *pDis = GetSubWnd(pWnd, 12);
	pDis = GetSubWnd(pDis, 0);
	long nDis = atoi(::RemoveComma(::GetStringFromEdit(m_pRcpDlg->m_EDT_CHARGE_DIS.pEdit)));
	//long nChargeCompany = atoi(::RemoveComma(::GetStringFromEdit(&m_pRcpDlg->m_edtChargeCompany)));
	AddCharge(pDis, ::GetStringFromLong(nDis)); //����

	CWnd *pTran = GetSubWnd(pWnd, 14);
	pTran = GetSubWnd(pTran, 0);

	long nTran = atoi(::RemoveComma(::GetStringFromEdit(m_pRcpDlg->m_EDT_CHARGE_TRANS.pEdit)));	
	AddCharge(pTran, ::GetStringFromLong(nTran));//Ź��


	/*
	// �ڵ�� ���
	CWnd *pDefault = GetSubWnd(pWnd, 17);
	pDefault = GetSubWnd(pDefault, 0);
	AddCharge(pDefault, ::RemoveComma(::GetStringFromEdit(m_pRcpDlg->m_EDT_CHARGE_BASIC.pEdit)));//�⺻���

	CWnd *pAdd = GetSubWnd(pWnd, 2);
	pAdd = GetSubWnd(pAdd, 0);
	long nAdd = atoi(::RemoveComma(::GetStringFromEdit(m_pRcpDlg->m_EDT_CHARGE_ADD.pEdit)));	
	AddCharge(pAdd, ::GetStringFromLong(nAdd));//�߰�

	CWnd *pDis = GetSubWnd(pWnd, 12);
	pDis = GetSubWnd(pDis, 0);
	long nDis = atoi(::RemoveComma(::GetStringFromEdit(m_pRcpDlg->m_EDT_CHARGE_DIS.pEdit)));
	long nChargeCompany = atoi(::RemoveComma(::GetStringFromEdit(&m_pRcpDlg->m_edtChargeCompany)));
	AddCharge(pDis, ::GetStringFromLong(nDis + nChargeCompany)); //����

	CWnd *pTran = GetSubWnd(pWnd, 14);
	pTran = GetSubWnd(pTran, 0);

	long nTran = atoi(::RemoveComma(::GetStringFromEdit(m_pRcpDlg->m_EDT_CHARGE_TRANS.pEdit)));	
	AddCharge(pTran, ::GetStringFromLong(nTran));//Ź��

	*/
}

void CIPass::AddCharge(CWnd *pWnd, CString strCharge)
{

	strCharge.Replace(",", "");
	::SendMessage(pWnd->GetSafeHwnd(), WM_LBUTTONDOWN, 0, 0);
	::SendMessage(pWnd->GetSafeHwnd(), WM_LBUTTONUP, 0, 0);
	//::SendMessage(pWnd->GetSafeHwnd(), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)"");

	Sleep(500);

	for (int i = 0; i < strCharge.GetLength(); i++) {
		::SendMessage(pWnd->GetSafeHwnd(), WM_CHAR, strCharge.GetAt(i), 0);
	}
	/*
	::SendMessage(pWnd->GetSafeHwnd(), WM_SETFOCUS, 0, 0);
	strCharge.Replace(",", "");

	for (int i = 0; i < strCharge.GetLength(); i++) {
		::SendMessage(pWnd->GetSafeHwnd(), WM_CHAR, strCharge.GetAt(i), 0);
		//Sleep(100);
	}

	::SendMessage(pWnd->GetSafeHwnd(), WM_KILLFOCUS, 0, 0);
	*/
}