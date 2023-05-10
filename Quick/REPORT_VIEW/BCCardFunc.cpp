#include "stdafx.h"
#include ".\bccardfunc.h"
#include "QSocket.h"

CMkDatabase *m_pMkDb4BCCard = NULL;
CMkDatabase *m_pMkDb4BTCard = NULL;


BOOL ConnectBTCardSvr()
{
	/*
	if(NULL == m_pMkDb4BTCard)
	{
		m_pMkDb4BTCard = new CMkDatabase;
		BYTE nXorKey = (m_pMkDb4BTCard->GetXorKey() + 3) % 128;
		BYTE des_key_new[] = {29,44,2,83,32,98,10,8};
		BYTE nXoredKey[8];

		for(int i = 0; i < 8; i++)
			nXoredKey[i] = des_key_new[i] ^ ((nXorKey + i) % 128);
		m_pMkDb4BTCard->SetServerKey(nXoredKey);

		CBranchInfo *pInfo = m_ci.GetBranchInfo();

		MSG_LOGIN_INFO info;
		ZeroMemory(&info, sizeof(MSG_LOGIN_INFO));
		info.nCompany = pInfo->nCompany;
		info.nWNo = m_ui.nWNo;
		info.nShareCode1 = pInfo->nShareCode1;
		info.nShareCode2 = pInfo->nShareCode2;
		info.nShareCode3 = pInfo->nShareCode3;
		info.nShareCode4 = pInfo->nShareCode4;
		info.nShareCode5 = pInfo->nShareCode5;
		info.nShareCode6 = pInfo->nShareCode6;
		info.nShareCode7 = pInfo->nShareCode7;
		info.nShareCode8 = pInfo->nShareCode8;
		info.nShareCode9 = pInfo->nShareCode9;
		info.nShareCode10 = pInfo->nShareCode10;
		info.nMsgGroupCode = 0;
		strcpy(info.szCompanyName, pInfo->strName);
		strcpy(info.szBranchName, pInfo->strBranchName);
		strcpy(info.szUserName, pInfo->strName);
		info.bIdle = 0;
		info.bManager =0;
		info.nDisplayType = 0;

		m_pMkDb4BTCard->SetParentWnd(NULL);
		m_pMkDb4BTCard->AsyncSelect(0);


		m_pMkDb4BTCard->SetLoginInfo(&info);
		//return m_pMkDb4BCCard->Open("192.168.1.107", 4300, TRUE);

		CString sSocket = "";

		if(pInfo->strServerAddr == "211.172.242.164")
			sSocket = "211.172.242.180";
		else
			sSocket = "211.172.242.170";
	
		 m_pMkDb->GetSocket()->GetPeerName();

		return m_pMkDb4BTCard->Open(sSocket, 3603, TRUE);
	}
	else
	{
		BOOL bRet = m_pMkDb4BTCard->GetSocket()->IsConnected();
//		delete m_pMkDb4BTCard;
//		m_pMkDb4BTCard = NULL;
		if(FALSE == bRet) m_pMkDb4BTCard->ConnectServer();

		return  bRet;
	}
	*/

	return 0;
}

BOOL ConnectBCCardSvr()
{
	/*
	if(NULL == m_pMkDb4BCCard)
	{
		m_pMkDb4BCCard = new CMkDatabase;
		BYTE nXorKey = (m_pMkDb4BCCard->GetXorKey() + 3) % 128;
		BYTE des_key_new[] = {29,44,2,83,32,98,10,8};
		BYTE nXoredKey[8];

		for(int i = 0; i < 8; i++)
			nXoredKey[i] = des_key_new[i] ^ ((nXorKey + i) % 128);
		m_pMkDb4BCCard->SetServerKey(nXoredKey);

		CBranchInfo *pInfo = m_ci.GetBranchInfo();

		MSG_LOGIN_INFO info;
		ZeroMemory(&info, sizeof(MSG_LOGIN_INFO));
		info.nCompany = pInfo->nCompany;
		info.nWNo = m_ui.nWNo;
		info.nShareCode1 = pInfo->nShareCode1;
		info.nShareCode2 = pInfo->nShareCode2;
		info.nShareCode3 = pInfo->nShareCode3;
		info.nShareCode4 = pInfo->nShareCode4;
		info.nShareCode5 = pInfo->nShareCode5;
		info.nShareCode6 = pInfo->nShareCode6;
		info.nShareCode7 = pInfo->nShareCode7;
		info.nShareCode8 = pInfo->nShareCode8;
		info.nShareCode9 = pInfo->nShareCode9;
		info.nShareCode10 = pInfo->nShareCode10;
		info.nMsgGroupCode = 0;
		strcpy(info.szCompanyName, pInfo->strName);
		strcpy(info.szBranchName, pInfo->strBranchName);
		strcpy(info.szUserName, pInfo->strName);
		info.bIdle = 0;
		info.bManager =0;
		info.nDisplayType = 0;

		m_pMkDb4BCCard->SetParentWnd(NULL);
		m_pMkDb4BCCard->AsyncSelect(0);


		m_pMkDb4BCCard->SetLoginInfo(&info);
		//return m_pMkDb4BCCard->Open("192.168.1.107", 4300, TRUE);
		return m_pMkDb4BCCard->Open("211.172.242.169", 4670, TRUE);
	}
	else
	{
		BOOL bRet = m_pMkDb4BCCard->GetSocket()->IsConnected();
		if(FALSE == bRet) m_pMkDb4BCCard->ConnectServer();
		return  bRet;
	}
	*/
	return 0;
}


#define PST_BC_GET_CARD_NUMBER	380				//전화번호로 카드번호를 가져오기
#define PST_BC_REQUSET_OK		381				//승인요청
#define PST_BC_REQUSET_CANCEL	382				//승인취소요청

#define PST_SERVER_CARD_REQUSET_OK		396				//카드승인    요청
#define PST_SERVER_CARD_REQUSET_CANCEL	397				//카드승인취소요청


int nCardType(int nTNo,int nCompany)
{

	if(nCompany >= 25900 && nCompany < 25980)	return 11;
	if(nCompany >= 20200 && nCompany < 20280)	return 11;
	if(nCompany <= 30)							return 11;

	return 0;
}

int CardOKRequest(int nTNo,CString& strError)
{

	BOOL bRet = ConnectBTCardSvr();
	if(!bRet)
	{
		strError = "Server 에 접속할수 없습니다. 다시 시도 바랍니다.";
		return -1;
	}
	
	char szdata[500];
	STRCPY(szdata, ::GetStringFromLong(nTNo), "00000000", "0", VL_END); //nTNo,CardNumber,결제금액(0, 디폴트)
	if( !m_pMkDb4BTCard->GetSocket()->SendData(PT_REQUEST,PST_SERVER_CARD_REQUSET_OK,szdata) )
	{
		strError = "Server에 데이터를 보낼수 없습니다.";
		return -1;
	}

	QPACKET *p = (QPACKET*)m_pMkDb4BTCard->GetSocket()->ReadStream();
	if(p != NULL) {

		if(PT_OK == p->nType )
		{
			free(p);
			return 0;
		}
		else
		{
			strError = p->data;
			return -1;
		}
	}

	strError = "Server에서 카드요청 데이터를 가져올수 없습니다.";
	return -1;

}

int CardCancelRequest(int nTNo,int nWCompany,int nWNo, const char* szTranNumber,CString& strError)
{
	BOOL bRet = ConnectBTCardSvr();
	if(!bRet)
	{
		strError = "Server 에 접속할수 없습니다. 다시 시도 바랍니다.";
		return -1;
	}
	
	char szTNo[20]={0,};
	char szWCompany[20]={0,};
	char szWNo[20]={0,};
	char szdata[500];
	STRCPY(szdata,ltoa(nTNo,szTNo,10),ltoa(nWCompany,szWCompany,10),ltoa(nWNo,szWNo,10),(char*)szTranNumber,VL_END); //nTNo,CardNumber,결제금액(0, 디폴트)
	if( !m_pMkDb4BTCard->GetSocket()->SendData(PT_REQUEST,PST_SERVER_CARD_REQUSET_CANCEL,szdata) )
	{
		strError = "Server에 데이터를 보낼수 없습니다.";
		return -1;
	}

	QPACKET *p = (QPACKET*)m_pMkDb4BTCard->GetSocket()->ReadStream();
	if(p != NULL) {

		if(PT_OK == p->nType )
		{
			free(p);
			return 0;
		}
		else
		{
			strError = p->data;
			return -1;
		}
	}

	strError = "Server에서 카드 취소요청 데이터를 가져올수 없습니다.";
	return -1;
}


int GetBCCardNumber(const char *szServer, CString sHeadBranchCode,CString strHp, CString& sCardNumber,
					CString& sCustomerName, CString &strBalance, CString& strError)
{
	BOOL bRet = ConnectBCCardSvr();
	if(!bRet)
	{
		strError = "BC Agent Server 에 접속할수 없습니다.";
		return -1;
	}

	char szdata[100];
	STRCPY(szdata,(char*)(LPCSTR)szServer, (char*)(LPCSTR)sHeadBranchCode,(char*)(LPCSTR)strHp,VL_END);
	if( !m_pMkDb4BCCard->GetSocket()->SendData(PT_REQUEST,PST_BC_GET_CARD_NUMBER,szdata) )
	{
		strError = "BC Agent Server에 데이터를 보낼수 없습니다.";
		return -1;
	}

	QPACKET *p = (QPACKET*)m_pMkDb4BCCard->GetSocket()->ReadStream();
	if(p != NULL) {

		if(PT_OK == p->nType )
		{
			char customername[100], cardnumber[100], balance[100];
			if(STRTOK(p->data, 0, customername, cardnumber, balance, VL_END))
			{
				sCustomerName = customername;
				sCardNumber = cardnumber;
				strBalance = balance;
				sCustomerName.Trim();
				sCardNumber.Trim();
				strBalance.Trim();
			}
			free(p);
			return 0;
		}
		else
		{
			int nRet = p->nSubType;
			strError = p->data;
			free(p);
			return nRet;
		}
	}

	strError = "BC Agent Server에서 데이터를 가져올수 없습니다.";
	return -1;
}



//  szServer ,"1" - 1번서버,"3" 3번서버
//	szInsurance="0", 보험가입시는 "1" szSSN에 주민번호 입력
//	szSSN="";

int BCCardRequestOK(const char* szServer,const char* szHeadBranchCode,const char* szPhoneNumber,const char* szCardNumber,const char* szCharge,const char* szInsurance,const char* szSSN,
						CString& strTransactionNumber, CString& strBalance, CString& strError)
{
	BOOL bRet = ConnectBCCardSvr();
	if(!bRet)
	{
		strError = "BC Agent Server 에 접속할수 없습니다.";
		return -1;
	}


	char szdata[500];
	STRCPY(szdata,szServer,szHeadBranchCode,szPhoneNumber,szCardNumber,szInsurance,szSSN,szCharge,VL_END);
	if( !m_pMkDb4BCCard->GetSocket()->SendData(PT_REQUEST,PST_BC_REQUSET_OK,szdata) )
	{
		strError = "BC Agent Server에 데이터를 보낼수 없습니다.";
		return -1;
	}

	QPACKET *p = (QPACKET*)m_pMkDb4BCCard->GetSocket()->ReadStream();
	if(p != NULL) {

		if(PT_OK == p->nType)
		{
			char tran[100], balance[100];
			if(STRTOK(p->data, 0, tran, balance, VL_END))
			{
				strTransactionNumber = tran;
				strBalance = balance;
			}
			free(p);
			return 0;
		}
		else
		{
			char error[100], balance[100];
			if(STRTOK(p->data, 0, error, balance, VL_END))
			{
				strBalance = balance;
				strError = error; 
			}

			int nRet = p->nSubType;
			free(p);
			return nRet;
		}
	}

	strError = "BC Agent Server에서 데이터를 가져올수 없습니다.";
	return -1;
}


/*
szCancelMode
1 : 정상 취소
5 : 지연응답 취소
6 : TIMEOUT 취소
7 : 자동 취소 (비씨내부)"
*/

int BCCardCancel(const char* szServer,const char* szTNo,const char* szCancelMode,const char* szTransactionNumber, CString& strError)
{
	BOOL bRet = ConnectBCCardSvr();
	if(!bRet)
	{
		strError = "BC Agent Server 에 접속할수 없습니다.";
		return -1;
	}


	char szdata[500];
	STRCPY(szdata,szServer,szTNo,szTransactionNumber,szCancelMode,VL_END);
	if( !m_pMkDb4BCCard->GetSocket()->SendData(PT_REQUEST,PST_BC_REQUSET_CANCEL,szdata) )
	{
		strError = "BC Agent Server에 데이터를 보낼수 없습니다.";
		return -1;
	}

	QPACKET *p = (QPACKET*)m_pMkDb4BCCard->GetSocket()->ReadStream();
	if(p != NULL) {

		if(PT_OK == p->nType )
		{
			free(p);
			return 0;
		}
		else
		{
			int nRet = p->nSubType;
			strError = p->data;
			free(p);
			return nRet;
		}
	}

	strError = "BC Agent Server에서 데이터를 가져올수 없습니다.";
	return -1;
}

