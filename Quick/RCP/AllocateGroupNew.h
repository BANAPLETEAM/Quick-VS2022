#pragma once


// CAllocateGroupNew ��ȭ �����Դϴ�.

class CAllocateGroupNew : public CMyDialog
{
	DECLARE_DYNAMIC(CAllocateGroupNew)

public:
	CAllocateGroupNew(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CAllocateGroupNew();
	BOOL bNewMode;
//	CString m_sName;
//	int m_nGNo;

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ALLOCATE_GROUP_NEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CString m_sGNo;
	CString m_sName;
	afx_msg void OnBnClickedDel();
};
