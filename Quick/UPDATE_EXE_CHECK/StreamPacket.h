#pragma once

#pragma pack(push, 1) 

#define STREAM_BUFFER			17000

class CStreamPacket 
{
public:
	CStreamPacket()
	{
		Init();
	}

	struct 
	{
		char m_szhead[2];
		UINT m_nPacketSize;				//이거 외부에서 쓰면 안됨, GetDataSize 사용바람
		BYTE m_nType;
		BYTE m_nSubType;

		union
		{
			UINT m_nData;
			struct
			{
				UINT m_nData8	:8;
				UINT m_nData24	:24;
			};
			struct
			{
				UINT m_nData16_1	:16;
				UINT m_nData16_2	:16;
			};
			struct
			{
				UINT m_nData8_1	:8;
				UINT m_nData8_2	:8;
				UINT m_nData8_3	:8;
				UINT m_nData8_4	:8;
			};
		};

		UINT m_nTranID			:6;		
		UINT m_bHasNextPacket	:1;
		UINT m_bCypherPacket	:1;
		UINT m_nPacketSeq		:24;

		char m_szData[0];
	};


	void Init()
	{
		m_szhead[0] = 'Q';
		m_szhead[1] = '\1';

		m_nPacketSize = 0;
		m_nType = 0;
		m_nSubType = 0;
		m_nPacketSeq = 0;
		m_nTranID = 0;
		m_bHasNextPacket = 0;
	}
};


#pragma pack(pop)




#define READ_SIZE			1024
#define STREAM_HEAD_SIZE	16
#define P_SUCCESS			0
#define P_SOCKET_ERROR		-1
#define P_FAILED			1
#define GRACEFUL_CLOSE		20000
#define WM_ASYNC_EVENT		(WM_USER + 101)
#define SOCKET				UINT
#define DEBUG_PRINT()		{ mkLog.Print("%s, %d\n", TEXT(__FILE__), TEXT(__LINE__)); }
//#define MAKE_STX(a)			(strcpy((char*) a, PACKET_STX))
#define HEADER_SIZE			8		//4+4+4+4
