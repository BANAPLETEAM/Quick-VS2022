#ifndef __SOCKETPACKET_H__
#define __SOCKETPACKET_H__

#include <stdarg.h>

#pragma warning(disable:4200)

#define MAX_PACKET_SIZE			2048
#define FILE_PACKET_SIZE_M		8192
#define FILE_PACKET_SIZE_PC		16375 //16384 - 8(hearder_size) - 1

#define DELIMITER			"\30\0"
#define ROW_DELIMITER		"\31\0"

#define VL_END				"@#"


inline static void STRCPY(char *dst, ...)
{
	char *src;

	va_list vl;
	va_start(vl, dst);

	dst[0] = 0;

	while(strncmp((src = va_arg(vl, char*)), VL_END, strlen(VL_END)) != 0)
	{
		strcat(dst, src);
		strcat(dst, (const char*) DELIMITER);
	}

	va_end(vl);
}

inline static void STRCAT(char *dst, ...)
{
	char *src;

	va_list vl;
	va_start(vl, dst);

	while(strncmp((src = va_arg(vl, char*)), VL_END, strlen(VL_END)) != 0)
	{
		strcat(dst, src);
		strcat(dst, (const char*) DELIMITER);
	}

	va_end(vl);
}

inline static int strcmp_(const char* s1, const char* s2) {
	int ret = 0;
	while (!(ret = *(unsigned char*)s1 - *(unsigned char*)s2) && *s2)
		++s1, ++s2;

	if (ret < 0)
		ret = -1;
	else if (ret > 0)
		ret = 1;

	return ret;
}

inline static int STRTOK(char* src, int nStart, ...)
{
    int pos = nStart;
    int len = (int)strlen(src), i = 0;

//    BANA_LOG("%s", src);

    va_list vl;
    va_start(vl, nStart);
    
    while (TRUE) {
        if (i >= len) {
            break;
        }

        char* dst = va_arg(vl, char*);
		//BANA_LOG("%X", dst);

		if (strncmp(dst, VL_END, strlen(VL_END)) == 0) {
            break;
        }

        for (i = pos; i < len; i++) {
            if (src[i] == '\30') {
                memcpy(dst, &src[pos], i - pos);
                dst[i - pos] = '\0';
                pos = i + 1;
                //BANA_LOG("%s", dst);
                break;
            }
        }
    }

    va_end(vl);
    return pos == nStart ? 0 : pos;
}


#define MAKE_STX(a)			(strcpy((char*) a, PACKET_STX))
#define HEADER_SIZE			8		//4+4+4+4


//General status
#define P_SUCCESS			0
#define P_SOCKET_ERROR		-1
#define P_FAILED			1


//Erorr 
#define P_ERROR_INVALID_USER		10
#define P_ERROR_INVALID_PWD			11
#define P_ERROR_ALREADY_ALLOCATED	12
#define P_ERROR_ALLOCATED_BY_ME		13
#define P_ERROR_ALLOCATED			14
#define P_ERROR_CANCELED			15
#define P_ERROR_INVALID_ITEM		16
#define P_ERROR_DB					17
#define P_ERROR_MAP_EXIST			18
#define P_ERROR_INVALID_MAP			19
#define P_ERROR_FILE_NOT_FOUND		20
#define P_ERROR_NO_TEMP_CNO			30
#define P_ERROR_NO_REAL_CNO			31
#define P_ERROR_DEL_REAL_CNO		32


//QPACKET.szheader
#define PACKET_STX			"Q\0"	


//QPACKET.nType
#define PT_REQUEST			100
#define PT_RESPONSE			101
#define PT_OK				102
#define PT_CANCEL			103
#define PT_ERROR			104
#define PT_NEXT				105
#define PT_END				106
#define PT_DATABASE			107
#define PT_ECHO				108
#define PT_CONNTEST			109
#define PT_CONNTEST2		110
#define PT_DATABASE2		150		//보안상 최초 프로토콜을 변경함
#define PT_FILE				151		//파일전송
#define PT_STATISTIC2		123


//QPAKCET.nSubType
#define PST_LOGIN			100		//로그인
#define PST_ORDER			101		//리스트
#define PST_ALLOCATE		102		//배차
#define PST_DETAIL			103		//상세정보
#define PST_ALL_MSG			104		//전체 메시지
#define PST_COM_MSG			105		//회사별 메시지
#define PST_INFO			106		//정보
#define PST_GPS_DATA		107		//GPS 데이터 
#define PST_UPDATE			108		//프로그램 업데이트
#define PST_FILE			109		//파일전송
#define PST_GPS_DUMMY		110		//GPS 테스트 데이터
#define PST_INSERT_MAP		120		//서버에 맵 추가
#define PST_MAP_LIST		121		//맵 리스트
#define PST_NODE_DATA		122		//맵 노드 데이터
#define PST_NODE_COUNT		123		//노드 수
#define PST_ACK_NODE		124		//노드 인증 추가
#define PST_SEND_FILE		125		//파일 전송
#define PST_FILE_INFO		126		//파일 정보 전송
#define PST_FILE_VERSION	127		//파일 버전
#define PST_WHOLE_FILE_INFO 128		//전체파일 정보
#define PST_FINISH_STATE	129		//완료 상태 전송
#define PST_TAXI_ORDER		130		//TAXI ORDER
#define PST_ALLOCATE_TAXI	131		//TAXI ALLOCATE
#define PST_UPDATE_DESKTOP	132		//업데이트의 버전 체크
#define PST_LOCAL_MSG		140		//전체메시지
#define PST_RIDER_MSG		141		//개별메시지
#define PST_NOT_ATTEND		142		//출근처리가 되지 않음
#define PST_LEAVE_STATE		143		//퇴근처리
#define PST_ALLOCATE_LIST	144		//배차리스트
#define PST_COMPLETE_LIST	145		//완료리스트
#define PST_INCOME_INFO		146		//수입정보
#define	PST_WORK_STOP		147		//업무중지상태
#define PST_ADD_CUSTOMER	150		//인터넷접수 고객등록
#define PST_EDIT_CUSTOMER	151		//인터넷접수 고객수정
#define PST_ADD_ORDER		152		//인터넷접수 오더등록
#define PST_RCP_CHECK		153		//접수확인
#define PST_START_MSG		154		//실시간 메신저 시작
#define PST_SEND_MSG		155		//메신저 데이터 전송(고객->상담원) 
#define PST_SEND_MSG_RCP	156		//메신저 데이터 전송(상담원->고객)
#define PST_RESERVE_TRG		157		//예약 트리거
#define PST_START_MSG_RCP	158		//실시간 메신저 시작(상담원용)
#define PST_LOSE_CONTROL	159		//제어권 잃음
#define	PST_REAL_CNO		160		//실제 고객번호를 얻음
#define PST_COMPANY_INFO	161		//회사정보 요청
#define PST_COMPELTE_CHECK	162		//오더종료체크
#define PST_CHECK_COMCODE	163		//COMCODE 체크
#define PST_CONN_TEST		164		//연결테스트
#define PST_START_ALLOC		165		//배차메시지 수신서비스 시작
#define PST_SEND_ALLOC		166		//배차정보전송
#define PST_SEND_AA_ALLOC	169 
#define PST_SEND_RF_UUID	170

#define PST_CONNECT_DB				200		//데이터베이스 연결
#define PST_EXECUTE_DB				201		//데이터베이스 실행
#define PST_EXECUTE_DB2				209		//데이터베이스 실행, des 모듈변경
#define PST_EXECUTE_DB_WITHOUT_ACK	206		//데이터베이스 실행, 응답패킷없이	
#define PST_JUST_OK					202		//명령을 성공적으로 처리함(리턴없음)
#define PST_PARAMETER_ONLY			203		//명령을 성공적으로 처리함(파라메터 리턴)
#define PST_RECORDSET_ONLY			204		//명령을 성공적으로 처리함(레코드셋 리턴)
#define PST_BOTH_RETURN				205		//명령을 성공적으로 처리함(파라메터 + 레코드셋 리턴)

#define PST_START_MSG2		300		//접수자 통신 메신져 기능
#define PST_START_MSG_RCP2	301		//접수자 통신 메신져 기능
#define PST_MSG_CONN_LIST	302		//메신저 접속 리스트
#define PST_SEND_MSG2		310
#define PST_DISCONNECT		311
#define PST_START_MSG3		312
#define PST_START_MSG4		313
#define PST_MSG_CONN_LIST2	314		//메신저 접속 리스트
#define PST_START_MSG5		320
#define PST_MSG_CONN_LIST3	330		//메신저 접속 리스트
#define PST_SEAT_EMPTY		340		//자리비움
#define PST_SEAT_OCCUPIED	341		//자리채움
#define PST_SEND_MSG3		360	
#define PST_DISCONNECT2		361
#define PST_INTERCALL_RECV	364
#define PST_INTERCALL_RECV2	365


#define PST_RIDER_LICENSE_VALID	400		//기사 면허 정보가 올바른지 경찰청에 조회

//QPACKET.data : the number of Item
#define PNI_LOGIN			2
#define PNI_ORDER			5
#define PNI_ALLOCATE		1
#define PNI_DETAIL			19


//QPACKET.data : the maximum size of data
#define PMS_LOGIN			42		//21+21
#define PMS_ORDER			42		//11+11+3+9+8
#define PMS_ALLOCATE		8		//8
#define PMS_DETAIL			359  	//8+5+5+5+5+10+21+11+15+21+11+15+21+11+15+151+21+5+3

/*
//QPACKET struct
typedef struct _QPACKET {
	char head[4];
	UINT nPacketSize;
	UINT nType;
    UINT nSubType;
	char data[0];
} QPACKET, *PQPACKET;
*/

//QPACKET struct
typedef struct _QPACKET {
	char head[2];
	USHORT nPacketSize;
	USHORT nType;
    USHORT nSubType;
	char data[0];
} QPACKET, *PQPACKET;


typedef struct _POSINFO_PACKET {
	long nLattFrac;
	long nLongFrac;
	short usDir;
	short usSpeed;
	short usState;
	short usDummy;
	char szUserID[0];
} POSINFO_PACKET, *P_POSINFO_PACKET;


typedef struct _MSG_LOGIN_INFO {
	long nCompany;
	long nWNo;
	long nShareCode1;
	long nShareCode2;
	long nShareCode3;
	long nShareCode4;
	long nShareCode5;
	long nShareCode6;
	long nShareCode7;
	long nShareCode8;
	long nShareCode9;
	long nShareCode10;
	long nMsgGroupCode;
	char szCompanyName[255];
	char szBranchName[255];
	char szUserName[255];
	BOOL bIdle;
	BOOL bManager;
	long nDisplayType;
	long etc1;
	long etc2;
	long etc3;
	long etc4;
	long etc5;
	char szEtc1[255];
	char szEtc2[255];	
} MSG_LOGIN_INFO, *P_MSG_LOGIN_INFO;


/*
typedef struct {
	UINT nReadBps;
	UINT nSendBps;
	UINT nConnection;
	UINT nCurQuery;
	UINT nTotalQuery;
	UINT nSessionFail;
	UINT nTransFail;

	UINT nRefreshCount;
	UINT nAllocateCount;
	UINT nCompleteCount;
	UINT nFailLoginCount;
	UINT nRestrictConnCount;
	char szVersion[20];

	UINT nActiveThread;
	UINT nProgramMemory;
	UINT nCpuUsage;
	double fMemUsage;
	COleDateTime dtStart;

} STATSTRUCT, *PSTATSTRUCT;
*/



#endif

