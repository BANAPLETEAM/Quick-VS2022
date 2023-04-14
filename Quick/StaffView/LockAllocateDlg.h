#pragma once


// CLockAllocateDlg 대화 상자입니다.

class CLockAllocateDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CLockAllocateDlg)

public:
	CLockAllocateDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CLockAllocateDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_LOCK_ALLOCATE_DLG };

protected: 
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	CString m_sMinute;
	CString m_sCount;
	CButton m_cmbMinute;
	CButton m_cmbCount;

	afx_msg void OnBnClickedOkBtn();
};
