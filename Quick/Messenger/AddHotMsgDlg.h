#pragma once


class CMkDatabase;

// CAddHotMsgDlg ��ȭ �����Դϴ�.

class CAddHotMsgDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CAddHotMsgDlg)

public:
	CAddHotMsgDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CAddHotMsgDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ADD_HOT_MSG_DLG };

	CMkDatabase *m_pMyDb;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual void OnOK();
	afx_msg void OnBnClickedOKBtn();

	DECLARE_MESSAGE_MAP()

	CString m_strKeyTitle;

public:
	CFlatEdit2 m_edtTitle;
	CFlatEdit2 m_edtMsg;
	CString m_strTitle;
	CString m_strMsg;
	virtual BOOL OnInitDialog();
};
