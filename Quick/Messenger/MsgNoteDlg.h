#pragma once
 

typedef struct {
	long nCompany;
	long nWNo;
	CString strCompany;
	CString strName;
} MSG_MEMBER;

typedef vector<MSG_MEMBER> MSG_MEMBER_VECTOR;

// CMsgNoteDlg ��ȭ ����z�Դϴ�.

class CMsgNoteDlg : public CMyResizeDialog
{
	DECLARE_DYNAMIC(CMsgNoteDlg)

public:
	CMsgNoteDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMsgNoteDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MSG_NOTE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedSendMsgBtn();
public:
	CString m_strTarget;
	CString m_strSend;
	long m_nCompany;
	long m_nMNo;
	long m_nClientType;
	CString m_strCompanyName;
	CString m_strName;
	CWnd *m_pParent;
	CString m_strTitle;
	CString m_strDescript;
	MSG_MEMBER_VECTOR m_vecMsgMember;
	BOOL m_bInstanceMsg;

public:
	void AddMultiMember(long nCompany, long nWNo, CString strCompany, CString strName);
	int GetMultiMemberCount();
	BOOL SendMsg();

};


AFX_INLINE int CMsgNoteDlg::GetMultiMemberCount()
{
	return m_vecMsgMember.size();
}

