/*----------------------------------------------------------------------
Debugging Applications for Microsoft .NET and Microsoft Windows
Copyright ?1997-2003 John Robbins -- All rights reserved.
----------------------------------------------------------------------*/
#include "stdafx.h"
#include "resource.h"
#include "CrashDlg.h"
#include <direct.h>

// CCrashDlg dialog

#ifndef _DEBUG



IMPLEMENT_DYNAMIC(CCrashDlg, CMyDialog)
CCrashDlg::CCrashDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CCrashDlg::IDD, pParent)
{
}

CCrashDlg::~CCrashDlg()
{
}

void CCrashDlg::DoDataExchange(CDataExchange* pDX)
{
    CMyDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_FAULTREASON, m_cFaultReason);
    DDX_Control(pDX, IDC_REGISTERS, m_cRegisters);
    DDX_Control(pDX, IDC_CALLSTACK, m_cCallStackList);
    DDX_Control(pDX, IDC_MINIDUMP, m_cMiniDumpBtn);
}


BEGIN_MESSAGE_MAP(CCrashDlg, CMyDialog)
    ON_BN_CLICKED(IDC_MINIDUMP, OnBnClickedMinidump)
	ON_BN_CLICKED(IDOK, &CCrashDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CCrashDlg message handlers
BOOL CCrashDlg::OnInitDialog()
{
    CMyDialog::OnInitDialog();
    
	ASSERT(NULL != m_pExptPtrs);

	LPCTSTR szStr;
	CString strFaultReason, strRegisters;

	strFaultReason.Format("%S", GetFaultReason(m_pExptPtrs));
	m_cFaultReason.SetWindowText(strFaultReason);
	strRegisters.Format("%S", GetRegisterString(m_pExptPtrs));
	m_cRegisters.SetWindowText(strRegisters);
    
    szStr = GetFirstStackTraceString(GSTSO_MODULE |
                                        GSTSO_SYMBOL |
                                        GSTSO_SRCLINE,
                                       m_pExptPtrs);
    while(NULL != szStr)
    {
		CString strCallStack;
		strCallStack.Format("%S", szStr);
	    m_cCallStackList.AddString(strCallStack);
        szStr = GetNextStackTraceString(GSTSO_MODULE     |
                                            GSTSO_SYMBOL   |
                                            GSTSO_SRCLINE   ,
                                          m_pExptPtrs) ;
    }
    
    if(FALSE == IsMiniDumpFunctionAvailable())
    {
        m_cMiniDumpBtn.EnableWindow(FALSE);
    }

    return(FALSE);
}

void CCrashDlg::OnBnClickedMinidump()
{
	char szPathName[_MAX_PATH], szFileName[_MAX_PATH], szCurTime[100];
	SYSTEMTIME st;
//	HANDLE hFile;
//DWORD dwWritten;

	strcpy(szPathName, (LPSTR)(LPCTSTR)GetModuleFullPath());
	strcat(szPathName, "MiniDump");
	mkdir(szPathName);

	GetLocalTime(&st);
	sprintf(szCurTime, "%d%02d%02d_%02d%02d%02d_%d", st.wYear, st.wMonth, st.wDay,
		st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);

	if(TRUE == IsMiniDumpFunctionAvailable())
	{
		strcpy(szFileName, szPathName);
		strcat(szFileName, "\\CRASH_");
		strcat(szFileName, szCurTime);
		strcat(szFileName, ".DMP");

		BSUMDRET eRet = CreateCurrentProcessCrashDumpA(MiniDumpWithHandleData,
			szFileName,
			GetCurrentThreadId(),
			m_pExptPtrs);

		ASSERT(eDUMP_SUCCEEDED == eRet);
		if(eDUMP_SUCCEEDED != eRet)
		{
			CString cPrompt ;
			cPrompt.Format(_T ("Dump failed : %d"), eRet);
			AfxMessageBox(cPrompt);
		}
	}
}

void CCrashDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();
}


#endif
