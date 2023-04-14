//#ifndef __SOCKETPACKET_H__
//#define __SOCKETPACKET_H__





#define MAX_PACKET_SIZE		2048
#define FILE_PACKET_SIZE	8192

#define DELIMITER			"\30\0"
#define ROW_DELIMITER		"\31\0"
#define VL_END				"@#"


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

inline static int STRTOK(const char *src, int nStart, ...)
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

/*
inline static BOOL STRTOK(char *a, char *b)
{
    char *p; 
	p = strtok(b, (const char*) DELIMITER); 
	if(p != NULL) strcpy(a, p);
	else strcpy(a, ""); 

	if(p != NULL) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}
*/


#define PACKET_STX_T			"Q14\0"	
#define MAKE_STX_T(a)			(strcpy((char*) a, PACKET_STX_T))
#define HEADER_SIZE_T			16		//4+4+4+4


//Erorr 
#define P_ERROR_INVALID_USER		10
#define P_ERROR_INVALID_PWD			11
#define P_ERROR_ALREADY_ALLOCATED	12
#define P_ERROR_ALLOCATED_BY_ME		13
#define P_ERROR_ALLOCATED			14
#define P_ERROR_CANCELED			15
#define P_ERROR_INVALID_ITEM		16
#define P_ERROR_DB					17


#define PT_REQUEST			100
#define PT_RESPONSE			101
#define PT_OK				102
#define PT_CANCEL			103
#define PT_ERROR			104
#define PT_NEXT				105
#define PT_END				106
#define PT_PHONE			110
#define PT_PHONE_INFO_SMDR	120
#define PT_PHONE_INFO_TAPI	121
#define PT_MONITER			130 
#define PT_MONITER_LOG		131
#define PT_PHONENUMER_INFO	132
#define PT_DID_ROUTE		143
#define PT_KILL_ME			151
#define PT_SYSTEM_COMMAND	152

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
#define PST_PHONE_NUMBER	130		//키폰데이터
#define PT_SUB_ANSWER				1101
#define PT_SUB_HANGUP				1102
#define PT_SUB_CALL					1103
#define PT_SUB_REDIRECT_ANSWER		1104
#define PT_SUB_DENYAL_ANSWER		1105
#define PT_SUB_MAKE_CALLING_OR_TRANSFER	1106
#define PT_SUB_QUEUE_PAUSE			1107
#define PT_SUB_RECORD_PLAY			1108
#define PT_SUB_MUTE					1109
#define PT_SUB_OP_TRANSFER			1110
#define PT_SUB_OP_PICKUP			1111
#define PT_SUB_MAKECALL_TWO			1112
#define PT_SUB_LOGIN_STATE			1113
#define PT_SUB_RING_REDIRECT		1114
#define PT_SUB_ANSWER_REC_PLAY		1115
#define PT_SUB_RECORDFILE_ID		1116
#define PT_SUB_CTI_PICKUP			1117
#define PT_SUB_DYNAMIC_QUEUE		1118
#define PT_SUB_BLIND_TRANSFER		1119
#define PT_SUB_BLIND_TRANSFER_HANGUP 1120

#define PT_SUB_MONITER_LOG				0
#define PT_SUB_MONITER_CALL				1
#define PT_SUB_MONITER_USER				2
#define PT_SUB_MONITER_SET_ALL_CALL_LINE		30
#define PT_SUB_MONITER_GET_ALL_CALL_LINE		40
#define PT_SUB_MONITER_GET_ANSWER_CALL_LINE		41
#define PT_SUB_MONITER_GET_ARS_CALL_LINE		42
#define PT_SUB_MONITER_GET_ROUTE_CALL_LINE		43
#define PT_SUB_KEYPHONE_INFO			5
#define PT_SUB_MONITER_VERSION			6
#define PT_SUB_MONITER_STARTING_TIME	7
#define PT_SUB_MONITER_ROUTE			8

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

//QPACKET struct
typedef struct _TPACKET {
	char head[4];
	UINT nPacketSize;
	UINT nType;
    UINT nSubType;
	char data[0];
} TPACKET, *PTPACKET;



//#endif

