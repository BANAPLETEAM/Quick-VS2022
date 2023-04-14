#pragma once


// CRunningMultiDlg 대화 상자입니다.
#include "afxwin.h"
#include "mybutton.h"
#include "textprogressctrl.h"
class CMkCommand;
class CRunningMultiDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRunningMultiDlg)

public:
	CRunningMultiDlg(BOOL* bRet,CMkCommand *pCmd1,CMkCommand *pCmd2, CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRunningMultiDlg();

	//socket thread
	static int staticProc(CRunningMultiDlg *app)
	{ return app->Proc((LPVOID)app); }

	static int staticProc2(CRunningMultiDlg *app)
	{ return app->Proc2((LPVOID)app); }


	static int staticProcIamLive(CRunningMultiDlg *app)
	{ return app->ProcIamLive((LPVOID)app); }

	UINT Proc(LPVOID lParam);
	UINT Proc2(LPVOID lParam);
	UINT ProcIamLive(LPVOID lParam);
// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_RUNNING_MULTI };

	BOOL*		m_pbRet;
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
	CMkCommand *m_pCmd1;	
	CMkCommand *m_pCmd2;	
	BOOL		m_bStop;

public:
	CStatic m_ElapsedSec;
	CMyButton m_btnCancel;
	CTextProgressCtrl m_ProgressBar;
	HANDLE m_hStopEvent[2];
	HANDLE m_hEndDialog[2];
	HANDLE m_hThreadProcEnd[2];
	BOOL m_bDialogShow;
	DWORD m_dwLastTickCount;
	BOOL m_bUIThreadEnd;
};
