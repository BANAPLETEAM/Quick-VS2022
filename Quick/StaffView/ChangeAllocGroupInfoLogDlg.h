#pragma once


// CChangeAllocGroupInfoLogDlg ��ȭ �����Դϴ�.

class CChangeAllocGroupInfoLogDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CChangeAllocGroupInfoLogDlg)

public:
	CChangeAllocGroupInfoLogDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CChangeAllocGroupInfoLogDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CHANGE_ALLOC_GROUP_INFO_LOG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	long m_nGroupAllocID;
	afx_msg void OnBnClickedRefreshBtn();
	CXTPListCtrl2 m_lst;
	void RefreshList();
	virtual BOOL OnInitDialog();
};
