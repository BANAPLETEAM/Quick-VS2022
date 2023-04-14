#pragma once


// CAllocateGroupNew 대화 상자입니다.

class CAllocateGroupNew : public CMyDialog
{
	DECLARE_DYNAMIC(CAllocateGroupNew)

public:
	CAllocateGroupNew(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CAllocateGroupNew();
	BOOL bNewMode;
//	CString m_sName;
//	int m_nGNo;

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_ALLOCATE_GROUP_NEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CString m_sGNo;
	CString m_sName;
	afx_msg void OnBnClickedDel();
};
