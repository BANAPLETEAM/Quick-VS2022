#pragma once


// CUploadingDlg 대화 상자입니다.
#include "afxwin.h"
#include "textprogressctrl.h"

class CMkCommand;
class CMkDatabase;

class CUploadingDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CUploadingDlg)

public:
	CUploadingDlg(BOOL* pbRet,CWnd* pParent, CMkDatabase *pDb, CString strFileName, char *pBuffer, DWORD dwLength);   // 표준 생성자입니다.
	virtual ~CUploadingDlg();

	//socket thread
	static int staticProc(CUploadingDlg *app)
	{ return app->Proc((LPVOID)app); }

	static int staticProcIamLive(CUploadingDlg *app)
	{ return app->ProcIamLive((LPVOID)app); }

	UINT Proc(LPVOID lParam);
	UINT ProcIamLive(LPVOID lParam);
	// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_UPLOADING };

	BOOL *m_pbRet;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

private:
	CString m_strFileName;
	char *m_pBuffer;
	BOOL m_bStop;
	CMkDatabase *m_pDb;

public:
	CStatic m_InfoStatic;
	CButton m_btnCancel;
	CTextProgressCtrl m_ProgressBar;
	HANDLE m_hStopEvent;
	HANDLE m_hEndDialog;
	HANDLE m_hThreadProcEnd;
	BOOL m_bDialogShow;
	DWORD m_dwLastTickCount;
	BOOL m_bUIThreadEnd;
	DWORD m_dwLength;
};

