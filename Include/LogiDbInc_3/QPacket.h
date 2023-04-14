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
#define PT_DATABASE2		150		//���Ȼ� ���� ���������� ������
#define PT_FILE				151		//��������
#define PT_STATISTIC2		123


//QPAKCET.nSubType
#define PST_LOGIN			100		//�α���
#define PST_ORDER			101		//����Ʈ
#define PST_ALLOCATE		102		//����
#define PST_DETAIL			103		//������
#define PST_ALL_MSG			104		//��ü �޽���
#define PST_COM_MSG			105		//ȸ�纰 �޽���
#define PST_INFO			106		//����
#define PST_GPS_DATA		107		//GPS ������ 
#define PST_UPDATE			108		//���α׷� ������Ʈ
#define PST_FILE			109		//��������
#define PST_GPS_DUMMY		110		//GPS �׽�Ʈ ������
#define PST_INSERT_MAP		120		//������ �� �߰�
#define PST_MAP_LIST		121		//�� ����Ʈ
#define PST_NODE_DATA		122		//�� ��� ������
#define PST_NODE_COUNT		123		//��� ��
#define PST_ACK_NODE		124		//��� ���� �߰�
#define PST_SEND_FILE		125		//���� ����
#define PST_FILE_INFO		126		//���� ���� ����
#define PST_FILE_VERSION	127		//���� ����
#define PST_WHOLE_FILE_INFO 128		//��ü���� ����
#define PST_FINISH_STATE	129		//�Ϸ� ���� ����
#define PST_TAXI_ORDER		130		//TAXI ORDER
#define PST_ALLOCATE_TAXI	131		//TAXI ALLOCATE
#define PST_UPDATE_DESKTOP	132		//������Ʈ�� ���� üũ
#define PST_LOCAL_MSG		140		//��ü�޽���
#define PST_RIDER_MSG		141		//�����޽���
#define PST_NOT_ATTEND		142		//���ó���� ���� ����
#define PST_LEAVE_STATE		143		//���ó��
#define PST_ALLOCATE_LIST	144		//��������Ʈ
#define PST_COMPLETE_LIST	145		//�ϷḮ��Ʈ
#define PST_INCOME_INFO		146		//��������
#define	PST_WORK_STOP		147		//������������
#define PST_ADD_CUSTOMER	150		//���ͳ����� �����
#define PST_EDIT_CUSTOMER	151		//���ͳ����� ������
#define PST_ADD_ORDER		152		//���ͳ����� �������
#define PST_RCP_CHECK		153		//����Ȯ��
#define PST_START_MSG		154		//�ǽð� �޽��� ����
#define PST_SEND_MSG		155		//�޽��� ������ ����(��->����) 
#define PST_SEND_MSG_RCP	156		//�޽��� ������ ����(����->��)
#define PST_RESERVE_TRG		157		//���� Ʈ����
#define PST_START_MSG_RCP	158		//�ǽð� �޽��� ����(������)
#define PST_LOSE_CONTROL	159		//����� ����
#define	PST_REAL_CNO		160		//���� ����ȣ�� ����
#define PST_COMPANY_INFO	161		//ȸ������ ��û
#define PST_COMPELTE_CHECK	162		//��������üũ
#define PST_CHECK_COMCODE	163		//COMCODE üũ
#define PST_CONN_TEST		164		//�����׽�Ʈ
#define PST_START_ALLOC		165		//�����޽��� ���ż��� ����
#define PST_SEND_ALLOC		166		//������������
#define PST_SEND_AA_ALLOC	169 
#define PST_SEND_RF_UUID	170

#define PST_CONNECT_DB				200		//�����ͺ��̽� ����
#define PST_EXECUTE_DB				201		//�����ͺ��̽� ����
#define PST_EXECUTE_DB2				209		//�����ͺ��̽� ����, des ��⺯��
#define PST_EXECUTE_DB_WITHOUT_ACK	206		//�����ͺ��̽� ����, ������Ŷ����	
#define PST_JUST_OK					202		//����� ���������� ó����(���Ͼ���)
#define PST_PARAMETER_ONLY			203		//����� ���������� ó����(�Ķ���� ����)
#define PST_RECORDSET_ONLY			204		//����� ���������� ó����(���ڵ�� ����)
#define PST_BOTH_RETURN				205		//����� ���������� ó����(�Ķ���� + ���ڵ�� ����)

#define PST_START_MSG2		300		//������ ��� �޽��� ���
#define PST_START_MSG_RCP2	301		//������ ��� �޽��� ���
#define PST_MSG_CONN_LIST	302		//�޽��� ���� ����Ʈ
#define PST_SEND_MSG2		310
#define PST_DISCONNECT		311
#define PST_START_MSG3		312
#define PST_START_MSG4		313
#define PST_MSG_CONN_LIST2	314		//�޽��� ���� ����Ʈ
#define PST_START_MSG5		320
#define PST_MSG_CONN_LIST3	330		//�޽��� ���� ����Ʈ
#define PST_SEAT_EMPTY		340		//�ڸ����
#define PST_SEAT_OCCUPIED	341		//�ڸ�ä��
#define PST_SEND_MSG3		360	
#define PST_DISCONNECT2		361
#define PST_INTERCALL_RECV	364
#define PST_INTERCALL_RECV2	365


#define PST_RIDER_LICENSE_VALID	400		//��� ���� ������ �ùٸ��� ����û�� ��ȸ

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

