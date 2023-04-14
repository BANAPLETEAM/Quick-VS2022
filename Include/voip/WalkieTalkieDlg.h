#pragma once
#include "afxwin.h"

class CRecordSound;
class CPlaySound;
class CWriteSound;
class CMyCallerRecv;
class CMyCaller4Send;

// CWalkieTalkieDlg 대화 상자입니다.

class CWalkieTalkieDlg : public CDialog
{
	DECLARE_DYNAMIC(CWalkieTalkieDlg)

public:
	CWalkieTalkieDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CWalkieTalkieDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_WALKIE_TALKIE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CListBox m_ConnListBox;
	CStatic m_RecvStatus;
	CStatic m_SendStatus;
	CStatic m_Status;
	CButton m_btnRecord;
	afx_msg void OnBnClickedCheckBi();
	afx_msg void OnBnClickedCheckTalk();

	LRESULT OnRecord(WPARAM wp,LPARAM lp);
	LRESULT OnTextData(WPARAM wp,LPARAM lp);
	LRESULT OnVoiceData(WPARAM wp,LPARAM lp);

	LRESULT OnConnected(WPARAM wp,LPARAM lp);
	LRESULT OnDisConnected(WPARAM wp,LPARAM lp);
	LRESULT OnConnList(WPARAM wp,LPARAM lp);
	LRESULT OnAddConnUser(WPARAM wp,LPARAM lp);
	LRESULT OnRemConnUser(WPARAM wp,LPARAM lp);

private:

	CMyCallerRecv*	m_recv ;
	CMyCaller4Send*	m_send ;

	CRecordSound*	m_record;
	CPlaySound*		m_play;
	CWriteSound*	m_write;
	CString			m_sTalkGroupCode;
	int				m_nGroupType;

private:

	UINT	m_MyVTMsgState	;
	INT		m_nCallState	;
	BOOL	m_bWaveST		;
	BOOL	m_bCompanyWT	;
	BOOL	m_bCaller		;

private:
	
	CString m_sID;
	CString m_sName;
	int m_uShareCompany;
	int m_uCompany;
	int m_nMNo;
	
	CString  m_sAddress;
	UINT	m_uPort;

public:
	void SetServerInfo(CString sAddr,UINT uPort);
	void SetUserInfo(CString sID,CString sName,int nShareCompany,int nCompany,int nMNo );

	void SetConnList(CString sConnList);
	void AddConnUser(CString sUser);
	void RemoveConnUser(CString sUser);

	void DisplayError(CString sError);
	void MakeTalkingGroup();
};
