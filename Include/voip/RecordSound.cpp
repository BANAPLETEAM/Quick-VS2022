// RecordSound.cpp : 구현 파일입니다.
//

#include "stdafx.h"
//#include "Sound.h"
#include "RecordSound.h"
#include "WriteSound.h"
#include "PlaySound.h"
//#include "u-law.h"
//#include "SoundDlg.h"


// CRecordSound

IMPLEMENT_DYNCREATE(CRecordSound, CWinThread)

CRecordSound::CRecordSound()
{

}

CRecordSound::CRecordSound(CWnd* pWnd,CPlaySound* playsound,const char* szSaveFileName) 
{
	play     = playsound;
	write	 = NULL;
	pWnd4Msg = pWnd;

//	log.Open("recfile.txt",CFile::modeCreate | CFile::modeWrite);
//	log.WriteString("In the Recordsound Constructor\n");

	m_brecording	= FALSE;
	m_isallocated	= 0; 

	GetDevProperty();

	//Create Headers for buffering
	PreCreateHeader();
	m_noise = NULL;

//	m_gsm_state = gsm_create();
			

	memset(&m_WaveFormatEx,0x00,sizeof(m_WaveFormatEx));
	
	m_WaveFormatEx.wFormatTag=WAVE_FORMAT_PCM;
	m_WaveFormatEx.nChannels=1;
	m_WaveFormatEx.wBitsPerSample=8;
	m_WaveFormatEx.cbSize=0;
	m_WaveFormatEx.nSamplesPerSec=SAMPLERSEC;  //22.05 KHz
	
	m_WaveFormatEx.nBlockAlign=1; //(m_WaveFormatEx.wBitsPerSample/8)*m_WaveFormatEx.nChannels;
	
	m_WaveFormatEx.nAvgBytesPerSec=SAMPLERSEC ;  //m_WaveFormatEx.nBlockAlign;

	if(szSaveFileName)
	{
		m_sFname	= szSaveFileName;
		write		= new CWriteSound;
		write->CreateThread();
	}
}           

CRecordSound::~CRecordSound()
{
//	log.Close();
	if(!m_isallocated)
	return;


	for(int i=0;i<MAXRECBUFFER;i++)
	{
		if(rechead[i])
		{
			if(rechead[i]->lpData) delete[] (rechead[i]->lpData);
				delete rechead[i];

			if(out[i]->lpData) delete[] (out[i]->lpData);
				delete out[i];
		}
	}

	if(m_noise)		delete[] m_noise;
//	if(m_gsm_state) gsm_destroy(m_gsm_state);
}

BOOL CRecordSound::InitInstance()
{
	// TODO: 여기에서 각 스레드에 대한 초기화를 수행합니다.
	return TRUE;
}

int CRecordSound::ExitInstance()
{
	// TODO: 여기에서 각 스레드에 대한 정리를 수행합니다.
	return CWinThread::ExitInstance();
}


LPWAVEHDR  CRecordSound::CreateWaveHeader()
{
	LPWAVEHDR lpHdr = new WAVEHDR;
	
	if(lpHdr==NULL)
	{
//		log.WriteString("\n Unable to allocate the memory");
		return NULL;
	}
	
	ZeroMemory(lpHdr, sizeof(WAVEHDR));
	char* lpByte = new char[RECBUFFER];//m_WaveFormatEx.nBlockAlign*SOUNDSAMPLES)];
	
	if(lpByte==NULL)
	{
//		log.WriteString("\n Unable to allocate the memory");
		return NULL;
	}
	lpHdr->lpData =  lpByte;
	lpHdr->dwBufferLength =RECBUFFER;   // (m_WaveFormatEx.nBlockAlign*SOUNDSAMPLES);
	return lpHdr;

}

void CRecordSound::PreCreateHeader()
{

	for(int i=0;i<MAXRECBUFFER;i++)
	{
		rechead[i]=CreateWaveHeader();
		out[i]=CreateWaveHeader();
	}

	m_outIdx = 0;
	m_isallocated=1;
}




void CRecordSound::GetDevProperty()
{
	WAVEINCAPS wavecap;
	int i,j,n=waveInGetNumDevs();
	char str[100];
	CString format;	
	int form[]={WAVE_FORMAT_1M08, 
				WAVE_FORMAT_1M16,
				WAVE_FORMAT_1S08,
				WAVE_FORMAT_1S16,
				WAVE_FORMAT_2M08,
				WAVE_FORMAT_2M16,
				WAVE_FORMAT_2S08,
				WAVE_FORMAT_2S16,
				WAVE_FORMAT_4M08,
				WAVE_FORMAT_4M16,
				WAVE_FORMAT_4S08,
				WAVE_FORMAT_4S16,
				};	
		
	CString fstr[]={
				"WAVE_FORMAT_1M08", 
				"WAVE_FORMAT_1M16",
				"WAVE_FORMAT_1S08",
				"WAVE_FORMAT_1S16",
				"WAVE_FORMAT_2M08",
				"WAVE_FORMAT_2M16",
				"WAVE_FORMAT_2S08",
				"WAVE_FORMAT_2S16",
				"WAVE_FORMAT_4M08",
				"WAVE_FORMAT_4M16",
				"WAVE_FORMAT_4S08",
				"WAVE_FORMAT_4S16",
				};


	sprintf(str,"\n Total no of devices = %d ",n);
//	log.WriteString(str);
	
	for(i=0;i<n;i++)
	{
		waveInGetDevCaps(i,&wavecap,sizeof(wavecap));
		sprintf(str,"\n Product Name = %s ",wavecap.szPname);
//		log.WriteString(str);
		sprintf(str,"\n No of channels %d ",wavecap.wChannels);

		format.Empty();
		format="\nIt supports  \n";
		for(j=0;j<12;j++)
		{
			if( (wavecap.dwFormats & (unsigned)form[j]) ==(unsigned) form[j])
			{
				format+=fstr[j]+"\n";	
			}
		}
	
//		log.WriteString(format);
	}

}

void CRecordSound::displayError(int mmReturn,char errmsg[])
{
	char errorbuffer[MAX_PATH];
	char errorbuffer1[MAX_PATH];

	waveInGetErrorText( mmReturn,errorbuffer,MAX_PATH);
	sprintf(errorbuffer1,"RECORD: %s : %x : %s",errmsg,mmReturn,errorbuffer);
	AfxMessageBox(errorbuffer1);  
}

BEGIN_MESSAGE_MAP(CRecordSound, CWinThread)
ON_THREAD_MESSAGE(MM_WIM_DATA, OnSoundData)
ON_THREAD_MESSAGE(WM_RECORDSOUND_STARTRECORDING,OnStartRecording)
ON_THREAD_MESSAGE(WM_RECORDSOUND_STOPRECORDING,OnStopRecording)
ON_THREAD_MESSAGE(WM_RECORDSOUND_ENDTHREAD,OnEndThread)
END_MESSAGE_MAP()


// CRecordSound 메시지 처리기입니다.

void CRecordSound::OnStartRecording(WPARAM wp,LPARAM lp)
{

	if(TRUE == m_brecording) return;

	if(write)
	{
		char* fname = new char[200];
		strcpy(fname,m_sFname);		
		write->PostThreadMessage(WM_WRITESOUND_CREATEFILE,0,(LPARAM)fname);
	}

	MMRESULT mmReturn = ::waveInOpen( &m_hRecord, WAVE_MAPPER,
			&m_WaveFormatEx, ::GetCurrentThreadId(), 0, CALLBACK_THREAD);
	
/*	//For GSM COMPRESSION use this code
	MMRESULT mmReturn = ::waveInOpen( &m_hRecord, WAVE_MAPPER,
			&m_WaveFormatEx.wfx, ::GetCurrentThreadId(), 0, CALLBACK_THREAD);
*/	

//	log.WriteString("In OnStartrecording\n");
	//Error has occured while opening device
		
	if(mmReturn!=MMSYSERR_NOERROR )
	{
		displayError(mmReturn,"Open");
		return;
	}					
			
	for(int i=0; i < MAXRECBUFFER ; i++)
	{
		mmReturn = ::waveInPrepareHeader(m_hRecord,rechead[i], sizeof(WAVEHDR));
		mmReturn = ::waveInAddBuffer(m_hRecord, rechead[i], sizeof(WAVEHDR));
	}
				
			
					
	mmReturn = ::waveInStart(m_hRecord);
			
	
	if(mmReturn!=MMSYSERR_NOERROR )	displayError(mmReturn,"Start");
	else							m_brecording=TRUE;
					
	return;
}


void CRecordSound::OnStopRecording(WPARAM wp,LPARAM lp)
{
	MMRESULT mmReturn = 0;
//	log.WriteString("\nIn the onstop recording");	
	
	if(!m_brecording)			return;

	mmReturn = ::waveInStop(m_hRecord);
		
		
	//To get the remaining sound data from buffer
	//Reset will call OnSoundData function	
		
	
	if(MMSYSERR_NOERROR == mmReturn)
	{
		m_brecording = FALSE;
		mmReturn = ::waveInReset(m_hRecord);  
	}
		
	
	/****  Code has been changed ****/	
	//	if(!mmReturn)
	//		recording = FALSE;
		
	Sleep(500); 
	
	if(!mmReturn)
	{
		mmReturn = ::waveInClose(m_hRecord);
		if(write) write->PostThreadMessage(WM_WRITESOUND_CLOSEFILE,0,0);
	}

	return;
}

////////////////////////////////////////////////////
// Call back function for WM_WIM_DATA
//


#ifdef __cplusplus
extern "C" {
#endif
extern  int WINAPI compress (unsigned char *dest,  unsigned long *destLen,
                                 const unsigned char  *source, unsigned long sourceLen);

#ifdef __cplusplus
}
#endif


void CRecordSound::OnSoundData(WPARAM wParam, LPARAM lParam)
{
//	log.WriteString("\nIn the onsound data");

	LPWAVEHDR lpHdr = (LPWAVEHDR) lParam;

	if(lpHdr->dwBytesRecorded==0 || lpHdr==NULL)
	{
		return;
	}	
	::waveInUnprepareHeader(m_hRecord, lpHdr, sizeof(WAVEHDR));

	if(NULL == m_noise && RECBUFFER == lpHdr->dwBufferLength)
	{	
		m_noise = new char[RECBUFFER];
		memcpy(m_noise, lpHdr->lpData,RECBUFFER);	
	}

	/*
	if(m_noise)
	{
		char* lp = (char*)lpHdr->lpData;
		for(int i = 0; i < RECBUFFER;i++) lp[i] =lp[i]&m_noise[i];
	}
	*/

//	if(write)	write->PostThreadMessage(WM_WRITESOUND_WRITEDATA,0,(LPARAM)lpHdr);
	if(pWnd4Msg)
	{
		LPWAVEHDR lpHdrPlay =  out[ m_outIdx++ % MAXRECBUFFER ];
		if(MAXRECBUFFER == m_outIdx) m_outIdx = 0;

		DWORD dtTick = ::GetTickCount();
		lpHdrPlay->dwBufferLength = RECBUFFER;
		unsigned long lDestLong = lpHdrPlay->dwBufferLength;

		int nRet = 0;

		nRet =  compress ((unsigned char*) lpHdrPlay->lpData,&lDestLong,
				  (unsigned char*) lpHdr->lpData, (unsigned long)lpHdr->dwBufferLength);

		if(0 == nRet)
		{
			lpHdrPlay->dwBufferLength = lDestLong;
			long lgap = (::GetTickCount() - dtTick);

			lpHdrPlay->dwFlags = 0;

		}
		else
		{
				CString str;
				str.Format(_T("Compress Error %d\r\n"),nRet);

				memcpy(lpHdrPlay->lpData,lpHdr->lpData,lpHdr->dwBufferLength);
				lpHdrPlay->dwBufferLength = lpHdr->dwBufferLength;
				lpHdrPlay->dwFlags = 0;
		};



	
/*
		short out[160];
		int out_lenght = ulawDecode( (unsigned char*)lpHdr->lpData, out, 160);

		if( GSM_ENCODED_FRAME_SIZE ==  gsm_encode(m_gsm_state, (short*) out, (unsigned char*) lpHdrPlay->lpData) )
		{
			lpHdrPlay->dwBufferLength = GSM_ENCODED_FRAME_SIZE;
			lpHdrPlay->dwFlags = 0;
			nRet = 0;
		}
		else
		{

		}



		{
			int nDecodeRet = gsm_decode(m_gsm_state, (unsigned char*)lpHdrPlay->lpData,(short*)out);
			int out_lenght =  ulawEncode(out,(unsigned char*)lpHdr->lpData,160);
			lpHdr->dwBufferLength = out_lenght;
			if(write)	write->PostThreadMessage(WM_WRITESOUND_WRITEDATA,0,(LPARAM)lpHdr);
			
		}
*/
		pWnd4Msg->SendMessage(MM_WIM_DATA,0,(LPARAM)lpHdrPlay);
	}

	if(play)
	{
		LPWAVEHDR lpHdrPlay =  CreateWaveHeader();
		memcpy(lpHdrPlay->lpData,lpHdr->lpData,lpHdr->dwBufferLength);
		lpHdrPlay->dwBufferLength = lpHdr->dwBufferLength;
		lpHdrPlay->dwFlags = 0;

		play->PlaySound(lpHdrPlay);
//		play->PostThreadMessage(WM_PLAYSOUND_PLAYBLOCK,0,(LPARAM)lpHdr);
	}

	


/*
	//Send message to server
	if(lpHdr->lpData!=NULL )
	((Display*)dlg)->sendMessage(lpHdr->lpData,lpHdr->dwBytesRecorded);
*/		

//	if(m_brecording)
	{
		//Reuse the old buffer
		::waveInPrepareHeader(m_hRecord,lpHdr, sizeof(WAVEHDR));
		::waveInAddBuffer(m_hRecord, lpHdr, sizeof(WAVEHDR));
	}


	return;
}

/////////////////////////////////////////////////
//  Quit the Thread....
//
//
void CRecordSound::OnEndThread(WPARAM wp,LPARAM lp)
{
	if(write) write->PostThreadMessage(WM_WRITESOUND_ENDTHREAD,0,0);
//	log.WriteString("\nIN the end thread");	
	
	if(m_brecording)
	OnStopRecording(0,0);

	::PostQuitMessage(0);
}

