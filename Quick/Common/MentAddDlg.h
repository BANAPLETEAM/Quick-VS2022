#pragma once

class CMentDlg;
class CSpecialCharDlg;

// CMentAddDlg ��ȭ �����Դϴ�.

class CMentAddDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CMentAddDlg)

public:
	CMentAddDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMentAddDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MENT_ADD_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSpecialCharBtn();
	afx_msg void OnBnClickedClose();
	afx_msg void OnBnClickedMentAddBtn();
	afx_msg void OnBnClickedCloseBtn();
	afx_msg void OnEnSetfocusTitleEdt();
	afx_msg void OnEnSetfocusMemoEdt();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnEnChangeMemoEdt();

	CMentDlg * m_pParent;
	CSpecialCharDlg * m_pSpecialCharDlg;

	CFlatEdit2 m_edtTitle;
	CFlatEdit2 m_edtMemo;
	CFlatEdit2 m_edtCopy;

	CMyStatic m_stcCharCount;

	CButton m_btnClose;
	CButton m_btnClose1;
	CButton m_btnMentAdd;
	CButton m_btnSpecialChar;
	
	BOOL m_bTitle; //��Ŀ��

	CString m_strID; //""�� �μ�Ʈ
	CString m_strTitle;
	CString m_strMemo;
};
