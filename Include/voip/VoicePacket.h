#ifndef __VOICEPACKET_H__
#define __VOICEPACKET_H__


#define MAX_PACKET_SIZE		2048
#define FILE_PACKET_SIZE	8192

#define DELIMITER			"\30\0"
#define ROW_DELIMITER		"\31\0"

#define VL_END				"@#"

/*
inline static void STRCPY(char *a, const char*b)
{
	if(b == NULL || strlen(b) < 1)	strcpy(a, " ");
	else strcpy(a, b);
	strcat(a, (const char*) DELIMITER);
}

inline static void STRCAT(char *a, const char *b)
{
	if(b == NULL || strlen(b) < 1)	
	{
		strcat(a, " ");
	}
	else strcat(a, b);
	strcat(a,  (const char*) DELIMITER);
}


inline static int STRTOK(char *src, int nStart, ...)
{
	char *dst;
	int pos = nStart;
	int len = strlen(src), i;

	va_list vl;
	va_start(vl, src);
	i = va_arg(vl, int);

	while(strncmp((dst = va_arg(vl, char*)), VL_END, strlen(VL_END)) != 0)
	{
		if(i == len) return 0;
		for(i = pos; i < len; i++)
		{
			if(src[i] == '\30')
			{
				memcpy(dst, &src[pos], i - pos);
				dst[i - pos] = '\0';
				pos = i + 1;
				break;
			}
		}
	}

	va_end(vl);
	return pos == nStart ? 0 : pos ;
}


//#define MAKE_STX(a)			(strcpy((char*) a, PACKET_STX))
*/


//Erorr 
#define P_ERROR_INVALID_USER		10
#define P_ERROR_INVALID_PWD			11
#define P_ERROR_ALREADY_ALLOCATED	12
#define P_ERROR_ALLOCATED_BY_ME		13
#define P_ERROR_ALLOCATED			14
#define P_ERROR_CANCELED			15
#define P_ERROR_INVALID_ITEM		16
#define P_ERROR_DB					17


//VOIP DLG
#define WM_CONN_LIST			WM_USER + 21
#define WM_ADD_CONN_USER		WM_USER + 22
#define WM_REM_CONN_USER		WM_USER + 23
#define WM_CURRENT_COMM_USER	WM_USER + 24
#define WM_STATE_MSG			WM_USER + 25
#define WM_CONN_STATE			WM_USER + 26


#define PST_ERROR				 99
#define PST_LOGIN				100		//로그인
#define PST_ECHO				190		//
#define PST_RING				200		//
#define PST_ANSWER				210		//
#define PST_HANGUP				220		//
#define PST_DELIVERY_1			300		//1명에게 전달
#define PST_DELIVERY_COMPANY	320		//동보 전달  동일회사
#define PST_DELIVERY_SHARECODE	340		//동보 전달  동일1차코드
#define PST_DELIVERY_ALLIANCE	360		//동보 전달  동일연합
#define PST_DELIVERY_CITY		380		//동보 전달  동일지역
#define PST_DELIVERY_ALL		400		//동보 전달  동일지역
#define PST_LOGIN_LIST			500		//현재 로그인된 LIST
#define PST_CONNECT_EVENT		510		//타 사용자 접속시 정보
#define PST_DISCONNECT_EVENT	520		//타 사용자 접속 해제시 정보


#define CMD_ANSWER				210		//
#define CMD_HANGUP				220		//
#define CMD_LOGIN_LIST_G		530		//현재 동일그룹으로 로그인된 LIST
#define CMD_ADJ_STD_TIME		550		//서버와 시간 간격을 리턴

#define CMD_MAKE_COMPANY_WT		690		//워키토키 통화를 위한 그룹을 설정한다
#define CMD_MAKE_GROUP_WT		700		//워키토키 통화를 위한 그룹을 설정한다
#define CMD_MAKE_GROUP_TP		705		//쌍방향 통화를 위한 그룹을 설정한다
#define CMD_MAKE_GROUP_DC		710		//쌍방향 통화를 위한 그룹을 설정한다
#define CMD_DELETE_GROUP		720		//통화를 위한 그룹을 해제한다
#define CMD_INVITE				730		//통화를 위한 초대제의
#define CMD_INVITE_FORCE		740		//통화를 위한 무조건 가입
#define CMD_ACCEPT_INVITE		750		//통화제의에 응답
#define CMD_GROUP_JOINED		760		//그룹에 참가 되었음
#define CMD_GROUP_OUT			770		//그룹에서 탈퇴
#define CMD_GROUP_NO_EXGIST		775		//그룹이 없음


#define CMD_DELIVERY_1			800		//1:1 
#define CMD_DELIVERY_G			810		//그룹 전송
#define CMD_DELIVERY_COMPANY	820		//동보 전달  동일회사
#define CMD_DELIVERY_SHARECODE	840		//동보 전달  동일1차코드
#define CMD_DELIVERY_ALLIANCE	860		//동보 전달  동일연합
#define CMD_DELIVERY_CITY		880		//동보 전달  동일지역
#define CMD_DELIVERY_ALL		900		//동보 전달
#define CMD_PUSH_WT				910		//워키토키 통화에서 통화톤큰을 가질수 있는지
#define CMD_RELEASE_WT			920		//워키토키 통화에서 통화해제
#define CMD_FREE_STATE_WT		930		//워키토키 토큰 해제
#define CMD_NOT_FREE_STATE_WT	940		//워키토키 토큰을 가질수 없어 전송 불가
#define CMD_FAIL_DELIVERY		950		//특정 원인으로 인해 보이스 전송 실패



#define  MT_USAGE_SEND					0                // 보내기 전용 SOCKET
#define  MT_USAGE_RECV					1                // 받기   전용 SOCKET

#define GROUP_WT						0				// 워키토키
#define GROUP_TP						1				// 전화통화
#define GROUP_DC						2				// 1:1 전화통화

#define PH_HANGUP						0
#define PH_RING							1
#define PH_ANSWER						2
/**************************************************************************
 * The Voice Talk Identity for socket message                             *
 **************************************************************************/
#define VT_IDENTITY               0xCC   


/**************************************************************************
 *  Voive Talk constants definitions                                      *
 **************************************************************************/
#define  VT_MAX      0x1000

#define  VT_TEXT     0x00                // Text message 
#define  VT_WAVE1M08 0x01                // Voice: 11.025 kHz, Mono, 8-bit  
#define  VT_WAVE1S08 0x02                // Voice: 11.025 kHz, Stereo, 8-bit
#define  VT_WAVE1M16 0x03                // Voice: 11.025 kHz, Mono, 16-bit 
#define  VT_WAVE1S16 0x04                // Voice: 11.025 kHz, Stereo, 16-bit 
#define  VT_WAVE2M08 0x05                // Voice: 22.05 kHz, Mono, 8-bit 
#define  VT_WAVE2S08 0x06                // Voice: 22.05 kHz, Stereo, 8-bit  
#define  VT_WAVE2M16 0x07                // Voice: 22.05 kHz, Mono, 16-bit 
#define  VT_WAVE2S16 0x08                // Voice: 22.05 kHz, Stereo, 16-bit 
#define  VT_WAVE4M08 0x09                // Voice: 44.1 kHz, Mono, 8-bit  
#define  VT_WAVE4S08 0x0A                // Voice: 44.1 kHz, Stereo, 8-bit  
#define  VT_WAVE4M16 0x0B                // Voice: 44.1 kHz, Mono, 16-bit 
#define  VT_WAVE4S16 0x0C                // Voice: 44.1 kHz, Stereo, 16-bit
#define  VT_WKITKI	 0x10				 // 워키토키용
#define  VT_WAVEST	 0x20				 // 단방향 대화
#define  VT_WAVECP	 0x40				 // 회사원전송
#define	 VT_GSM		 0x100				 // GSM CODEC
#define  VT_AMRNB	 0x200				 // AMR-NB CODEC


#pragma pack(push, 1) //- packing is now 1
typedef struct _VTMSG  
{
    BYTE  m_ucIdentity;   // Identifies the message  
    UINT  m_ucCmd;        // message command
    UINT  m_ucMsgType;    // The message type 
	char  m_sToID[21];
	char  m_sName[21];
	UINT  m_uToCompany;	  // 메세지를 받을 대상
	UINT  m_uToRNo;		  // 메세지를 받을 대상
	long  m_lSTDCurMil;	  // 서버기준 1/1000 단위 시각
    UINT  m_lLength;      // size of the message block 
	BYTE  m_pData[0];	  // message data
} VTMSG, *LPVTMSG;

#pragma pack(pop) 

#define HEADER_SIZE		(sizeof(VTMSG))

typedef struct tagVTMSGInfo
{
	UINT		m_uVTMsgState;
	BOOL		m_bWaveST;
	BOOL		m_bCompanyWT;
	CString		m_sChannel;
	int			m_nGroupType;
	BOOL		m_bCaller;
	int			m_nCallState;
} VTMSGInfo,*LPVTMSGInfo;

#endif

