#pragma once

class CMentDlg;
class CSpecialCharDlg;

// CMentAddDlg 대화 상자입니다.

class CMentAddDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CMentAddDlg)

public:
	CMentAddDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMentAddDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MENT_ADD_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
	
	BOOL m_bTitle; //포커스

	CString m_strID; //""면 인서트
	CString m_strTitle;
	CString m_strMemo;
};
