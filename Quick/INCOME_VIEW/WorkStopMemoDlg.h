#pragma once
#include "afxwin.h"


// CWorkStopMemoDlg ��ȭ �����Դϴ�.

class CWorkStopMemoDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CWorkStopMemoDlg)

public:
	CWorkStopMemoDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CWorkStopMemoDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_WORKSTOP_MEMO_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedWorkstopButton();

	CString m_strWorkStopMemo;
	CString m_strContent;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CComboBox m_cmbWorkStopMemo;
	CEdit m_edtContent;
	afx_msg void OnBnClickedCancelButton();
	afx_msg void OnBnClickedWorkstopButton2();
};
