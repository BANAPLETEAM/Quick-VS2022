// WalkieTalkieDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "WalkieTalkieDlg.h"

#include "RecordSound.h"
#include "PlaySound.h"
#include "MyCallerRecv.h"
#include "MyCaller4Send.h"



// CWalkieTalkieDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CWalkieTalkieDlg, CDialog)

CWalkieTalkieDlg::CWalkieTalkieDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWalkieTalkieDlg::IDD, pParent)
{

	m_uPort = 4505;
	m_sID= _T("user1");
	m_uShareCompany = 20;
	m_uCompany		= 20;
	m_nMNo			= 1;
	m_nGroupType	= -1;
	m_sAddress		= _T("211.172.242.176");

	m_record = NULL;
	m_play   = NULL;

	m_MyVTMsgState	= 0;
	m_nCallState	= PH_HANGUP;
	m_bWaveST		= TRUE;
	m_bCompanyWT	= TRUE;
	m_bCaller		= TRUE;

}

CWalkieTalkieDlg::~CWalkieTalkieDlg()
{
	if(m_record) 
	{
		if(m_record->IsRecording() ==TRUE)		m_record->PostThreadMessage(WM_RECORDSOUND_STOPRECORDING,0,0);
		m_record->PostThreadMessage(WM_RECORDSOUND_ENDTHREAD,0,0);
	}

	if(m_play)
	{
		if(m_play->IsPlaying() == TRUE)			m_play->PostThreadMessage(WM_PLAYSOUND_STOPPLAYING,0,0);
		m_record->PostThreadMessage(WM_PLAYSOUND_ENDTHREAD,0,0);
	}

}

void CWalkieTalkieDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CONNUSER, m_ConnListBox);
	DDX_Control(pDX, IDC_STATIC_RECV_STATUS, m_RecvStatus);
	DDX_Control(pDX, IDC_STATIC_SEND_STATUS, m_SendStatus);
	DDX_Control(pDX, IDC_STATIC_STATUS, m_Status);
	DDX_Control(pDX, IDC_CHECK_TALK, m_btnRecord);
}


BEGIN_MESSAGE_MAP(CWalkieTalkieDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CWalkieTalkieDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CWalkieTalkieDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_CHECK_BI, &CWalkieTalkieDlg::OnBnClickedCheckBi)
	ON_BN_CLICKED(IDC_CHECK_TALK, &CWalkieTalkieDlg::OnBnClickedCheckTalk)
	ON_MESSAGE(MM_WIM_DATA,OnRecord)
	ON_MESSAGE(MM_TEXT_DATA,OnTextData)
	ON_MESSAGE(MM_VOICE_DATA,OnVoiceData)
	ON_MESSAGE(UM_CONNECTED,OnConnected)
	ON_MESSAGE(UM_DISCONNECTED,OnDisConnected)
	ON_MESSAGE(UM_CONNLIST,OnConnList)
	ON_MESSAGE(UM_ADD_CONNUSER,OnAddConnUser)
	ON_MESSAGE(UM_REM_CONNUSER,OnRemConnUser)
END_MESSAGE_MAP()


// CWalkieTalkieDlg 메시지 처리기입니다.
void CWalkieTalkieDlg::SetServerInfo(CString sAddr,UINT uPort)
{
	m_sAddress	= sAddr ;
	m_uPort		= uPort;

}

void CWalkieTalkieDlg::SetUserInfo(CString sID,CString sName,int nShareCompany,int nCompany,int nMNo )
{
	m_sID	= sID;
	m_sName	= sName;
	m_uShareCompany=nShareCompany;
	m_uCompany=nCompany;
	m_nMNo=nMNo;

}

BOOL CWalkieTalkieDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	m_btnRecord.EnableWindow(FALSE);

	m_play = new CPlaySound(this);
	if(m_play)	m_play->CreateThread();


	m_record = new CRecordSound(this,NULL,"c:\\test.wav");
	if(m_record) m_record->CreateThread();

	m_recv = new CMyCallerRecv(this,m_play);
	m_send = new CMyCaller4Send(this);


	CString sLoginInfo;
	sLoginInfo.Format("%s@%d@%d@%d@%s@",m_sID,m_uCompany,m_nMNo,m_uShareCompany,m_sName);
	m_recv->Connect(m_sAddress,m_uPort,sLoginInfo,MT_USAGE_RECV);
	m_send->Connect(m_sAddress,m_uPort,sLoginInfo,MT_USAGE_SEND);

	if(m_play) m_play->PostThreadMessage(WM_PLAYSOUND_STARTPLAYING,0,0);


	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CWalkieTalkieDlg::DisplayError(CString sError)
{
	m_Status.SetWindowText(sError);
}

void CWalkieTalkieDlg::MakeTalkingGroup()
{
	UINT ucCmd = CMD_MAKE_GROUP_WT;
	if(m_bCompanyWT) ucCmd = CMD_MAKE_COMPANY_WT;

	if(TRUE ==  m_send->SendData(ucCmd,VT_TEXT,"","") )
	{
		m_MyVTMsgState = CMD_DELIVERY_G;
		m_nGroupType   = GROUP_WT;
		m_bCaller	   = TRUE;

		m_nCallState = PH_RING;
		if(m_play)	m_play->PostThreadMessage(WM_PLAYSOUND_STARTPLAYING,0,0);
	}

	m_MyVTMsgState = CMD_DELIVERY_G;
}

void CWalkieTalkieDlg::SetConnList(CString sConnList)
{
	m_btnRecord.EnableWindow(m_bCaller);

	m_ConnListBox.ResetContent();
	int nCurPos = 0;
	CString resToken;

	BOOL bRet = FALSE;
	do 
	{
		resToken = sConnList.Tokenize("/@; ",nCurPos);
		if(resToken == "") break;
		m_ConnListBox.AddString(resToken);

	}while(TRUE);

	MakeTalkingGroup();
}

void CWalkieTalkieDlg::AddConnUser(CString sUser)
{
	if( m_ConnListBox.FindString(-1,sUser) < 0 ) m_ConnListBox.AddString(sUser);
}

void CWalkieTalkieDlg::RemoveConnUser(CString sUser)
{
	int nFInd =			m_ConnListBox.FindString(-1,sUser);
	if( nFInd >= 0 )	m_ConnListBox.DeleteString(nFInd);
}

LRESULT CWalkieTalkieDlg::OnRecord(WPARAM wp,LPARAM lp)
{
	LPWAVEHDR lpHdrPlay = (LPWAVEHDR)lp;

	if(0 == m_MyVTMsgState)
	{
		return 0L;
	}

	if(m_btnRecord.GetCheck() <= 0 ) return 0L;


	if(CMD_DELIVERY_G == m_MyVTMsgState)
	{
		if(m_sTalkGroupCode.IsEmpty() )
		{
			DisplayError("대화 그룹이 없습니다. 대화 가능상태가 아닙니다.");
			return 0L;
		}

		UINT ucMsgType = VT_WAVE1M08;
		if(m_bWaveST)		ucMsgType = (VT_WAVE1M08 | VT_WAVEST);
		if(m_bCompanyWT)	ucMsgType = (ucMsgType | VT_WAVECP);
		m_send->SendBinary(CMD_DELIVERY_G,ucMsgType,m_sTalkGroupCode,lpHdrPlay->lpData,lpHdrPlay->dwBufferLength);
	}

	return 0L;
}

LRESULT CWalkieTalkieDlg::OnTextData(WPARAM wp,LPARAM lp)
{
	LPVTMSG p = (LPVTMSG)lp;
//	SetLog(CString("onTextData") + (char*)p->m_pData);

	if( PST_ERROR == p->m_ucCmd)
	{

	}
	else if( PST_LOGIN_LIST == p->m_ucCmd)
	{
		SetConnList( (char*)p->m_pData );
	}
	else if(PST_CONNECT_EVENT == p->m_ucCmd)
	{
		AddConnUser((char*)p->m_pData);
	}
	else if(PST_DISCONNECT_EVENT == p->m_ucCmd)
	{
		RemoveConnUser((char*)p->m_pData);
	}
	else if(CMD_NOT_FREE_STATE_WT == p->m_ucCmd)		//워키토키에서 송신권한을 가질수 없는 상태 무조건 레코딩 중지
	{
		if( m_btnRecord.GetCheck() > 0 ) m_btnRecord.SetCheck(0);
		if(m_record) 
		{
			m_record->PostThreadMessage(WM_RECORDSOUND_STOPRECORDING,0,0);
		}

	}
	else if(CMD_MAKE_COMPANY_WT == p->m_ucCmd || CMD_MAKE_GROUP_WT == p->m_ucCmd || CMD_MAKE_GROUP_TP == p->m_ucCmd || CMD_MAKE_GROUP_DC == p->m_ucCmd)
	{
		GetOptionString( (char*)p->m_pData,"GROUP",m_sTalkGroupCode);
		CString sTitle;
		sTitle.Format("그룹무전 그루ID %s",m_sTalkGroupCode);
		SetWindowText(sTitle);
	}
	else if(CMD_INVITE == p->m_ucCmd || CMD_INVITE_FORCE == p->m_ucCmd)
	{
/*
		m_nCallState= PH_RING;
		Invited(p);
		m_nCallState= PH_ANSWER;
*/
	}
	else if(CMD_ANSWER == p->m_ucCmd) //상대방이 전화에 응한경우	-- 이떄부터 통화가능
	{

		m_nCallState= PH_ANSWER;

/*
		if(m_play)
		{
			m_play->PostThreadMessage(WM_PLAYSOUND_STARTPLAYING,0,0);
		}

		if(GROUP_DC == m_nGroupType)
		{
			if(m_record) 
			{
				m_record->PostThreadMessage(WM_RECORDSOUND_STARTRECORDING,0,0);
			}		
		}
		else if(GROUP_WT == m_nGroupType)
		{
			m_btnMakeWT.EnableWindow(TRUE);
			if(m_bCaller)
			{
				m_btnMakeDC.SetWindowText("워키토키 해제하기");
			}

		}
		else if(GROUP_TP == m_nGroupType)
		{
			m_btnMakeGroupTP.EnableWindow(TRUE);
			m_btnMakeGroupTP.SetWindowText("전화끓기");
		}
*/

	}
	else if(CMD_HANGUP == p->m_ucCmd) //상대방이 전화를 끓은경우	-- 전화를 끓는다.
	{
		m_nCallState= PH_HANGUP;
		if(m_play)
		{
			m_play->PostThreadMessage(WM_PLAYSOUND_STOPPLAYING,0,0);
		}

		if(m_record) 
		{
			m_record->PostThreadMessage(WM_RECORDSOUND_STOPRECORDING,0,0);
		}

	}
	else if(CMD_GROUP_JOINED == p->m_ucCmd)		//누군가가 그룹에 참여
	{
		m_nCallState= PH_ANSWER;
	}
	else if(CMD_GROUP_OUT == p->m_ucCmd)			//누군가가 그룹에서 탈퇴
	{

	}
	else if(CMD_GROUP_NO_EXGIST == p->m_ucCmd)	//통화대상 그룹이 없음 --전화를 끓는다.
	{
		m_nCallState= PH_HANGUP;

		m_btnRecord.SetCheck(0);			
		if(m_record) 
		{
			m_record->PostThreadMessage(WM_RECORDSOUND_STOPRECORDING,0,0);
		}
	}
	else if(CMD_FAIL_DELIVERY== p->m_ucCmd)	//보이스 전송 실패
	{


	}


	return 0L;
}

LRESULT CWalkieTalkieDlg::OnVoiceData(WPARAM wp,LPARAM lp)
{
	m_btnRecord.EnableWindow(m_bCaller);

	LPVTMSG p = (LPVTMSG)lp;
	m_sTalkGroupCode = p->m_sToID;

	CString sMsg;
	sMsg.Format("%s(사번:%d) 님과 통화중",p->m_sName,p->m_uToRNo);
	m_Status.SetWindowText(sMsg);

	return 0L;
}

LRESULT CWalkieTalkieDlg::OnConnected(WPARAM wp,LPARAM lp)
{
	if(MT_USAGE_SEND == (int)wp)	m_SendStatus.SetWindowText("보이스 서버에 접속됨");
	if(MT_USAGE_RECV == (int)wp)	m_RecvStatus.SetWindowText("보이스 서버에 접속됨");
		
	return 0L;
}

LRESULT CWalkieTalkieDlg::OnDisConnected(WPARAM wp,LPARAM lp)
{
	if(MT_USAGE_SEND == (int)wp)	m_SendStatus.SetWindowText("송신할수 없음-접속불량");
	if(MT_USAGE_RECV == (int)wp)	m_RecvStatus.SetWindowText("수신할수 없음-접속불량");

	return 0L;
}

LRESULT CWalkieTalkieDlg::OnConnList(WPARAM wp,LPARAM lp)
{

	SetConnList((char*)wp);
	return 0L;
}

LRESULT CWalkieTalkieDlg::OnAddConnUser(WPARAM wp,LPARAM lp)
{
	AddConnUser((char*)wp);
	return 0L;
}

LRESULT CWalkieTalkieDlg::OnRemConnUser(WPARAM wp,LPARAM lp)
{
	RemoveConnUser((char*)wp);
	return 0L;
}

void CWalkieTalkieDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	return;

	OnOK();
}

void CWalkieTalkieDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if( m_btnRecord.GetCheck() > 0 )	OnBnClickedCheckTalk();


/*
	if(m_record) 
	{
		if(m_record->IsRecording() ==TRUE)		m_record->PostThreadMessage(WM_RECORDSOUND_STOPRECORDING,0,0);
		m_record->PostThreadMessage(WM_RECORDSOUND_ENDTHREAD,0,0);
	}

	if(m_play)
	{
		if(m_play->IsPlaying() == TRUE)			m_play->PostThreadMessage(WM_PLAYSOUND_STOPPLAYING,0,0);
		m_record->PostThreadMessage(WM_PLAYSOUND_ENDTHREAD,0,0);
	}

	OnCancel();
*/
	ShowWindow(SW_HIDE);
}

//쌍방향 무전 옵션
void CWalkieTalkieDlg::OnBnClickedCheckBi()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_bWaveST = !m_bWaveST;
}

//말하기
void CWalkieTalkieDlg::OnBnClickedCheckTalk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if( m_btnRecord.GetCheck() > 0 )
	{
		if(m_record) 
		{
			m_record->PostThreadMessage(WM_RECORDSOUND_STARTRECORDING,0,0);
		}
	}
	else
	{

		if(m_record) 
		{
			m_record->PostThreadMessage(WM_RECORDSOUND_STOPRECORDING,0,0);
		}

		Sleep(100);
		m_send->SendData(CMD_RELEASE_WT,VT_TEXT,m_sTalkGroupCode,"");

	}
}
