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

			if(strTitle.Find("[ISMOR101-������Ȳ]") >= 0 ||
				strTitle.Find("õ������") >= 0 || 
				strTitle.Find("SONJA") >= 0 || 
				strTitle.Find("������") >= 0 || 
				strTitle.Find("����") >= 0)
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

	return MINUTE * 60; //�����̸� 1�ð� �Ŀ� ���
}

BOOL CCaptureUpload::CaptureImage()
{
	CImage capImage;
	HDC hProcessDC = ::GetDC(m_hWnd); // <-- ĸ�� �ϰ����ϴ� process�� HWND �� �־��ش�.
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
	//1. Bitmap �����͸� �����ϱ����� stream ���� ����
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
	//2. stream ���Ͽ� Bitmap ������ ����
	hr = capImage.Save(pStream, Gdiplus::ImageFormatPNG);//stream���Ͽ� bmp���� ����
	if(FAILED(hr))
		return FALSE;

	capImage.ReleaseDC();


	///////////////////////////////////////////////////////////////////////
	//3. stream ���Ͽ� ����� Bitmap �����͸� BYTE �����ͷ� ��ȯ
	BYTE* pBuff = NULL;
	ULONG nRead = 0;

	ULARGE_INTEGER uFileSize;
	LARGE_INTEGER lnOffset = {0,};
	lnOffset.QuadPart = 0;

	pStream->Seek(lnOffset, STREAM_SEEK_END, &uFileSize);//�̹��� ������ ũ�⸦ ����
	pStream->Seek(lnOffset, STREAM_SEEK_SET, NULL);//��Ʈ������ ���� ������ ������ �̵�

	if(uFileSize.HighPart == 0 && uFileSize.LowPart == 0)
		return FALSE;

	ULONG nFileSize = uFileSize.LowPart;
	m_pImageBuffer = new CHAR[nFileSize];
	if(!m_pImageBuffer)
		return FALSE;//�޸��Ҵ� ����

	hr = pStream->Read(m_pImageBuffer, nFileSize, &nRead);
	if(nRead < nFileSize || FAILED(hr))
	{
		//����ũ�� ��ŭ ������ �б� ����
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
			throw "������ ������ �� �����ϴ�.";

		CMkRecordset rs(pMkDb);
		UINT nType = PT_OK, nSubType = PST_START_UPDATE_UPLOAD, nSize = 0;
		if(!rs.ExecuteRecordsetOnly(nType, nSubType, nSize, ""))
			throw "����߿� ������ �߻��߽��ϴ�.";

		rs.GetFieldValue(0, strServerPath);
		rs.GetFieldValue(1, strBackup);
		rs.GetFieldValue(2, strUpdateFiles);
		rs.GetFieldValue(3, strUpdateSystem);
		rs.Close();

		CString strServerFileName = strServerPath + "\\" + strBackup + "\\QuickImage\\" + strFileName;

		if(!pMkDb->UploadFile(strServerFileName, m_pImageBuffer, m_nFileSize))
			throw "���� ���ε��߿� �����߻�";

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