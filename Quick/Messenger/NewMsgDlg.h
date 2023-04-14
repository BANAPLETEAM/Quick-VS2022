#pragma once


// CNewMsgDlg 대화 상자입니다.

#include "DalsuRichEdit.h"
#include "MyCheckBtn.h"
#include "MyStatic.h"
#include "FlatEdit2.h"

#define WM_CLOSE_MSG_DLG	WM_USER + 682

class CQSocket;

class CNewMsgDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CNewMsgDlg)

public:
	CNewMsgDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CNewMsgDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_NEW_MSG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strMsg;
	CString m_strSend;
	
	CString m_strMNo;
	CString m_strCompanyCode;
	CString m_strIntercall;
	CString m_strCompanyName;
	CString m_strName;
	CString m_strMyName;
	int m_nSendType;

	CWnd *m_pParentWnd;
	CFont m_Font;
	CQSocket *m_pSocket;
	CMyCheckBtn m_chkShowJustPopup;
	BOOL m_bNoFocus;
	DWORD m_dwLastTyping;

	HANDLE m_hTypeingHandle;
	HANDLE m_hExitHandle;
	HANDLE m_hThreadDiedHandle;
	CFlatEdit2 m_edtSend;
	CFlatEdit2 m_edtInfo;
	CString m_strLastRecvTime;
	CMyCheckBtn m_chkNoClose;
	CDalsuRichEdit m_edtMsgRich;
	CStatic m_stcInfo;
	CStringArray m_saHotMsg;
	CStringArray m_saHotMsgTitle;
	CMkDatabase *m_pMainDb;
	CButton m_btnMenu;
	CString m_strInfo;

protected:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnOK();
	virtual void OnCancel();

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedSendMsgBtn();
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	afx_msg void OnEnChangeSendEdit(); 
	afx_msg void OnBnClickedShowJustPopupCheck();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
	afx_msg void OnMenuHotMsg(UINT nID);
	afx_msg void OnBnClickedShowJustPopupCheck2();
	afx_msg void OnBnClickedNoCloseCheck();
	afx_msg void OnMenuMsg(UINT nID);

	void MoveClient();
	void SetSocket(CQSocket *pSocket) { m_pSocket = pSocket; };
	CString GetAdminID();
	void MsgTyping();
	static int staticTypingProc(CNewMsgDlg *app)
	{ return app->TypingProc((LPVOID)app); }

	UINT TypingProc(LPVOID lParam);
	void SetLastRecvTime(CString strTime);
	void OnContextMenu();
	void SendMsg(CString strMsg, BOOL bNoShow = FALSE);
	void PrintInfo(CString strMsg);

	afx_msg void OnBnClickedMenuBtn();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
