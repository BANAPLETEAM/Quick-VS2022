#pragma once


// CRunningDlg ��ȭ �����Դϴ�.
#include "afxwin.h"
#include "mybutton.h"
#include "textprogressctrl.h"
class CMkCommand;
class CRunningDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRunningDlg)

public:
	CRunningDlg(BOOL* bRet,CMkCommand *pCmd,CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRunningDlg();

	//socket thread
	static int staticProc(CRunningDlg *app)
	{ return app->Proc((LPVOID)app); }

	static int staticProcIamLive(CRunningDlg *app)
	{ return app->ProcIamLive((LPVOID)app); }

	UINT Proc(LPVOID lParam);
	UINT ProcIamLive(LPVOID lParam);
// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_RUNNING };

	BOOL*		m_pbRet;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

private:
	CMkCommand *m_pCmd;	
	BOOL		m_bStop;

public:
	CStatic m_ElapsedSec;
	CMyButton m_btnCancel;
	CTextProgressCtrl m_ProgressBar;
	HANDLE m_hStopEvent;
	HANDLE m_hEndDialog;
	HANDLE m_hThreadProcEnd;
	BOOL m_bDialogShow;
	DWORD m_dwLastTickCount;
	BOOL m_bUIThreadEnd;
};
