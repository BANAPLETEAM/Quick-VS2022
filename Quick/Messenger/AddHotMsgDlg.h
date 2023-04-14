#pragma once


class CMkDatabase;

// CAddHotMsgDlg 대화 상자입니다.

class CAddHotMsgDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CAddHotMsgDlg)

public:
	CAddHotMsgDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CAddHotMsgDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ADD_HOT_MSG_DLG };

	CMkDatabase *m_pMyDb;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
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
