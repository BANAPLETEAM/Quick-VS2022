#pragma once


// CLockAllocateDlg ��ȭ �����Դϴ�.

class CLockAllocateDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CLockAllocateDlg)

public:
	CLockAllocateDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CLockAllocateDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_LOCK_ALLOCATE_DLG };

protected: 
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	CString m_sMinute;
	CString m_sCount;
	CButton m_cmbMinute;
	CButton m_cmbCount;

	afx_msg void OnBnClickedOkBtn();
};
