#pragma once

// CSmallTalkEditDlg ��ȭ �����Դϴ�.

class CSmallTalkEditDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSmallTalkEditDlg)

public:
	CSmallTalkEditDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSmallTalkEditDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SMALL_TALK_EDIT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedInsertBtn();
	afx_msg void OnBnClickedCancelBtn();

	void MoveControl();

	CWnd* m_pParent;
	CButton m_btnInsert;
	CButton m_btnCancel;

	BOOL m_bUpdate;
	BOOL m_bHomeForm;
	CFlatEdit2 m_edtText;
	CString m_strText;
	long m_nParentID;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
